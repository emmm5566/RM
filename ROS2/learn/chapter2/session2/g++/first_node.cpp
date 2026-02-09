// 包含rclcpp头文件，如果vscode显示红色的波浪线也没关系，vscode只是编辑器而不是编译器
// 修复：c_cpp_properties.json中加"includePath":/opt/ros/humble/include/**

#include "rclcpp/rclcpp.hpp"
int main(int argc, char ** argv) {
    // 调用rclcpp的初始化函数
    rclcpp::init(argc, argv);
    // 调用rclcpp的循环运行first_node节点
    rclcpp::spin(std::make_shared<rclcpp::Node>("first_node"));
    return 0;
}





// 1.加载ros2环境
// source /opt/ros/humble/setup.zsh 或 source /opt/ros/humble/setup.bash
// 2.用g++编译节点
// (sudo apt install g++ 安装g++)
// g++ first_node.cpp \
// -I/opt/ros/humble/include/rclcpp/ \
// -I /opt/ros/humble/include/rcl/ \
// -I /opt/ros/humble/include/rcutils/ \
// -I /opt/ros/humble/include/rmw \
// -I /opt/ros/humble/include/rcl_yaml_param_parser/ \
// -I /opt/ros/humble/include/rosidl_runtime_c \
// -I /opt/ros/humble/include/rosidl_typesupport_interface \
// -I /opt/ros/humble/include/rcpputils \
// -I /opt/ros/humble/include/builtin_interfaces \
// -I /opt/ros/humble/include/rosidl_runtime_cpp \
// -I /opt/ros/humble/include/tracetools \
// -I /opt/ros/humble/include/rcl_interfaces \
// -I /opt/ros/humble/include/libstatistics_collector \
// -I /opt/ros/humble/include/statistics_msgs \
// -L /opt/ros/humble/lib/ \
// -lrclcpp -lrcutils \
// -o first_node
// 3.运行
// ./first_node

// 报错：
// 1. No such file or directory 
// 找不到头文件，可以用-I（大写i）来为g++指定这个目录
// 2. undefined reference to xxxxx
// 赵不到库文件，通过-L参数指定库目录，-l（小写L）指定库的名字
   