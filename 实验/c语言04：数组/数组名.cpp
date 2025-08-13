#include<stdio.h>
int main()
{
	int a[10];
	printf("&a[0] = %u\n", &a[0]);
	printf("a = %u\n", a);
	printf("&a = %u\n", &a);
	
	printf("\n\n进行加一操作，前面两个的地址是指向数组中的第二个，而最后一个的地址则是跨过整个数组，指向数组下面空间的地址\n\n\n");
	
	printf("&a[0]+1 = %u\n", &a[0]+1);
	printf("a+1 = %u\n", a+1);
	printf("&a+1 = %u\n", &a + 1);
	return 0;
}