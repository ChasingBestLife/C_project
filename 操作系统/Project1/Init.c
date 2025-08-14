#include"DEFINITION.h"

// ��ʼ�����������������ж���
void QueueInit(PCBQueue** q)
{
	*q = (PCBQueue*)malloc(sizeof(PCBQueue));
	(*q)->first_pro = (PCB*)malloc(sizeof(PCB));
	(*q)->first_pro->next = NULL;
	(*q)->last_pro = (*q)->first_pro;
	(*q)->size = 0;
}

// ��ʼ���ź��� 
void SemaphoreInit()
{
	empty = (Semaphore*)malloc(sizeof(Semaphore));
	filled = (Semaphore*)malloc(sizeof(Semaphore));
	rw_mux = (Semaphore*)malloc(sizeof(Semaphore));

	strcpy(empty->name, "empty");
	empty->num = BUF;
	empty->flag = 0;

	strcpy(filled->name, "filled");
	filled->num = 0;
	filled->flag = 1;

	strcpy(rw_mux->name, "rw_mux");
	rw_mux->num = 1;
	rw_mux->flag = 2;
}

// ���̳�ʼ��
void DiskInit()
{

}

// ��ʼ�� 
void Init()
{
	// ��ʼ���ĸ�����
	QueueInit(&ready_queue);
	QueueInit(&block_queue);
	QueueInit(&product_block_queue);
	QueueInit(&consume_block_queue);
	QueueInit(&run_queue);

	// ��ʼ���ź��� 
	SemaphoreInit();

	// �ڴ��ʼ��
	setMem();

	// ���̳�ʼ��
	DiskInit();

	/*��ʼ�������ߺ������߽���*/
	printf("������������������������������������������������������������������������\n");
	printf("���ڳ�ʼ�������ߺ������߽���...\n");
	printf("\n�����������߸���: ");
	scanf("%d", &PRODUCT);
	getchar();
	printf("��������������������: ");
	scanf("%d", &CONSUME);
	getchar();
	/*printf("������������������(<=3): ");
	scanf("%d", &PROCESS);*/

	// ��ʼ�������߽��� 
	printf("******************************\n*��ʼ��ʼ�������ߺ������߽���...\n");
	for (int i = 0; i < PRODUCT; i++)
	{
		// ��ʼ�������������
		srand(time(NULL));
		// ����һ��129 �� 1024֮��������
		int size = rand() % 1920 + 1024;

		strcpy(pro[i].name, "Producer");
		pro[i].PID = i + 1;
		strcpy(pro[i].state, "Ready");
		strcpy(pro[i].reason, "Null");
		pro[i].start_time = 0;
		pro[i].end_time = 0;
		pro[i].zztime = -1;
		pro[i].breakp = 0;
		pro[i].next = NULL;
		pro[i].flag = 0;
		pro[i].Address = -1;
		pro[i].size = size;
		pro[i].usage_count = 0;
	}
	// ��ʼ�������߽��� 
	for (int i = PRODUCT; i < PRODUCT + CONSUME; i++)
	{
		// ��ʼ�������������
		srand(time(NULL));
		// ����һ��129 �� 1024֮��������
		int size = rand() % 1920 + 129;

		strcpy(pro[i].name, "Consume");
		pro[i].PID = i + 1;
		strcpy(pro[i].state, "Ready");
		strcpy(pro[i].reason, "Null");
		pro[i].start_time = 0;
		pro[i].end_time = 0;
		pro[i].zztime = -1;
		pro[i].breakp = 0;
		pro[i].next = NULL;
		pro[i].flag = 1;
		pro[i].Address = -1;
		pro[i].size = size;
		pro[i].usage_count = 0;
	}

	// �û�������̵���ʱ�� 
	printf("*������������̵�:����ʱ��\t����ʱ��\t���ȼ�\n");
	for (int i = 0; i < PRODUCT + CONSUME; i++)
	{
		printf("*****************\n*%s %d\t  ", pro[i].name, pro[i].PID);
		if (scanf("%d %d %d", &pro[i].arrive_time, &pro[i].running_time, &pro[i].priority) != 3)
		{
			printf("�������������������ȷ������ֵ��\n");
		}
		getchar();
		pro[i].start_time = pro[i].arrive_time;

		EnQueue(ready_queue, &pro[i]);
		printf("*****************\n\n");
	}

	// ���������������� 
	Alogorithm();

	pc = 0;
	con_cnt = 0; //���Ѽ�����

	printf("\n������������������������������������������������������������������������\n");
	printf("�������������...\n");
	getchar();
	system("cls");
}