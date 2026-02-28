/*
  需求：编写参数客户端，获取或修改服务端参数。
  流程:
    1.包含头文件；
    2.初始化ROS2客户端；
    3.自定义节点类；
      3-1.创建参数客户端对象；
      3-2.连接服务端；
      3-3.查询参数；
      3-4.修改参数。
    4.创建自定义节点类对象，并调用其函数实现；
    5.资源释放。
*/

// 1.包含头文件
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

// 3.自定义节点类
class ParamClient : public rclcpp::Node
{
public:
    ParamClient() : Node("param_client_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "参数客户端");

        // 3-1.创建参数客户端对象；
        /*
            template<typename NodeT>
            explicit SyncParametersClient(
                std::shared_ptr<NodeT> node, // 参数1.当前对象依赖的节点
                const std::string & remote_node_name = "", // 参数2.远程连接的参数服务端节点的名称
                const rmw_qos_profile_t & qos_profile = rmw_qos_profile_parameters)
            : SyncParametersClient(
                std::make_shared<rclcpp::executors::SingleThreadedExecutor>(),
                node,
                remote_node_name,
                qos_profile)
        */
        param_client_ = std::make_shared<rclcpp::SyncParametersClient>(this, "param_server_node_cpp");

        /*
            问题：服务通信通过服务话题关联，为什么参数客户端是通过参数服务端的节点名称关联
            答： 1.参数服务端启动后，底层封装了多个服务通信的服务端；
                2.每个服务端的话题，都是采用 /服务端节点名称/XXXX；
                3.参数客户端创建后，也会封装多个服务通信的客户端；
                4.这些客户端与服务端相呼应，也要使用相同的话题，因此客户端再创建时需要使用服务端节点名称。
        */
    }

    // 3-2.连接服务端；
    bool connect_server() {
        while (!param_client_->wait_for_service(1s)) {
            if(!rclcpp::ok()) {
                return false;
            }
            RCLCPP_INFO(this->get_logger(), "服务连接中......");
        }
        return true;
    }

    // 3-3.查询参数；
    void get_param() {
        RCLCPP_INFO(this->get_logger(), "--------------查询参数--------------");

        //获取某个参数
        std::string car_name = param_client_->get_parameter<std::string>("car_name");
        double width = param_client_->get_parameter<double>("width");
        RCLCPP_INFO(this->get_logger(), "car_name = %s", car_name.c_str());
        RCLCPP_INFO(this->get_logger(), "width = %.2f", width);

        //获取多个参数
        auto params = param_client_->get_parameters({"car_name", "width", "wheels"});
        for(auto && param : params) {
            RCLCPP_INFO(this->get_logger(), "%s = %s", param.get_name().c_str(), param.value_to_string().c_str());
        }

        //判断是否包含某个参数
        RCLCPP_INFO(this->get_logger(), "包含car_name吗? %d", param_client_->has_parameter("car_name"));
        RCLCPP_INFO(this->get_logger(), "包含length吗? %d", param_client_->has_parameter("length"));
    }

    // 3-4.修改参数。
    void update_param() {
        RCLCPP_INFO(this->get_logger(), "--------------修改参数--------------");
        param_client_->set_parameters({rclcpp::Parameter("car_name", "hero"),
            rclcpp::Parameter("width", 3.0),
            // 设置一个参数服务端不存在的参数
            // 注意：如果允许此操作，那么参数服务端必须声明 rclcpp::NodeOptions().allow_undeclared_parameters(true)
            rclcpp::Parameter("length", 5.0)});
        RCLCPP_INFO(this->get_logger(), "新设置的参数 length:%.2f", param_client_->get_parameter<double>("length"));
    }

private:
    // SyncParametersClient 同步的参数客户端
    rclcpp::SyncParametersClient::SharedPtr param_client_;
};

int main(int argc, char ** argv)
{
    // 2.初始化ROS2客户端
    rclcpp::init(argc, argv);
    // 4.创建自定义节点类对象，并调用其函数实现；
    auto client = std::make_shared<ParamClient>();
    bool flag = client->connect_server();
    if(!flag) {
        return 0;
    }
    client->get_param();
    client->update_param(); 
    client->get_param();
    // 5.资源释放
    rclcpp::shutdown();

    return 0;
}
