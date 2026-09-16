#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "参数数量" << argc << std::endl;
    std::cout << "程序名字" << argv[0] << std::endl;
    std::string arg1 = argv[1];
    if (arg1 == "--help")
    {
        std::cout << "这里是程序帮助，但是这个程序什么用都没有" << std::endl;
    }

    //程序在运行时会默认传参
    // argc是参数数量，argv是参数数组，默认第一个参数是程序名字
    //g++ test_args.cpp编译
    //./a.out --help 1 2 3
    //参数数量是5，程序名字是./a.out，arg1=="--help"为真cout输出
    //如果只输入./a.out，arg1变成野指针

    return 0;
}

