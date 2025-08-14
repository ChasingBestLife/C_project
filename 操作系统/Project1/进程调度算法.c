#include"DEFINITION.h"

void Alogorithm()
{
	ReorderQueue(ready_queue);
}

// 根据到达时间进行排序 
void FCFS(PCB** arr, int n)
{
	PCB* tpp;

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			if (arr[j]->start_time > arr[j + 1]->start_time)
			{
				tpp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tpp;
			}
		}
	}
}

// 按照运行时间排序
void SPF(PCB** arr, int n)
{
	PCB* tpp;

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			if (arr[j]->running_time > arr[j + 1]->running_time)
			{
				tpp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tpp;
			}
		}
	}
}

// 按照优先级排序
void PRIORITY(PCB** arr, int n)
{
	PCB* tpp;

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			// 数越大，优先级越小
			if (arr[j]->priority > arr[j + 1]->priority)
			{
				tpp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tpp;
			}
		}
	}
}

void HRRN(PCB** arr, int n)
{
	PCB* tpp;
	int tp_num = 0;

	for (int i = 0; i < n; i++)
	{
		if (arr[i]->breakp != 0 || arr[i]->breakp != -1)
		{
			if (tp_num != i)
			{
				tpp = arr[tp_num];
				arr[tp_num] = arr[i];
				arr[i] = tpp;
			}
			tp_num++;
		}
	}

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = n - 1; j >= tp_num + i; j--)
		{
			if (arr[j]->dqzztime < arr[j + 1]->dqzztime)
			{
				tpp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tpp;
			}
		}
	}
}

// 重排队列
void ReorderQueue(PCBQueue* q)
{
	if (NULL == q)
	{
		return;
	}

	int n = q->size;

	if (n != 0)
	{
		PCB* tp_p;			// 临时PCB
		PCB* tp_arr[MAX];	// 临时PCB数组

		tp_p = q->first_pro->next;
		for (int i = 0; i < n; i++)
		{
			//tp_arr[i] = DeQueue(q, tp_p);
			tp_arr[i] = DeQueue(q);
		}

		switch (alo)
		{
		case 1:
			printf("按FCFS调度算法重新排序!\n");
			FCFS(tp_arr, n);
			break;
		case 2:
			printf("按SPF调度算法重新排序!\n");
			SPF(tp_arr, n);
			break;
		case 3:
			printf("按PRIORITY调度算法重新排序!\n");
			PRIORITY(tp_arr, n);
			break;
		case 4:
			printf("按HRRN调度算法重新排序!\n");
			HRRN(tp_arr, n);
			break;
		default:
			printf("按FCFS调度算法重新排序!\n");
			FCFS(tp_arr, n);
			break;
		}

		//printf("\n每次淘汰的页面号：");
		for (int i = 0; i < n; i++)
		{
			//printf("%d ", tp_arr[i]->PID); // 输出每次淘汰的页面号
			EnQueue(q, tp_arr[i]);
		}
		//printf("\n淘汰总页面数：");
	}
}