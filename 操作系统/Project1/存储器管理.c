#include"DEFINITION.h"

/*
	��������ǰ��Ҫ�����ڴ棬�ڴ��㹻�Ҹ��������˲�������
		cbl* һ�������ʾ�ڴ�����
		* �ڴ��С���������͵�ȫ�ֱ�����ʾ��
		* �ڴ������ɱ�ʶ����ʾ��Ҳ����ֱ���жϣ��ڴ�-���̴�С ?< 0��
		* ���̱�����������������ڴ�Ҫ��ʱ���
*/
void setMem()
{
	system("cls");  //��������
	
	/*��ʼ���ڴ�*/
	printf("������������������������������������������������������������������������\n");
	printf("���ڳ�ʼ���ڴ�...\n");
	printf("\n�������ڴ�Ĵ�С(K): \n");
	scanf("%d", &mem);
	while (mem < 128)
	{
		// ��ɫ�ı�
		printf("\033[35m");
		printf("�ڴ��С������������: \n");
		printf("\033[0m");

		scanf("%d", &mem);
	}
	mem = mem * 1024;		// ���ڴ� K
	tp_mem = mem;

	m = (int*)malloc(sizeof(int) * mem);
	if (NULL == m)
	{
		exit(0);
	}
	memset(m, 0, sizeof(int) * mem);

	int size = 4 * 1024;				// ����ϵͳ��СΪ4*1024 
	m[0] = 0 + size - 1;				// ��һλ��¼���һλλ��
	m[0 + 1] = 001;						// �ڶ�λ��¼����PID
	mem -= size;
	m[0 + size - 1] = -1;				// ���һλΪ-1

	/*ѡ�������ʽ*/
	printf("******************************\n*��ѡ���ڴ����ʽ��\n");
	printf("*\t1: �̶�����\n");
	printf("*\t2: �ɱ����\n");
	printf("******************************\n");
	scanf("%d", &memory_allocation_method);
	getchar();

	/*ѡ����̵����㷨*/
	printf("******************************\n*��ѡ�����µ�һ�ֽ��̵����㷨:\n");
	printf("*\t1: �����ȷ������FCFS\n");
	printf("*\t2: ����ռʽ�̽������ȵ���SPF\n");
	printf("*\t3: ��̬���ȼ�����PRIORITY\n");
	printf("*\t4: ����Ӧ�ȵ���HRRN\n");
	printf("******************************\n");
	scanf("%d", &alo);
	getchar();

	/*ѡ��ҳ������㷨*/
	printf("******************************\n*��ѡ�����µ�һ�ֽ��̵����㷨:\n");
	printf("*\t1: �Ƚ��ȳ�FIFO\n");
	printf("*\t2: �������ʹ�õ����㷨LRU\n");
	printf("*\t3: �������õ����㷨LFU\n");
	printf("******************************\n");
	scanf("%d", &page_scheduling_alo);
	getchar();

	printf("\n������������������������������������������������������������������������\n");
	printf("�������������...\n");
	getchar();
	system("cls");

}

// �����ڴ�
int memAllocation(PCB* p)
{
	/*���ɽ����ڴ�*/
	int size = p->size;
	int tp_num = 0;				// ��¼ȱҳ����

	if (mem - size < 0)
	{
		// ��ɫ�ı�
		printf("\033[31m");
		printf("�ڴ治���󣬽����޷�����!\n");
		printf("\033[0m");

		Look_DeQueue(run_queue, p);
		strcpy(p->state, "Ready");
		EnQueue(ready_queue, p);

		return 0;
	}
	else if (memory_allocation_method == 1)
	{
		// �̶���ȴ�С���������ڴ�
		int tp = 0;			// tp��������¼���������С
		int add = 4096;		// 4096����Ϊ����ϵͳռ��4096
		int temp = 0;		// ��ʱָ��

		// ����������������ͬ i+=1024
		for (int i = 4096; tp<size && i<tp_mem; i += 1024)
		{
			if (m[i] == 0)  // �������0��˵�����ڴ�û������
			{
				tp += 1024;

				if (tp < size)	// ���һ������1024�������㣬������һ��
				{
					p->Address = add;					// ���̼�¼�ڴ���ʼλ��
					// ��ɫ�ı�
					printf("\033[36m");
					printf("����%d��Ҫ��������洢!\n", p->PID);
					printf("\033[0m");
					// Ѱ�ҵڶ�������
					for (int j = add + 1024; j < tp_mem; j += 1024)
					{
						if (m[j] == 0)  // �������0��˵�����ڴ�û������
						{
							m[add] = j;							// ��һλ��¼�ڶ�������λ��
							m[add + 1] = p->PID;				// �ڶ�λ��¼����PID

							i = j - 1024;
							add = j;							// add��¼�ڶ�������λ��
							tp_num++;
							
							break;
						}
					}
				}
			}
			else			// ��Ϊ0��˵������
			{
				add = i+1024;
			}
		}
		// ���һ����ҳ��
		m[add] = add + 1024 - 1;			// ��һλ��¼���һλλ��
		m[add + 1] = p->PID;				// �ڶ�λ��¼����PID
		//p->Address = add;					// ���̼�¼�ڴ���ʼλ��
		mem -= size;
		m[add + 1024 - 1] = -1;				// ���һλΪ-1����Ƿ�������
		tp_num++;
	}
	else
	{
		// ��̬���������ڴ�
		int tp = 0;			// tp��������¼���������С
		int add = 4096;		// 4096����Ϊ����ϵͳռ��4096


		///*���m���з�0��λ��*/
		//printf("\n\n\n\n");
		//for (int i = 4096;i < tp_mem; i++)
		//{
		//	if (m[i] != 0)printf("m[%d]: %d\n", i, m[i]);
		//}
		//printf("\n\n\n\n");
		///*----------------------*/


		for (int i = 4096; tp < size && i < tp_mem; i++)
		{
			if (m[i] == 0)  // �������0��˵�����ڴ�û������
			{
				tp++;
			}
			else			// ��Ϊ0��˵�����ã�����һλ�洢�������һλλ�ã�ֱ����i = m[i] + 1����������ʱ��
			{
				tp = 0;
				i = m[i] + 1;
				add = i;
			}
		}

		if (tp < size)
		{
			// ��ɫ�ı�
			printf("\033[31m");
			printf("�ⲿ��Ƭ���࣬�����޷�ֱ�Ӳ����ڴ�!\n");
			printf("\033[0m");
			Look_DeQueue(run_queue, p);
			strcpy(p->state, "Ready");
			EnQueue(ready_queue, p);
			return 0;
		}

		m[add] = add + size - 1;			// ��һλ��¼���һλλ��
		m[add + 1] = p->PID;				// �ڶ�λ��¼����PID
		p->Address = add;					// ���̼�¼�ڴ���ʼλ��
		mem -= size;
		m[add + size - 1] = -1;				// ���һλΪ-1
		tp_num++;
	}

	pageFaults += tp_num;					// ��¼ȱҳ�ܴ���
	//printf("ȱҳ�ܴ���:%d\n", pageFaults);
	return 1;
}

void memClear(PCB* p)
{
	page_miss_flag = 1;
	//printf("��̭��ҳ���Ϊ��%d\n", p->Address / 1024);
	int temp_page_pointer;			// ��ʱҳ�������ָ��

	int temp = m[p->Address];
	while (m[temp] != -1)
	{
		temp_page_pointer = 1;
		// ��¼��̭ҳ���
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

		// ͬ����Ϣ
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