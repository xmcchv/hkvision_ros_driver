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

#include "HCNetSDK.h"
#include "LinuxPlayM4.h"

#ifndef PTP_CLOCK_GETTIME
#define PTP_CLOCK_GETTIME _IOR('P', 0x0e, struct ptp_clock_time)
#endif

// 全局变量
cv::Mat pImg_mat;
std::mutex image_mutex;
ros::Publisher combined_pub;
std::string ptp_device = "/dev/ptp0";

// 帧率控制变量
int target_fps = 25; // 默认25fps
std::chrono::milliseconds frame_interval(1000 / target_fps);

// std::chrono::steady_clock::time_point start_time, end_time, pub_time;  // 全局变量
// std::chrono::duration<double> elapsed_time, pub_elapsed_time;

// 获取gPTP时间
#include <sys/timex.h>
#include <linux/ptp_clock.h>

ros::Time getGPTPTime() {
    static bool ptp_initialized = false;
    static bool ptp_available = true;
    static int ptp_fd = -1;
    static bool use_sys_offset = false;

    // 第一次调用时初始化
    if (!ptp_initialized) {
        ptp_initialized = true;
        ptp_fd = open(ptp_device.c_str(), O_RDONLY);
        if (ptp_fd < 0) {
            ROS_WARN("Failed to open PTP device %s: %s", ptp_device.c_str(), strerror(errno));
            ptp_available = false;
        } else {
            // 检查设备能力
            struct ptp_clock_caps caps;
            if (ioctl(ptp_fd, PTP_CLOCK_GETCAPS, &caps) == 0) {
                ROS_INFO("PTP device capabilities: max_adj=%d, n_alarm=%d, n_ext_ts=%d, n_per_out=%d",
                        caps.max_adj, caps.n_alarm, caps.n_ext_ts, caps.n_per_out);
                
                // 根据设备能力选择最佳时间获取方法
                use_sys_offset = (caps.n_ext_ts >= 1);
            }
        }
    }

    // 如果PTP不可用，回退到系统时间
    if (!ptp_available) {
        return ros::Time::now();
    }

    // 方法1: 优先尝试PTP_SYS_OFFSET（如果设备支持）
    if (use_sys_offset) {
        struct ptp_sys_offset offset;
        memset(&offset, 0, sizeof(offset));
        offset.n_samples = 1;
        
        if (ioctl(ptp_fd, PTP_SYS_OFFSET, &offset) == 0) {
            return ros::Time(offset.ts[0].sec, offset.ts[0].nsec);
        } else {
            ROS_WARN_THROTTLE(60, "PTP_SYS_OFFSET failed: %s, trying fallback", strerror(errno));
            use_sys_offset = false; // 下次尝试其他方法
        }
    }

    // 方法2: 尝试PTP_CLOCK_GETTIME
    struct ptp_clock_time ptp_time;
    if (ioctl(ptp_fd, PTP_CLOCK_GETTIME, &ptp_time) == 0) {
        return ros::Time(ptp_time.sec, ptp_time.nsec);
    }

    // 方法3: 最后回退到系统时间
    ROS_WARN_THROTTLE(60, "All PTP methods failed: %s, using system time", strerror(errno));
    ptp_available = false; // 标记PTP为不可用
    close(ptp_fd);
    ptp_fd = -1;
    return ros::Time::now();
}

// 增强版PTP时间获取
ros::Time getAdjustedPTPTime() {
    static std::mutex ptp_mutex;
    std::lock_guard<std::mutex> lock(ptp_mutex);
    
    // 原始PTP时间获取
    ros::Time raw_time = getGPTPTime();
    
    // 添加动态补偿（校准网络延迟等）
    static ros::Duration adjustment(0); // 使用 ros::Duration
    static ros::Time last_raw_time;
    
    if (!last_raw_time.isZero()) {
        auto interval = (raw_time - last_raw_time).toNSec();
        adjustment = ros::Duration(interval * 0.1 * 1e-9); // 低通滤波，转换为秒
    }
    
    last_raw_time = raw_time;
    
    return raw_time + adjustment; // 使用 ros::Duration 进行加法
}


ros::Time current_ptp,end_time,pub_time;
double current_time, elapsed_time, pub_elapsed_time;
// 解码回调
void CALLBACK G_DecCBFun(int nPort, char * pBuf, int nSize, FRAME_INFO * pFrameInfo, void* nReserved1, int nReserved2) {
    if (pFrameInfo->nType == T_YV12) {
        static auto last_process_time = getGPTPTime().toSec();
        
        // 获取当前PTP时间
        ros::Time current_ptp = getGPTPTime();
        // 获取精确的PTP时间（微秒级同步）
        // ros::Time current_ptp = getAdjustedPTPTime();
       

        current_time = current_ptp.toSec();
        
        // 帧率控制
        if ((current_time - last_process_time) < frame_interval.count() / 1000.0) {
            return;
        }
        last_process_time = current_time;

        // 处理图像
        cv::Mat yv12_frame(pFrameInfo->nHeight + pFrameInfo->nHeight/2, pFrameInfo->nWidth, CV_8UC1, pBuf);
        
        {
            std::lock_guard<std::mutex> lock(image_mutex);
            cv::cvtColor(yv12_frame, pImg_mat, cv::COLOR_YUV2BGR_YV12);
        }
        
#ifdef USE_TIMER
        end_time = getGPTPTime();
        elapsed_time = (end_time - current_ptp).toSec();
#endif
        
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", pImg_mat).toImageMsg();
        msg->header.stamp = current_ptp;  // 使用PTP时间作为时间戳
        msg->header.frame_id = "hikrobot_camera";
        combined_pub.publish(msg);

#ifdef USE_TIMER
        pub_time = getGPTPTime();
        pub_elapsed_time = (pub_time - end_time).toSec();
        ROS_INFO_STREAM("CallBack cvt_time:" << elapsed_time * 1000 << "ms pub_time:" 
                        << pub_elapsed_time * 1000 << "ms totaltime:" 
                        << 1000 * (pub_elapsed_time + elapsed_time) << "ms");
#endif
        // last_publish_time = current_ptp;
    }
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
                if (!PlayM4_InputData(G_nPort, pPacketBuffer, nPacketSize)) break;
            }
            break;
        default:
            if (nPacketSize > 0 && G_nPort != -1) {
                if (!PlayM4_InputData(G_nPort, pPacketBuffer, nPacketSize)) break;
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

    if (iUserID >= 0) {
        NET_DVR_PREVIEWINFO struPreviewInfo = {0};
        struPreviewInfo.lChannel = channel;
        struPreviewInfo.dwStreamType = 0;
        struPreviewInfo.dwLinkMode = 0;
        struPreviewInfo.bBlocked = 1;
        
        LONG nPort = -1;
        int iRealPlayHandle = NET_DVR_RealPlay_V40(iUserID, &struPreviewInfo, PsDataCallBack, &nPort);
        
        if (iRealPlayHandle >= 0) {
            while (ros::ok()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            NET_DVR_StopRealPlay(iRealPlayHandle);
        }
        NET_DVR_Logout(iUserID);
    }
    NET_DVR_Cleanup();
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "hikrobot_camera");
    ros::NodeHandle nh("~");
    
    // 从参数服务器获取PTP设备路径
    nh.param<std::string>("ptp_device", ptp_device, "/dev/ptp0");
    
    // 检查PTP设备是否存在
    if (access(ptp_device.c_str(), F_OK) == -1) {
        ROS_WARN("PTP device %s not found. Time synchronization will use system time.", ptp_device.c_str());
    } else {
        ROS_INFO("Using PTP device: %s", ptp_device.c_str());
    }

    // 获取参数
    std::string ip;
    int port;
    std::string username;
    std::string password;
    int channel;
    std::string combined_topic;
    
    nh.param<std::string>("ip", ip, "");
    nh.param<int>("port", port, 8000);
    nh.param<std::string>("username", username, "admin");
    nh.param<std::string>("password", password, "12345");
    nh.param<int>("channel", channel, 1);
    nh.param<std::string>("topic_name", combined_topic, "hikrobot/image");
    
    // 设置帧率 (默认25fps)
    nh.param<int>("target_fps", target_fps, 25);
    nh.param<int>("target_fps", target_fps, 25);
    frame_interval = std::chrono::milliseconds(1000 / target_fps);
    ROS_INFO("Target FPS set to %d", target_fps);
    
    // 初始化图像矩阵
    pImg_mat = cv::Mat(1440, 2560, CV_8UC3);
    combined_pub = nh.advertise<sensor_msgs::Image>(combined_topic, 1);
    
    // 启动视频流线程
    std::thread t(GetStream, ip, port, username, password, channel);
    
    ros::spin();
    
    t.join();
    return 0;
}