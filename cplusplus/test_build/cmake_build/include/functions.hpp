//#pragma once 可以替代传统的头文件保护宏（#ifndef + #define + #endif）

//C++ 预处理指令（#ifndef/#define/#endif）的语法要求：指令关键字和宏名之间必须加空格
#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_

void helloworld();
int sum(int a, int b);

#endif  // _FUNCTIONS_HPP_