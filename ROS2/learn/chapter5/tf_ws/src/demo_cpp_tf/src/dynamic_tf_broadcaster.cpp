#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp" //提供消息接口
#include "tf2/LinearMath/Quaternion.h" //提供tf2::Quaternion类
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp" //消息类型转换函数
#include "tf2_ros/transform_broadcaster.h" //坐标广播类
#include <chrono> //时间
using namespace std::chrono_literals; 

class TFBroadcaster : public rclcpp::Node 
{
private:
    //声明TF广播器指针
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    //声明定时器
    rclcpp::TimerBase::SharedPtr timer_;

public:
    //构造函数
    TFBroadcaster() : Node("tf_broadcaster") {
        //创建TF广播器
        this->tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
        //创建定时器，不断发布/tf话题
        timer_ = this->create_wall_timer(100ms, std::bind(&TFBroadcaster::publish_tf, this));
    }
    
    void publish_tf() {
        geometry_msgs::msg::TransformStamped transform;
        transform.header.stamp = this->get_clock()->now(); //时间戳
        transform.header.frame_id = "map"; //父坐标系
        transform.child_frame_id = "base_link"; //子坐标系
        transform.transform.translation.x = 2.0; //平移量
        transform.transform.translation.y = 3.0;
        transform.transform.translation.z = 0.0;
        tf2::Quaternion q; //定义四元数类
        q.setRPY(0.0, 0.0, 30*M_PI/180.0); //RPY(欧拉角,弧度制)转换成四元数
        transform.transform.rotation = tf2::toMsg(q); //转成消息接口类型
        //发布TF
        this->tf_broadcaster_->sendTransform(transform); 
    }
};

int main(int argc, char** argv) 
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TFBroadcaster>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}



// 原理：不断发布 /tf 话题