#include<stdio.h>

struct stu
{
	int a;
	char* b;
	char name[128]; 
};

// �ṹ��ֻ��һ��ģ�棬��û�пռ�
// ��ʱstuû�пռ�

struct stu D;	
// ��ʱ�пռ��ˣ����Ը�����ֵ
// ���ǣ�D�����b��Ա��ָ�����ͣ�
// ��ʱ���洢�ĵ�ַ���������Ҫ��������ռ� 

struct stu* p;
// ��ʱp��Ұָ�룬��Ҫ������ַ 

 
D.a = 1;	// ����
// D.name = "world";		// ���������� 
							// ��Ϊname�������� 
strcpy(D.name, "world");// ���� 


/*
�����壨�����壩union 
*/
union abc
{
	char a;
	short b;
	char buf[2];
};
union abc temp;



/*
ö�٣�enum�� 
*/
// enum ab{A, B, C}; 	// Ĭ�ϴ�0��ʼ������Ϊ1  
enum ab{A, B=5, C};		// ��ʱA=0��B=5��C=6 
typedef enum BOOL bool{false, true};
bool a;
a = false;	���� ���0 

