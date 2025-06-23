#include <stdio.h>
#include <sys/time.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <errno.h>
#include <condition_variable>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/ptp_clock.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/PointCloud2.h>

#include "HCNetSDK.h"
#include "LinuxPlayM4.h"

// 图像缓存结构
struct TimestampedImage {
    cv::Mat image;
    ros::Time timestamp;
    bool valid = false;
};

// 全局变量
std::mutex image_mutex;
ros::Publisher image_pub;
int target_fps = 25; // 默认帧率
ros::Duration frame_interval; // 帧间隔
std::chrono::steady_clock::time_point last_callback_time;
int frame_count = 0;
ros::Time last_reference_time;

// 时间戳对齐管理器
class TimestampAligner {
public:
    TimestampAligner() : ref_stamp_valid(false), max_time_diff(0.1) {}
    
    void setMaxTimeDiff(double diff) {
        max_time_diff = diff;
    }
    
    void updateReference(const std_msgs::Header& header) {
        std::lock_guard<std::mutex> lock(ref_mutex);
        ref_stamp = header.stamp;
        last_ref_update = ros::Time::now();
        ref_stamp_valid = true;
        last_reference_time = ref_stamp;
        ROS_DEBUG("Updated reference stamp: %f", ref_stamp.toSec());
    }
    
    ros::Time alignTimestamp(const ros::Time& img_stamp) {
        std::lock_guard<std::mutex> lock(ref_mutex);
        // 如果没有有效参考或参考时间太旧，使用原始时间戳
        if (!ref_stamp_valid || (ros::Time::now() - last_ref_update).toSec() > max_time_diff) {
            ROS_WARN_THROTTLE(5.0, "No valid reference timestamp, using original image time");
            return img_stamp;
        }
        
        // 计算时间差并检查是否在允许范围内
        double time_diff = (img_stamp - ref_stamp).toSec();
        if (fabs(time_diff) > max_time_diff) {
            ROS_WARN_THROTTLE(1.0, "Large time difference: %.3fs (img:%.3f ref:%.3f). Using reference time.", 
                             time_diff, img_stamp.toSec(), ref_stamp.toSec());
            return ref_stamp;
        }
        
        // 在允许范围内，使用参考时间戳
        return ref_stamp;
    }

private:
    ros::Time ref_stamp;
    ros::Time last_ref_update;
    bool ref_stamp_valid;
    double max_time_diff;
    std::mutex ref_mutex;
};

// 图像缓存管理器
class ImageCache {
public:
    void update(const cv::Mat& img, const ros::Time& stamp) {
        std::lock_guard<std::mutex> lock(mutex_);
        latest_image_ = img.clone();
        latest_stamp_ = stamp;
        valid_ = true;
    }

    bool getLatest(cv::Mat& img, ros::Time& stamp) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!valid_) return false;
        img = latest_image_.clone();
        stamp = latest_stamp_;
        return true;
    }

private:
    cv::Mat latest_image_;
    ros::Time latest_stamp_;
    bool valid_ = false;
    std::mutex mutex_;
};

// 全局变量
ImageCache image_cache;
TimestampAligner timestamp_aligner;  // 全局时间戳对齐器


// 时间戳序列生成器
class TimestampSequenceGenerator {
public:
    TimestampSequenceGenerator() : active(false), frame_count(0) {}
    
    void startSequence(const ros::Time& ref_stamp, const ros::Time& recv_time, double target_interval) {
        std::lock_guard<std::mutex> lock(mutex);
        sequence_start = ref_stamp;
        last_recv_time = recv_time;
        expected_interval = ros::Duration(target_interval);
        frame_count = 0;
        active = true;
        
        // 计算实际与理论帧间隔的偏差
        if (last_ref_stamp.isValid()) {
            ros::Duration actual_interval = recv_time - last_ref_recv_time;
            interval_error = actual_interval - ros::Duration(target_interval * frame_count);
        }
        last_ref_stamp = ref_stamp;
        last_ref_recv_time = recv_time;
    }
    
    ros::Time getNextTimestamp() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!active) return ros::Time(0);
        
        // 生成当前帧的时间戳: 参考时间起点 + (帧数 * 帧间隔) + 偏差补偿
        ros::Time stamp = sequence_start + 
                          ros::Duration(frame_count * expected_interval.toSec()) + 
                          interval_error * (frame_count / (frame_count + 1.0));
        
        frame_count++;
        return stamp;
    }
    
    bool isActive() const { return active; }
    void deactivate() { active = false; }

private:
    ros::Time sequence_start;
    ros::Time last_recv_time;
    ros::Time last_ref_stamp;
    ros::Time last_ref_recv_time;
    ros::Duration expected_interval;
    ros::Duration interval_error;
    int frame_count;
    bool active;
    std::mutex mutex;
};

// 全局时间戳生成器
TimestampSequenceGenerator timestamp_generator;

// 参考时间戳处理
void handleReferenceStamp(const ros::Time& ref_stamp) {
    ros::Time now = ros::Time::now();
    timestamp_generator.startSequence(ref_stamp, now, 1.0/target_fps);
    last_reference_time = ref_stamp;
}

// 参考话题回调函数
void referenceCallback(const std_msgs::Header::ConstPtr& msg) {
    handleReferenceStamp(msg->stamp);
}

// 解码回调
void CALLBACK G_DecCBFun(int nPort, char * pBuf, int nSize, FRAME_INFO * pFrameInfo, void* nReserved1, int nReserved2) {
    if (pFrameInfo->nType == T_YV12) {
        auto now = std::chrono::steady_clock::now();
        ros::Time current_time = ros::Time::now();
        
        // 计算实际帧率
        static double actual_fps = target_fps;
        if (frame_count > 0) {
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_callback_time).count();
            if (duration > 0) {
                actual_fps = 1000.0 / duration;
            }
        }
        
        // 计算需要补偿的延时
        ros::Duration compensation(0);
        if (actual_fps > 0 && target_fps > 0) {
            double target_interval = 1.0 / target_fps;
            double actual_interval = 1.0 / actual_fps;
            
            // 计算时间偏差
            if (actual_interval < target_interval) {
                compensation = ros::Duration(target_interval - actual_interval);
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(compensation.toSec() * 1000)));
                current_time = ros::Time::now();
            }
        }
        
        // 更新帧计数和时间
        last_callback_time = now;
        frame_count++;
        
        cv::Mat yv12_frame(pFrameInfo->nHeight + pFrameInfo->nHeight/2, pFrameInfo->nWidth, CV_8UC1, pBuf);
        cv::Mat bgr_frame;
        cv::cvtColor(yv12_frame, bgr_frame, cv::COLOR_YUV2BGR_YV12);

        ros::Time image_stamp;
        if (timestamp_generator.isActive()) {
            image_stamp = timestamp_generator.getNextTimestamp();
        } else {
            image_stamp = ros::Time::now();
            ROS_WARN_THROTTLE(1.0, "No active reference sequence, using system time");
        }
        
        image_cache.update(bgr_frame, image_stamp);
    }
}

// 参考话题回调函数
// void referenceCallback(const std_msgs::Header::ConstPtr& msg) {
//     timestamp_aligner.updateReference(*msg);
// }

void referenceCallback(const sensor_msgs::Image::ConstPtr& msg) {
    referenceCallback(msg->header);
}

void referenceCallback(const sensor_msgs::PointCloud2::ConstPtr& msg) {
    referenceCallback(msg->header);
}

LONG G_nPort = -1;
void PsDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pPacketBuffer, DWORD nPacketSize, void* pUser) {
    switch (dwDataType) {
        case NET_DVR_SYSHEAD:
            if (!PlayM4_GetPort(&G_nPort)) break;
            if (nPacketSize > 0) {
                if (!PlayM4_SetStreamOpenMode(G_nPort, STREAME_REALTIME)) break;
                if (!PlayM4_OpenStream(G_nPort, pPacketBuffer, nPacketSize, 10 * 1024 * 1024)) break;
                if (!PlayM4_Play(G_nPort, 0)) break;
                if (!PlayM4_SetDecCallBack(G_nPort, G_DecCBFun)) break;
            }
            break;
        case NET_DVR_STREAMDATA:
            if (nPacketSize > 0 && G_nPort != -1) {
                PlayM4_InputData(G_nPort, pPacketBuffer, nPacketSize);
            }
            break;
        default:
            if (nPacketSize > 0 && G_nPort != -1) {
                PlayM4_InputData(G_nPort, pPacketBuffer, nPacketSize);
            }
            break;
    }
}

void GetStream(const std::string& ip, int port, const std::string& username, 
              const std::string& password, int channel) {
    NET_DVR_Init();
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    int iUserID = NET_DVR_Login_V30(const_cast<char*>(ip.c_str()), port, 
                                  const_cast<char*>(username.c_str()), 
                                  const_cast<char*>(password.c_str()), 
                                  &struDeviceInfo);

    if (iUserID < 0) {
        ROS_ERROR("Login failed for %s: error %d", ip.c_str(), NET_DVR_GetLastError());
        NET_DVR_Cleanup();
        return;
    }

    NET_DVR_PREVIEWINFO struPreviewInfo = {0};
    struPreviewInfo.lChannel = channel;
    struPreviewInfo.dwStreamType = 0;
    struPreviewInfo.dwLinkMode = 0;
    struPreviewInfo.bBlocked = 1;
    
    LONG nPort = -1;
    int iRealPlayHandle = NET_DVR_RealPlay_V40(iUserID, &struPreviewInfo, PsDataCallBack, &nPort);
    
    if (iRealPlayHandle < 0) {
        ROS_ERROR("RealPlay failed: error %d", NET_DVR_GetLastError());
        NET_DVR_Logout(iUserID);
        NET_DVR_Cleanup();
        return;
    }

    ROS_INFO("Stream started successfully");
    while (ros::ok()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    NET_DVR_StopRealPlay(iRealPlayHandle);
    NET_DVR_Logout(iUserID);
    NET_DVR_Cleanup();
}

void publishThreadFunc() {
    ros::Rate rate(target_fps);
    
    while (ros::ok()) {
        cv::Mat current_image;
        ros::Time image_stamp;
        if (timestamp_generator.isActive()) {
            ros::Time now = ros::Time::now();
            if ((now - last_reference_time).toSec() > 1.5 * (1.0/target_fps)) {
                timestamp_generator.deactivate();
                ROS_WARN("Reference timestamp expired. Deactivating sequence.");
            }
        }
        if (image_cache.getLatest(current_image, image_stamp)) {
            sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", current_image).toImageMsg();
            msg->header.stamp = image_stamp;
            msg->header.frame_id = "hikrobot_camera";
            image_pub.publish(msg);
            
            ROS_DEBUG_THROTTLE(1.0, "Published image at time: %.6f", image_stamp.toSec());
        }
        
        rate.sleep();
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "hikrobot_camera");
    ros::NodeHandle nh("~");
    
    // 从参数服务器获取配置
    nh.param<int>("target_fps", target_fps, 25);
    frame_interval = ros::Duration(1.0 / target_fps);
    
    // 获取相机参数
    std::string ip, username, password, image_topic, reference_topic, reference_topic_type;
    double max_time_diff;
    int port, channel;
    nh.param<std::string>("ip", ip, "");
    nh.param<int>("port", port, 8000);
    nh.param<std::string>("username", username, "admin");
    nh.param<std::string>("password", password, "12345");
    nh.param<int>("channel", channel, 1);
    nh.param<std::string>("topic_name", image_topic, "hikrobot/image");
    nh.param<std::string>("reference_topic", reference_topic, "");  // 参考话题名称
    nh.param<std::string>("reference_topic_type", reference_topic_type, "sensor_msgs/PointCloud2");  // 参考话题名称
    nh.param<double>("max_time_diff", max_time_diff, 0.1);  // 最大允许时间差
    
    // 设置最大时间差
    timestamp_aligner.setMaxTimeDiff(max_time_diff);
    
    ROS_INFO("Starting camera driver with FPS: %d", target_fps);
    image_pub = nh.advertise<sensor_msgs::Image>(image_topic, 1);
    
    // 如果配置了参考话题，则订阅它
    ros::Subscriber ref_sub;
    if (!reference_topic.empty()) {
        if(reference_topic_type == "sensor_msgs/PointCloud2"){
            ref_sub = nh.subscribe<sensor_msgs::PointCloud2>(reference_topic, 10, referenceCallback);
        }else if(reference_topic_type == "sensor_msgs/Image"){
            ref_sub = nh.subscribe<sensor_msgs::Image>(reference_topic, 10, referenceCallback);
        }else{
            ref_sub = nh.subscribe<std_msgs::Header>(reference_topic, 10, referenceCallback);
        }
        
        ROS_INFO("Subscribed to reference topic: %s", reference_topic.c_str());
    } else {
        ROS_WARN("No reference topic specified. Timestamps will not be aligned.");
    }
    
    // 初始化时间点
    last_callback_time = std::chrono::steady_clock::now();
    
    // 启动视频流线程
    std::thread stream_thread(GetStream, ip, port, username, password, channel);
    
    // 启动发布线程
    std::thread publish_thread(publishThreadFunc);
    
    ros::spin();
    
    publish_thread.join();
    stream_thread.join();
    return 0;
}