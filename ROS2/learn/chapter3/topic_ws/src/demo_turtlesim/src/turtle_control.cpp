/*************************订阅话题*******************************/
/* 控制小海龟 —— 发布话题
   监视小海龟位置 —— 订阅话题
   根据当前位置和目标位置计算角速度和线速度 —— 两点之间距离->线速度，当前朝向和目标朝向差->角速度 */

// ros2 interface show turtlesim/msg/Pose 查看消息接口定义
// float32 x
// float32 y
// float32 theta
// float32 linear_velocity
// float32 angular_velocity



#include "rclcpp/rclcpp.hpp" 
#include "geometry_msgs/msg/twist.hpp"
#include <string>
#include <chrono> 
#include "turtlesim/msg/pose.hpp" // /turtle1/pose

using namespace std::chrono_literals; 



class TurtleControlNode : public rclcpp::Node
{
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;  //发布者的智能共享指针
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_; //订阅者的智能共享指针
    double target_x_{1.0}; //目标x坐标
    double target_y_{1.0}; //目标y坐标
    double k_{1.0}; //比例系数
    double max_speed_{2.0}; //最大速度

public:
    explicit TurtleControlNode(const std::string & node_name) : Node(node_name)
    {
        //创建发布者
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        //创建订阅者，绑定回调函数
        //std::placeholders::_1 占位符，回调函数有1个参数
        subscriber_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, 
            std::bind(&TurtleControlNode::pose_callback, this, std::placeholders::_1));

    }

    //成员函数：订阅者回调函数
    //参数：接收到的消息智能指针，指针类型为turtlesim::msg::Pose的共享指针
    void pose_callback(const turtlesim::msg::Pose::SharedPtr pose)
    {
        //获取当前位置
        double current_x = pose->x;
        double current_y = pose->y;
        RCLCPP_INFO(this->get_logger(), "Current Position: x=%.2f, y=%.2f", current_x, current_y);

        //计算当前位置跟目标位置之间的距离差和角度差
        // auto distance = std::sqrt(
        //     (target_x_ - current_x) * (target_x_ - current_x) +
        //     (target_y_ - current_y) * (target_y_ - current_y)
        // );
        auto distance = std::sqrt(std::pow(target_x_ - current_x, 2) + std::pow(target_y_ - current_y, 2)); //距离差
        auto angle = std::atan2(target_y_ - current_y, target_x_ - current_x) - pose->theta; //角度差

        //控制策略
        auto msg = geometry_msgs::msg::Twist(); //创建并配置消息
        if(distance > 0.1) //距离差大于0.1时才移动
        {
            if(fabs(angle) > 0.2) //角度差大于0.2时优先调整角度（角速度）
            {
                msg.angular.z = fabs(angle); 
            }
            else //角度差小于0.2时调整距离（线速度）
            {
                msg.linear.x = k_ * distance;
            }
        }

        //限制最大速度
        if(msg.linear.x > max_speed_)
        {
            msg.linear.x = max_speed_;
        }

        //发布消息
        publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Published: linear.x=%.2f, angular.z=%.2f", msg.linear.x, msg.angular.z);
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); //初始化ROS2客户端库
    auto node = std::make_shared<TurtleControlNode>("turtle_control_node"); //创建节点对象
    rclcpp::spin(node); //进入循环，等待回调函数被触发
    rclcpp::shutdown(); //关闭ROS2客户端库

    return 0;
}





//ctrl + f 打开查找
//ctrl + h 打开替换
//ctrl + / 注释


//变量初始化：
// 1. 等号初始化
// double target_x_ = 1.0;
// 2. 直接初始化（圆括号）
// double target_x_(1.0);
// 3. 列表初始化（花括号）
// double target_x_{1.0}; 


// // rclcpp::Node::create_subscription 创建一个话题订阅者
// template <typename MessageT, typename AllocatorT = std::allocator<void>, typename CallbackT>
// typename rclcpp::Subscription<MessageT, AllocatorT>::SharedPtr
// create_subscription(
//   const std::string &topic_name,  // 订阅的话题名称
//   size_t qos_history_depth,       // 消息队列长度（QoS 历史深度）
//   CallbackT &&callback,           // 消息接收后的回调函数
//   const rclcpp::QoS &qos = ...    // QoS 配置（可选，默认使用系统默认）
// );