#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicPublisher : public rclcpp::Node {

public:
    // 构造函数，初始化 message_published_ = false
    // TopicPublisher(std::string node_name) : Node(node_name), message_published_(false)
    TopicPublisher(std::string node_name) : Node(node_name)
    {
        RCLCPP_INFO(this->get_logger(), "Node %s start", node_name.c_str());
        //创建话题发布者
        command_publisher_ = this->create_publisher<std_msgs::msg::String>("command", 10);
    
        // // 创建定时器
        // timer_ = this->create_wall_timer(
        //     std::chrono::milliseconds(500),
        //     [this]() {
        //         if(!message_published_) {  // 如果没发布过，就发布一次消息
        //             publish_message("forward");
        //             message_published_ = true;  // 只发布一次
        //             timer_->cancel();  // 取消定时器
        //             RCLCPP_INFO(this->get_logger(), "Message published. Stopping timer.");
        //         }
        //     });
    }

    // 手动发布消息
    void publish_message(const std::string& message_data) {
        std_msgs::msg::String message;
        message.data = message_data;
        command_publisher_->publish(message);
        RCLCPP_INFO(this->get_logger(), "Publishing: %s", message.data.c_str());
    }

private:
    //声明话题发布者
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;

    // // 声明定时器
    // rclcpp::TimerBase::SharedPtr timer_;
    // bool message_published_;  // 标记消息是否已经发布
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicPublisher>("one_message_publisher");

    // // 发布一次消息
    node->publish_message("forward");

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}



// 使用定时器和回调函数的主要目的是让消息周期性发布，适用于需要持续更新状态或者定期发送指令的场景
// 如果应用场景不需要定期发送消息，那么可以
// （1）不使用定时器，直接在需要时手动发布消息或者根据其他事件进行控制；
// （2）调用一次定时器之后就取消
