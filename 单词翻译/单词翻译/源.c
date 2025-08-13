#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_NUM 2
#define FILENAME "C:\\Users\\Cbl04\\Desktop\\学习\\1.编程\\1.C语言基础语法_fited\\单词翻译\\dict.txt"
 
typedef struct _dict
{
	char* key;
	char* content;
}DICT;

// 给存储单词开辟空间
FILE* open_file()
{
	FILE* fp = fopen(FILENAME, "r");
	if (NULL == fp)
	{
		perror("");
		return NULL;
	}

	return fp;
}

// 过滤掉单词后面的显示不了的字符
void filter_buf(char* buf)
{
	int n = strlen(buf) - 1;
	while (buf[n] == '\n' || buf[n] == '\t' || buf[n] == '\r')
		n--;
	buf[n + 1] = 0;
}

int search_dict(char* cmd, DICT* dict, int n, char* content)
{
	for (int i = 0; i < n; i++)
	{
		if(strcmp(cmd, dict[i].key) == 0)
		{
			strcpy(content, dict[i].content);
			return 1;
		}
	}
	return 0;
}

void dict_init(DICT** tmp)
{
	DICT* p;
	char* q = NULL;
	p = malloc(sizeof(DICT) * LINE_NUM);

	char buf[256];

	int i = 0;
	FILE* fp = open_file();
	while (1)
	{
		q = fgets(buf, sizeof(buf), fp);	// 读取一行单词
		if (q == NULL)
			break;

		filter_buf(buf);				// 过滤掉单词后面的显示不了的字符
		p[i].key = malloc(strlen(buf) + 1);
		strcpy(p[i].key, buf + 1);		// 将单词#后面的内容拷贝

		q = fgets(buf, sizeof(buf), fp);	// 读取一行翻译
		if (q == NULL)
			break;
		p[i].content = malloc(strlen(buf) + 1);
		strcpy(p[i].content, buf + 6);
		i++;
	}
	fclose(fp);

	*tmp = p;
}

int get_file_num()
{
	FILE* fp = open_file();
	int i = 0;
	char buf[256] = "";
	char* q = NULL;
	
	while (1)
	{
		q = fgets(buf, sizeof(buf), fp);	// 读取一行单词
		if (q == NULL)
			break;

		i++;
	}
	fclose(fp);
	
	return i;
} 

int main()
{

	char* buf;
	buf = malloc(sizeof(buf) * 128);
	int ret = 0;
	
	DICT* dict = NULL;
	dict_init(&dict);
	char content[256] = "";
	char cmd[256] = "";

	while (1)
	{
		printf("请输入需要翻译的单词:");
		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd) - 1] = 0; // 将最后一个字符'\0'去掉
		ret = search_dict(cmd, dict, LINE_NUM, content);	// 查找
		if (ret == 0)
		{
			printf("not trant\n");
		}
		else
		{
			printf("翻译为:%s\n", content);
		}
	}
}
