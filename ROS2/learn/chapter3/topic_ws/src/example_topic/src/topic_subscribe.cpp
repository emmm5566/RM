#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp" 

class TopicSubsribe : public rclcpp::Node
{
private:
    // 声明话题订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_; 

    // 收到话题数据的回调函数
    void command_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        double speed = 0.0f;
        if(msg->data == "forward")
        {
            speed = 0.2f;
        }
        RCLCPP_INFO(this->get_logger(), "收到[%s]指令，发送速度 %f",msg->data.c_str(), speed);
    }

public:
    // 构造函数,有一个参数为节点名称
    TopicSubsribe(std::string node_name) : Node(node_name)
    {
        RCLCPP_INFO(this->get_logger(), "节点 '%s' 启动", node_name.c_str());
        // 创建话题订阅者
        //"control_command"和发布者topic_name一致
        command_subscribe_ = this->create_subscription<std_msgs::msg::String>("control_command", 10, 
            std::bind(&TopicSubsribe::command_callback, this, std::placeholders::_1));
    }
};



int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicSubsribe>("topic_subscriber");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}





// 创建订阅者
// create_subscription()
// template<typename MessageT , typename CallbackT , typename AllocatorT , typename CallbackMessageT , typename SubscriptionT , typename MessageMemoryStrategyT >
// std::shared_ptr< SubscriptionT > rclcpp::Node::create_subscription 	
// ( 	const std::string &  	topic_name,
// 		const rclcpp::QoS &  	qos,
// 		CallbackT &&  	callback,
// 		const SubscriptionOptionsWithAllocator< AllocatorT > &  	options = SubscriptionOptionsWithAllocator<AllocatorT>(),
// 		typename MessageMemoryStrategyT::SharedPtr  	msg_mem_strat = (      MessageMemoryStrategyT::create_default()    ) 
// 	) 
// 参数：话题名称、Qos和回调函数，后面两个都是默认的参数	
