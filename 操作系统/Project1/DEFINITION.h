#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<ctype.h>
#include<malloc.h> 	/* malloc()等 */
#include<limits.h> 	/* INT_MAX等 */
#include<stdio.h> 	/* EOF(=^Z或F6),NULL */
#include<stdlib.h> 	/* atoi() */
#include<io.h> 		/* eof() */
#include<math.h> 	/* floor(),ceil(),abs() */
#include<process.h> /* exit() */
#include<time.h>	
 
#include"Process.h"
#include"Memory.h"
#include"FileManage.h"


/*------------------------------ 全局变量 -------------------------------*/
extern char str[MAX]; 							// 输入的字符串
extern char buffer[BUF]; 						// 缓冲池


/*------------------------------ 定义函数 -------------------------------*/
void Close();							// 释放内存、进程


 
