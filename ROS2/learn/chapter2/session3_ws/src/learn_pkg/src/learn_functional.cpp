//函数包装器
//同一不同函数调用方式
//保护成员函数接口

#include <iostream>
#include <string>
#include <functional>

// 自由函数
void save_with_free_fun(const std::string& file_name)
{
	std::cout << "调用了自由函数，保存：" << file_name << std::endl;
}

// 成员函数
class FileSave
{
public:
	FileSave() = default;
	~FileSave() = default;

	void save_with_member_fun(const std::string& file_name)
	{
		std::cout << "调用了成员函数，保存：" << file_name << std::endl;
	}
};

int main()
{
	// Lambda函数
	auto save_with_lambda_fun = [](const std::string& file_name) -> void
		{
			std::cout << "调用了Lambda函数，保存：" << file_name << std::endl;
		};

	// save_with_free_fun("file.txt");
	// file_name.save_with_member_fun("file.txt");
	// save_with_lambda_fun("file.txt");

	//std::function：函数包装器类型
	//std::function<返回值类型(参数类型1, 参数类型2, ...)> 包装器变量名;
	std::function<void(const std::string&)> save1 = save_with_free_fun;
	std::function<void(const std::string&)> save3 = save_with_lambda_fun;
	// 成员函数，放入包装器
	// 绑定（类的成员函数的指针，对象的指针，占位符）
	FileSave file_save; // 实例化对象
	std::function<void(const std::string&)> save2 =
		std::bind(&FileSave::save_with_member_fun,  // 成员函数指针
					&file_save,  // 绑定到的对象（指针）
					std::placeholders::_1); // 占位符：表示调用时传入的第一个参数
	//std::bind 将成员函数、对象指针、参数占位符绑定为一个新的可调用对象，使其签名与std::function匹配。
	//std::placeholders::_1 表示 “调用这个绑定对象时，第一个参数会传递给成员函数的第一个参数”

	save1("file.txt");
	save2("file.txt");
	save3("file.txt");

	return 0;
}



//函数包装器
//std::function<返回值类型(参数类型1, 参数类型2, ...)> 包装器变量名;

//std::bind 是一个函数模板，用于绑定可调用对象与其参数，生成一个新的可调用对象
// auto 新可调用对象 = std::bind(
//     原可调用对象,    // 要绑定的函数/成员函数/函数对象
//     参数1, 参数2, ... // 绑定的参数（可以是具体值，或占位符）
// );