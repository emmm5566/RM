#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv)
{
    //初始化rclcpp
    rclcpp::init(argc, argv);
    //产生一个cpp_node节点
    auto node = std::make_shared<rclcpp::Node>("cpp_node");
    //打印一句介绍
    RCLCPP_INFO(node->get_logger(), "你好,c++节点！");
    //运行节点，并检测退出信号 Ctrl+C(打断运行)
    rclcpp::spin(node);
    //停止运行
    rclcpp::shutdown();

    return 0;
}



// 创建：
// mkdir -p ws/src/  # 创建工作空间 
// cd ws/src 
// ros2 pkg create pkg_name --build-type ament_cmake --dependencies rclcpp # 创建功能包
// cd pkg_name && mkdir src 
// cd src && touch node_name.cpp # 创建节点

// 编译:
// source /opt/ros/humble/setup.zsh 或 source /opt/ros/humble/setup.bash
// colcon build #在工作空间下
// colcon build --package-select pkg_name
// source install/setup.bash 或 source install/setup.zsh
// ros2 run pkg_name node_name
// 注意：若移动文件要删除build,install,log重新编译
//
// 目录结构：
// ws
// ├── build
// ├── install
// ├── log
// └── src
//     ├── pkg1
//     │   ├── CMakeLists.txt
//     │   ├── package.xml
//     │   └── src
//     │       ├── node01.cpp
//     │       └── node02.cpp
//     └── pkg2
//         ├── CMakeLists.txt
//         ├── package.xml
//         └── src
//             └── node03.cpp



//ros2 node list 查看节点列表
//ros2 node info node_name 查看节点信息



//ldd [选项] 目标文件
//ldd,List Dynamic Dependencies,用于列出可执行文件或共享库(.so 文件)所依赖的动态链接库

//"... not found"经常是因为环境原因，检查环境
//printenv | grep
//ros2 pkg prefix

//注：这里的工作空间是session3，要在工作空间下colcon build，不能在功能包里面
//session3/src/pkg_name   #session3是工作空间
//chapter2/pkg_name   #chapter2是工作空间

//ctrl+左键单击 查看定义（头文件）