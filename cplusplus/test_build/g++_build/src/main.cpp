#include <iostream>
#include "functions.hpp"
using namespace std;
int main() {

    helloworld();

    int a = 0, b = 0;
    cin >> a >> b;
    cout << "sum=" << sum(a, b) << endl;

    return 0;
}

//code ./ 用vscode打开当前目录

//配置：task.json -> launch.json -> c_cpp_properties.json
//CTRL + SHIFT + P 输入命令 : C/C++: Edit configurations (UI)，在Include path中添加：${workspaceFolder}/include

//编译运行：ctrl + shift + b 进行build
//调试运行：f5 启动调试器

// 设置断点：点击行号左侧空白处，会出现一个红点，表示断点已设置；
// 运行到断点，才能调试VARIABLES和WATCH
// Continue(f5) 继续运行
// Step Over(f10) 单步执行
// Step Into(f11) 进入函数
// Step Out(shift+f11) 跳出函数
// Restart(ctrl+shift+f5) 重启调试
// Stop Shift+F5 停止调试