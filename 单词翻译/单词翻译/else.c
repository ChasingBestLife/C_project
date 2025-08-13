#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int number;           //ȫ�ֱ�����������



void menu();          //������
void translation_e(); //Ӣ�뺺
void translation_c(); //����Ӣ
void view();          //�鿴����
void remove_();       //ɾ������
void add();           //���ӵ���

void color(short x); //�ı�������ɫ
void read();          //���ļ��ж�ȡ��Ϣ
void save();         //���浥�ʵ��ļ��ﺯ��

void back_t_e();      //Ӣ�뺺 ���ؽ���
void back_t_c();      //����Ӣ ���ؽ���
void back_v();        //�鿴���� ���ؽ���
void back_r();        //ɾ������ ���ؽ���
void back_a();        //���ӵ��� ���ؽ���






struct words {

    char english[30];
    char chinese[128];

}word[100];

int main()
{
    menu();
    return 0;
}

void menu()//������
{
    read();
    int l;
    printf("\t��ӭʹ��СϫӢ���ʵ�\t\n");
    printf("\t     1.Ӣ�뺺 \t\n");
    printf("\t     2.����Ӣ \t\n");
    printf("\t     3.�鿴���� \t\n");
    printf("\t     4.ɾ������ \t\n");
    printf("\t     5.���ӵ��� \t\n");
    printf("\t     6.ˢ��   \n");
    printf("\t     7.�˳�   \n");
    printf("=================================\n");
    printf("������ѡ��ĵ�½��: ");
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
        printf("��л����ʹ��,���˳���\n");
        exit(0);
    default:
        color(772);
        printf("[�������]��3�������������Ч����!\n");
        // Sleep(3000);
        color(7);
        system("cls");
        menu();
        break;
    }
}

void color(short x) //�ı�������ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void translation_e() //Ӣ�뺺
{
    char eng[30] = "\0";
    int i;
    printf("���뵥��: ");
    getchar();//ȥ���س�
    scanf("%s", eng);
    for (i = 0; i < number; i++)
    {
        if (strcmp(eng, word[i].english) == 0)
        {
            printf("\n�õ��ʺ���:  ");
            printf("%s\n", word[i].chinese);
            break;
        }
    }
    if (i == number)
    {
        color(772);
        printf("\n[����]δ�ҵ��õ���!\n");
        color(7);
    }
    back_t_e();
}

void back_t_e()  //Ӣ�뺺 ���ؽ���
{
    int l;
    printf("\n1.����");
    printf("\n2.����");
    printf("\n=========================");
    printf("\n������Ҫִ�еĲ���: ");
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
        printf("[�������]��3�������������Ч����!\n");
        // Sleep(3000);
        color(7);
        back_t_e();
        break;
    }
}

void translation_c() //����Ӣ
{
    char chi[128];
    int i;
    printf("��������: ");
    scanf("%s", chi);
    for (i = 0; i < number; i++)
    {
        if (strcmp(chi, word[i].chinese) == 0)
        {
            printf("\n�õ���Ϊ:  ");

            printf("%s\n", word[i].english);
            break;
        }
    }
    if (i == number)
    {
        color(772);
        printf("\n[����]δ�ҵ��õ���!\n");
        color(7);
    }
    back_t_c();
}

void back_t_c()  //����Ӣ ���ؽ���
{
    int l;
    printf("\n1.����");
    printf("\n2.����");
    printf("\n=========================");
    printf("\n������Ҫִ�еĲ���: ");
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
        printf("[�������]��3�������������Ч����!\n");
        // Sleep(3000);
        color(7);
        back_t_c();
        break;
    }
}

void save()  //���浥�ʵ��ļ��ﺯ��
{
    FILE* fp;
    int i, ret;
    fp = fopen("C:\\Users\\Cbl04\\Desktop\\ѧϰ\\1.���\\1.C���Ի����﷨_fited\\���ʷ���\\����.txt", "w");
    if (fp == NULL)
    {
        color(772);
        printf("\n[����]�ļ���ʧ��\n");
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
        printf("\n[����]�ļ�д��ʧ��\n");
        color(7);
    }
    else
    {
        color(2);
        printf("\n[tip]�ļ�д��ɹ�\n");
        color(7);

    }
    fclose(fp);		//�ر��ļ�ָ��
}

void read()//���ļ��ж�ȡ��Ϣ
{
    FILE* fp;
    int i;
    fp = fopen("C:\\Users\\Cbl04\\Desktop\\ѧϰ\\1.���\\1.C���Ի����﷨_fited\\���ʷ���\\����.txt", "r");
    if (fp == NULL)
    {
        color(772);
        printf("[����]�ļ���ʧ��\n");
        color(7);
    }
    else {
        color(2);
        printf("[tip]�ļ���ȡ�ɹ�\n");
        color(7);
        fscanf(fp, "%d\n", &number);
        for (i = 0; i < number; i++)
        {
            fscanf(fp, "%s %s\n", word[i].english, word[i].chinese);
        }
    }

    fclose(fp);
}

void add()    //���ӵ���
{
    int i = number, j, flag, m;
    printf("�����ӵĵ�����:");
    scanf("%d", &m);
    getchar();
    if (m > 0) {
        do
        {
            flag = 1;
            printf("\n�������%d������:\n", i + 1);
            while (flag)
            {
                flag = 0;

                printf("Ӣ��:");
                scanf("%s", word[i].english);
                for (j = 0; j < i; j++) {
                    if (strcmp(word[i].english, word[j].english) == 0) {
                        color(772);
                        printf("[����]�Ѵ��ڸõ���,����������!\n");
                        color(7);
                        flag = 1;
                        break;
                    }
                }
            }
            getchar();

            printf("����: ");
            scanf("%s", word[i].chinese);

            if (0 == flag) {
                i++;
            }
        } while (i < number + m);

        number += m;
        color(2);
        printf("[�ɹ�]���������ϣ�����");
        color(7);
        save();
    }
    else {
        color(772);
        printf("[�������]��3�������������Ч����!\n");
        // Sleep(3000);
        system("cls");
        color(7);
        add();
    }
    back_a();
}

void back_a()  //���ӵ��� ���ؽ���
{
    int l;
    printf("\n1.����");
    printf("\n2.����");
    printf("\n=========================");
    printf("\n������Ҫִ�еĲ���: ");
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
        printf("[�������]��3�������������Ч����!\n");
        // Sleep(3000);
        color(7);
        back_a();
        break;
    }
}


void view()  //�鿴����
{
    int i;
    printf(" Ӣ��\t\t\t ����\n");
    printf(" --------------------------------------------------------------------------\n");
    for (i = 0; i < number; i++)
    {
        printf(" %-25s%s\n", word[i].english, word[i].chinese);
    }
    printf(" --------------------------------------------------------------------------\n");
    back_v();
}

void back_v()  //�鿴���� ���ؽ���
{
    int l;
    printf("1.����");
    printf("\n2.����");
    printf("\n=========================");
    printf("\n������Ҫִ�еĲ���: ");
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
        printf("[�������]��3�������������Ч����!\n");
        // Sleep(3000);
        color(7);
        back_v();
        break;
    }
}

void remove_() //ɾ������
{
    int a;
    char eng1[30];
    printf("�����뵥�ʣ�");
    scanf("%s", eng1);
    int i, j;
    for (i = 0; i < number; i++)
    {
        if (strcmp(word[i].english, eng1) == 0)
        {
            printf("�㽫Ҫɾ���õ���\n\n");
            printf(" --------------------------------------------------------------------------\n");
            printf(" %-25s%s\n", word[i].english, word[i].chinese);
            printf(" --------------------------------------------------------------------------\n");
            printf("\n1.ȷ��ɾ��");
            printf("\n2.ȡ��ɾ��");
            printf("\n=========================");
            printf("\n�����룺");
            scanf("%d", &a);
            if (a == 1)
            {
                for (j = i; j < number - 1; j++) {
                    word[j] = word[j + 1];
                }
                color(2);
                printf("\n[tip]ɾ���ɹ���");
                color(7);
                number--;
                save();
                break;
            }
            else
            {
                color(2);
                printf("\n[tip]��ȡ������!");
                color(7);
                break;
            }
        }
    }
    if (i == number)
    {
        color(772);
        printf("\n[����]δ�ҵ��õ���!!!");
        color(7);
    }
    back_r();
}

void back_r() //ɾ������ ���ؽ���
{
    int l;
    printf("\n1.����");
    printf("\n2.����");
    printf("\n=========================");
    printf("\n������Ҫִ�еĲ���: ");
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
        printf("[�������]��3�������������Ч����!\n");
        // Sleep(3000);
        color(7);
        back_r();
        break;
    }
}
