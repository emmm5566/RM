#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class AddClient : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    AddClient(const std::string& node_name) : Node(node_name) {
        RCLCPP_INFO(this->get_logger(), "节点已启动： %s", node_name.c_str());
        // 创建客户端
        add_ints_client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints_srv");
    }

    // 发送请求
    void send_request(int a, int b) {
        RCLCPP_INFO(this->get_logger(), "计算:%d + %d", a, b);

        // 1.等待服务端上线
        while(!add_ints_client_->wait_for_service(std::chrono::seconds(1))) {
            // 等待时检测rclcpp状态
            if(!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "等待服务的过程中被打断...");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "等待服务端上线中...");
        }

        // 2.构造请求的参数
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts_Request>();
        request->a = a;
        request->b = b;

        // 3.发布异步请求，然后等待返回，返回时调用回调函数
        add_ints_client_->async_send_request(
            request, std::bind(&AddClient::result_callback_, this, std::placeholders::_1));
    };

private:
    // 声明客户端
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr add_ints_client_;

    // 创建结果回调函数
    void result_callback_ (
        rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture result_future) {
            auto response = result_future.get();
            RCLCPP_INFO(get_logger(), "计算结果： %ld", response->sum);
        }
};

int main(int argc, char** argv) 
{
    rclcpp::init(argc, argv);
    /*创建对应节点的共享指针对象*/
    auto node = std::make_shared<AddClient>("add_client");
    /* 运行节点，并检测退出信号*/
    node->send_request(5, 6);  // 调用服务端发送请求
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}





// 创建客户端
// create_client() [1/2]
// template<typename ServiceT >
// rclcpp::Client<ServiceT>::SharedPtr rclcpp::Node::create_client 	( 	const std::string &  	service_name,
// 		const rmw_qos_profile_t &  	qos_profile = rmw_qos_profile_services_default,
// 		rclcpp::CallbackGroup::SharedPtr  	group = nullptr 
// 	) 	

// 异步发送请求
// 发送服务请求后不阻塞主线程，等服务端响应后再处理结果，可以同时处理多个任务
// async_send_request()
// template<typename ServiceT >
// template<typename CallbackT , typename std::enable_if< rclcpp::function_traits::same_arguments< CallbackT, CallbackType >::value >::type * = nullptr>
// SharedFuture rclcpp::Client< ServiceT >::async_send_request 	
// ( 	SharedRequest  	request,
// 		CallbackT &&  	cb 
// 	) 	
// 参数：
// request，请求的消息，这里用于放a，b两个数。
// CallBack，回调函数，异步接收服务器的返回的函数。	

// 等待服务端上线
// 在发送请求之前保证服务端启动了，避免发送请求出去而无人响应
// wait_for_service()
// template<typename RepT = int64_t, typename RatioT = std::milli>
// bool rclcpp::ClientBase::wait_for_service 	
// ( 	std::chrono::duration< RepT, RatioT >  	timeout = std::chrono::duration<RepT, RatioT>(-1)	) 	
// 参数：等待的时间；
// 返回值：bool，上线了就是true，不上线就是false

// std::future和std::shared_future是C++标准库中的两个类（<future>头文件），用于处理异步操作的结果
// 它们就像"未来值"的承诺，发起一个异步任务后，用它来“等待任务完成”和“获取任务结果”，本身不执行任务只负责“等结果”和“拿结果” 
// 两者的核心区别在于“独占性”与“共享性”，std::shared_future允许多个线程等候同一共享状态
// SharedFuture
// template<typename ServiceT >
// using rclcpp::Client< ServiceT >::SharedFuture = std::shared_future<SharedResponse>
// API：get    #返回结果 