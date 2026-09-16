/*   
  需求：编写动态坐标变换程序，启动 turtlesim_node 以及 turtle_teleop_key 后，该程序可以发布
       乌龟坐标系到窗口坐标系的坐标变换，并且键盘控制乌龟运动时，乌龟坐标系与窗口坐标系的相对关系
       也会实时更新。

  步骤：
    1.包含头文件；
    2.初始化 ROS 客户端；
    3.定义节点类；
      3-1.创建动态坐标变换发布方；
      3-2.创建乌龟位姿订阅方；
      3-3.根据订阅到的乌龟位姿生成坐标帧并广播。
    4.调用 spin 函数，并传入对象指针；
    5.释放资源。
*/

// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "turtlesim/msg/pose.hpp"
using std::placeholders::_1;

// 3.自定义节点类;
class TFDynamicFrameBroadcaster: public rclcpp::Node {
  public:
    TFDynamicFrameBroadcaster(): Node("tf_dynamic_frame_broadcaster_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "tf_dynamic_frame_broadcaster_node_cpp");
    
        // 3-1.创建动态坐标变换发布方；
        tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
        
        // 3-2.创建乌龟位姿订阅方；
        std::string topic_name = "/turtle/pose";
        subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            topic_name, 10, std::bind(&TFDynamicFrameBroadcaster::handle_turtle_pose, this, _1));
    }

  private:
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;

    // 3-3.根据订阅到的乌龟位姿生成坐标帧并广播。   
    void handle_turtle_pose(const turtlesim::msg::Pose & msg) {
        // 组织消息
        geometry_msgs::msg::TransformStamped t;
        rclcpp::Time now = this->get_clock()->now();
        t.header.stamp = now;
        t.header.frame_id = "world";
        t.child_frame_id = "turtle";
        t.transform.translation.x = msg.x;
        t.transform.translation.y = msg.y;
        t.transform.translation.z = 0.0;
        tf2::Quaternion q;
        q.setRPY(0, 0, msg.theta);
        t.transform.rotation.x = q.x();
        t.transform.rotation.y = q.y();
        t.transform.rotation.z = q.z();
        t.transform.rotation.w = q.w();
        // 发布消息
        tf_broadcaster_->sendTransform(t);
    }
};

int main(int argc, char ** argv)
{
    // 2.初始化ROS2客户端;
    rclcpp::init(argc, argv);
    // 4.调用spin函数, 并传入节点对象指针;
    auto node = std::make_shared<TFDynamicFrameBroadcaster>();
    rclcpp::spin(node);
    // 5.释放资源. 
    rclcpp::shutdown();
    return 0;
}