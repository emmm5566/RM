cmake_minimum_required(VERSION 3.8)
project(demo_turtlesim)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

# Create executables
add_executable(turtle_circle src/turtle_circle.cpp)
add_executable(turtle_control src/turtle_control.cpp)

# Link libraries
ament_target_dependencies(turtle_circle rclcpp geometry_msgs) #添加头文件和库
ament_target_dependencies(turtle_control rclcpp geometry_msgs turtlesim)
#链接依赖ament_target_dependencies必须放在查找依赖find_package后面

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

# Install executables
install(TARGETS
  turtle_circle turtle_control
  DESTINATION lib/${PROJECT_NAME}
) #把可执行文件放到install中

ament_package()
