/*
����VS��һ����Ŀ��ˢ������Ŀ����VS��һ��ֻ��һ������main��Դ�ļ��������ɣ�����Ϊÿ����Ŀ�½���Ŀ�����鷳������

�������
����������Ҫ�μ����ɵİ���main��Դ�ļ��Ҽ����ԡ������������ų�����ѡ���ǡ��������ɹ��󣬲���Ҫ��Դ�ļ�������ų��±ꡣ
*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	char ch = 0;
	char num = 0;
	scanf("%c", &ch);
	printf("ch = %c\n", ch);
	// scanf�ǽ�һ������ĵ�һ��Ԫ�ظ���ch
	// �ڸ�ch����ֵ����Ҫ��enter����������һ��������ָ���enter��Ԫ��ȴ���ᱻ���ջ�ɾ��
	// ������getchar��enter��Ԫ�����յ�
	num = getchar();
	printf("num = %c", num);
	return 0;
}