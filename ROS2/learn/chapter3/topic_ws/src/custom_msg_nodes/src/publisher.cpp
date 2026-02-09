#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/my_message.hpp"  // 自定义消息头文件
using namespace std::chrono_literals;

class MyPublisher : public rclcpp::Node {
public:
  MyPublisher() : Node("my_publisher"), count_(0) {
    // 创建发布者：话题名 "custom_topic"，消息类型 MyMessage，队列长度 10
    publisher_ = this->create_publisher<custom_interfaces::msg::MyMessage>("custom_topic", 10);
    
    // 定时器：每 1 秒发布一次消息
    timer_ = this->create_wall_timer(
      1s, std::bind(&MyPublisher::publish_msg, this)
    );
  }

private:
  void publish_msg() {
    // 构造自定义消息
    auto msg = custom_interfaces::msg::MyMessage();
    msg.content = "Hello, Custom Msg!";  // 字符串字段
    msg.num = count_++;                  // 整数字段（自增）
    
    publisher_->publish(msg);
    RCLCPP_INFO(this->get_logger(), "发送: content=%s, num=%d", msg.content.c_str(), msg.num);
  }

  rclcpp::Publisher<custom_interfaces::msg::MyMessage>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyPublisher>());
  rclcpp::shutdown();
  return 0;
}