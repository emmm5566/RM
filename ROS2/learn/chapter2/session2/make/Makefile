build: # g++编译
	g++ first_ros2_node.cpp \
    -I/opt/ros/humble/include/rclcpp/ \
    -I /opt/ros/humble/include/rcl/ \
    -I /opt/ros/humble/include/rcutils/ \
    -I /opt/ros/humble/include/rmw \
    -I /opt/ros/humble/include/rcl_yaml_param_parser/ \
    -I /opt/ros/humble/include/rosidl_runtime_c \
    -I /opt/ros/humble/include/rosidl_typesupport_interface \
    -I /opt/ros/humble/include/rcpputils \
    -I /opt/ros/humble/include/builtin_interfaces \
    -I /opt/ros/humble/include/rosidl_runtime_cpp \
    -I /opt/ros/humble/include/tracetools \
    -I /opt/ros/humble/include/rcl_interfaces \
    -I /opt/ros/humble/include/libstatistics_collector \
    -I /opt/ros/humble/include/statistics_msgs \
    -L /opt/ros/humble/lib/ \
    -lrclcpp -lrcutils \
    -o first_ros2_node

clean: # 提供clean功能，使用make clean删掉first_ros2_node
	rm first_ros2_node





# 编译运行
# source /opt/ros/humble/setup.zsh 或 source /opt/ros/humble/setup.bash #加载ros2环境
# make build #在Makefile同级目录输入
# ./first_ros2_node #同级目录下也产生了first_node可执行文件（绿色代表可执行）
# make clean #删掉first_ros2_node