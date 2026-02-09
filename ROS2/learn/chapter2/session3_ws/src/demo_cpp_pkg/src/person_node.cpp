#include "rclcpp/rclcpp.hpp"

//rclcpp::Node   ROS2中节点的基类，所有自定义节点必须继承它，它是节点功能的“容器”，提供创建发布者、订阅者、服务、客户端的接口
// 创建一个类节点，名字叫做PersonNode，继承自Node 
class PersonNode : public rclcpp::Node 
{
private:
	std::string name_;
	int age_;

public:
    // 构造函数
	PersonNode(const std::string& node_name, const std::string& name, const int& age) : Node(node_name)
	{
		this->name_ = name;
		this->age_ = age;
	}

	//RCLCPP_INFO   ROS2中的日志宏，用于输出信息级别的日志（类似printf，但关联到ROS2日志系统）
	//c_str()   将std::string转换为const char*
	//get_logger()   rclcpp::Node类的成员函数，用于获取当前节点的日志器（logger）
    //this指向类的成员变量，food_name是函数的参数（局部变量）不用this指针
	void eat(const std::string& food_name)
	{
		// 打印一句话
		RCLCPP_INFO(this->get_logger(), "我是%s,%d岁,爱吃%s",
			this->name_.c_str(), this->age_, food_name.c_str());
	}
};

int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);
    
    // 创建节点实例
	auto node = std::make_shared<PersonNode>("person_node", "张三", 18);
    RCLCPP_INFO(node->get_logger(), "c++节点启动");

    node->eat("蛋糕");

	// 运行节点，并检测退出信号
    rclcpp::spin(node);
    rclcpp::shutdown();

	return 0;
}