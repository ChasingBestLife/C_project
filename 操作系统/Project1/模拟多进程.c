#include"DEFINITION.h"

void Control() //处理器调度程序
{
	int num;					// 就绪进程数目 
	if (ready_queue->size == 0 && run_queue->size == 0)
	{
		// 彩色文本
		printf("\033[31m");
		printf("死锁!!!");
		printf("\033[0m");
		exit(0);
	}

	num = ready_queue->size;	// 统计就绪进程个数
	printf("\t* 就绪进程个数为:%d\n", num);
	//int num_run = run_queue->size;	// 统计就绪进程个数
	//printf("\t* 运行进程个数为:%d\n", num_run);
	//int num_block = block_queue->size;	// 统计就绪进程个数
	//printf("\t* 运行进程个数为:%d\n", num_run);

	// 每次 就绪队列重新排序
	ReorderQueue(ready_queue);

	// 插入运行队列，多进程并行最大数量为PROCESS
	PCB* p;
	for (int i = run_queue->size; i < PROCESS && num != 0; i++, num--)
	{
		p = DeQueue(ready_queue);
		strcpy(p->state, "Run");
		EnQueue(run_queue, p);
	}

	// 开启模拟多进程，执行操作 
	for (PCB* p = run_queue->first_pro->next; p != NULL; p = p->next)
	{
		tp_time += 1;
		printf("当前时间: %ds\n", tp_time);

		// 检查断点，如果断点为0，则表示该进程刚开始执行，需特殊处理 
		if (p->breakp == 0)
		{
			if (tp_time >= p->arrive_time)
			{
				// 彩色文本实现
				printf("\033[36m");
				Processor(p);
				printf("\033[0m");
			}
			else if(p->arrive_time - tp_time >= 20)	// 到达时间过长，则特殊处理
			{
				// 如果运行队列内的每个进程的到达时间都很长，且就绪队列没有进程了，则特殊处理
				if(ready_queue->size == 0)
				{
					p->arrive_time = tp_time;
					// 彩色文本实现
					printf("\033[36m");
					Processor(p);
					printf("\033[0m");
				}
				else
				{
					printf("\t* 进程未到达，请等待!\n");
					Look_DeQueue(run_queue, p);
					strcpy(p->state, "Ready");
					EnQueue(ready_queue, p);
					EnQueue(ready_queue, DeQueue(ready_queue));
				}
			}
			else
			{
				printf("\t* 进程未到达，请等待!\n");
				Look_DeQueue(run_queue, p);
				strcpy(p->state, "Ready");
				EnQueue(ready_queue, p);
				EnQueue(ready_queue, DeQueue(ready_queue));
			}
		}
		else if (tp_time - p->break_time >= 2)		// cb每步操作是20ms,执行不超过20ms就是没执行完毕l
		{
			// 彩色文本实现
			printf("\033[36m");
			Processor(p);
			printf("\033[0m");
		}

		// 同步信息
		for (int k = 0; k < PRODUCT + CONSUME; k++)
		{
			if (pro[k].flag == p->flag && pro[k].PID == p->PID)
			{
				CopyProcess(&pro[k], p);
				break;
			}
		}
		
		// 判断是否已经输入完毕，是则关闭进程
		CloseProcess();
	}
}

//模拟处理器指令执行
void Processor(PCB* p)
{
	// 内存判断
	if (p->Address == -1)
	{
		if (memAllocation(p) != 1)
		{
			return;
		}
	}

	p->usage_count++;	// 进程使用次数加一
	if (p->flag == 0) //当前进程为生产者
		switch (p->breakp)
		{
		case 0:		// produce
			p->break_time = tp_time;		// 保存时间断点

			if (count <= 0) { 				// 生产结束
				Look_DeQueue(run_queue, p);
				printf("\t* 生产者%d结束生产!\n", p->PID);
				strcpy(p->state, "Stop");
				strcpy(p->reason, "Null");

				p->break_time = tp_time;
				p->end_time = p->break_time;// 保存结束时间
				p->breakp = -1;
				memClear(p);				// 内存中清除该进程
			}
			else
			{
				printf("\t* 开始运行%s %d\n", p->name, p->PID);
				p->start_time = p->break_time;// 记录开始时间 
				printf("\t* %s %d生产了字符%c\n", p->name, p->PID, str[sp]);

				rec_p[p_l] = str[sp];		// 添加到生产记录
				p_l++;
				sp = (sp + 1) % len;
				count--; 					// 剩余字符个数减1

				pc++;						// 程序计数器记录位置
				p->breakp++; 				// 保存断点
			}

			break;
		case 1: 	// 申请 访问临界区 
			pc++;						// 程序计数器记录位置
			p->breakp++; 				// 保存断点
			P(empty, p);

			break;
		case 2:
			// 互斥访问
			pc++;						// 程序计数器记录位置
			p->breakp++; 				// 保存断点
			P(rw_mux, p);
			break;
		case 3: 	// 访问临界区 
			p->break_time = tp_time;	// 保存时间断点

			buffer[in] = rec_p[p_f]; 	// 放到缓冲区
			printf("\t* %c字符成功入驻空缓存!\n", buffer[in]);

			in = (in + 1) % BUF;		// 生产头指针+1
			p_f++;						// 缓冲区尾指针+1
			pc++;						// 程序计数器记录位置
			p->breakp++; 				// 保存断点
			break;
		case 4: 	// 退出临界区 
			p->break_time = tp_time;	// 保存时间断点
			pc++;						// 程序计数器记录位置
			p->breakp++; 				// 保存断点

			V(rw_mux, p);
			printf("\t* 释放一个%s信号\n", rw_mux->name);
			V(filled, p);
			printf("\t* 释放一个%s信号\n", filled->name);

			break;
		case 5:		// goto01  
			printf("\t* %s %d goto 0 操作\n", p->name, p->PID);
			pc = 0;						// 程序计数器归零
			p->breakp = 0;
			Look_DeQueue(run_queue, p); // 从运行队列删除该进程
			printf("\t* 剩余字符count=%d个\n", count);

			p->break_time = tp_time;	// 保存时间断点
			p->end_time = p->break_time;// 保存结束时间 
			p->zztime = p->end_time - p->start_time;		// 周转时间

			memClear(p);				// 内存中清除该进程

			if (count <= 0) { 				// 生产结束
				printf("\t* 生产者%d结束生产!\n", p->PID);
				strcpy(p->state, "Stop");
				strcpy(p->reason, "Null");

				p->breakp = -1;
			}
			else
			{
				strcpy(p->state, "Ready");
				strcpy(p->reason, "Null");
				p->start_time = 0;
				EnQueue(ready_queue, p);
			}
		}
	else  //当前进程为消费者
		switch (p->breakp)
		{
		case 0: 	// 判断缓冲区是否有东西 
			printf("\t* 开始运行%s %d\n", p->name, p->PID);

			p->break_time = tp_time;		// 保存时间断点
			p->start_time = p->break_time;	// 记录开始时间 
			pc++;							// 程序计数器记录位置
			p->breakp++;

			P(filled, p);
			break;
		case 1:
			// 互斥访问
			pc++;						// 程序计数器记录位置
			p->breakp++; 				// 保存断点
			P(rw_mux, p);
			break;
		case 2: 	// 将字符取出缓冲区 
			p->break_time = tp_time;	// 保存时间断点

			printf("\t* %s %d取字符!\n", p->name, p->PID);
			rec_c[c_l] = buffer[out];

			out = (out + 1) % BUF;		// 缓冲区头指针加一
			c_l++;						// 输出尾指针+1
			pc++;						// 程序计数器记录位置
			p->breakp++; 				// 保存断点

			break;
		case 3: 	// 释放信号量 
			p->break_time = tp_time;	// 保存时间断点
			pc++;						// 程序计数器记录位置
			p->breakp++;				// 保存断点

			V(rw_mux, p);
			printf("\t* 释放一个%s\n", rw_mux->name);
			V(empty, p);
			printf("\t* 释放一个%s\n", empty->name);

			break;
		case 4: 	// 消费字符 
			p->break_time = tp_time;		// 保存时间断点
			printf("\t* 消费了字符%c\n", rec_c[c_f]);			// 添加到消费记录
			c_f++;
			
			con_cnt++;
			if (con_cnt >= len) 
			{
				strcpy(p->state, "Stop");	// 完成态
				p->breakp = -1;
				DeQueue(run_queue);

				p->break_time = tp_time;	// 保存时间断点
				p->end_time = p->break_time;// 保存结束时间
				p->zztime = p->end_time - p->start_time;		// 周转时间

				memClear(p);				// 内存中清除该进程

				return;
			}

			pc++;						// 程序计数器记录位置
			p->breakp++; 				// 保存断点
			break;
		case 5: 	// goto0
			p->break_time = tp_time;	// 保存时间断点
			printf("\t* 消费进程goto 0 操作\n");
			pc = 0;
			p->breakp = 0;				// 保存断点
			Look_DeQueue(run_queue, p);
			strcpy(p->state, "Ready");
			strcpy(p->reason, "NULL");
			p->start_time = 0;
			p->break_time = tp_time;	// 保存时间断点
			p->end_time = p->break_time;// 保存结束时间
			p->zztime = p->end_time - p->start_time;		// 周转时间

			memClear(p);				// 内存中清除该进程
			
			EnQueue(ready_queue, p);

			break;
		}

		p->dqzztime = (tp_time - p->start_time) / p->running_time;		// 带权周转时间
}

