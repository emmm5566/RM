#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.hpp"



class VideoPublisherNode : public rclcpp::Node
{
public:
    VideoPublisherNode(std::string node_name) : Node(node_name)
    {
        RCLCPP_INFO(this->get_logger(), "%s has been started.", node_name.c_str());

        // 创建图像发布者,话题名video_frames
        img_pub_ = image_transport::create_publisher(this, "video_frames");

        // 打开视频文件
        cap_.open("/home/emmm/Desktop/scnu_rm/ROS2/task/cvtopic_ws/img/task2_video.mp4");
        if(!cap_.isOpened())
        {
            RCLCPP_INFO(this->get_logger(), "Error opening video stream or file");
            rclcpp::shutdown();
            return;
        }

        // 创建定时器
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(33),
            std::bind(&VideoPublisherNode::publish_frame, this)
        );
    } 

    // // 析构函数：关闭所有窗口（避免内存泄漏）
    // ~VideoPublisherNode()
    // {
    //     cv::destroyAllWindows();
    //     RCLCPP_INFO(this->get_logger(), "All windows have been closed.");
    // }

private:
    cv::VideoCapture cap_; // 视频捕获对象
    image_transport::Publisher img_pub_; // 图像发布者
    rclcpp::TimerBase::SharedPtr timer_; // 定时器

    // 发布视频帧回调函数
    void publish_frame()
    {
        cv::Mat frame_;
        cap_ >> frame_; // 读取第一帧视频

        if(frame_.empty())
        {
            RCLCPP_INFO(this->get_logger(), "No frames to read");
            timer_->cancel(); // 停止定时器
            return;
        }

        // cv::imshow("publisher_video_test", frame_);
        // if(cv::waitKey(100) == 27)
        // {
        //     RCLCPP_INFO(this->get_logger(), "Press ESC to exit");
        //     timer_->cancel();
        //     rclcpp::shutdown();
        //     return;
        // }

        // 将OpenCV的Mat格式转换为ROS2的sensor_msgs::msg::Image消息格式
        std_msgs::msg::Header header; // 消息头
        header.stamp = this->now(); // 时间戳
        sensor_msgs::msg::Image::SharedPtr ros2_img = cv_bridge::CvImage(header, "bgr8", frame_).toImageMsg(); // 转换
        
        // 发布ROS2图像消息
        img_pub_.publish(ros2_img);
    }

};



int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<VideoPublisherNode>("video_publisher");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}





//打印绝对路径 pwd