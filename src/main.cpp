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

#ifndef PTP_CLOCK_GETTIME
#define PTP_CLOCK_GETTIME _IOR('P', 0x0e, struct ptp_clock_time)
#endif

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
std::string ptp_device = "/dev/ptp0";

// 时间同步器类
class PTPSynchronizer {
public:
    PTPSynchronizer() {
        ptp_fd = open(ptp_device.c_str(), O_RDONLY);
        if (ptp_fd < 0) {
            ROS_WARN("Failed to open PTP device %s: %s", ptp_device.c_str(), strerror(errno));
            ptp_available = false;
        } else {
            ptp_available = true;
            last_sync_time = ros::Time::now();
            offset = ros::Duration(0);
        }
    }
    
    ~PTPSynchronizer() {
        if (ptp_fd >= 0) close(ptp_fd);
    }
    
    ros::Time getSynchronizedTime() {
        if (!ptp_available) return ros::Time::now();
        
        std::lock_guard<std::mutex> lock(ptp_mutex);
        ros::Time now = ros::Time::now();
        
        if ((now - last_sync_time).toSec() > 0.1) {
            struct ptp_clock_time ptp_time;
            if (ioctl(ptp_fd, PTP_CLOCK_GETTIME, &ptp_time) == 0) {
                ros::Time ptp_now(ptp_time.sec, ptp_time.nsec);
                offset = ptp_now - now;
                last_sync_time = now;
                #ifdef USE_LOG
                ROS_DEBUG("PTP offset updated: %.9f sec", offset.toSec());
                #endif
            }
        }
        
        return now + offset;
    }

private:
    int ptp_fd = -1;
    bool ptp_available = false;
    ros::Time last_sync_time;
    ros::Duration offset;
    std::mutex ptp_mutex;
};

class TimestampAligner {
public:
    TimestampAligner() : ref_stamp_valid(false), 
                        max_time_diff(0.1),
                        window_size(10),  
                        filtered_diff(0) {}
    
    void setMaxTimeDiff(double diff) {
        max_time_diff = diff;
    }
    
    void updateReference(const std_msgs::Header& header) {
        std::lock_guard<std::mutex> lock(ref_mutex);
        ref_stamp = header.stamp;
        last_ref_update = ros::Time::now();
        ref_stamp_valid = true;
        #ifdef USE_LOG
        ROS_DEBUG("Updated reference stamp: %f", ref_stamp.toSec());
        #endif
    }
    
    ros::Time alignTimestamp(const ros::Time& img_stamp) {
        std::lock_guard<std::mutex> lock(ref_mutex);
        
        if (!ref_stamp_valid || (ros::Time::now() - last_ref_update).toSec() > max_time_diff) {
            #ifdef USE_LOG
            ROS_WARN_THROTTLE(5.0, "No valid reference timestamp, using original image time");
            #endif
            return img_stamp;
        }
        
        double time_diff = (img_stamp - ref_stamp).toSec();
        if (fabs(time_diff) > max_time_diff) {
            #ifdef USE_LOG
            ROS_WARN_THROTTLE(1.0, "Large time difference: %.3fs (img:%.3f ref:%.3f). Using reference time.", 
                             time_diff, img_stamp.toSec(), ref_stamp.toSec());
            #endif
            return ref_stamp;
        }
        
        return ref_stamp;
    }

private:
    ros::Time ref_stamp;
    ros::Time last_ref_update;
    bool ref_stamp_valid;
    double max_time_diff;
    std::mutex ref_mutex;
    // 滑动窗口容器
    std::deque<double> time_diff_window;
    double filtered_diff = 0;
    int window_size = 10;
};

// 图像缓存管理器
class ImageCache {
public:
    void update(cv::Mat&& img, const ros::Time& stamp) {  // 使用右值引用
        std::lock_guard<std::mutex> lock(mutex_);
        latest_image_ = std::move(img);  // 移动而非拷贝
        latest_stamp_ = stamp;
        valid_ = true;
    }

    bool getLatest(cv::Mat& img, ros::Time& stamp) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!valid_) return false;
        img = std::move(latest_image_);  // 移动而非拷贝
        stamp = latest_stamp_;
        valid_ = false;  // 标记为已取走
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

// 解码回调 - 修改后只负责拷贝数据
void CALLBACK G_DecCBFun(int nPort, char * pBuf, int nSize, FRAME_INFO * pFrameInfo, void* nReserved1, int nReserved2) {
    if (pFrameInfo->nType == T_YV12) {
        static PTPSynchronizer ptp_sync;
        ros::Time current_ptp = ptp_sync.getSynchronizedTime();

        cv::Mat yv12_frame(pFrameInfo->nHeight + pFrameInfo->nHeight/2, 
                          pFrameInfo->nWidth, 
                          CV_8UC1, 
                          pBuf);

        image_cache.update(std::move(yv12_frame), current_ptp);
    }
}

// 参考话题回调函数
void referenceCallback(const std_msgs::Header::ConstPtr& msg) {
    timestamp_aligner.updateReference(*msg);
}

void referenceCallback(const sensor_msgs::Image::ConstPtr& msg) {
    timestamp_aligner.updateReference(msg->header);
}

void referenceCallback(const sensor_msgs::PointCloud2::ConstPtr& msg) {
    timestamp_aligner.updateReference(msg->header);
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

int main(int argc, char **argv) {
    ros::init(argc, argv, "hikrobot_camera");
    ros::NodeHandle nh("~");
    
    // 从参数服务器获取配置
    nh.param<std::string>("ptp_device", ptp_device, "/dev/ptp0");
    nh.param<int>("target_fps", target_fps, 25);
    
    // 检查PTP设备
    if (access(ptp_device.c_str(), F_OK) == -1) {
        ROS_WARN("PTP device %s not found. Using system time.", ptp_device.c_str());
    } else {
        ROS_INFO("Using PTP device: %s", ptp_device.c_str());
    }

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
    
    // 启动视频流线程
    std::thread stream_thread(GetStream, ip, port, username, password, channel);
    
    // 启动发布循环
    ros::Rate rate(target_fps);
    cv::Mat current_image;
    ros::Time image_stamp;
    ros::Time aligned_stamp;
    while (ros::ok()) {
        cv::Mat yv12_image;
        if (image_cache.getLatest(yv12_image, image_stamp)) {
            cv::Mat bgr_frame;
            cv::cvtColor(yv12_image, bgr_frame, cv::COLOR_YUV2BGR_YV12);
            
            // 对齐时间戳
            aligned_stamp = timestamp_aligner.alignTimestamp(image_stamp);
            
            sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", bgr_frame).toImageMsg();
            msg->header.stamp = aligned_stamp;  // 使用对齐后的时间戳
            msg->header.frame_id = "hikrobot_camera";
            image_pub.publish(msg);
            #ifdef USE_LOG
            ROS_DEBUG_THROTTLE(1.0, "Published image. Original: %.3f, Aligned: %.3f", 
                              image_stamp.toSec(), aligned_stamp.toSec());
            #endif
        }
        rate.sleep();
    }
}
