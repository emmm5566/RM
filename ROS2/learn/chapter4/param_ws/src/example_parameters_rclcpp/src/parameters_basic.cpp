#include <chrono>
#include "rclcpp/rclcpp.hpp"

/*
    # declare_parameter	        声明和初始化一个参数，参数有两个：参数名和参数值
    # describe_parameter(name)  通过参数名字获取参数的描述
    # get_parameter	            通过参数名字获取一个参数，参数有两个：参数名和放入结果的变量
    # set_parameter	            设置参数的值
*/
class ParametersBasicNode : public rclcpp::Node {
 public:
  // 构造函数,有一个参数为节点名称
  //explicit禁止编译器对该构造函数进行「隐式类型转换」，强制要显式调用构造函数创建对象
  explicit ParametersBasicNode(const std::string& name) : Node(name) {
    RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());

    this->declare_parameter("rcl_log_level", 0); /*声明参数*/
    this->get_parameter("rcl_log_level", log_level); /*获取参数*/
    /*设置日志级别*/
    this->get_logger().set_level((rclcpp::Logger::Level)log_level);
    using namespace std::literals::chrono_literals;
    timer_ = this->create_wall_timer(
      500ms, std::bind(&ParametersBasicNode::timer_callback, this));
  }

 private:
  int log_level; //声明日志级别
  rclcpp::TimerBase::SharedPtr timer_; //声明定时器

  //创建定时器回调函数
  void timer_callback() {
    this->get_parameter("rcl_log_level", log_level); /*获取参数*/
    /*设置日志级别*/
    this->get_logger().set_level((rclcpp::Logger::Level)log_level);
    std::cout << "================================================" << std::endl;
    RCLCPP_DEBUG(this->get_logger(), "这是DEBUG级别的日志!");
    RCLCPP_INFO(this->get_logger(), "这是INFO级别的日志!");
    RCLCPP_WARN(this->get_logger(), "这是WARN级别的日志!");
    RCLCPP_ERROR(this->get_logger(), "这是ERROR级别的日志!");
    RCLCPP_FATAL(this->get_logger(), "这是FATAL级别的日志!");
  }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  /*创建对应节点的共享指针对象*/
  auto node = std::make_shared<ParametersBasicNode>("parameters_basic");
  /* 运行节点，并检测退出信号*/
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}



// DEBUG级别的日志并没有被打印出来
// 原因：节点的日志级别设置为了0，0对应的日志级别为RCUTILS_LOG_SEVERITY_UNSET即未设置使用默认级别，
//      节点默认的日志级别就是INFO级别的，所以只能打印INFO以上的日志信息。
// 解决方法：运行节点时指定参数的值，log_level=10即DEBUG级别
// (1)在节点运行前通过CLI传递参数:：ros2 run example_parameters_rclcpp parameters_basic --ros-args -p rcl_log_level:=10
// (2)在运动的过程中也可以动态的修改参数：ros2 param set /parameters_basic rcl_log_level 10
// (3)使用ROS2提供的配置：ros2 run package-name node-name --ros-args --log-level debug

// ros2 param list #查看参数列表






// 设置日志级别API：
// this->get_logger().set_level(log_level);
// set_level，设置日志级别，ROS2的日志级别定义在文件/opt/ros/humble/include/rcutils/rcutils/logging.h的167-175行
// /// The severity levels of log messages / loggers.
// enum RCUTILS_LOG_SEVERITY
// {
//   RCUTILS_LOG_SEVERITY_UNSET = 0,  ///< The unset log level
//   RCUTILS_LOG_SEVERITY_DEBUG = 10,  ///< The debug log level 开发调试
//   RCUTILS_LOG_SEVERITY_INFO = 20,  ///< The info log level 常规运行信息
//   RCUTILS_LOG_SEVERITY_WARN = 30,  ///< The warn log level 警告
//   RCUTILS_LOG_SEVERITY_ERROR = 40,  ///< The error log level 错误
//   RCUTILS_LOG_SEVERITY_FATAL = 50,  ///< The fatal log level 致命错误
// };

// declare_parameter（声明并初始化参数）
// template <typename T>
// void declare_parameter(
//     const std::string &name,                // 参数名称
//     const T &default_value,                 // 参数默认值（支持int/float/string/bool/vector等）
//     const rcl_interfaces::msg::ParameterDescriptor &descriptor = rcl_interfaces::msg::ParameterDescriptor()  // 参数描述
// );

// describe_parameter（获取参数描述）
// rcl_interfaces::msg::ParameterDescriptor describe_parameter(
//     const std::string &name  // 要查询的参数名称
// ) const;  // const表示该函数不修改节点状态

// get_parameter（获取参数值）
// template <typename T>
// bool get_parameter(
//     const std::string &name,  // 参数名称
//     T &value                  // 输出参数：存储获取到的参数值
// ) const;

// set_parameter（设置参数值）
// bool set_parameter(
//     const rclcpp::Parameter &parameter  // 封装了参数名和新值的对象
// );

