#include<stdio.h>
/*
1�����鲻��ָ�룬�����������鳤����Ϣ��ָ��û�У�

2����Ϊ��������ʱ������ᱻ����ָ�롣
	���� �ı��Ӻ�������ֵ��Ӱ���������������ֵ


	// c++��֧�֣�int* b = a;
	// int(*p)[3]��n��3�еĶ�ά����

*/

	// ����ת�� ���ʾ��ǶԳ������߻���ԳƵ�����Ԫ�ؽ�����ֵ
	// ��λ�󽻻�
	// �����ƶ���Ҫ�����䣬�������䣬�����ƶ���Ҫ�����䣬��������


int a[][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
const int row = sizeof(a) / sizeof(a[0]);			// ��Ϊ������������Ϊ��������
const int col = sizeof(a[0]) / sizeof(a[0][0]);		// ��Ϊ������������Ϊ��������

// ֻ������n*n����
void transpose01(int a[row][col])
{
	int i = 0, j = 0;

	int temp;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			printf("%d\t", a[i][j]);
			if (j == col - 1)	printf("\n");
		}

	for (i = 0; i < row; i++)
	{
		for (j = i + 1; j < col; j++)
		{
			temp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = temp;
		}
	}

	printf("ת�ú�\n");
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			printf("%d\t", a[i][j]);
			if (j == col - 1)	printf("\n");
		}
}

// ����n*m�о��󣬲�����Ҫ���¶���һ�����飬����������ָ��
void transpose02()
{

}

int main()
{	

	transpose01(a);

	return 0;
}