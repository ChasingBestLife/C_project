#include<stdio.h>
int main()
{
	// ��ӡʱ��Ĭ��ֵ���6λС����
	// float�����ܹ���֤�ľ�����7λ��Ч���֣���������λ��
	// double�����ܹ���֤�ľ�����15λ��Ч����
	float a = 3.1415926535;
	double b = 3.1415926535;
	printf("a = %.8f\n", a);
	printf("b = %.8lf\n", b);
	return 0;
}