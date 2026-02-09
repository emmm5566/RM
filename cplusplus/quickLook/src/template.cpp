#include <iostream>

//模板函数
//template声明模板的关键字
//typename T是模板的类型参数，typename和class等价，T是参数类型名称

//情况1：未知参数类型
template<class T1, class T2, typename R>
R add(T1 a, T2 b)
{
    return a + b;
}

template<class T1, class T2>
double add1(T1 a, T2 b)
{
    return a + b;
}



//情况2：未知参数的值
template<int A>
int function()
{
    return A;
}



//情况3：未知参数的数量（变元模板）
template<class ... Args> //模板参数包：接收任意数量的类型；... 是“包扩展”运算符，Args代表一个“类型集合”
void add2(Args ... args) //函数参数包：接收任意数量、任意类型的参数；args是一个“值集合”，其类型对应模板参数包Args
{
    // 右折叠表达式（right fold），等价于递归展开参数包并累加：
    // 对于 args = (a, b, c, d)，展开为 ((a + b) + c) + d
    // 要求所有参数类型支持 + 运算符（如基本类型 int、double 等）
    std::cout << "Sum = " << (args + ...) << ' ';
    std::cout << "List: ";
    // 右折叠表达式，等价于递归展开并依次输出：
    // 对于 args = (a, b, c, d)，展开为 (((std::cout << a) << b) << c) << d。
    // 要求所有参数类型支持 << 运算符（与 std::cout 兼容）
    (std::cout << ... << args);
    std::cout << std::endl;
}



int main()
{
    std::cout << add<int, float, double>(66, 88.8) << std::endl; //154.8
    //T1=int, T2=float, R=double, a=66, b=88.8f
    std::cout << add1(66, 88.8) << std::endl; //154.8
    //T1=int, T2=double, a=66, b=88.8

    constexpr int n = 3; //constexpr关键字，声明编译期可计算的常量表达式(#define也是编译期确定的)
    std::cout << function<n>() << std::endl; //3
    std::cout << function<3>() << std::endl; //3
    // double x = 3;
    // const double y = 3; //const只读，在运行时确定
    // std::cout << function<x>() << std::endl; //错误
    // std::cout << function<y>() << std::endl; //错误
    // 模板是在编译期通过编译器实例化来运行，必须要在编译期确定，constexpr和define定义的变量都可以做模板参数

    add2(1, 2, 3, 4); //Sum = 10 List: 1234
    add2(1.5, 2.5, 3.5, 4.5, 5.5); //Sum = 17.5 List: 1.52.53.54.55.5
    add2(1, 2, 3.5); //Sum = 6.5 List: 123.5
    //混合类型（如int和double）参与运算时，依赖隐式类型转换（如 int→double），若转换不支持则报错

    return 0;
}