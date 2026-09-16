cmake_minimum_required(VERSION 3.8)
project(opencv_use)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) # Include OpenCV headers
# rclcpp：ROS2 C++ 核心库
# sensor_msgs：ROS2 图像消息类型（sensor_msgs/msg/Image）
# cv_bridge：ROS 图像与 OpenCV 图像（cv::Mat）的转换工具
# image_transport：ROS2 高效图像传输库（优化视频流传输）
# OpenCV：OpenCV 开发库（已通过libopencv-dev安装）

add_executable(my_opencv src/my_opencv.cpp)
target_link_libraries(my_opencv ${OpenCV_LIBRARIES}) # Link OpenCV libraries
target_include_directories(my_opencv PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(my_opencv PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  my_opencv
  "rclcpp"
  "OpenCV"
  "sensor_msgs"
  "cv_bridge"
  "image_transport"
)

install(TARGETS my_opencv
  DESTINATION lib/${PROJECT_NAME})

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

ament_package()
