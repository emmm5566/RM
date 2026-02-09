#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp" //提供消息接口
#include "tf2/LinearMath/Quaternion.h" //提供tf2::Quaternion类
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp" //消息类型转换函数
#include "tf2_ros/static_transform_broadcaster.h" //静态坐标广播类

class StaticTFBroadcaster : public rclcpp::Node 
{
private:
    //声明静态TF广播器指针
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> broadcaster_;

public:
    //构造函数
    StaticTFBroadcaster() : Node("static_tf_broadcaster") {
        //初始化静态TF广播器
        //this当前节点指针，传this进入StaticTransformBroadcaster中创建发布者，调用静态发布时发布者把坐标关系发布出去
        this->broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
        //发布静态TF
        this->publish_tf();
    }
    
    //静态TF只需发布一次，ROS2会持续广播
    void publish_tf() {
        geometry_msgs::msg::TransformStamped transform;
        transform.header.stamp = this->get_clock()->now(); //时间戳
        transform.header.frame_id = "map"; //父坐标系
        transform.child_frame_id = "target_point"; //子坐标系
        transform.transform.translation.x = 5.0; //平移量
        transform.transform.translation.y = 3.0;
        transform.transform.translation.z = 0.0;
        tf2::Quaternion q; //定义四元数类
        q.setRPY(0.0, 0.0, 60*M_PI/180.0); //RPY(欧拉角,弧度制)转换成四元数
        transform.transform.rotation = tf2::toMsg(q); //转成消息接口类型
        //发布静态TF
        this->broadcaster_->sendTransform(transform); 
    }
};

int main(int argc, char** argv) 
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<StaticTFBroadcaster>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}



// # 创建功能包
// ros2 pkg create demo_cpp_tf --build-type ament_cmake --dependencies rclcpp tf2_ros geometry_msgs tf2_geometry_msgs --license Apache-2.0

// 原理：发布 /tf_static 话题
// ros2 ropic list
// ros2 topic echo /tf_static





// #include <tf2/utils.h>
// #include <tf2_ros/transform_broadcaster.h>
// //声明&初始化发布者
// std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
// tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(this);
// //发布
// geometry_msgs::msg::TransformStamped transform;
// transform.header.stamp = this->now();
// transform.header.frame_id = "odom";
// transform.child_frame_id = "base_link";
// // Fill in transform.transform.translation
// transform.transform.translation.x = 0.0;
// transform.transform.translation.y = 0.0;
// transform.transform.translation.z =0.0;
// // Fill in transform.transform.rotation
// auto quat = tf2::Quaternion();
// quat.setRPY(0.0;, 0.0, 0.0);
// transform.transform.rotation.x = 0.0;
// transform.transform.rotation.y = 0.0;
// transform.transform.rotation.z = 0.0;
// transform.transform.rotation.w = 0.0;
// tf_broadcaster_->sendTransform(transform);

