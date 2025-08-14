#include"DEFINITION.h"

void PrintStatus()
{
	printf("————————生产者消费者模拟———————\n");
	printf("* 模拟过程的字符串为:\t");
	printf("%s\n", &str);

	printf("* 已生产:");
	for (int j = p_f; j <= p_l; j++)
		printf("%c", rec_p[j]);
	printf("\n* 空缓存:");
	for (int j = out; j != in; j = (j + 1) % BUF)
		printf("%c", buffer[j]);
	printf("\n* 已消费:");
	for (int j = 0; j <= c_l; j++)
		printf("%c", rec_c[j]);

	printf("\n———————进程控制块的信息————————\n");
	printf("进程名\t\t状态\t开始时间\t运行时间\t高响应比\t优先级\t等待原因\t断点\n");
	for (int i = 0; i < PRODUCT + CONSUME; i++)
	{
		if (pro[i].flag == 0)
			printf("生产者%d\t\t%s\t%7d\t\t%7d\t\t%.3lf\t\t%6d\t%s\t\t%d\n", pro[i].PID, pro[i].state, pro[i].start_time, pro[i].running_time, pro[i].dqzztime, pro[i].priority, pro[i].reason, pro[i].breakp);
		else
			printf("消费者%d\t\t%s\t%7d\t\t%7d\t\t%.3lf\t\t%6d\t%s\t\t%d\n", pro[i].PID, pro[i].state, pro[i].start_time, pro[i].running_time, pro[i].dqzztime, pro[i].priority, pro[i].reason, pro[i].breakp);
	}
	printf("———————————————————————————————\n");

	printf("\n————————内存存储情况————————\n");
	if (1 == memory_allocation_method)printf("固定分区方式\n");
	else if (2 == memory_allocation_method)printf("可变分区方式\n");
	printf("**********************************************\n");
	printf("*\n");
	printf("*[ ");
	printf("|%d 操作系统 %d| ", 0, m[0]);
	for (int i = 4096; i < tp_mem; i++)
	{
		if (mem == tp_mem-4096)	break;
		if (m[i] > 0)
		{
			printf("|%d 进程%d %d| ", i, m[i + 1], m[i]);
			
			/* 针对固定分区 */
			int temp = m[i];
			//while (m[temp] != -1)	// 如果最后一位不为-1，则代表多个分区存储一个程序
			//{
			//	
			//	printf("|%d 进程%d %d| ", temp, m[temp + 1], m[temp]);
			//	temp = m[temp];
			//}
			if (m[i] != -1 && i < tp_mem)	// 如果最后一位不为-1，则代表多个分区存储一个程序
			{
				while ((m[i] != -1) && i+1024<tp_mem )
				{
					i += 1024;
					if (m[i] > 0)
					{
						printf("|%d 进程%d %d| ", i, m[i + 1], m[i]);
					}
				}
				break;
			}

			i = m[i];

		}
	}
	printf("\t%d]\n*\n", tp_mem);
	printf("**********************************************\n");
	printf("———————————————————————————————\n");

	printf("\n————————虚拟存储器情况————————\n");
	if (2 == page_scheduling_alo)printf("LRU页面调度算法\n");
	else if (3 == page_scheduling_alo)printf("LFU页面调度算法\n");
	else printf("FIFO页面调度算法\n");
	printf("淘汰页面号: ");
	if (page_miss_flag == 1)
	{
		while (page_die_num[page_pointer] != 0)
		{
			printf("%d ", page_die_num[page_pointer]);
			page_pointer++;
		}
	}
	printf("\n缺页总次数: %d\n", pageFaults);
	page_miss_flag = 0;
	printf("———————————————————————————————\n");

	printf("1.继续 0.退出\n");
	int n;
	scanf("%d", &n);
	if (n == 0)	exit(0);
}