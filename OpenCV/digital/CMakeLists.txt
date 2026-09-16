cmake_minimum_required(VERSION 2.8)   #最低版本
project(digital)   #项目名称
find_package(OpenCV REQUIRED)   #添加opencv库到本项目
include_directories(${OpenCV_INCLUDE_DIRS})   #添加opencv头文件路径

add_executable(demo src/demo.cpp)   #添加可执行文件
add_executable(demo1 src/demo1.cpp)
add_executable(demo2 src/demo2.cpp)
add_executable(learn_Mat src/learn_Mat.cpp)
add_executable(channel_demo src/channel_demo.cpp)
add_executable(gray src/gray.cpp)
add_executable(binary src/binary.cpp)
add_executable(morphology src/morphology.cpp)
add_executable(contours src/contours.cpp)
add_executable(RotatedRect src/RotatedRect.cpp)
add_executable(approxPolyDP src/approxPolyDP.cpp)
add_executable(API src/API.cpp)

target_link_libraries(demo ${OpenCV_LIBS})   #链接opencv库到可执行文件
target_link_libraries(demo1 ${OpenCV_LIBS})
target_link_libraries(demo2 ${OpenCV_LIBS})
target_link_libraries(learn_Mat ${OpenCV_LIBS})
target_link_libraries(channel_demo ${OpenCV_LIBS})
target_link_libraries(gray ${OpenCV_LIBS})
target_link_libraries(binary ${OpenCV_LIBS})
target_link_libraries(morphology ${OpenCV_LIBS})
target_link_libraries(contours ${OpenCV_LIBS})
target_link_libraries(RotatedRect ${OpenCV_LIBS})
target_link_libraries(approxPolyDP ${OpenCV_LIBS})
target_link_libraries(API ${OpenCV_LIBS})