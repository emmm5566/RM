cmake_minimum_required(VERSION 3.8)
project(demo_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1.查找头文件和库
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# 2.添加可执行文件
#文件名和扩展名之间不能有空格，否则会导致CMake找不到正确的源文件
add_executable(cpp_node src/cpp_node.cpp)
add_executable(person_node src/person_node.cpp)

# 3.添加依赖
# target_include_directories(cpp_node PUBLIC ${rclcpp_INCLUDE_DIRS})   #头文件包含
# target_link_libraries(cpp_node ${rclcpp_LIBRARIES})   #库文件链接
ament_target_dependencies(cpp_node rclcpp)   #相当于把引用头文件和库文件两句合成一句
ament_target_dependencies(person_node rclcpp)

# 4.将可执行文件拷贝到install/lib目录
#手动把可执行文件(TARGETS)从build拷贝到install/lib(DESTINATION)
#用ros2启动节点，命令从install中找可执行文件而不是build；直接./启动，在build中找可执行文件
install(TARGETS cpp_node person_node
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

ament_package()   #表示命令结束，要放到最后






# 修改CMakeLists.txt
# 1.添加可执行文件
# 2.添加依赖
# 3.使用install指令安装到install目录