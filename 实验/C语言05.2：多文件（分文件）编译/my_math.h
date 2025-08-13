// 头文件中只声明，不定义
// 定义只在.c 中定义

// 防止头文件重复包含的第一种方法，ifndef、endif
#ifndef _MY_MATH_H_				// 如果没有有定义一个宏，则进入操作，遇到endif结束
#define _MY_MATH_H_				// 定义一个宏
int my_max(int a, int b);
int my_min(int a, int b);
int my_sum(int a, int b);
#endif

// 第二种方法：在前面加这个 # pragma once