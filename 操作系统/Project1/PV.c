#include"DEFINITION.h"

/* 0为empty, 1为filled，2为rw_mux */

void P(Semaphore* mux, PCB* p)
{
	mux->num--;

	// 彩色文本实现
	printf("\033[35m");
	if (mux->num < 0)
	{
		Block(mux, p);
		pc--;						// 程序计数器记录位置
	}
	else
	{

		printf("\t* %s信号申请成功!\n", mux->name);
	}
	printf("\033[34m");
}

void Block(Semaphore* mux, PCB* p)
{
	// 定义两个阻塞队列：生产者和消费者 
	int num = 0;

	strcpy(p->state, "Block");		// 改变状态
	strcpy(p->reason, mux->name);	// 说明原因
	memClear(p);					// 内存中清除该进程

	if (mux->flag == 2)
	{
		Look_DeQueue(run_queue, p);
		EnQueue(block_queue, p);
	}
	else
	{
		if (p->flag == 0)
		{
			Look_DeQueue(run_queue, p);
			EnQueue(product_block_queue, p);
		}
		else
		{
			Look_DeQueue(run_queue, p);
			EnQueue(consume_block_queue, p);
		}
	}

	printf("\t* %s %d进程阻塞了!\n", p->name, p->PID);

	num = block_queue->size;
	printf("\t* 阻塞的进程个数为:%d\n", num);
}

void V(Semaphore* mux, PCB* p)
{
	mux->num++;

	if (mux->num <= 0)
	{
		Wakeup(mux, p);
		pc++;						// 程序计数器记录位置
	}
}

//唤醒函数
void Wakeup(Semaphore* mux, PCB* p)
{
	PCB* tp;

	if (mux->flag == 0)
	{
		tp = DeQueue(product_block_queue);
	}
	else if (mux->flag == 1)
	{
		tp = DeQueue(consume_block_queue);
	}
	else
	{
		tp = DeQueue(block_queue);
	}

	if (tp == NULL)	return;
	strcpy(tp->state, "Ready");
	strcpy(tp->reason, "Null");

	// 同步进程信息 
	for (int k = 0; k < PRODUCT + CONSUME; k++)
	{
		if (pro[k].flag == tp->flag && pro[k].PID == tp->PID)
		{
			CopyProcess(&pro[k], tp);
			break;
		}
	}

	EnQueue(ready_queue, tp);
	// 彩色文本
	printf("\033[35m");
	printf("\t* %s %d进程被唤醒了!\n", tp->name, tp->PID);
	printf("\033[0m");
	printf("\033[34m");
}