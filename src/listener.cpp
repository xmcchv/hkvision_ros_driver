#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

int imageCallbackcount = 0;

class ImageListener {
public:
    ImageListener() {
        // 订阅图像话题
        image_sub_ = nh_.subscribe("/hikcam_left", 1, &ImageListener::imageCallback, this);
    }

    void imageCallback(const sensor_msgs::ImageConstPtr& img_msg) {
        try {
            // 将 ROS 图像消息转换为 OpenCV 图像
            // cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(img_msg, sensor_msgs::image_encodings::BGR8);
            cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(img_msg, sensor_msgs::image_encodings::BGR8);
            // ros::param::get("imagecount",imageCallbackcount);
            ROS_INFO_STREAM("imageCallbackcount:"<<imageCallbackcount<<" time:"<<ros::Time::now());
            imageCallbackcount++;
            // cv::imshow("Received Image", cv_ptr->image);
            // cv::waitKey(1); // 显示图像，等待30毫秒
        } catch (cv_bridge::Exception& e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
        }
    }

private:
    ros::NodeHandle nh_;
    ros::Subscriber image_sub_;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "image_listener");
    ImageListener listener;
    ros::spin(); // 进入事件循环
    return 0;
}
