#include"DEFINITION.h"

// 插入队列
void EnQueue(PCBQueue* q, PCB* p)
{
	if (NULL == q)
	{
		return;
	}
	PCB* tp = q->first_pro->next;
	// 避免插入相同值
	for (int i = 0; i < q->size && tp != NULL; i++)
	{
		if (tp->flag == p->flag && tp->PID == p->PID)
		{
			return;
		}
	}

	q->last_pro->next = (PCB*)malloc(sizeof(PCB));
	q->last_pro = q->last_pro->next;
	CopyProcess(q->last_pro, p);
	q->last_pro->next = NULL;

	q->size++;
}

// 将进程pro2的信息复制到进程pro1中
void CopyProcess(PCB* pro1, PCB* pro2)
{
	memcpy(pro1->name, pro2->name, sizeof(pro2->name));
	//strcpy(pro1->name, pro2->name);
	pro1->PID = pro2->PID;
	memcpy(pro1->state, pro2->state, sizeof(pro2->state));
	//strcpy(pro1->state, pro2->state);
	memcpy(pro1->reason, pro2->reason, sizeof(pro2->reason));
	//strcpy(pro1->reason, pro2->reason);
	pro1->Address = pro2->Address;
	pro1->breakp = pro2->breakp;
	pro1->flag = pro2->flag;
	pro1->priority = pro2->priority;
	pro1->arrive_time = pro2->arrive_time;
	pro1->start_time = pro2->start_time;
	pro1->running_time = pro2->running_time;
	pro1->end_time = pro2->end_time;
	pro1->copy_run_time = pro2->copy_run_time;
	pro1->next = pro2->next;
	pro1->zztime = pro2->zztime;
	pro1->dqzztime = pro2->dqzztime;
	pro1->break_time = pro2->break_time;
	pro1->size = pro2->size;
	pro1->usage_count = pro2->usage_count;
}

// 清空队列
void Clean_Queue(PCBQueue* q)
{
	if (NULL == q)
	{
		return;
	}

	for (PCB* tpp = DeQueue(q); tpp != NULL; tpp = DeQueue(q)) {};
}


// 输出队列
PCB* DeQueue(PCBQueue* q)
{
	if (NULL == q || NULL == q->first_pro->next)
	{
		return NULL;
	}

	PCB* tp;
	tp = q->first_pro->next;

	if (tp == q->last_pro)
	{
		q->first_pro->next = NULL;
		q->last_pro = q->first_pro;

		q->size--;
		return tp;
	}
	q->first_pro->next = q->first_pro->next->next;
	q->size--;

	return tp;
}

// 找到指定进程并删除
void Look_DeQueue(PCBQueue* q, PCB* p)
{
	if (NULL == q || NULL == p)
	{
		return;
	}

	PCB* tp = q->first_pro;
	PCB* ttp = tp->next;
	while (ttp != NULL)
	{
		if (ttp->PID == p->PID && ttp->flag == p->flag)
		{
			// 删除指定结点时，需要注意最后一个结点 
			if (ttp == q->last_pro)
			{
				q->last_pro = tp;
				q->last_pro->next = NULL;
				q->size--;
				break;
			}
			tp->next = ttp->next;
			q->size--;
			break;
		}
		tp = ttp;
		ttp = ttp->next;
	}
}

int BlockProCount()
{
	int n = 0;
	n = block_queue->size + product_block_queue->size + consume_block_queue;

	return n;
}