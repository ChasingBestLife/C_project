#include"DEFINITION.h"

/*
	进程运行前需要申请内存，内存足够且给它分配了才能运行
		cbl* 一个数组表示内存区域，
		* 内存大小由整型类型的全局变量表示，
		* 内存阻塞由标识符表示，也可以直接判断（内存-进程大小 ?< 0）
		* 进程被阻塞或者完成任务，内存要及时清除
*/
void setMem()
{
	system("cls");  //清屏操作
	
	/*初始化内存*/
	printf("————————————————————————————————————\n");
	printf("正在初始化内存...\n");
	printf("\n请输入内存的大小(K): \n");
	scanf("%d", &mem);
	while (mem < 128)
	{
		// 彩色文本
		printf("\033[35m");
		printf("内存过小，请重新输入: \n");
		printf("\033[0m");

		scanf("%d", &mem);
	}
	mem = mem * 1024;		// 总内存 K
	tp_mem = mem;

	m = (int*)malloc(sizeof(int) * mem);
	if (NULL == m)
	{
		exit(0);
	}
	memset(m, 0, sizeof(int) * mem);

	int size = 4 * 1024;				// 操作系统大小为4*1024 
	m[0] = 0 + size - 1;				// 第一位记录最后一位位置
	m[0 + 1] = 001;						// 第二位记录进程PID
	mem -= size;
	m[0 + size - 1] = -1;				// 最后一位为-1

	/*选择分区方式*/
	printf("******************************\n*请选择内存管理方式：\n");
	printf("*\t1: 固定分区\n");
	printf("*\t2: 可变分区\n");
	printf("******************************\n");
	scanf("%d", &memory_allocation_method);
	getchar();

	/*选择进程调度算法*/
	printf("******************************\n*请选择以下的一种进程调度算法:\n");
	printf("*\t1: 先来先服务调度FCFS\n");
	printf("*\t2: 非抢占式短进程优先调度SPF\n");
	printf("*\t3: 静态优先级调度PRIORITY\n");
	printf("*\t4: 高响应比调度HRRN\n");
	printf("******************************\n");
	scanf("%d", &alo);
	getchar();

	/*选择页面调度算法*/
	printf("******************************\n*请选择以下的一种进程调度算法:\n");
	printf("*\t1: 先进先出FIFO\n");
	printf("*\t2: 最近最少使用调度算法LRU\n");
	printf("*\t3: 最近最不常用调度算法LFU\n");
	printf("******************************\n");
	scanf("%d", &page_scheduling_alo);
	getchar();

	printf("\n————————————————————————————————————\n");
	printf("按下任意键继续...\n");
	getchar();
	system("cls");

}

// 分配内存
int memAllocation(PCB* p)
{
	/*生成进程内存*/
	int size = p->size;
	int tp_num = 0;				// 记录缺页次数

	if (mem - size < 0)
	{
		// 彩色文本
		printf("\033[31m");
		printf("内存不够大，进程无法加载!\n");
		printf("\033[0m");

		Look_DeQueue(run_queue, p);
		strcpy(p->state, "Ready");
		EnQueue(ready_queue, p);

		return 0;
	}
	else if (memory_allocation_method == 1)
	{
		// 固定相等大小分区分配内存
		int tp = 0;			// tp是用来记录空闲区域大小
		int add = 4096;		// 4096是因为操作系统占了4096
		int temp = 0;		// 临时指针

		// 这里与下面有所不同 i+=1024
		for (int i = 4096; tp<size && i<tp_mem; i += 1024)
		{
			if (m[i] == 0)  // 如果等于0，说明该内存没被利用
			{
				tp += 1024;

				if (tp < size)	// 如果一个分区1024不能满足，则再找一个
				{
					p->Address = add;					// 进程记录内存起始位置
					// 彩色文本
					printf("\033[36m");
					printf("进程%d需要多个分区存储!\n", p->PID);
					printf("\033[0m");
					// 寻找第二个分区
					for (int j = add + 1024; j < tp_mem; j += 1024)
					{
						if (m[j] == 0)  // 如果等于0，说明该内存没被利用
						{
							m[add] = j;							// 第一位记录第二个分区位置
							m[add + 1] = p->PID;				// 第二位记录进程PID

							i = j - 1024;
							add = j;							// add记录第二个分区位置
							tp_num++;
							
							break;
						}
					}
				}
			}
			else			// 不为0，说明被用
			{
				add = i+1024;
			}
		}
		// 最后一个分页的
		m[add] = add + 1024 - 1;			// 第一位记录最后一位位置
		m[add + 1] = p->PID;				// 第二位记录进程PID
		//p->Address = add;					// 进程记录内存起始位置
		mem -= size;
		m[add + 1024 - 1] = -1;				// 最后一位为-1，标记分区结束
		tp_num++;
	}
	else
	{
		// 动态分区分配内存
		int tp = 0;			// tp是用来记录空闲区域大小
		int add = 4096;		// 4096是因为操作系统占了4096


		///*输出m所有非0的位置*/
		//printf("\n\n\n\n");
		//for (int i = 4096;i < tp_mem; i++)
		//{
		//	if (m[i] != 0)printf("m[%d]: %d\n", i, m[i]);
		//}
		//printf("\n\n\n\n");
		///*----------------------*/


		for (int i = 4096; tp < size && i < tp_mem; i++)
		{
			if (m[i] == 0)  // 如果等于0，说明该内存没被利用
			{
				tp++;
			}
			else			// 不为0，说明被用，（第一位存储进程最后一位位置）直接令i = m[i] + 1，减少搜索时间
			{
				tp = 0;
				i = m[i] + 1;
				add = i;
			}
		}

		if (tp < size)
		{
			// 彩色文本
			printf("\033[31m");
			printf("外部碎片过多，进程无法直接插入内存!\n");
			printf("\033[0m");
			Look_DeQueue(run_queue, p);
			strcpy(p->state, "Ready");
			EnQueue(ready_queue, p);
			return 0;
		}

		m[add] = add + size - 1;			// 第一位记录最后一位位置
		m[add + 1] = p->PID;				// 第二位记录进程PID
		p->Address = add;					// 进程记录内存起始位置
		mem -= size;
		m[add + size - 1] = -1;				// 最后一位为-1
		tp_num++;
	}

	pageFaults += tp_num;					// 记录缺页总次数
	//printf("缺页总次数:%d\n", pageFaults);
	return 1;
}

void memClear(PCB* p)
{
	page_miss_flag = 1;
	//printf("淘汰的页面号为：%d\n", p->Address / 1024);
	int temp_page_pointer;			// 临时页面号数组指针

	int temp = m[p->Address];
	while (m[temp] != -1)
	{
		temp_page_pointer = 1;
		// 记录淘汰页面号
		page_die_num[page_pointer + temp_page_pointer] = m[temp] / 1024;
		temp_page_pointer++;

		int temp_temp = m[temp];
		m[temp+1] = 0;
		m[temp] = 0;
		temp = temp_temp;
	}
	temp_page_pointer = 0;
	page_die_num[page_pointer + temp_page_pointer] = m[p->Address] / 1024;
	m[p->Address] = 0;
	m[p->Address + 1] = 0;
	m[temp] = 0;
	p->Address = -1;
	//mem += sizeof(*p);
	mem += p->size;
}

void memCloseProcess()
{
	for (int i = run_queue->size; i > 0; i--)
	{
		PCB* p = DeQueue(run_queue);
		strcpy(p->state, "Stop");
		//mem += sizeof(*p);
		memClear(p);

		// 同步信息
		for (int k = 0; k < PRODUCT + CONSUME; k++)
		{
			if (pro[k].flag == p->flag && pro[k].PID == p->PID)
			{
				CopyProcess(&pro[k], p);
				break;
			}
		}
	}

	free(m);
}