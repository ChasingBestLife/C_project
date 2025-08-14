#include"DEFINITION.h"

void Alogorithm()
{
	ReorderQueue(ready_queue);
}

// ���ݵ���ʱ��������� 
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

// ��������ʱ������
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

// �������ȼ�����
void PRIORITY(PCB** arr, int n)
{
	PCB* tpp;

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			// ��Խ�����ȼ�ԽС
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

// ���Ŷ���
void ReorderQueue(PCBQueue* q)
{
	if (NULL == q)
	{
		return;
	}

	int n = q->size;

	if (n != 0)
	{
		PCB* tp_p;			// ��ʱPCB
		PCB* tp_arr[MAX];	// ��ʱPCB����

		tp_p = q->first_pro->next;
		for (int i = 0; i < n; i++)
		{
			//tp_arr[i] = DeQueue(q, tp_p);
			tp_arr[i] = DeQueue(q);
		}

		switch (alo)
		{
		case 1:
			printf("��FCFS�����㷨��������!\n");
			FCFS(tp_arr, n);
			break;
		case 2:
			printf("��SPF�����㷨��������!\n");
			SPF(tp_arr, n);
			break;
		case 3:
			printf("��PRIORITY�����㷨��������!\n");
			PRIORITY(tp_arr, n);
			break;
		case 4:
			printf("��HRRN�����㷨��������!\n");
			HRRN(tp_arr, n);
			break;
		default:
			printf("��FCFS�����㷨��������!\n");
			FCFS(tp_arr, n);
			break;
		}

		//printf("\nÿ����̭��ҳ��ţ�");
		for (int i = 0; i < n; i++)
		{
			//printf("%d ", tp_arr[i]->PID); // ���ÿ����̭��ҳ���
			EnQueue(q, tp_arr[i]);
		}
		//printf("\n��̭��ҳ������");
	}
}