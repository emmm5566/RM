#include <iostream>

struct A
{
    int x;
    double y;
    char z;
};


int main()
{
    //指名初始化 (Designated Initializers) 
    //一种初始化聚合类型（Aggregate Types）成员的方式
    //结构体是聚合类型（无自定义构造函数、无基类、无私有 / 保护成员），非聚合类型不支持指名初始化
    //每个 designator 必须命名 T 的直接非静态数据成员，并且表达式中使用的所有 designator 必须与 T 的数据成员以相同的顺序出现
    
    //乱序指定初始化、嵌套指定初始化、混合指定初始化器和常规初始化器，以及数组的指定初始化都在 C 编程语言中受支持，但在 C++ 中不允许

    //  类型名 对象名{.成员名1 = 初始值1, .成员名2 = 初始值2,...};
    A a{.x = 1, .y = 2, .z = 3}; // ok
    // A b{.y = 2, .z = 3, .x = 1}; // error; designator order does not match declaration order

    return 0;
}