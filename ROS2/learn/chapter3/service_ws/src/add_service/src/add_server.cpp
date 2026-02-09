// 用ROS2自带的example_interfaces接口
// ros2 interface show example_interfaces/srv/AddTwoInts  #查看接口定义



#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"  //引入服务接口头文件

class AddServer : public rclcpp::Node
{
public:
    AddServer(const std::string& node_name) : Node(node_name) {
        RCLCPP_INFO(this->get_logger(), "节点已启动： %s", node_name.c_str());
        // 创建服务
        add_ints_server_ = this->create_service<example_interfaces::srv::AddTwoInts>(
            "add_two_ints_srv", 
            std::bind(&AddServer::handle_add_two_ints, this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    // 声明服务
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr add_ints_server_;

    // 收到请求的处理函数
    void handle_add_two_ints(
        const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
        std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response) {
        RCLCPP_INFO(this->get_logger(), "收到 a: %ld,b: %ld", request->a, request->b);
        response->sum = request->a + request->b;
    };
};

int main(int argc, char** argv) 
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddServer>("add_server");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}





// 创建服务端
// create_service()
// template<typename ServiceT , typename CallbackT >
// rclcpp::Service< ServiceT >::SharedPtr rclcpp::Node::create_service 	( 	const std::string &  	service_name,
// 		CallbackT &&  	callback,
// 		const rmw_qos_profile_t &  	qos_profile = rmw_qos_profile_services_default,
// 		rclcpp::CallbackGroup::SharedPtr  	group = nullptr 
// 	) 	
// 参数：
// ServiceT，消息接口类型example_interfaces::srv::AddTwoInts
// service_name，服务名称
// callback，回调函数，使用成员函数作为回调函数，std::bind进行转换
// qos_profile，服务质量配置文件，默认rmw_qos_profile_services_default
// group，调用服务的回调组，默认nullptr