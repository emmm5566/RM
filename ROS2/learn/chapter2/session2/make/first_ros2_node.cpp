#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto note = std::make_shared<rclcpp::Node>("first_ros2_node");
    RCLCPP_INFO(note->get_logger(), "first_ros2_node");
    rclcpp::spin(note);
    rclcpp::shutdown();
    return 0;
}