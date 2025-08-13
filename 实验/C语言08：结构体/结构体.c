#include<stdio.h>

struct stu
{
	int a;
	char* b;
	char name[128]; 
};

// 结构体只是一个模版，并没有空间
// 此时stu没有空间

struct stu D;	
// 此时有空间了，可以给它赋值
// 但是，D里面的b成员是指针类型，
// 此时它存储的地址是随机，需要另外申请空间 

struct stu* p;
// 此时p是野指针，需要给个地址 

 
D.a = 1;	// 合理
// D.name = "world";		// 不合理，报错 
							// 因为name是数组名 
strcpy(D.name, "world");// 合理 


/*
共用体（联合体）union 
*/
union abc
{
	char a;
	short b;
	char buf[2];
};
union abc temp;



/*
枚举（enum） 
*/
// enum ab{A, B, C}; 	// 默认从0开始，增量为1  
enum ab{A, B=5, C};		// 此时A=0，B=5，C=6 
typedef enum BOOL bool{false, true};
bool a;
a = false;	—— 输出0 

