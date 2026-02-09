// ros2 topic list -t 查看话题的功能包
// /turtle1/cmd_vel 订阅者 [geometry_msgs/msg/Twist] 接口geometry_msgs
// /turtle1/pose 发布者 [turtlesim/msg/Pose] 接口turtlesim



/*************************发布话题*******************************/
/* 控制小海龟 —— 发布话题
   画圆 —— 线速度/角速度=半径
   循环发布 —— 定时器 */

   

#include "rclcpp/rclcpp.hpp" // 配置 /opt/ros/humble/include/**
#include "geometry_msgs/msg/twist.hpp" // /turtle1/cmd_vel
#include <string>
#include <chrono> //处理时间和时间间隔

using namespace std::chrono_literals; //引入std::chrono_literals命名空间中的“时间字面量”，让代码中可以直接用直观的单位表示时间间隔



class TurtleCircleNode : public rclcpp::Node
{
private:
    //声明发布者的智能指针
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_; 
    //声明定时器的智能指针
    rclcpp::TimerBase::SharedPtr timer_;

public:
    //explicit 关键字用于防止单参数构造函数被隐式调用（防止隐式类型转换）
    explicit TurtleCircleNode(const std::string & node_name) : Node(node_name)
    {
        //创建发布者
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        //创建定时器，周期性调用回调函数
        //std::bind 成员函数绑定实例对象，在类中直接用this，在类外需要传入对象指针；无参数时不需要占位符
        //std::chrono::milliseconds(1000)
        timer_ = this->create_wall_timer(1000ms, std::bind(&TurtleCircleNode::timer_callback, this));
    }

    //成员函数：定时器回调函数
    void timer_callback()
    {
        // 创建并配置消息
        auto msg = geometry_msgs::msg::Twist();
        msg.linear.x = 1.0; // 线速度
        msg.angular.z = 0.5; // 角速度

        // 发布消息
        publisher_->publish(msg); //发布消息
        RCLCPP_INFO(this->get_logger(), "Published: linear.x=%.2f, angular.z=%.2f", msg.linear.x, msg.angular.z); //日志输出
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); //初始化ROS2客户端库
    auto node = std::make_shared<TurtleCircleNode>("turtle_circle_node"); //创建节点对象
    rclcpp::spin(node); //进入循环，等待回调函数被触发
    rclcpp::shutdown(); //关闭ROS2客户端库

    return 0;
}



//colcon build --packages-select demo_turtlesim 编译
//source install/setup.bash 运行环境配置（每次新开终端都要执行）
// 编译后运行：ros2 run demo_turtlesim turtle_circle



// // rclcpp::Node::create_publisher  创建一个话题发布者 
// template <typename MessageT, typename AllocatorT = std::allocator<void>>
// typename rclcpp::Publisher<MessageT, AllocatorT>::SharedPtr
// create_publisher(
//   const std::string &topic_name,  // 话题名称（字符串）
//   size_t qos_history_depth,       // 消息队列长度（QoS 历史深度）
//   const rclcpp::QoS &qos = ...    // QoS 配置（可选，默认使用默认配置）
// );
// Qos，Qos支持直接指定一个数字，这个数字对应的是KeepLast队列长度。一般设置成10，即如果一次性有100条消息，默认保留最新的10个，其余的都扔掉


// // rclcpp::Node::create_wall_timer  创建一个定时器
// template <typename DurationRepT = int64_t, typename DurationT = std::milli, typename CallbackT>
// typename rclcpp::TimerBase::SharedPtr
// create_wall_timer(
//   std::chrono::duration<DurationRepT, DurationT> period,  // 定时器周期（时间间隔）
//   CallbackT &&callback                                   // 周期触发的回调函数
// );