#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/my_message.hpp"  // 自定义消息头文件

class MySubscriber : public rclcpp::Node {
public:
  MySubscriber() : Node("my_subscriber") {
    // 创建订阅者：订阅 "custom_topic" 话题，消息类型 MyMessage
    subscriber_ = this->create_subscription<custom_interfaces::msg::MyMessage>(
      "custom_topic", 10,
      [this](const custom_interfaces::msg::MyMessage &msg) {
        // 接收消息并打印
        RCLCPP_INFO(this->get_logger(), "收到: content=%s, num=%d", msg.content.c_str(), msg.num);
      }
    );
  }

private:
  rclcpp::Subscription<custom_interfaces::msg::MyMessage>::SharedPtr subscriber_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MySubscriber>());
  rclcpp::shutdown();
  return 0;
}