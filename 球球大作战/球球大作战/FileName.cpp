#include<stdio.h>
#include"Graphics.h"	//����ͼ�ο�ͷ�ļ�
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<mmsystem.h>	//��������
#pragma comment(lib, "winmm.lib")


/*

	�������ս
	���ڣ���ͼ��EasyXͼ�ο⣩�����˹����ϣ����棩���ϰ���ʳ�Բ�����꣬�뾶����ɫ���Ƿ���ڵı�־����

*/


#define FOOD_NUM 200		// ʳ������
#define AI_NUM 10			// �˹���������
#define WIDTH 1024
#define HEIGHT 640


typedef struct Ball		// С��ṹ����ң�ʳ��˹�����
{
	int x;
	int y;
	int r;			// ʳ����С��İ뾶
	DWORD color;	// С����ɫ		//DWORD �� double word��ÿ��wordΪ2���ֽڣ�dword����4�����������������ַ���൱��unsigned long
	bool flag;		// �Ƿ����
}Ball;

int score = 0;			// ����
Ball food[FOOD_NUM];	// ʳ��
Ball player;			// ���
Ball ai[AI_NUM];		// �˹�����


// ��Ϸ��ʼ��
void GameInit()			
{
	// ��������
	// mciSendString("open ./BallBGM.mp3 alias BGM", 0, 0, 0);
	
	// ������������� ʱ�����ڲ��ϱ仯��
	srand((unsigned)time(NULL));
	
	// �ҵ�ÿһ��Ԫ��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		food[i].x = rand() % WIDTH;		// ˮƽλ���� 0-1024 ֮��
		food[i].y = rand() % HEIGHT;	// ��ֱλ���� 0-640 ֮��
		food[i].flag = true;			// �տ�ʼʳ�ﶼ�Ǵ��ڵģ�û�б��Ե�
		food[i].r = rand() % 6 + 1;		// ʳ��뾶��С�� 1-7 ֮��
		food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	// ��ʼ���������
	player.x = rand() % WIDTH;
	player.y = rand() % HEIGHT;
	player.r = 13;					// ֻҪ������ʳ��������
	player.flag = true;
	player.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	
	// ��ʼ��AI
	for (int i = 0; i < AI_NUM; i++)
	{
		ai[i].x = rand() % WIDTH;		
		ai[i].y = rand() % HEIGHT;	
		ai[i].flag = true;			
		ai[i].r = rand() % 13 + 7;		
		ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}


// ����
void GameDraw()
{
	// ��ֹ����
	BeginBatchDraw();	// ����������ڿ�ʼ������ͼ��ִ�к��κλ�ͼ����������ʱ���������ͼ�����ϣ�ֱ��ִ�� FlushBatchDraw �� EndBatchDraw �Ž�֮ǰ�Ļ�ͼ�����
	setbkcolor(WHITE);
	cleardevice();		// ����
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag)
		{
			solidcircle(food[i].x, food[i].y, food[i].r);	// ��һ�����Բ
			setfillcolor(food[i].color);			// ���������ɫ
		}
		else
		{
			food[i].x = rand() % WIDTH;		// ˮƽλ���� 0-1024 ֮��
			food[i].y = rand() % HEIGHT;	// ��ֱλ���� 0-640 ֮��
			food[i].flag = true;			// �տ�ʼʳ�ﶼ�Ǵ��ڵģ�û�б��Ե�
			food[i].r = rand() % 6 + 1;		// ʳ��뾶��С�� 1-7 ֮��
			food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		}
	}

	// �������
	solidcircle(player.x, player.y, player.r);	// ��һ�����Բ
	setfillcolor(player.color);					// ���������ɫ		// �����ɸĳɹ̶���ɫ
	settextcolor(GREEN);						// ���������ɫ
	settextstyle(30, 0, _T("����"));
	setbkmode(0);								// �������ֱ�����ɫ͸��
	outtextxy(player.x, player.y, _T("Jack"));	//�����
	
	// �������
	settextcolor(BLACK);
	// ����Ӧ�ַ���
	TCHAR str[30];
	_stprintf_s(str, "������" _T("%d"), score);			// ��ʽ���ַ���
	outtextxy(20, 20, str);

	// ����AI
	for (int i = 0; i < AI_NUM; i++)
	{
		if (ai[i].flag)
		{
			solidcircle(ai[i].x, ai[i].y, ai[i].r);		// ��һ��Բ
			setfillcolor(ai[i].color);					// ���������ɫ
		}
	}
	EndBatchDraw();
}


// ����Ҷ�����
void keyControl(int speed)
{
	// ��ȡ������Ϣ����������һ���� _getch();	GetAsyncKeyState() Windowsϵͳ����
	if ((GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) && player.y >= 0)		// �����ϼ�ͷ�ͻ�������speed�ٶ��ƶ�
	{
		player.y -= speed;
	}
	if ((GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) && player.y <= HEIGHT)	// �����¼�ͷ�ͻ�������speed�ٶ��ƶ�
	{
		player.y += speed;
	}
	if ((GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) && player.x >= 0)		// �������ͷ�ͻ�������speed�ٶ��ƶ�
	{
		player.x -= speed;
	}
	if ((GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)) && player.x <= WIDTH)		// �����Ҽ�ͷ�ͻ�������speed�ٶ��ƶ�
	{
		player.x += speed;
	}
}


// ������֮�����
double distance(Ball a, Ball b)
{
	return sqrt((double)(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


// ��ʳ��
void eatFood()
{
	// ��ҳ�ʳ��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag && distance(food[i], player) <= player.r)			// ���ʳ�������ʳ������ҵľ���С�������İ뾶
		{
			food[i].flag = false;											// OMG�����Ե���
			player.r += food[i].r / 4;										// ���԰��㷨���Ե�ʳ����С��뾶����ʳ��С��뾶��1/4
			score++;	// �ӷ�
		}
	}

	/*	
	* �����⴮�����������
	// ai��ʳ��
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag && distance(food[i], ai[i]) <= ai[i].r)
		if (food[i].flag && distance(food[i], ai[i]) <= ai[i].r)
		{
			food[i].flag = false;											// OMG�����Ե���
			ai[i].r += food[i].r / 4;										// ���԰��㷨���Ե�ʳ����С��뾶����ʳ��С��뾶��1/4
		}
	}
	*/

}


// AI�ƶ�
// С���ƶ��е����
void aiMove()
{
	for (int i = 0; i < AI_NUM; i++)
	{
		if (ai[i].flag)
		{
			ai[i].x += rand() % 3 - 1;		// AIС��ˮƽλ������ƶ�
			ai[i].y += rand() % 3 - 1;		// aIС����ֱλ������ƶ�
		}
	}
}


// aiС��Ҳ���Ա��Ե�
void aiFood()
{
	for (int i = 0; i < AI_NUM; i++)
	{
		if (ai[i].flag && distance(ai[i], player) <= player.r)
		{
			ai[i].flag = false;
			player.r += ai[i].r / 4;
			score++;
		}
	}
}


// ���Ҳ���Ա�ai�Ե�
void playerFood()
{
	for (int i = 0; i < AI_NUM; i++)
	{
		if (ai[i].r > player.r && distance(player, ai[i]) <= ai[i].r)
		{
			player.flag = false;
			ai[i].r += player.r / 4;
			score--;
			printf("You've been eaten.Game over!");
			return;
		}
	}
}


// ��Ҳ��Զ������ݣ�Խ���ݵ�Խ��,�Զ������đ��
//void playerslim()
//{
//	for (int i = 0; i < ai_num; i++)
//	{
//		if (ai[i].r > player.r && distance(player, ai[i]) <= ai[i].r)
//		{
//			player.flag = false;
//			ai[i].r += player.r / 4;
//			score--;
//			printf("you've been eaten.game over!");
//		}
//	}
//}


int main(int argc, char *agv[])
{
	initgraph(WIDTH, HEIGHT);
	GameInit();
	while (1)
	{
		keyControl(1);
		GameDraw();
		eatFood();
		aiFood();
		playerFood();
		aiMove();
	}

	system("pause");
	getchar();
	return 0;
}