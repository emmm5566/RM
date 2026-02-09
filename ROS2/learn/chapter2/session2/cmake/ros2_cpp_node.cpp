#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("cpp_node");
    RCLCPP_INFO(node->get_logger(), "你好,c++节点！");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}





//ctrl + Alt + t 打开终端（ubuntu）
//ctrl + shift + 5 打开新终端（vscode）