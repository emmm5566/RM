#include <iostream>
#include <functional>
#include <vector>
#include <algorithm> //std::sort



// 函数对象（仿函数）
struct Multiply {
    int operator()(int a, int b) const { return a * b; }
}; 


int plus(int a, int b)
{
    return a + b;
}


int main()
{
    //Lambda 表达式是 匿名函数语法，用于快速定义 “即用即弃” 的函数对象，没有名字，只能在运行时创建
    
    // #include<functional>
    // 完成版：捕获列表 mutable throw (异常列表) -> 返回值 {函数体}
    // 简化版：捕获列表 {函数体}
    //mutable：允许修改按值捕获的变量（默认按值捕获的变量是 const 的）
    //throw(...)：指定异常抛出规则（如 throw() 表示不抛异常）

    // [捕获列表](参数列表) 修饰符 -> 返回类型 { 函数体 }
    //  []：不捕获任何外部变量；
    //  [x]：按值捕获变量 x（复制一份，Lambda 内修改不影响外部），深拷贝；
    //  [&x]：按引用捕获变量 x（Lambda 内修改会影响外部），浅拷贝；
    //  [=]：按值捕获所有用到的外部变量，值捕获，深拷贝；
    //  [&]：按引用捕获所有用到的外部变量，引用捕获，浅拷贝；
    //  [this]：捕获当前类的 this 指针（用于访问类的成员变量 / 函数）。
    //初始化捕获：通过 [var = 表达式] 语法，在捕获时对变量进行初始化（如 [x = 10](){...} 捕获并初始化 x 为 10）
    // 值捕获：会拷贝外部变量的副本，Lambda内部操作的是副本，默认情况下不能修改副本的值（视为常量），若需修改，需结合 mutable 关键字
    // 引用捕获：直接绑定外部变量的引用，Lambda 内部操作的是原变量，可直接修改原变量的值

    // 浅拷贝（Shallow Copy）：
    // 仅复制成员变量的 “表面值”（如指针地址，不会复制指针指向的实际内容），多个对象共享同一份资源（如堆内存）
    // 默认行为：C++ 编译器自动生成的默认拷贝构造函数和默认赋值运算符，执行的就是浅拷贝
    // 易引发 “重复释放”“悬垂指针” 等内存错误
    // 当类的成员变量都是基本类型（如 int、double）或无需独立资源的对象时，浅拷贝足够高效
    // 深拷贝（Deep Copy）：
    // 复制成员变量的 “深层资源”（如指针指向的堆内存），每个对象拥有独立的资源副本
    // 实现方式：需要自定义拷贝构造函数和自定义赋值运算符，在其中显式复制指针指向的资源
    // 当类包含动态分配的资源（如堆内存、文件句柄、网络连接等）时，必须使用深拷贝，否则会导致资源冲突或内存泄漏
    //
    // 如果使用值捕获，这里是否是深拷贝取决于拷贝构造函数，如果拷贝构造函数中是移动或者引用语义，那么遵从拷贝构造的语义
    // 但是这个值会被设置成不可操作的状态，他的值被视为常量，不能被修改。这时，可以使用 mutable 关键字来声明这个值是可修改的
    
    //注意：lambda末尾有两个';'，一个最后一条语句后，一个函数结束}后'};'

    auto add = [](int a, int b) -> int { return a + b; }; 
    std::cout << add(2, 3) << std::endl;
    
    int a = 0;
    auto fun = [a]() mutable 
    {
        return ++a;//如果不写mutable，编译器会报错，const a值捕获是常数
    };
    std::cout << fun() << std::endl;
    
    int c = 0, d = 1;
    auto fun1 = [c, &d]() -> void  
    { 
        d += c;
    };
    fun1();
    std::cout << d << ' ' << c << std::endl;

    auto fun2 = []() -> int { return 10; };    //简化  auto fun2 = []{ return 10; }; 
    std::cout << fun2() << std::endl;

    //int add = [](auto a, auto b) { return a + b; };  //错误
    //Lambda 表达式是编译器生成的匿名函数对象（其类型是一个独特的、编译器内部定义的类类型，无法显式写出），只能写auto，不能用int之类的基本数据类型



    std::vector<int> vec = {3, 5, 2, 4, 1};
    std::sort( vec.begin(), vec.end(), [](int a, int b){ return a>b; } );
    for(auto i : vec)
    {
        std::cout << i << " ";
    }
    //std::sort   是<algorithm>中的排序函数，用于对容器或数组中的元素进行排序
    // template< class RandomIt, class Compare >
    // void sort( RandomIt first, RandomIt last, Compare comp );
    //comp：自定义比较函数（可是函数指针、函数对象、Lambda 表达式等），用于定义排序规则；不写时默认升序排序



    //初始化捕获
    int n = 0;
    auto f = [n = 10]() -> int
    {
        return n;
    };
    std::cout << f() << std::endl;





    //泛型 Lambda 表达式：允许用 auto 声明参数类型，使 Lambda 能接受任意类型的参数，自动适配不同类型的输入，实现 “泛型” 功能
    //  [捕获列表](auto 参数1, auto 参数2, ...) { 函数体 }

    auto add1 = [](auto a, auto b) { return a + b; }; //泛型
    std::cout << add1(2.5, 3) << std::endl;
    std::cout << add1(std::string("Hello "), "World") << std::endl;

    auto print = [](int prefix, auto value) 
    {
        std::cout << prefix << value << std::endl;
    };
    print(2, "test");  // 2 test（第二个参数是 const char*）


    


    //函数指针
    //指向函数的指针变量，用于存储函数的内存地址，通过它可以间接调用函数
    //int plus(int a, int b) { return a + b; }     // 普通函数（签名：int(int, int)）
    //普通函数的定义必须在全局作用域、命名空间内或类内部，绝对不能嵌套在另一个函数（如 main()）内部
    int (*func_ptr)(int, int);      // 声明函数指针：指向 "返回int，参数为两个int" 的函数
    func_ptr = &plus;  // 赋值：指向 plus 函数, &可省略，函数名本身就是地址
    std::cout << func_ptr(2, 3) << std::endl;  //  调用：通过函数指针调用函数



    //std::function 函数包装器，只要其“签名”匹配可以存储、复制、传递任何“可调用对象”
    //#include <functional> 
    
    // 定义 std::function：包装 "返回int，参数为两个int" 的可调用对象
    std::function<int(int, int)> func1;
    // 1. 包装普通函数
    func1 = add;
    std::cout << func1(2, 3) << std::endl;  // 输出：5
    // 2. 包装 Lambda 表达式（无捕获）
    std::function<int(int, int)> func2;
    func2 = [](int a, int b) { return a - b; };
    std::cout << func2(2, 3) << std::endl;  // 输出：-1
    // 3. 包装带捕获的 Lambda 表达式
    std::function<int(int, int)> func3;
    int factor = 10;
    func3 = [factor](int a, int b) { return (a + b) * factor; };
    std::cout << func3(2, 3) << std::endl;  // 输出：50
    // 4. 包装函数对象
    // struct Multiply {
    //     int operator()(int a, int b) const { return a * b; }
    // };     // 函数对象（仿函数）
    std::function<int(int, int)> func4;
    func4 = Multiply();
    std::cout << func4(2, 3) << std::endl;  // 输出：6

    return 0;
}