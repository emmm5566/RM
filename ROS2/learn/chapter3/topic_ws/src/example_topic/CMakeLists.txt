cmake_minimum_required(VERSION 3.8)
project(example_topic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED) #查找消息接口包的头文件和库

#话题发布者
add_executable(topic_publisher src/topic_publisher.cpp)
ament_target_dependencies(topic_publisher rclcpp std_msgs) #给可执行文件添加消息接口的依赖

add_executable(one_message_publisher src/one_message_publisher.cpp)
ament_target_dependencies(one_message_publisher rclcpp std_msgs)

#话题订阅者
add_executable(topic_subscribe src/topic_subscribe.cpp)
ament_target_dependencies(topic_subscribe rclcpp std_msgs) #给可执行文件添加消息接口的依赖

add_executable(one_message_subscribe src/one_message_subscribe.cpp)
ament_target_dependencies(one_message_subscribe rclcpp std_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

#安装到install
install (TARGETS topic_publisher topic_subscribe one_message_publisher one_message_subscribe
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()





# 编译话题发布者、订阅者
# 1. 添加可执行文件 add_executable
# 2. 添加依赖 ament_target_dependencies
# 3. 安装 install

# 导入消息接口
# 1. CMakeLists.txt中，添加find_packages和ament_target_dependencies
# 2. packages.xml中，添加depend标签，将消息接口写入
# 3. 代码中，#include"消息功能包/xxx/xxx.hpp"