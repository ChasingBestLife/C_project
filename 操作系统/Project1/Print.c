#include"DEFINITION.h"

void PrintStatus()
{
	printf("����������������������������ģ�⡪������������\n");
	printf("* ģ����̵��ַ���Ϊ:\t");
	printf("%s\n", &str);

	printf("* ������:");
	for (int j = p_f; j <= p_l; j++)
		printf("%c", rec_p[j]);
	printf("\n* �ջ���:");
	for (int j = out; j != in; j = (j + 1) % BUF)
		printf("%c", buffer[j]);
	printf("\n* ������:");
	for (int j = 0; j <= c_l; j++)
		printf("%c", rec_c[j]);

	printf("\n�����������������̿��ƿ����Ϣ����������������\n");
	printf("������\t\t״̬\t��ʼʱ��\t����ʱ��\t����Ӧ��\t���ȼ�\t�ȴ�ԭ��\t�ϵ�\n");
	for (int i = 0; i < PRODUCT + CONSUME; i++)
	{
		if (pro[i].flag == 0)
			printf("������%d\t\t%s\t%7d\t\t%7d\t\t%.3lf\t\t%6d\t%s\t\t%d\n", pro[i].PID, pro[i].state, pro[i].start_time, pro[i].running_time, pro[i].dqzztime, pro[i].priority, pro[i].reason, pro[i].breakp);
		else
			printf("������%d\t\t%s\t%7d\t\t%7d\t\t%.3lf\t\t%6d\t%s\t\t%d\n", pro[i].PID, pro[i].state, pro[i].start_time, pro[i].running_time, pro[i].dqzztime, pro[i].priority, pro[i].reason, pro[i].breakp);
	}
	printf("��������������������������������������������������������������\n");

	printf("\n�����������������ڴ�洢�������������������\n");
	if (1 == memory_allocation_method)printf("�̶�������ʽ\n");
	else if (2 == memory_allocation_method)printf("�ɱ������ʽ\n");
	printf("**********************************************\n");
	printf("*\n");
	printf("*[ ");
	printf("|%d ����ϵͳ %d| ", 0, m[0]);
	for (int i = 4096; i < tp_mem; i++)
	{
		if (mem == tp_mem-4096)	break;
		if (m[i] > 0)
		{
			printf("|%d ����%d %d| ", i, m[i + 1], m[i]);
			
			/* ��Թ̶����� */
			int temp = m[i];
			//while (m[temp] != -1)	// ������һλ��Ϊ-1��������������洢һ������
			//{
			//	
			//	printf("|%d ����%d %d| ", temp, m[temp + 1], m[temp]);
			//	temp = m[temp];
			//}
			if (m[i] != -1 && i < tp_mem)	// ������һλ��Ϊ-1��������������洢һ������
			{
				while ((m[i] != -1) && i+1024<tp_mem )
				{
					i += 1024;
					if (m[i] > 0)
					{
						printf("|%d ����%d %d| ", i, m[i + 1], m[i]);
					}
				}
				break;
			}

			i = m[i];

		}
	}
	printf("\t%d]\n*\n", tp_mem);
	printf("**********************************************\n");
	printf("��������������������������������������������������������������\n");

	printf("\n��������������������洢���������������������\n");
	if (2 == page_scheduling_alo)printf("LRUҳ������㷨\n");
	else if (3 == page_scheduling_alo)printf("LFUҳ������㷨\n");
	else printf("FIFOҳ������㷨\n");
	printf("��̭ҳ���: ");
	if (page_miss_flag == 1)
	{
		while (page_die_num[page_pointer] != 0)
		{
			printf("%d ", page_die_num[page_pointer]);
			page_pointer++;
		}
	}
	printf("\nȱҳ�ܴ���: %d\n", pageFaults);
	page_miss_flag = 0;
	printf("��������������������������������������������������������������\n");

	printf("1.���� 0.�˳�\n");
	int n;
	scanf("%d", &n);
	if (n == 0)	exit(0);
}