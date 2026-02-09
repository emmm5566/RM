#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp" //导入消息接口

class TopicPublisher : public rclcpp::Node
{
private:
    // 声明话题发布者指针
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_; 
    // 声明定时器指针
    /* 定时器对应的类是rclcpp::TimerBase，调用create_wall_timer将返回其共享指针 */
    rclcpp::TimerBase::SharedPtr timer_;
    
    // 回调函数
    void timer_callback()
    {
        // 创建消息
        /* std_msgs::msg::String是通过ROS2的消息文件自动生成的类 */
        std_msgs::msg::String message;
        message.data = "forward";
        // 日志打印
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        // 发布消息
        command_publisher_->publish(message);
    }

public:
    // 构造函数,有一个参数为节点名称
    TopicPublisher(std::string node_name) : Node(node_name)
    {
        RCLCPP_INFO(this->get_logger(), "Node '%s' has been started.", node_name.c_str());
        // 创建话题发布者
        command_publisher_ = this->create_publisher<std_msgs::msg::String>("control_command", 10);
        // 创建定时器，周期为500ms，定时发布
        /*  std::chrono::milliseconds(500)，代表500ms，chrono是c++ 11中的时间库，提供计时，时钟等功能
            std::bind(&TopicPublisher01::timer_callback, this)，bind() 函数的意义就像它的函数名一样，是用来绑定函数调用的某些参数的
            成员函数放入函数包装器需要绑定,绑定（类的成员函数的指针，对象的指针，占位符） */
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), 
            std::bind(&TopicPublisher::timer_callback, this));
        /* 使用定时器和回调函数的主要目的是让消息周期性发布，持续更新状态或者定期发送指令 */
    }
};



int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    // 创建对应节点的共享指针对象
    auto node = std::make_shared<TopicPublisher>("topic_publisher");
    // 运行节点，等待定时器发布消息，并检测退出信号
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}





// 测试：
// # 查看列表
// ros2 topic list
// # 输出内容
// ros2 topic echo /command

// 查看接口：
// ros2 interface list | grep std_msgs
// ros2 interface package std_msgs  #查看std_msgs包提供的所有消息接口
// ros2 interface show std_msgs/msg/String  #查看某个具体消息的定义
// ros2 pkg prefix std_msgs  #找到std_msgs包的安装位置





// 创建发布者
// create_publisher()
// template<typename MessageT , typename AllocatorT , typename PublisherT >
// std::shared_ptr< PublisherT > rclcpp::Node::create_publisher 	
// ( 	const std::string &  	topic_name,
// 		const rclcpp::QoS &  	qos,
// 		const PublisherOptionsWithAllocator< AllocatorT > &  	options = PublisherOptionsWithAllocator<AllocatorT>() 
// 	) 	
// 1. 消息类型（msgT）:导入消息接口std_msgs/msg/string.hpp->std_msgs::msg::String。
// 2. 话题名称（topic_name）:"control_command"。
// 3. 服务指令（qos）:Quality of Service服务质量。Qos支持直接指定一个数字，这个数字对应的是KeepLast队列长度(保留最后N条)。
// 一般设置成10，即如果一次性有100条消息，默认保留最新的10个，其余的都扔掉。


// 创建定时器
// create_wall_timer()
// template<typename DurationRepT , typename DurationT , typename CallbackT >
// rclcpp::WallTimer< CallbackT >::SharedPtr rclcpp::Node::create_wall_timer 	
// ( 	std::chrono::duration< DurationRepT, DurationT >  	period,
// 		CallbackT  	callback,
// 		rclcpp::CallbackGroup::SharedPtr  	group = nullptr 
// 	) 	
// 参数：
// 1. period，回调函数调用周期(ms)。
// 2. callback，回调函数。
// 3. group，调用回调函数所在的回调组，默认为nullptr。