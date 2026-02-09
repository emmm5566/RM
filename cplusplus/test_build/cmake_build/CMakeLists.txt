cmake_minimum_required(VERSION 3.10)
project(main)

# 添加头文件路径
include_directories(include)

# 生成可执行文件
add_executable(main src/main.cpp src/helloworld.cpp src/sum.cpp)



# 手动编译
# mkdir build && cd build
# cmake ..  # 回到CMakeLists.txt所在目录
# make
# ./main

# 使用CMake Tools
# CMake图标 -> PROJECT STATUS
# （1）文件夹Folder后的小铅笔，配置项目信息
# （2）配置Configure：先选中后2项模式(GCC,Debug)，后点击带有箭头的图标
# （3）生成Build：生成可执行文件