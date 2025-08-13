#include<stdio.h>
#include"Graphics.h"	//包含图形库头文件
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<mmsystem.h>	//播放音乐
#pragma comment(lib, "winmm.lib")


/*

	球球大作战
	窗口，画图（EasyX图形库），球，人工智障（陪玩），障碍，食物（圆（坐标，半径，颜色，是否存在的标志））

*/


#define FOOD_NUM 200		// 食物数量
#define AI_NUM 10			// 人工智障数量
#define WIDTH 1024
#define HEIGHT 640


typedef struct Ball		// 小球结构，玩家，食物，人工智障
{
	int x;
	int y;
	int r;			// 食物、玩家小球的半径
	DWORD color;	// 小球颜色		//DWORD 是 double word，每个word为2个字节，dword就是4个，经常用来保存地址，相当于unsigned long
	bool flag;		// 是否存在
}Ball;

int score = 0;			// 分数
Ball food[FOOD_NUM];	// 食物
Ball player;			// 玩家
Ball ai[AI_NUM];		// 人工智障


// 游戏初始化
void GameInit()			
{
	// 播放音乐
	// mciSendString("open ./BallBGM.mp3 alias BGM", 0, 0, 0);
	
	// 设置随机数种子 时间是在不断变化的
	srand((unsigned)time(NULL));
	
	// 找到每一个元素
	for (int i = 0; i < FOOD_NUM; i++)
	{
		food[i].x = rand() % WIDTH;		// 水平位置在 0-1024 之间
		food[i].y = rand() % HEIGHT;	// 竖直位置在 0-640 之间
		food[i].flag = true;			// 刚开始食物都是存在的，没有被吃掉
		food[i].r = rand() % 6 + 1;		// 食物半径大小在 1-7 之间
		food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	// 初始化玩家数据
	player.x = rand() % WIDTH;
	player.y = rand() % HEIGHT;
	player.r = 13;					// 只要比最大的食物大就行了
	player.flag = true;
	player.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	
	// 初始化AI
	for (int i = 0; i < AI_NUM; i++)
	{
		ai[i].x = rand() % WIDTH;		
		ai[i].y = rand() % HEIGHT;	
		ai[i].flag = true;			
		ai[i].r = rand() % 13 + 7;		
		ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}


// 绘制
void GameDraw()
{
	// 防止闪屏
	BeginBatchDraw();	// 这个函数用于开始批量绘图。执行后，任何绘图操作都将暂时不输出到绘图窗口上，直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出。
	setbkcolor(WHITE);
	cleardevice();		// 清屏
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag)
		{
			solidcircle(food[i].x, food[i].y, food[i].r);	// 画一个填充圆
			setfillcolor(food[i].color);			// 设置填充颜色
		}
		else
		{
			food[i].x = rand() % WIDTH;		// 水平位置在 0-1024 之间
			food[i].y = rand() % HEIGHT;	// 竖直位置在 0-640 之间
			food[i].flag = true;			// 刚开始食物都是存在的，没有被吃掉
			food[i].r = rand() % 6 + 1;		// 食物半径大小在 1-7 之间
			food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		}
	}

	// 绘制玩家
	solidcircle(player.x, player.y, player.r);	// 画一个填充圆
	setfillcolor(player.color);					// 设置填充颜色		// 后续可改成固定颜色
	settextcolor(GREEN);						// 玩家名字颜色
	settextstyle(30, 0, _T("黑体"));
	setbkmode(0);								// 设置文字背景颜色透明
	outtextxy(player.x, player.y, _T("Jack"));	//玩家名
	
	// 输出分数
	settextcolor(BLACK);
	// 自适应字符集
	TCHAR str[30];
	_stprintf_s(str, "分数：" _T("%d"), score);			// 格式化字符串
	outtextxy(20, 20, str);

	// 绘制AI
	for (int i = 0; i < AI_NUM; i++)
	{
		if (ai[i].flag)
		{
			solidcircle(ai[i].x, ai[i].y, ai[i].r);		// 画一个圆
			setfillcolor(ai[i].color);					// 设置填充颜色
		}
	}
	EndBatchDraw();
}


// 让玩家动起来
void keyControl(int speed)
{
	// 获取键盘消息，按的是哪一个键 _getch();	GetAsyncKeyState() Windows系统函数
	if ((GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) && player.y >= 0)		// 按了上箭头就会向上以speed速度移动
	{
		player.y -= speed;
	}
	if ((GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) && player.y <= HEIGHT)	// 按了下箭头就会向下以speed速度移动
	{
		player.y += speed;
	}
	if ((GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) && player.x >= 0)		// 按了左箭头就会向左以speed速度移动
	{
		player.x -= speed;
	}
	if ((GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)) && player.x <= WIDTH)		// 按了右箭头就会向右以speed速度移动
	{
		player.x += speed;
	}
}


// 求两点之间距离
double distance(Ball a, Ball b)
{
	return sqrt((double)(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


// 吃食物
void eatFood()
{
	// 玩家吃食物
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag && distance(food[i], player) <= player.r)			// 如果食物存在且食物与玩家的距离小于玩家球的半径
		{
			food[i].flag = false;											// OMG，被吃掉了
			player.r += food[i].r / 4;										// 简略版算法，吃掉食物，玩家小球半径增加食物小球半径的1/4
			score++;	// 加分
		}
	}

	/*	
	* 加入这串代码就闪退了
	// ai吃食物
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag && distance(food[i], ai[i]) <= ai[i].r)
		if (food[i].flag && distance(food[i], ai[i]) <= ai[i].r)
		{
			food[i].flag = false;											// OMG，被吃掉了
			ai[i].r += food[i].r / 4;										// 简略版算法，吃掉食物，玩家小球半径增加食物小球半径的1/4
		}
	}
	*/

}


// AI移动
// 小球移动有点诡异
void aiMove()
{
	for (int i = 0; i < AI_NUM; i++)
	{
		if (ai[i].flag)
		{
			ai[i].x += rand() % 3 - 1;		// AI小球水平位置随便移动
			ai[i].y += rand() % 3 - 1;		// aI小球竖直位置随便移动
		}
	}
}


// ai小球也可以被吃掉
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


// 玩家也可以被ai吃掉
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


// 玩家不吃东西会瘦，越大瘦得越快,吃东西长的戝快
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