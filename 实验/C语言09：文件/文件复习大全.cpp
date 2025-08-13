#include<stdio.h>
#include<stdlib.h>		//exit
#include<stdbool.h>		//feof()函数->判断文件是否为空
#include<string.h>		//strlen


//	!!!	一定要检查文件是否能打开

//读写字符:fgetc,fputc
//读写字符串:fgets(返回一个整数),fputs(返回字符串)  注意:只读写一行,如果要读取多行，需要循环读取
//格式化读写:fprintf ->写进文件		fscanf ->读		注意:只读写一行,如果要读取多行，需要循环读取

//打开模式：“r”只读模式，文件必须存在，否则打开失败
void fileread()
{
	//以指定的模式打开文件
	FILE* fp = fopen("d:/data/1.txt", "r");		//   "/" 不能换成 "\",但可以替换成"\\"

/*		Unix使用斜杆/ 作为路径分隔符，而web应用最新使用在Unix系统上面，所以目前所有的网络地址都采用 斜杆/ 作为分隔符。
		Windows由于使用 斜杆/ 作为DOS命令提示符的参数标志了，为了不混淆，所以采用 反斜杠\ 作为路径分隔符。
		所以目前windows系统上的文件浏览器都是用 反斜杠\ 作为路径分隔符。随着发展，DOS系统已经被淘汰了，命令提示符也用的很少，
		斜杆和反斜杠在大多数情况下可以互换，没有影响。
		知道这个背景后，可以总结一下结论：

		（1）浏览器地址栏网址使用 斜杆/ ;
		（2）windows文件浏览器上使用 反斜杠\ ;
		（3）出现在html url() 属性中的路径，指定的路径是网络路径，所以必须用 斜杆/ ;
		（4）出现在普通字符串中的路径，如果代表的是windows文件路径，则使用 斜杆/ 和 反斜杠\ 是一样的；
		如果代表的是网络文件路径，则必须使用 斜杆/ ;

		斜杆/ 和 反斜杠\ 的区别基本上就是这些了，下面再讨论一下相对路径和绝对路径。
		./SRC/ 这样写表示，当前目录中的SRC文件夹；
		../SRC/ 这样写表示，当前目录的上一层目录中SRC文件夹；
		/SRC/ 这样写表示，项目根目录（可以只磁盘根目录，也可以指项目根目录，具体根据实际情况而定）

		！注意这里：但是由于 \ 也是转义字符的起始字符，
		所以， 路径中的 \ 通常需要使用 \\如果是 / 就不需要使用转义了
		如C中文件操作，c:\\kkk\\dd.txt c:/kkk/dd.txt一样
*/

	//判断一下文件是否打开成功
	if (fp == NULL)
	{
		perror("open file failed:");
		exit(0);
		//exit（0）;可以用return;代替
	};
	//读取文件
	while (1)
	{
		char ch = fgetc(fp);
		if(feof(fp))break;
		printf("%c", ch);
	}
	 
	fclose(fp);
}

//打开模式：“w”只写模式，文件不存在则创建，否则直接打开
void filewrite()
{
	FILE* fp = fopen("D:/data/2.txt", "w");		
	//在data文件夹里没有2.txt文件的话，就会自动在data文件夹中创建一个编码为ANSI的名为2.txt的文件
	
	if (fp == NULL)
	{
		perror("open file failed:");
		exit(0);
		//exit（0）;可以用return;代替
	};   
	char str[] = "大家好，我很不好"; //一个中文占两个字节，全角；一个英文字符占一个字节，半角
	//写文件
	for (int i = 0; i <	strlen(str); i++)
	{
		//char ch = fputc(i + 'A', fp);
		//printf("%c", ch);
		char ch = fputc(str[i], fp);
		printf("%c", ch);
	}
}

//打开模式：“w+”读写模式，文件存在则清空文件，否则创建文件 
void filereadwrite()
{
	char wstr[] = {
		"\
天王盖地虎，小鸡炖蘑菇\n\
春眠不觉晓\n\
处处蚊子咬\n\
来点敌敌畏\n\
不知死多少\n"
	};
	FILE* fp=fopen("d:/data/1.txt","w+");
	if (fp == NULL)
	{
		perror("open file failed:");
		return;
	}
	//先写文件
	int fpret = fputs(wstr, fp);
	printf("fputs return:%d\n", fpret);	//此时文件指针指向内容的末尾处

	//把文件位置指针移动到文件的开头
	rewind(fp);

	//读取文件

	while (!feof(fp))
	{
		char buf[128] = { 0 };	//最好先初始化
		char* restr = fgets(buf, sizeof(buf), fp);
		printf("%s", buf);
	}
}

//打开模式：“r”只读模式，文件必须存在，否则打开失败
void fileFormatread()
{
	FILE* fp = fopen("d:/data/student.txt", "r");
	if (fp == NULL)
	{
		perror("file open failed:");
		return;
	}
	//格式化读取
	/*
	第一种方法:
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

//打开模式：“w+”读写模式，文件存在则清空文件，否则创建文件 
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
