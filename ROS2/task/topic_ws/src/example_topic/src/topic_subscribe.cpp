#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp" 

class TopicSubsribe : public rclcpp::Node
{
private:
    // 声明话题订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_; 

    // 收到话题数据的回调函数
    void command_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "收到: %s", msg->data.c_str());
    }

public:
    TopicSubsribe(std::string node_name) : Node(node_name)
    {
        RCLCPP_INFO(this->get_logger(), "节点 '%s' 已启动", node_name.c_str());
        // 创建话题订阅者
        command_subscribe_ = this->create_subscription<std_msgs::msg::String>("string_topic", 10, 
            std::bind(&TopicSubsribe::command_callback, this, std::placeholders::_1));
    }
};



int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicSubsribe>("topic_subscriber");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
