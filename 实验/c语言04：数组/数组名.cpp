#include<stdio.h>
int main()
{
	int a[10];
	printf("&a[0] = %u\n", &a[0]);
	printf("a = %u\n", a);
	printf("&a = %u\n", &a);
	
	printf("\n\n���м�һ������ǰ�������ĵ�ַ��ָ�������еĵڶ����������һ���ĵ�ַ���ǿ���������飬ָ����������ռ�ĵ�ַ\n\n\n");
	
	printf("&a[0]+1 = %u\n", &a[0]+1);
	printf("a+1 = %u\n", a+1);
	printf("&a+1 = %u\n", &a + 1);
	return 0;
}