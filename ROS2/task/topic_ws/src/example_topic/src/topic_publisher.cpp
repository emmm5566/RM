#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp" //导入消息接口

class TopicPublisher : public rclcpp::Node
{
private:
    // 声明话题发布者
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr string_publisher_; 
    // 声明定时器
    rclcpp::TimerBase::SharedPtr timer_;
    
    // 回调函数
    void timer_callback()
    {
        // 创建消息
        std_msgs::msg::String message;
        message.data = "forward"; //发布字符串
        // 日志打印
        RCLCPP_INFO(this->get_logger(), "发布: '%s'", message.data.c_str());
        // 发布消息
        string_publisher_->publish(message);
    }

public:
    TopicPublisher(std::string node_name) : Node(node_name)
    {
        RCLCPP_INFO(this->get_logger(), "节点 '%s' 已启动", node_name.c_str());
        // 创建话题发布者
        string_publisher_ = this->create_publisher<std_msgs::msg::String>("string_topic", 10);
        // 创建定时器，周期为500ms，定时发布
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), 
            std::bind(&TopicPublisher::timer_callback, this));
    }
};



int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    /*创建对应节点的共享指针对象*/
    auto node = std::make_shared<TopicPublisher>("topic_publisher");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}