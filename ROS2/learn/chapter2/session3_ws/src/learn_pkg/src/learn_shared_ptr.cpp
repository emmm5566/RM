//智能指针（共享指针）shared_ptr
//自动管理内存
//共享指针每次复制时都会创建一个引用计数，当计数为0时自动销毁

#include <iostream>
#include <string>
#include <memory> // 包含智能指针库，提供std::shared_ptr等智能指针类型

int main()
{
	//std::make_shared<数据类型/类>(参数);
	//返回值，对应类的共享指针 std::shared_ptr<std::string> 写成 auto
	// 这里创建一个指向std::string对象的共享指针p1，对象内容为"This is a str."
    // 此时p1的引用计数为1（只有p1指向该对象）
	auto p1 = std::make_shared<std::string>("This is a str."); // 1

	// 复制共享指针p1到p2：
    // 共享指针的复制会导致引用计数+1（此时计数变为2）
    // p1和p2指向同一块内存，共享该string对象的所有权
	auto p2 = p1;
	// use_count()：返回当前共享该对象的指针数量（引用计数）
    // get()：返回指向对象的原始指针（用于查看内存地址）
    // 此时p1和p2的引用计数均为2，且指向同一地址
	std::cout << "p1的引用计数：" << p1.use_count() << "，指向内存地址：" << p1.get() << std::endl; // 2
	std::cout << "p2的引用计数：" << p2.use_count() << "，指向内存地址：" << p2.get() << std::endl; // 2
	
	// reset()：主动释放p1对当前对象的所有权
    // 调用后p1不再指向该string对象（变为nullptr），引用计数-1（从2变为1）
	p1.reset(); // 释放引用，不指向"This is a str."所在内存
	// 释放后p1的引用计数为0（不再指向任何对象），p2的引用计数为1（仅剩p2持有所有权）
	std::cout << "p1的引用计数：" << p1.use_count() << "，指向内存地址：" << p1.get() << std::endl; // 0
	std::cout << "p2的引用计数：" << p2.use_count() << "，指向内存地址：" << p2.get() << std::endl; // 2-1=1

	// ->操作符：共享指针重载了->，可直接访问指向对象的成员方法
    // 此时p2仍持有对象所有权，因此能正常调用c_str()获取字符串内容
	std::cout << "p2指向内存地址的数据" << p2->c_str() << std::endl; //调用成员方法，"This is a str."
	
	//注：c_str()要用指针调用

	return 0;
}





//std::shared_ptr（共享指针）
//可以进行自动内存管理的指针
//1. std::shared_ptr<类型名> 指针变量名;  （模板类）
//2. 创建共享指针 std::make_shared<类型>(构造参数)
//3. 复制与赋值：共享所有权，自动更新引用计数
//4. 引用计数操作：use_count()获取当前计数
//5. 访问对象：兼容普通指针的*和->
//6. 释放所有权：reset()方法
//   reset()：释放当前对象，指针变为nullptr，引用计数 - 1（若计数变为 0 则释放内存）
//   reset(新指针)：释放当前对象，转而指向新对象（新对象的引用计数初始化为 1
//7. 获取原始指针：get()方法
//8. 空指针判断：支持operator bool()
//   if (!p) { // 等价于p == nullptr，判断是否为空
//     std::cout << "p is null";
//   }