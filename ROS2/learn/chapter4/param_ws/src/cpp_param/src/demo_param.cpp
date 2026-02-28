/*
  需求：演示参数API使用。
  流程:
    1.包含头文件；
    2.初始化ROS2客户端；
    3.自定义节点类；
      3-1.参数对象创建；
      3-2.参数对象解析（获取建、值、将值转换成字符串......）；
    4.调用spin函数，并传入节点对象指针；
    5.资源释放。
*/

// 1.包含头文件
#include "rclcpp/rclcpp.hpp"

// 3.自定义节点类
class MyParam : public rclcpp::Node
{
public:
  MyParam() : Node("my_param_node_cpp") {
    RCLCPP_INFO(this->get_logger(), "参数API使用");

    // 3-1.参数对象创建；
    /*
      Parameter<ValueTypeT>(const std::string &name, ValueTypeT value)
    */
    rclcpp::Parameter p1("car_name", "guard");
    rclcpp::Parameter p2("height", 1.68);
    rclcpp::Parameter p3("wheels", 4);

    // 3-2.参数对象解析（获取键、值、将值转换成字符串......）；

    // 解析值
    RCLCPP_INFO(this->get_logger(), "car_name = %s", p1.as_string().c_str());
    RCLCPP_INFO(this->get_logger(), "height = %.2f", p2.as_double());
    RCLCPP_INFO(this->get_logger(), "wheels = %ld", p3.as_int()); //int64_t 长整型 

    // 获取参数键
    RCLCPP_INFO(this->get_logger(), "name = %s", p1.get_name().c_str()); //获取键
    RCLCPP_INFO(this->get_logger(), "type = %s", p1.get_type_name().c_str()); //获取参数数据类型（的名字）
    RCLCPP_INFO(this->get_logger(), "value_to_string = %s", p2.value_to_string().c_str()); //获取值转字符串

    // Store the type and value of a parameter : class ParameterValue
    // rclcpp::ParameterValue value();
  }
};

int main(int argc, char ** argv)
{
  // 2.初始化ROS2客户端
  rclcpp::init(argc, argv);
  // 4.调用spin函数，并传入节点对象指针
  rclcpp::spin(std::make_shared<MyParam>());
  // 5.资源释放
  rclcpp::shutdown();

  return 0;
}
