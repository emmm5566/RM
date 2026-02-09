//auto自动类型推导
//注：auto不是一种类型
//例：auto node = std::make_shared<rclcpp::Node>("cpp_node");

#include <iostream>

int main()
{
	auto x = 5; // int x = 5;
	auto y = 3.14; // double y = 3.14;
	auto z = 'a'; 

	std::cout << x << std::endl;
	std::cout << y << std::endl;
	std::cout << z << std::endl;

	return 0;
}