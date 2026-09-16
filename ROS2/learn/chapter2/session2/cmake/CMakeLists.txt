cmake_minimum_required(VERSION 3.8)
project(ros2_cpp)
add_executable(ros2_cpp_node ros2_cpp_node.cpp)

#查找到对应的头文件和库文件
find_package(rclcpp REQUIRED) 
#[[message打印
message(STATUS ${rclcpp_INCLUDE_DIRS})   #头文件及rclcpp依赖的头文件
message(STATUS ${rclcpp_LIBRARIES})   #库文件及rclcpp依赖的库文件
]]

#头文件包含
target_include_directories(ros2_cpp_node PUBLIC ${rclcpp_INCLUDE_DIRS})
#库文件链接
target_link_libraries(ros2_cpp_node ${rclcpp_LIBRARIES})
#${ 和 变量名 之间不能有空格






# 编译运行
# source /opt/ros/humble/setup.zsh 或 source /opt/ros/humble/setup.bash
# mkdir build && cd build
# cmake ..
# make
# ./ros2_cpp_node