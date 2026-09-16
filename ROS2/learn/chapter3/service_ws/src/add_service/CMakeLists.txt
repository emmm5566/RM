cmake_minimum_required(VERSION 3.8)
project(add_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)  #添加接口功能包

#添加可执行文件和依赖
add_executable(add_server src/add_server.cpp)
ament_target_dependencies(add_server rclcpp example_interfaces)  #添加接口依赖

add_executable(add_client src/add_client.cpp)
ament_target_dependencies(add_client rclcpp example_interfaces)  #添加接口依赖

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

#安装
install(TARGETS
  add_server add_client
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()





# ament_cmake导入接口：
# 1. 在CMakeLists.txt中，添加find_packages和ament_target_dependencies。
# 2. 在packages.xml中，添加depend标签并将消息接口写入。
# 3. 在代码中，添加#include"消息功能包/xxx/xxx.hpp"。