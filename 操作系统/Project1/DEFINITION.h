#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<ctype.h>
#include<malloc.h> 	/* malloc()�� */
#include<limits.h> 	/* INT_MAX�� */
#include<stdio.h> 	/* EOF(=^Z��F6),NULL */
#include<stdlib.h> 	/* atoi() */
#include<io.h> 		/* eof() */
#include<math.h> 	/* floor(),ceil(),abs() */
#include<process.h> /* exit() */
#include<time.h>	
 
#include"Process.h"
#include"Memory.h"
#include"FileManage.h"


/*------------------------------ ȫ�ֱ��� -------------------------------*/
extern char str[MAX]; 							// ������ַ���
extern char buffer[BUF]; 						// �����


/*------------------------------ ���庯�� -------------------------------*/
void Close();							// �ͷ��ڴ桢����


 
