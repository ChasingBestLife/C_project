#include<stdio.h>
#include<stdlib.h>		//exit
#include<stdbool.h>		//feof()����->�ж��ļ��Ƿ�Ϊ��
#include<string.h>		//strlen


//	!!!	һ��Ҫ����ļ��Ƿ��ܴ�

//��д�ַ�:fgetc,fputc
//��д�ַ���:fgets(����һ������),fputs(�����ַ���)  ע��:ֻ��дһ��,���Ҫ��ȡ���У���Ҫѭ����ȡ
//��ʽ����д:fprintf ->д���ļ�		fscanf ->��		ע��:ֻ��дһ��,���Ҫ��ȡ���У���Ҫѭ����ȡ

//��ģʽ����r��ֻ��ģʽ���ļ�������ڣ������ʧ��
void fileread()
{
	//��ָ����ģʽ���ļ�
	FILE* fp = fopen("d:/data/1.txt", "r");		//   "/" ���ܻ��� "\",�������滻��"\\"

/*		Unixʹ��б��/ ��Ϊ·���ָ�������webӦ������ʹ����Unixϵͳ���棬����Ŀǰ���е������ַ������ б��/ ��Ϊ�ָ�����
		Windows����ʹ�� б��/ ��ΪDOS������ʾ���Ĳ�����־�ˣ�Ϊ�˲����������Բ��� ��б��\ ��Ϊ·���ָ�����
		����Ŀǰwindowsϵͳ�ϵ��ļ������������ ��б��\ ��Ϊ·���ָ��������ŷ�չ��DOSϵͳ�Ѿ�����̭�ˣ�������ʾ��Ҳ�õĺ��٣�
		б�˺ͷ�б���ڴ��������¿��Ի�����û��Ӱ�졣
		֪����������󣬿����ܽ�һ�½��ۣ�

		��1���������ַ����ַʹ�� б��/ ;
		��2��windows�ļ��������ʹ�� ��б��\ ;
		��3��������html url() �����е�·����ָ����·��������·�������Ա����� б��/ ;
		��4����������ͨ�ַ����е�·��������������windows�ļ�·������ʹ�� б��/ �� ��б��\ ��һ���ģ�
		���������������ļ�·���������ʹ�� б��/ ;

		б��/ �� ��б��\ ����������Ͼ�����Щ�ˣ�����������һ�����·���;���·����
		./SRC/ ����д��ʾ����ǰĿ¼�е�SRC�ļ��У�
		../SRC/ ����д��ʾ����ǰĿ¼����һ��Ŀ¼��SRC�ļ��У�
		/SRC/ ����д��ʾ����Ŀ��Ŀ¼������ֻ���̸�Ŀ¼��Ҳ����ָ��Ŀ��Ŀ¼���������ʵ�����������

		��ע������������� \ Ҳ��ת���ַ�����ʼ�ַ���
		���ԣ� ·���е� \ ͨ����Ҫʹ�� \\����� / �Ͳ���Ҫʹ��ת����
		��C���ļ�������c:\\kkk\\dd.txt c:/kkk/dd.txtһ��
*/

	//�ж�һ���ļ��Ƿ�򿪳ɹ�
	if (fp == NULL)
	{
		perror("open file failed:");
		exit(0);
		//exit��0��;������return;����
	};
	//��ȡ�ļ�
	while (1)
	{
		char ch = fgetc(fp);
		if(feof(fp))break;
		printf("%c", ch);
	}
	 
	fclose(fp);
}

//��ģʽ����w��ֻдģʽ���ļ��������򴴽�������ֱ�Ӵ�
void filewrite()
{
	FILE* fp = fopen("D:/data/2.txt", "w");		
	//��data�ļ�����û��2.txt�ļ��Ļ����ͻ��Զ���data�ļ����д���һ������ΪANSI����Ϊ2.txt���ļ�
	
	if (fp == NULL)
	{
		perror("open file failed:");
		exit(0);
		//exit��0��;������return;����
	};   
	char str[] = "��Һã��Һܲ���"; //һ������ռ�����ֽڣ�ȫ�ǣ�һ��Ӣ���ַ�ռһ���ֽڣ����
	//д�ļ�
	for (int i = 0; i <	strlen(str); i++)
	{
		//char ch = fputc(i + 'A', fp);
		//printf("%c", ch);
		char ch = fputc(str[i], fp);
		printf("%c", ch);
	}
}

//��ģʽ����w+����дģʽ���ļ�����������ļ������򴴽��ļ� 
void filereadwrite()
{
	char wstr[] = {
		"\
�����ǵػ���С����Ģ��\n\
���߲�����\n\
��������ҧ\n\
����е�η\n\
��֪������\n"
	};
	FILE* fp=fopen("d:/data/1.txt","w+");
	if (fp == NULL)
	{
		perror("open file failed:");
		return;
	}
	//��д�ļ�
	int fpret = fputs(wstr, fp);
	printf("fputs return:%d\n", fpret);	//��ʱ�ļ�ָ��ָ�����ݵ�ĩβ��

	//���ļ�λ��ָ���ƶ����ļ��Ŀ�ͷ
	rewind(fp);

	//��ȡ�ļ�

	while (!feof(fp))
	{
		char buf[128] = { 0 };	//����ȳ�ʼ��
		char* restr = fgets(buf, sizeof(buf), fp);
		printf("%s", buf);
	}
}

//��ģʽ����r��ֻ��ģʽ���ļ�������ڣ������ʧ��
void fileFormatread()
{
	FILE* fp = fopen("d:/data/student.txt", "r");
	if (fp == NULL)
	{
		perror("file open failed:");
		return;
	}
	//��ʽ����ȡ
	/*
	��һ�ַ���:
	char  buf[4][128];
	fscanf(fp, "%s	%s	%s	%s", buf[0], buf[1], buf[2], buf[3]);
	for (int i = 0; i < 4; i++)
	{
		puts(buf[i]);
	}*/
	char nam[128];
	int ages;
	char pro[128];
	char score[20];
	
	for (int i = 0; i < 4; i++)
	{
		fscanf(fp, "%s %d %s %s", nam, &ages, pro, score);
		printf("%s	%d	%s	%s\n", nam, ages, pro, score);
	}
	fclose(fp);
}

//��ģʽ����w+����дģʽ���ļ�����������ļ������򴴽��ļ� 
void fileFormatwrite()
{
	FILE* fp = fopen("D:/data/stduent2.0.txt", "w+");
	if (fp == NULL)
	{
		perror("open file failed : ");
		return;
	}


	fclose(fp);
}

int main()
{
	//fileread();
	//filewrite();
	//filereadwrite();
	fileFormatread();
	//fileFormatwrite();
	return 0;
}
