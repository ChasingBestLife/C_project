#include<stdio.h>

/*
全局变量可以重复定义
因为，它可以被误认为是声明
因此，为避免编译器分不清是声明还是定义，
建议在声明前面加extern 

其他文件想用不属于本文件的全局变量，需要声明 
*/
int val;
// int val;
// int val;
extern int val;

/*
内存操作函数

memset(void* s, int c, size_t n)
功能： 将s的内存区域的前n个字节以参数c填入
		（c必须是：unsigned char，范围：0-255） 
返回值：s的首地址 

memcpy（void* dest, const void* src, size_t n）
功能：拷贝src所指的内容的前n个字节到dest所指的内存地址上
		（src与dest所指的内存空间不能重叠，可能会导致报错） 
		strncpy函数遇到'/0'就停止copy，memcpy不会 
返回值：dest的首地址 
*/

/*
向堆区内存申请地址malloc 
返回值：成功：空间首地址；失败：NULL 
*/

/*
内存泄漏
内存只申请，不释放，导致程序使用的内存空间一致增长
程序退出，程序使用的所有内存都会释放 
*/
int main()
{
	return 0;
 } 
