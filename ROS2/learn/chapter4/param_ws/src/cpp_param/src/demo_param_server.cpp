/*
  需求：编写参数服务端，设置并操作参数。
  流程:
    1.包含头文件；
    2.初始化ROS2客户端；
    3.自定义节点类；
      3-1.声明参数；
      3-2.查询参数；
      3-3.修改参数；
      3-4.删除参数；
    4.创建节点对象指针，调用参数操作函数，并传递给spin函数；
    5.资源释放。
*/

// 1.包含头文件
#include "rclcpp/rclcpp.hpp"

// 3.自定义节点类
class ParamServer : public rclcpp::Node
{
public:
    // 如果允许删除参数，那么需要通过 NodeOptions 声明
    // allow_undeclared_parameters允许删除参数行为，undeclared解除声明
    ParamServer() : Node("param_server_node_cpp",
      rclcpp::NodeOptions().allow_undeclared_parameters(true)) {
        RCLCPP_INFO(this->get_logger(), "参数服务端");
    }

    // 3-1.声明参数；
    void declare_param() {
        RCLCPP_INFO(this->get_logger(), "--------------增--------------");
        // 一次声明一个参数 this->declare_parameter
        // 一次声明多个参数 this->declare_parameters
        this->declare_parameter("car_name", "guard");
        this->declare_parameter("width", 1.55);
        this->declare_parameter("wheels", 5);
        // 使用 set_parameter 新增参数，前提需要 rclcpp::NodeOptions().allow_undeclared_parameters(true)
        this->set_parameter(rclcpp::Parameter{"height", 2.00});
    }

    // 3-2.查询参数；
    void get_param() {
        RCLCPP_INFO(this->get_logger(), "--------------查--------------");
        
        // 获取执行参数
        // this->get_parameter(); 根据参数的键来获取参数对象
        auto car = this->get_parameter("car_name");
        RCLCPP_INFO(this->get_logger(), "key = %s, value = %s", car.get_name().c_str(), car.as_string().c_str());

        // 获取一些参数
        // this->get_parameters(); 根据由键组成的vector来获取一些param对象
        auto params = this->get_parameters({"car_name", "width", "wheels"});
        for (auto && param : params) {
            RCLCPP_INFO(this->get_logger(), "{%s = %s}", param.get_name().c_str(), param.value_to_string().c_str());
        }

        // 判断是否包含参数
        // this->has_parameter(); 是否包含某个参数
        RCLCPP_INFO(this->get_logger(), "是否包含width? %d", this->has_parameter("width"));
        RCLCPP_INFO(this->get_logger(), "是否包含length? %d", this->has_parameter("length"));
    }   

    // 3-3.修改参数；
    void update_param() {
        RCLCPP_INFO(this->get_logger(), "--------------改--------------");
        // set_parameter必须传入一个已经存在的parameter对象，新值覆盖旧值
        RCLCPP_INFO(this->get_logger(), "修改前 width = %.2f", this->get_parameter("width").as_double());
        this->set_parameter(rclcpp::Parameter{"width", 1.75});
        RCLCPP_INFO(this->get_logger(), "修改后 width = %.2f", this->get_parameter("width").as_double());
    }

    // 3-4.删除参数；
    void delete_param() {
        RCLCPP_INFO(this->get_logger(), "--------------删--------------");
        // 不能删除声明的参数 declare_parameter，可以删除 set_parameter 设置的参数
        RCLCPP_INFO(this->get_logger(), "是否包含height? %d", this->has_parameter("height"));
        this->undeclare_parameter("height");
        RCLCPP_INFO(this->get_logger(), "是否包含height? %d", this->has_parameter("height"));
    }
};

int main(int argc, char ** argv)
{
    // 2.初始化ROS2客户端
    rclcpp::init(argc, argv);
    // 4.创建节点对象指针，调用参数操作函数，并传递给spin函数；
    auto node = std::make_shared<ParamServer>();
    node->declare_param();
    node->get_param();
    node->update_param();
    node->delete_param();
    rclcpp::spin(node);
    // 5.资源释放
    rclcpp::shutdown();

    return 0;
}

// ros2 param list 查看参数
// ros2 param get /node_name param_name 查看参数具体信息
// ros2 param get /param_server_node_cpp width