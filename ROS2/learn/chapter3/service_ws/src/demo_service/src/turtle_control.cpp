/* 客户端（发送目标） →服务端（接收目标） → 订阅者（获取当前位置） → 计算控制量 → 发布者（发送速度指令） → 小海龟移动 */
//服务端：（接收客户端发送的目标坐标，并通过订阅者获取小海龟当前位置，计算控制量后通过发布者发送速度指令，）控制小海龟移动到目标位置


#include "rclcpp/rclcpp.hpp" 
#include "geometry_msgs/msg/twist.hpp"
//#include <string>
#include <chrono> 
#include "turtlesim/msg/pose.hpp" 
//#include <cmath>
#include "service_interfaces/srv/patrol.hpp"

using namespace std::chrono_literals; 
using Patrol = service_interfaces::srv::Patrol; //类型别名定义，重定义接口名


class TurtleController : public rclcpp::Node
{
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;  //声明话题发布者
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscription_; //声明话题订阅者

    //服务端的智能共享指针
    rclcpp::Service<Patrol>::SharedPtr patrol_service_; //声明服务端
    
    //控制参数
    double target_x_{1.0}; //目标x坐标
    double target_y_{1.0}; //目标y坐标
    double k_{1.0}; //比例系数
    double max_speed_{2.0}; //最大速度

public:
    TurtleController() : Node("turtle_controller")
    {
        //创建发布者
        //控制速度：linear.x 控制前进 / 后退速度，angular.z 控制转向速度
        velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        //创建订阅者，绑定回调函数
        //获取当前位置：接收小海龟当前的 x、y 坐标和朝向 theta
        pose_subscription_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, 
            std::bind(&TurtleController::pose_callback, this, std::placeholders::_1));

        //创建服务端
        //接收客户端请求的目标坐标，设置响应结果
        //<template T>模板类
        patrol_service_ = this->create_service<Patrol>("patrol",
            //Lambda表达式作为回调函数,[&]按引用捕获所有外部变量
            [&](const std::shared_ptr<Patrol::Request> request,  //const Patrol::Request::SharedPtr request
                const std::shared_ptr<Patrol::Response> response) -> void  //Patrol::Response::SharedPtr response       )
                {
                    // 坐标合法性检查：判断目标坐标是否在 [0, 12.0] 范围内
                    if(0<=request->target_x && request->target_x<=12.0f &&
                       0<=request->target_y && request->target_y<=12.0f) //合法范围检查
                       {
                            // 合法：更新服务端自身的目标坐标（成员变量）
                            this->target_x_ = request->target_x;
                            this->target_y_ = request->target_y;
                            // 响应客户端：设置结果为“成功”（使用 .srv 中定义的 SUCCESS 常量）
                            response->result = Patrol::Response::SUCCESS; //设置响应结果
                       }
                       else
                       {
                            // 不合法：响应客户端“失败” 
                            response->result = Patrol::Response::FAIL; 
                       }
                }
            );
    }

    //成员函数：订阅者回调函数
    void pose_callback(const turtlesim::msg::Pose::SharedPtr pose)
    {
        //获取当前位置
        double current_x = pose->x;
        double current_y = pose->y;
        RCLCPP_INFO(this->get_logger(), "Current Position: x=%.2f, y=%.2f", current_x, current_y);

        //计算距离和角度差
        auto distance = std::sqrt(std::pow(target_x_ - current_x, 2) + std::pow(target_y_ - current_y, 2)); //距离差
        auto angle = std::atan2(target_y_ - current_y, target_x_ - current_x) - pose->theta; //角度差

        //控制策略
        auto msg = geometry_msgs::msg::Twist(); 
        if(distance > 0.1)
        {
            if(fabs(angle) > 0.2) 
            {
                msg.angular.z = fabs(angle); 
            }
            else 
            {
                msg.linear.x = k_ * distance;
            }
        }

        //限制最大速度
        if(msg.linear.x > max_speed_)
        {
            msg.linear.x = max_speed_;
        }

        //发布消息
        velocity_publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Published: linear.x=%.2f, angular.z=%.2f", msg.linear.x, msg.angular.z);
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); //初始化ROS2客户端库
    //构造函数中已指定节点名，无需传参（构造函数是无参数的，不能传参）
    auto node = std::make_shared<TurtleController>(); //创建节点对象
    rclcpp::spin(node); //进入循环，等待回调函数被触发
    rclcpp::shutdown(); //关闭ROS2客户端库

    return 0;
}





//ros2 run turtlesim turtlesim_node 启动乌龟模拟节点

//rqt - 启动rqt图形化界面
//rqt - Plugins - Services - Service Caller 调用服务界面
//rqt中要调用服务/patrol：
// 运行turtlesim_node节点和turtle_control节点后，在工作空间终端中source install/setup.bash，然后运行rqt
// 选择Service Caller插件，在Service Name中选择/patrol，输入请求参数target_x和target_y，点击Call Service按钮即可调用服务，乌龟会移动到指定位置



// // rclcpp::Node::create_service 创建服务端
// template <typename ServiceT>  // ServiceT：服务类型（如自定义的Patrol）
// typename rclcpp::Service<ServiceT>::SharedPtr
// create_service(
//   const std::string &service_name,  // 服务名称（客户端需用相同名称调用）
//   CallbackT &&callback,             // 处理请求的回调函数
//   const rmw_qos_profile_t &qos_profile = rmw_qos_profile_services_default  // QoS配置（默认即可）
// );
