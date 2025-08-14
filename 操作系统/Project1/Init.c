#include"DEFINITION.h"

// 初始化就绪、阻塞、运行队列
void QueueInit(PCBQueue** q)
{
	*q = (PCBQueue*)malloc(sizeof(PCBQueue));
	(*q)->first_pro = (PCB*)malloc(sizeof(PCB));
	(*q)->first_pro->next = NULL;
	(*q)->last_pro = (*q)->first_pro;
	(*q)->size = 0;
}

// 初始化信号量 
void SemaphoreInit()
{
	empty = (Semaphore*)malloc(sizeof(Semaphore));
	filled = (Semaphore*)malloc(sizeof(Semaphore));
	rw_mux = (Semaphore*)malloc(sizeof(Semaphore));

	strcpy(empty->name, "empty");
	empty->num = BUF;
	empty->flag = 0;

	strcpy(filled->name, "filled");
	filled->num = 0;
	filled->flag = 1;

	strcpy(rw_mux->name, "rw_mux");
	rw_mux->num = 1;
	rw_mux->flag = 2;
}

// 磁盘初始化
void DiskInit()
{

}

// 初始化 
void Init()
{
	// 初始化四个队列
	QueueInit(&ready_queue);
	QueueInit(&block_queue);
	QueueInit(&product_block_queue);
	QueueInit(&consume_block_queue);
	QueueInit(&run_queue);

	// 初始化信号量 
	SemaphoreInit();

	// 内存初始化
	setMem();

	// 磁盘初始化
	DiskInit();

	/*初始化生产者和消费者进程*/
	printf("————————————————————————————————————\n");
	printf("正在初始化生产者和消费者进程...\n");
	printf("\n请输入生产者个数: ");
	scanf("%d", &PRODUCT);
	getchar();
	printf("请输入消费者数量个数: ");
	scanf("%d", &CONSUME);
	getchar();
	/*printf("请输入进程最大并行数量(<=3): ");
	scanf("%d", &PROCESS);*/

	// 初始化生产者进程 
	printf("******************************\n*开始初始化生产者和消费者进程...\n");
	for (int i = 0; i < PRODUCT; i++)
	{
		// 初始化随机数生成器
		srand(time(NULL));
		// 生成一个129 到 1024之间的随机数
		int size = rand() % 1920 + 1024;

		strcpy(pro[i].name, "Producer");
		pro[i].PID = i + 1;
		strcpy(pro[i].state, "Ready");
		strcpy(pro[i].reason, "Null");
		pro[i].start_time = 0;
		pro[i].end_time = 0;
		pro[i].zztime = -1;
		pro[i].breakp = 0;
		pro[i].next = NULL;
		pro[i].flag = 0;
		pro[i].Address = -1;
		pro[i].size = size;
		pro[i].usage_count = 0;
	}
	// 初始化消费者进程 
	for (int i = PRODUCT; i < PRODUCT + CONSUME; i++)
	{
		// 初始化随机数生成器
		srand(time(NULL));
		// 生成一个129 到 1024之间的随机数
		int size = rand() % 1920 + 129;

		strcpy(pro[i].name, "Consume");
		pro[i].PID = i + 1;
		strcpy(pro[i].state, "Ready");
		strcpy(pro[i].reason, "Null");
		pro[i].start_time = 0;
		pro[i].end_time = 0;
		pro[i].zztime = -1;
		pro[i].breakp = 0;
		pro[i].next = NULL;
		pro[i].flag = 1;
		pro[i].Address = -1;
		pro[i].size = size;
		pro[i].usage_count = 0;
	}

	// 用户输入进程到达时间 
	printf("*请依次输入进程的:到达时间\t运行时间\t优先级\n");
	for (int i = 0; i < PRODUCT + CONSUME; i++)
	{
		printf("*****************\n*%s %d\t  ", pro[i].name, pro[i].PID);
		if (scanf("%d %d %d", &pro[i].arrive_time, &pro[i].running_time, &pro[i].priority) != 3)
		{
			printf("输入错误，请重新输入正确的整数值。\n");
		}
		getchar();
		pro[i].start_time = pro[i].arrive_time;

		EnQueue(ready_queue, &pro[i]);
		printf("*****************\n\n");
	}

	// 就绪队列重新排序 
	Alogorithm();

	pc = 0;
	con_cnt = 0; //消费计数器

	printf("\n————————————————————————————————————\n");
	printf("按下任意键继续...\n");
	getchar();
	system("cls");
}