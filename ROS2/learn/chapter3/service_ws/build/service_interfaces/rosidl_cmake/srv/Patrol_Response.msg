
int8 SUCCESS = 1  #定义常量，表示成功 （大写常量）
int8 FAIL = 0     #定义常量，表示失败
int8 result       #处理结果，SUCCESS / FAIL 取其一 （小写变量）





#创建接口功能包
#ros2 pkg create example_ros2_interfaces --build-type ament_cmake --dependencies rosidl_default_generators geometry_msgs
#功能包类型必须为：ament_cmake
#依赖rosidl_default_generators必须添加(把自定义消息文件转换成c++/Python源码)