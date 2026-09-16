#include "rclcpp/rclcpp.hpp"
#include "image_transport/image_transport.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"


class VideoSubscriberNode : public rclcpp::Node
{
public:
    VideoSubscriberNode(std::string node_name) : Node(node_name)
    {
        RCLCPP_INFO(this->get_logger(), "%s has been started.", node_name.c_str());

        // 创建图像订阅者,话题名video_frame
        // 传输模式：raw=原始图像
        img_sub_ = image_transport::create_subscription(this, "video_frames",
            std::bind(&VideoSubscriberNode::img_callback, this, std::placeholders::_1), "raw");
    }

    // 析构函数：关闭所有窗口 
    ~VideoSubscriberNode()
    {
        cv::destroyAllWindows();
        RCLCPP_INFO(this->get_logger(), "All windows have been closed.");
    }

private:
    image_transport::Subscriber img_sub_; // 图像订阅者

    //处理视频图像回调函数
    // 接收的是img_pub_.publish(ros2_img);的传参
    void img_callback(const sensor_msgs::msg::Image::ConstSharedPtr & ros2_img)
    {
        try
        {
            // 将ROS2图像消息转为OpenCV的cv::Mat（BGR8格式）
            // image 是 cv_bridge::CvImage 结构体的成员变量，专门用来存储转换后的像素数据（cv::Mat 类型）
            cv::Mat frame = cv_bridge::toCvShare(ros2_img, "bgr8")->image;


            //图像处理

            //预处理
            cv::Mat channels[3], binary, Gaussian;
            cv::split(frame, channels);
            int Threshold = 200; // 阈值
            cv::threshold(channels[2], binary, Threshold, 255, 0);
            cv::GaussianBlur(binary, Gaussian, cv::Size(5,5), 0);

            //识别小灯条
            std::vector< std::vector <cv::Point> > contours;
            std::vector< cv::Vec4i > hierarchy;
            cv::findContours(Gaussian, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
            std::vector< cv::RotatedRect > lightBars;
            for(auto & contour : contours)
            {
                double area = cv::contourArea(contour);
                if(area < 50.0) continue;
                cv::RotatedRect minRect = cv::minAreaRect(contour);
                float width = minRect.size.width;
                float height = minRect.size.height;
                if(width == 0 || height == 0) continue;
                float aspectRatio = std::max(width, height) / std::min(width, height);
                if(aspectRatio >= 1.3 && std::max(height, width)>36)
                {
                    lightBars.push_back(minRect);
                }
            }
            for(auto & lightBar : lightBars)
            {
                cv::Point2f vertices[4];
                lightBar.points(vertices);
                for(int i=0; i<4; i++)
                {
                    cv::line(frame, vertices[i], vertices[(i+1)%4], cv::Scalar(0,255,0), 3);
                }
            }

            //识别装甲板
            if(lightBars.size() < 2) return;
            //所有顶点
            std::vector<cv::Point2f> allVertices;
            cv::Point2f pts[4];
            lightBars[0].points(pts);
            for (int i = 0; i < 4; i++) allVertices.push_back(pts[i]);
            lightBars[1].points(pts);
            for (int i = 0; i < 4; i++) allVertices.push_back(pts[i]);
            //x、y坐标 
            float minX = allVertices[0].x, maxX = allVertices[0].x;
            float minY = allVertices[0].y, maxY = allVertices[0].y;
            for(auto & allVertice : allVertices)
            {
                minX = std::min(minX, allVertice.x);
                maxX = std::max(maxX, allVertice.x);
                minY = std::min(minY, allVertice.y);
                maxY = std::max(maxY, allVertice.y);
            }
            std::vector< cv::Point2f > armorPoints; 
            armorPoints.push_back(cv::Point2f(minX, minY));
            armorPoints.push_back(cv::Point2f(maxX, minY));
            armorPoints.push_back(cv::Point2f(maxX, maxY));
            armorPoints.push_back(cv::Point2f(minX, maxY)); 
            //绘制装甲板
            //cv::RotatedRect rect = cv::minAreaRect(armorPoints);
            for(int i=0; i<4; i++)
            {
                line(frame, armorPoints[i], armorPoints[(i+1)%4], cv::Scalar(0,0,255), 2);
            }  


            //窗口显示
            cv::imshow("Frame", frame);
            cv::imshow("Gaussian", Gaussian);
            if(cv::waitKey(100) == 27)
            {
                rclcpp::shutdown();
                RCLCPP_INFO(this->get_logger(), "Press ESC to exit");
            }
        }
        catch(cv_bridge::Exception &e)
        {
            // 异常处理
            RCLCPP_ERROR(this->get_logger(), "Image conversion failed: %s", e.what());
        }
    }

};



int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<VideoSubscriberNode>("video_subscriber");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}