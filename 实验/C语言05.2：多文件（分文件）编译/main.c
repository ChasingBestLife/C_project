#include<stdio.h>

#include"my_math.h"			// ˫���������ѱ����������ڵ�ǰ����Ŀ¼���ң�ͷ�ļ���Դ�ļ�����ͬһĿ¼�ģ������ܽ�ʡʱ��


/*
	���������ļ��ĺ������������һ�£���Ȼ������Ҳ�����У����ǻᱨ����ʾ������δ���壩
	��һ����������(�鷳)
	int my_max(int a, int b);
	int my_min(int a, int b);
	int my_sum(int a, int b);
*/
/*
	�ڶ��ַ���
	��include ͷ�ļ�
		ͷ�ļ��ĺ�׺һ����.h, ��Ϊͷ��Ӣ����head
	��������ֻ��Ҫ�������ŵ�ͷ�ļ��������
		ͷ�ļ�������Ӧ���� ���Ҫ�����ĺ������ļ���һ�£����˺�׺
*/

int main()
{

	int a = 6, b = 8;
	printf("max = %d\n", my_max(a, b));
	printf("min = %d\n", my_min(a, b));
	printf("sum = %d\n", my_sum(a, b));

	scanf("%d", &a);
	return 0;
}