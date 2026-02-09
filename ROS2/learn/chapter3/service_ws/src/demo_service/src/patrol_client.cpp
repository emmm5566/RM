//客户端：随机产生目标点，把目标点发送给服务端
//创建客户端和定时器，定时产生目标点并向服务端发送请求

#include "rclcpp/rclcpp.hpp" 
#include "service_interfaces/srv/patrol.hpp"
#include <chrono>
#include <cstdlib> //std::rand(), std::srand()
#include <ctime>   //std::time()

using Patrol = service_interfaces::srv::Patrol; //类型别名定义，重定义接口名
using namespace std::chrono_literals; //定义字面量

class PatrolClient : public rclcpp::Node
{
private:
    rclcpp::Client<Patrol>::SharedPtr patrol_client_; //声明客户端
    rclcpp::TimerBase::SharedPtr timer_; //定时器

public:
    //构造函数
    PatrolClient() : Node("patrol_client")
    {
        //创建客户端
        //客户端名字要和服务端保持一致
        patrol_client_ = this->create_client<Patrol>("patrol");

        srand(time(NULL)); //设置随机数种子(只设置一次)
        //创建定时器
        timer_ = this->create_wall_timer(5s, 
            [&]() -> void //Lambda表达式作为回调函数
            {
                // 1.检测服务端是否上线
                while (! this->patrol_client_->wait_for_service(1s))
                {
                    if(!rclcpp::ok())
                    {
                        RCLCPP_ERROR(this->get_logger(), "等待服务器的过程中被中断，程序退出...");
                        return;
                    }
                    RCLCPP_INFO(this->get_logger(), "等待服务端上线中...");
                }

                // 2.创建请求对象，随机生成目标坐标
                auto request = std::make_shared<Patrol::Request>();
                request -> target_x = rand() % 13;
                request -> target_y = rand() % 13;
                //request->target_x = static_cast<float>(rand()) / RAND_MAX * 12.0f; 
                //request->target_y = static_cast<float>(rand()) / RAND_MAX * 12.0f;
                RCLCPP_INFO(this->get_logger(), "请求目标坐标: x=%.2f, y=%.2f", request->target_x, request->target_y);

                // 3.发送请求,并设置响应回调函数
                this->patrol_client_->async_send_request(request,
                    [&](rclcpp::Client<Patrol>::SharedFuture result_future) -> void
                    {
                        auto response = result_future.get();
                        if(response->result == Patrol::Response::SUCCESS)
                        {
                            RCLCPP_INFO(this->get_logger(), "请求巡逻目标点成功");
                        }
                        if(response->result == Patrol::Response::FAIL)
                        {
                            RCLCPP_WARN(this->get_logger(), "请求巡逻目标点失败");
                        }
                    });

            });
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<PatrolClient>(); 
    rclcpp::spin(node); 
    rclcpp::shutdown(); 

    return 0;
}



//测试
//在共同工作空间下：ros2 run turtlesim turtlesim_node
//打开新终端，在共同工作空间下：
// source install/setup.bash
// ros2 run demo_service turtle_controller 
//打开新终端，在共同工作空间下：
// source install/setup.bash
// ros2 run demo_service patrol_client
//为了显示发布的信息（服务）更完整，先运行客户端/订阅者，再运行服务端/发布者



// // rclcpp::Node::create_client 创建服务客户端
// template <typename ServiceT, typename AllocatorT = std::allocator<void>>
// typename rclcpp::Client<ServiceT, AllocatorT>::SharedPtr
// create_client(
//   const std::string &service_name,  // 服务名称（需与服务端一致）
//   const rmw_qos_profile_t &qos_profile = rmw_qos_profile_services_default  // QoS配置（默认即可）
// );

// // rclcpp::Client::async_send_request 异步发送请求
// template <typename ServiceT>
// typename rclcpp::Client<ServiceT>::SharedFuture
// async_send_request(
//   const std::shared_ptr<typename ServiceT::Request> &request,  // 请求消息对象
//   CallbackT &&callback  // 响应回调函数（可选）
// );

//rclcpp::Client<ServiceT>::SharedFuture 异步获取服务响应,在服务端返回响应时获取结果
//类模板 std::shared_future 提供访问异步操作结果的机制，类似 std::future ，除了允许多个线程等候同一共享状态
//future.get() 阻塞当前线程，直到服务端（ServiceT::Response 对象）的响应到达

// // rclcpp::Client::wait_for_service 阻塞等待服务端启动并提供服务
// template <typename RepT, typename PeriodT>
// bool wait_for_service(
//   const std::chrono::duration<RepT, PeriodT> &timeout  // 超时时间
// );