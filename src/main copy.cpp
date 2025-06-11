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
#include <opencv2/core/ocl.hpp> // 用于OpenCL加速
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <camera_info_manager/camera_info_manager.h>

#include "HCNetSDK.h"
#include "LinuxPlayM4.h"

#ifndef PTP_CLOCK_GETTIME
#define PTP_CLOCK_GETTIME _IOR('P', 0x0e, struct ptp_clock_time)
#endif

// 全局变量
cv::Mat pImg_mat; // 使用Mat替代UMat
std::mutex image_mutex;
ros::Publisher combined_pub;
bool use_hardware_accel = false;
std::string ptp_device = "/dev/ptp0";

std::chrono::high_resolution_clock::time_point start_time, end_time, pub_time;
std::chrono::duration<double> elapsed_time, pub_elapsed_time;


// 获取gPTP时间
ros::Time getGPTPTime() {
    static bool ptp_available = true;
    static bool first_run = true;
    
    if (!ptp_available) {
        return ros::Time::now();
    }
    
    // 方法1: 尝试直接获取 PTP 时间
    int fd = open(ptp_device.c_str(), O_RDONLY);
    if (fd >= 0) {
        struct ptp_clock_time ptp_time;
        if (ioctl(fd, PTP_CLOCK_GETTIME, &ptp_time) == 0) {
            close(fd);
            return ros::Time(ptp_time.sec, ptp_time.nsec);
        }
        close(fd);
        ROS_WARN_THROTTLE(60, "Failed to get PTP time from %s: %s, using system time instead", 
            ptp_device.c_str(), strerror(errno));
    }
    
    // 方法2: 尝试通过系统时钟获取
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
        return ros::Time(ts.tv_sec, ts.tv_nsec);
    }
    
    // 方法3: 最后回退到 ROS 时间
    if (first_run) {
        ROS_WARN("PTP time unavailable, falling back to ROS time. Error: %s", strerror(errno));
        first_run = false;
    }
    
    ptp_available = false;
    return ros::Time::now();
}

// 优化的解码回调
void CALLBACK G_DecCBFun(int nPort, char * pBuf, int nSize, FRAME_INFO * pFrameInfo, void* nReserved1, int nReserved2) {
    if (pFrameInfo->nType == T_YV12) {
        ros::Time capture_time = getGPTPTime();
        #ifdef USE_TIMER
            start_time = std::chrono::high_resolution_clock::now();
        #endif
        
        // 直接创建Mat而不拷贝
        cv::Mat yv12_frame(pFrameInfo->nHeight + pFrameInfo->nHeight/2, pFrameInfo->nWidth, CV_8UC1, pBuf);
        
        {
            std::lock_guard<std::mutex> lock(image_mutex);
            cv::cvtColor(yv12_frame, pImg_mat, cv::COLOR_YUV2BGR_YV12);
        }

        #ifdef USE_TIMER
            end_time = std::chrono::high_resolution_clock::now();
            elapsed_time = end_time - start_time;
        #endif
        
        // 发布图像
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", pImg_mat).toImageMsg();
        msg->header.stamp = capture_time;
        msg->header.frame_id = "hikrobot_camera";
        combined_pub.publish(msg);

        #ifdef USE_TIMER
            pub_time = std::chrono::high_resolution_clock::now();
            pub_elapsed_time = pub_time - end_time;
            ROS_INFO_STREAM("CallBack cvt_time:"<<elapsed_time.count()*1000<<"ms pub_time:"<<pub_elapsed_time.count()*1000<<"ms totaltime:"<<1000*(pub_elapsed_time.count()+elapsed_time.count())<<"ms");
        #endif

    }
}

LONG G_nPort = -1;
void PsDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pPacketBuffer, DWORD nPacketSize, void* pUser) {
    switch (dwDataType) {
        case NET_DVR_SYSHEAD: //系统头
            if (!PlayM4_GetPort(&G_nPort)) { //获取播放库未使用的通道号
                break;
            }
            if (nPacketSize > 0) {
                if (!PlayM4_SetStreamOpenMode(G_nPort, STREAME_REALTIME)) { //设置实时流播放模式
                    break;
                }

                if (!PlayM4_OpenStream(G_nPort, pPacketBuffer, nPacketSize, 10 * 1024 * 1024)) { //打开流接口
                    break;
                }

                if (!PlayM4_Play(G_nPort, 0)) { //播放开始
                    break;
                }

                if (!PlayM4_SetDecCallBack(G_nPort, G_DecCBFun)) {
                    break;
                }
            }
            break;
        case NET_DVR_STREAMDATA:   //码流数据
            if (nPacketSize > 0 && G_nPort != -1) {
                if (!PlayM4_InputData(G_nPort, pPacketBuffer, nPacketSize)) {
                    break;
                }
            }
            break;
        default: //其他数据
            if (nPacketSize > 0 && G_nPort != -1) {
                if (!PlayM4_InputData(G_nPort, pPacketBuffer, nPacketSize)) {
                    break;
                }
            }
            break;
    }
}

void GetStream(const std::string& ip, int port, const std::string& username, const std::string& password, int channel) {
    NET_DVR_Init();
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    int iUserID = NET_DVR_Login_V30(const_cast<char*>(ip.c_str()), port, const_cast<char*>(username.c_str()), const_cast<char*>(password.c_str()), &struDeviceInfo);
    printf("Login result: %d\n", iUserID);

    if (iUserID >= 0) {
        NET_DVR_PREVIEWINFO struPreviewInfo = {0};
        struPreviewInfo.lChannel = channel;
        struPreviewInfo.dwStreamType = 0;
        struPreviewInfo.dwLinkMode = 0;
        struPreviewInfo.bBlocked = 1;
        struPreviewInfo.bPassbackRecord = 1;
        LONG nPort = -1;
        int iRealPlayHandle = NET_DVR_RealPlay_V40(iUserID, &struPreviewInfo, PsDataCallBack, &nPort);
        if (iRealPlayHandle >= 0) {
            printf("[GetStream]---RealPlay %s:%d success, \n", ip.c_str(), channel);
        } else {
            printf("[GetStream]---RealPlay %s:%d failed, error = %d\n", ip.c_str(), channel, NET_DVR_GetLastError());
        }
    } else {
        printf("[GetStream]---Login %s failed, error = %d\n", ip.c_str(), NET_DVR_GetLastError());
    }
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
    
    // 检查并启用硬件加速
    use_hardware_accel = cv::ocl::haveOpenCL();
    if (use_hardware_accel) {
        cv::ocl::setUseOpenCL(true);
        ROS_INFO("OpenCL acceleration enabled");
    } else {
        ROS_INFO("OpenCL acceleration not available");
    }
    
    // 初始化UMat
    pImg_mat = cv::Mat(1440, 2560, CV_8UC3);

    cv::setNumThreads(cv::getNumberOfCPUs());
    std::string ip;

    int port;
    std::string username;
    std::string password;
    int channel;
    std::string combined_topic;

    nh.getParam("ip", ip);
    nh.getParam("port", port);
    nh.getParam("username", username);
    nh.getParam("password", password);
    nh.getParam("channel", channel);
    nh.getParam("topic_name", combined_topic);

    std::thread t(GetStream, ip, port, username, password, channel);

#ifdef USE_COMPRESS
    combined_pub = nh.advertise<sensor_msgs::CompressedImage>(combined_topic, 1);
#else
    combined_pub = nh.advertise<sensor_msgs::Image>(combined_topic, 1);
#endif

    // 设置线程优先级
    // pthread_t this_thread = pthread_self();
    // struct sched_param params;
    // params.sched_priority = sched_get_priority_max(SCHED_FIFO);
    // if (pthread_setschedparam(this_thread, SCHED_FIFO, &params)) {
    //     ROS_WARN("Failed to set thread priority, running with default priority");
    // }

    ros::Rate loop_rate(30);
    while (ros::ok()) {
        loop_rate.sleep();
        ros::spinOnce();
    }


    t.join();
    NET_DVR_Cleanup();
    return 0;
}
