cmake_minimum_required(VERSION 3.8)
project(learn_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

include_directories(include) #包含include头文件目录

# 添加可执行文件
add_executable(learn_auto src/learn_auto.cpp)
add_executable(learn_shared_ptr src/learn_shared_ptr.cpp)
add_executable(learn_lambda src/learn_lambda.cpp)
add_executable(learn_functional src/learn_functional.cpp)
add_executable(learn_thread src/learn_thread.cpp)

# 添加依赖
ament_target_dependencies(learn_auto rclcpp)
ament_target_dependencies(learn_shared_ptr rclcpp)
ament_target_dependencies(learn_lambda rclcpp)
ament_target_dependencies(learn_functional rclcpp)
ament_target_dependencies(learn_thread rclcpp)

# 安装到install目录
install(TARGETS learn_auto learn_shared_ptr learn_lambda learn_functional learn_thread
  DESTINATION lib/${PROJECT_NAME}
)

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
