#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int number;           //全局变量单词总数



void menu();          //主界面
void translation_e(); //英译汉
void translation_c(); //汉译英
void view();          //查看单词
void remove_();       //删除单词
void add();           //增加单词

void color(short x); //改变字体颜色
void read();          //从文件中读取信息
void save();         //保存单词到文件里函数

void back_t_e();      //英译汉 返回界面
void back_t_c();      //汉译英 返回界面
void back_v();        //查看单词 返回界面
void back_r();        //删除单词 返回界面
void back_a();        //增加单词 返回界面






struct words {

    char english[30];
    char chinese[128];

}word[100];

int main()
{
    menu();
    return 0;
}

void menu()//主界面
{
    read();
    int l;
    printf("\t欢迎使用小汐英汉词典\t\n");
    printf("\t     1.英译汉 \t\n");
    printf("\t     2.汉译英 \t\n");
    printf("\t     3.查看单词 \t\n");
    printf("\t     4.删除单词 \t\n");
    printf("\t     5.增加单词 \t\n");
    printf("\t     6.刷新   \n");
    printf("\t     7.退出   \n");
    printf("=================================\n");
    printf("请输入选择的登陆端: ");
    scanf("%d", &l);

    switch (l) {
    case 1:
        system("cls");
        translation_e();
        break;
    case 2:
        system("cls");
        translation_c();
        break;
    case 3:
        system("cls");
        view();
        break;
    case 4:
        system("cls");
        remove_();
        break;
    case 5:
        system("cls");
        add();
        break;
    case 6:
        system("cls");
        menu();
        break;
    case 7:
        printf("感谢您的使用,已退出！\n");
        exit(0);
    default:
        color(772);
        printf("[输入错误]请3秒后重新输入有效数字!\n");
        // Sleep(3000);
        color(7);
        system("cls");
        menu();
        break;
    }
}

void color(short x) //改变字体颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void translation_e() //英译汉
{
    char eng[30] = "\0";
    int i;
    printf("输入单词: ");
    getchar();//去掉回车
    scanf("%s", eng);
    for (i = 0; i < number; i++)
    {
        if (strcmp(eng, word[i].english) == 0)
        {
            printf("\n该单词含义:  ");
            printf("%s\n", word[i].chinese);
            break;
        }
    }
    if (i == number)
    {
        color(772);
        printf("\n[错误]未找到该单词!\n");
        color(7);
    }
    back_t_e();
}

void back_t_e()  //英译汉 返回界面
{
    int l;
    printf("\n1.继续");
    printf("\n2.返回");
    printf("\n=========================");
    printf("\n请输入要执行的操作: ");
    scanf("%d", &l);
    switch (l) {
    case 1:
        system("cls");
        translation_e();
        break;
    case 2:
        system("cls");
        menu();
        break;
    default:
        color(772);
        printf("[输入错误]请3秒后重新输入有效数字!\n");
        // Sleep(3000);
        color(7);
        back_t_e();
        break;
    }
}

void translation_c() //汉译英
{
    char chi[128];
    int i;
    printf("输入中文: ");
    scanf("%s", chi);
    for (i = 0; i < number; i++)
    {
        if (strcmp(chi, word[i].chinese) == 0)
        {
            printf("\n该单词为:  ");

            printf("%s\n", word[i].english);
            break;
        }
    }
    if (i == number)
    {
        color(772);
        printf("\n[错误]未找到该单词!\n");
        color(7);
    }
    back_t_c();
}

void back_t_c()  //汉译英 返回界面
{
    int l;
    printf("\n1.继续");
    printf("\n2.返回");
    printf("\n=========================");
    printf("\n请输入要执行的操作: ");
    scanf("%d", &l);
    switch (l) {
    case 1:
        system("cls");
        translation_c();
        break;
    case 2:
        system("cls");
        menu();
        break;
    default:
        color(772);
        printf("[输入错误]请3秒后重新输入有效数字!\n");
        // Sleep(3000);
        color(7);
        back_t_c();
        break;
    }
}

void save()  //保存单词到文件里函数
{
    FILE* fp;
    int i, ret;
    fp = fopen("C:\\Users\\Cbl04\\Desktop\\学习\\1.编程\\1.C语言基础语法_fited\\单词翻译\\单词.txt", "w");
    if (fp == NULL)
    {
        color(772);
        printf("\n[警告]文件打开失败\n");
        color(7);
    }
    fprintf(fp, "%d\n", number);

    for (i = 0; i < number; i++)
    {

        ret = fprintf(fp, "%s %s\n", word[i].english, word[i].chinese);
    }

    if (ret < 0)
    {
        color(772);
        printf("\n[错误]文件写入失败\n");
        color(7);
    }
    else
    {
        color(2);
        printf("\n[tip]文件写入成功\n");
        color(7);

    }
    fclose(fp);		//关闭文件指针
}

void read()//从文件中读取信息
{
    FILE* fp;
    int i;
    fp = fopen("C:\\Users\\Cbl04\\Desktop\\学习\\1.编程\\1.C语言基础语法_fited\\单词翻译\\单词.txt", "r");
    if (fp == NULL)
    {
        color(772);
        printf("[警告]文件打开失败\n");
        color(7);
    }
    else {
        color(2);
        printf("[tip]文件读取成功\n");
        color(7);
        fscanf(fp, "%d\n", &number);
        for (i = 0; i < number; i++)
        {
            fscanf(fp, "%s %s\n", word[i].english, word[i].chinese);
        }
    }

    fclose(fp);
}

void add()    //增加单词
{
    int i = number, j, flag, m;
    printf("待增加的单词数:");
    scanf("%d", &m);
    getchar();
    if (m > 0) {
        do
        {
            flag = 1;
            printf("\n请输入第%d个单词:\n", i + 1);
            while (flag)
            {
                flag = 0;

                printf("英文:");
                scanf("%s", word[i].english);
                for (j = 0; j < i; j++) {
                    if (strcmp(word[i].english, word[j].english) == 0) {
                        color(772);
                        printf("[错误]已存在该单词,请重新输入!\n");
                        color(7);
                        flag = 1;
                        break;
                    }
                }
            }
            getchar();

            printf("中文: ");
            scanf("%s", word[i].chinese);

            if (0 == flag) {
                i++;
            }
        } while (i < number + m);

        number += m;
        color(2);
        printf("[成功]单词添加完毕！！！");
        color(7);
        save();
    }
    else {
        color(772);
        printf("[输入错误]请3秒后重新输入有效数字!\n");
        // Sleep(3000);
        system("cls");
        color(7);
        add();
    }
    back_a();
}

void back_a()  //增加单词 返回界面
{
    int l;
    printf("\n1.继续");
    printf("\n2.返回");
    printf("\n=========================");
    printf("\n请输入要执行的操作: ");
    scanf("%d", &l);
    switch (l) {
    case 1:
        system("cls");
        add();
        break;
    case 2:
        system("cls");
        menu();
        break;
    default:
        color(772);
        printf("[输入错误]请3秒后重新输入有效数字!\n");
        // Sleep(3000);
        color(7);
        back_a();
        break;
    }
}


void view()  //查看单词
{
    int i;
    printf(" 英文\t\t\t 中文\n");
    printf(" --------------------------------------------------------------------------\n");
    for (i = 0; i < number; i++)
    {
        printf(" %-25s%s\n", word[i].english, word[i].chinese);
    }
    printf(" --------------------------------------------------------------------------\n");
    back_v();
}

void back_v()  //查看单词 返回界面
{
    int l;
    printf("1.继续");
    printf("\n2.返回");
    printf("\n=========================");
    printf("\n请输入要执行的操作: ");
    scanf("%d", &l);
    switch (l) {
    case 1:
        system("cls");
        view();
        break;
    case 2:
        system("cls");
        menu();
        break;
    default:
        color(772);
        printf("[输入错误]请3秒后重新输入有效数字!\n");
        // Sleep(3000);
        color(7);
        back_v();
        break;
    }
}

void remove_() //删除单词
{
    int a;
    char eng1[30];
    printf("请输入单词：");
    scanf("%s", eng1);
    int i, j;
    for (i = 0; i < number; i++)
    {
        if (strcmp(word[i].english, eng1) == 0)
        {
            printf("你将要删除该单词\n\n");
            printf(" --------------------------------------------------------------------------\n");
            printf(" %-25s%s\n", word[i].english, word[i].chinese);
            printf(" --------------------------------------------------------------------------\n");
            printf("\n1.确认删除");
            printf("\n2.取消删除");
            printf("\n=========================");
            printf("\n请输入：");
            scanf("%d", &a);
            if (a == 1)
            {
                for (j = i; j < number - 1; j++) {
                    word[j] = word[j + 1];
                }
                color(2);
                printf("\n[tip]删除成功！");
                color(7);
                number--;
                save();
                break;
            }
            else
            {
                color(2);
                printf("\n[tip]已取消操作!");
                color(7);
                break;
            }
        }
    }
    if (i == number)
    {
        color(772);
        printf("\n[错误]未找到该单词!!!");
        color(7);
    }
    back_r();
}

void back_r() //删除单词 返回界面
{
    int l;
    printf("\n1.继续");
    printf("\n2.返回");
    printf("\n=========================");
    printf("\n请输入要执行的操作: ");
    scanf("%d", &l);
    switch (l) {
    case 1:
        system("cls");
        remove_();
        break;
    case 2:
        system("cls");
        menu();
        break;
    default:
        color(772);
        printf("[输入错误]请3秒后重新输入有效数字!\n");
        // Sleep(3000);
        color(7);
        back_r();
        break;
    }
}
