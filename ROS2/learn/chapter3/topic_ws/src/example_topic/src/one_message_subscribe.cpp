#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicSubscribe : public rclcpp::Node 
{
public:
    TopicSubscribe(std::string node_name) : Node(node_name) {
        RCLCPP_INFO(this->get_logger(), "Node %s start", node_name.c_str());
        //创建话题订阅者
        topic_subscriber_ = this->create_subscription<std_msgs::msg::String>("command", 10,
            std::bind(&TopicSubscribe::command_callback, this, std::placeholders::_1));
    }

private:
    //声明话题订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr topic_subscriber_;
    //创建订阅者回调函数
    void command_callback(const std_msgs::msg::String::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Subscribing: %s", msg->data.c_str());
    }
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicSubscribe>("one_message_subscriber");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}