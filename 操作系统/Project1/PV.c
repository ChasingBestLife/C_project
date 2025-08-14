#include"DEFINITION.h"

/* 0Ϊempty, 1Ϊfilled��2Ϊrw_mux */

void P(Semaphore* mux, PCB* p)
{
	mux->num--;

	// ��ɫ�ı�ʵ��
	printf("\033[35m");
	if (mux->num < 0)
	{
		Block(mux, p);
		pc--;						// �����������¼λ��
	}
	else
	{

		printf("\t* %s�ź�����ɹ�!\n", mux->name);
	}
	printf("\033[34m");
}

void Block(Semaphore* mux, PCB* p)
{
	// ���������������У������ߺ������� 
	int num = 0;

	strcpy(p->state, "Block");		// �ı�״̬
	strcpy(p->reason, mux->name);	// ˵��ԭ��
	memClear(p);					// �ڴ�������ý���

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

	printf("\t* %s %d����������!\n", p->name, p->PID);

	num = block_queue->size;
	printf("\t* �����Ľ��̸���Ϊ:%d\n", num);
}

void V(Semaphore* mux, PCB* p)
{
	mux->num++;

	if (mux->num <= 0)
	{
		Wakeup(mux, p);
		pc++;						// �����������¼λ��
	}
}

//���Ѻ���
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

	// ͬ��������Ϣ 
	for (int k = 0; k < PRODUCT + CONSUME; k++)
	{
		if (pro[k].flag == tp->flag && pro[k].PID == tp->PID)
		{
			CopyProcess(&pro[k], tp);
			break;
		}
	}

	EnQueue(ready_queue, tp);
	// ��ɫ�ı�
	printf("\033[35m");
	printf("\t* %s %d���̱�������!\n", tp->name, tp->PID);
	printf("\033[0m");
	printf("\033[34m");
}