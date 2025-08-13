#include<stdio.h>
int main()
{
	/*
	实现思想
    从第一个开始，与第二个比较，若第一个大，则交换顺序，以此类推，最后一个就是最大的啦
    然后开始排第二个大的值，接着第三个......到最小的

	时间复杂度
    最坏情况o(n^2)
    最好就是o(n)
	*/
	int a[5] = { 2, 5, 6, 3, 1 };
	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n - 1; i++)
	{
		// 因为每次比较的次数都要减一，刚好i每次加一，所以每一轮 比较的次数是n-1-i
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])		// 如果前面的元素比后面的元素大，则交换位置
			{
				int tmp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = tmp;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		printf("%d", a[i]);
	}
	printf("\n");
	return 0;
}