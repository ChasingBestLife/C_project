#include"DEFINITION.h"

// 关闭剩余进程
void CloseProcess()
{
	if (con_cnt >= len)
	{
		for (PCB* tpp = DeQueue(ready_queue); tpp != NULL; tpp = tpp->next)
		{
			tpp->breakp = -1;
			strcpy(tpp->state, "Stop");
			strcpy(tpp->reason, "NULL");
			tpp->end_time = tp_time;

			// 同步信息
			for (int k = 0; k < PRODUCT + CONSUME; k++)
			{
				if (pro[k].flag == tpp->flag && pro[k].PID == tpp->PID)
				{
					CopyProcess(&pro[k], tpp);
					break;
				}
			}
		}
		for (PCB* tpp = DeQueue(block_queue); tpp != NULL; tpp = tpp->next)
		{
			tpp->breakp = -1;
			strcpy(tpp->state, "Stop");
			strcpy(tpp->reason, "NULL");
			tpp->end_time = tp_time;

			// 同步信息
			for (int k = 0; k < PRODUCT + CONSUME; k++)
			{
				if (pro[k].flag == tpp->flag && pro[k].PID == tpp->PID)
				{
					CopyProcess(&pro[k], tpp);
					break;
				}
			}
		}
		for (PCB* tpp = DeQueue(product_block_queue); tpp != NULL; tpp = tpp->next)
		{
			tpp->breakp = -1;
			strcpy(tpp->state, "Stop");
			strcpy(tpp->reason, "NULL");
			tpp->end_time = tp_time;

			// 同步信息
			for (int k = 0; k < PRODUCT + CONSUME; k++)
			{
				if (pro[k].flag == tpp->flag && pro[k].PID == tpp->PID)
				{
					CopyProcess(&pro[k], tpp);
					break;
				}
			}
		}
		for (PCB* tpp = DeQueue(consume_block_queue); tpp != NULL; tpp = tpp->next)
		{
			tpp->breakp = -1;
			strcpy(tpp->state, "Stop");
			strcpy(tpp->reason, "NULL");
			tpp->end_time = tp_time;

			// 同步信息
			for (int k = 0; k < PRODUCT + CONSUME; k++)
			{
				if (pro[k].flag == tpp->flag && pro[k].PID == tpp->PID)
				{
					CopyProcess(&pro[k], tpp);
					break;
				}
			}
		}
	}
}

// 释放队列
void DestroyQueue(PCBQueue* q)
{
	PCB* current = q->first_pro->next;
	PCB* next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	free(q->first_pro);
	free(q);
}

// 释放信号量
void DestroySemaphore(Semaphore* mux)
{
	printf("关闭信号量%s\n", mux->name);
	free(mux);
}

void Close()
{
	// 关闭队列
	printf("关闭队列\n");
	DestroyQueue(ready_queue);
	DestroyQueue(block_queue);
	DestroyQueue(product_block_queue);
	DestroyQueue(consume_block_queue);
	DestroyQueue(run_queue);

	// 关闭信号量
	DestroySemaphore(empty);
	DestroySemaphore(filled);
	DestroySemaphore(rw_mux);

	// 清除内存
	memCloseProcess();
}