# CMake解析文件所需的最低版本
cmake_minimum_required(VERSION 3.8)

# 工程名
project(HelloWorld)

# 可执行文件
#[[ 声明一个可执行文件目标（target），名字叫 learn_cmake；
它由单个源文件 hello_world.cpp 编译链接而成 ]]
add_executable(learn_cmake hello_world.cpp)

#[[
cmake .   //.表示当前目录，在当前目录生成Makefile
mkdir build && cd build
cmake ..   //请在当前目录（build）里生成 Makefile/ Ninja 文件，但去上一级目录找 CMakeLists.txt
make   //生成可执行文件
./learn_cmake   //执行文件

cmake不是编译器，调用g++或其他编译器进行编译
c++只是编辑器，编辑器报错不影响编译
]]#