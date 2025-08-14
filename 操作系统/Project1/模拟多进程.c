#include"DEFINITION.h"

void Control() //���������ȳ���
{
	int num;					// ����������Ŀ 
	if (ready_queue->size == 0 && run_queue->size == 0)
	{
		// ��ɫ�ı�
		printf("\033[31m");
		printf("����!!!");
		printf("\033[0m");
		exit(0);
	}

	num = ready_queue->size;	// ͳ�ƾ������̸���
	printf("\t* �������̸���Ϊ:%d\n", num);
	//int num_run = run_queue->size;	// ͳ�ƾ������̸���
	//printf("\t* ���н��̸���Ϊ:%d\n", num_run);
	//int num_block = block_queue->size;	// ͳ�ƾ������̸���
	//printf("\t* ���н��̸���Ϊ:%d\n", num_run);

	// ÿ�� ����������������
	ReorderQueue(ready_queue);

	// �������ж��У�����̲����������ΪPROCESS
	PCB* p;
	for (int i = run_queue->size; i < PROCESS && num != 0; i++, num--)
	{
		p = DeQueue(ready_queue);
		strcpy(p->state, "Run");
		EnQueue(run_queue, p);
	}

	// ����ģ�����̣�ִ�в��� 
	for (PCB* p = run_queue->first_pro->next; p != NULL; p = p->next)
	{
		tp_time += 1;
		printf("��ǰʱ��: %ds\n", tp_time);

		// ���ϵ㣬����ϵ�Ϊ0�����ʾ�ý��̸տ�ʼִ�У������⴦�� 
		if (p->breakp == 0)
		{
			if (tp_time >= p->arrive_time)
			{
				// ��ɫ�ı�ʵ��
				printf("\033[36m");
				Processor(p);
				printf("\033[0m");
			}
			else if(p->arrive_time - tp_time >= 20)	// ����ʱ������������⴦��
			{
				// ������ж����ڵ�ÿ�����̵ĵ���ʱ�䶼�ܳ����Ҿ�������û�н����ˣ������⴦��
				if(ready_queue->size == 0)
				{
					p->arrive_time = tp_time;
					// ��ɫ�ı�ʵ��
					printf("\033[36m");
					Processor(p);
					printf("\033[0m");
				}
				else
				{
					printf("\t* ����δ�����ȴ�!\n");
					Look_DeQueue(run_queue, p);
					strcpy(p->state, "Ready");
					EnQueue(ready_queue, p);
					EnQueue(ready_queue, DeQueue(ready_queue));
				}
			}
			else
			{
				printf("\t* ����δ�����ȴ�!\n");
				Look_DeQueue(run_queue, p);
				strcpy(p->state, "Ready");
				EnQueue(ready_queue, p);
				EnQueue(ready_queue, DeQueue(ready_queue));
			}
		}
		else if (tp_time - p->break_time >= 2)		// cbÿ��������20ms,ִ�в�����20ms����ûִ�����l
		{
			// ��ɫ�ı�ʵ��
			printf("\033[36m");
			Processor(p);
			printf("\033[0m");
		}

		// ͬ����Ϣ
		for (int k = 0; k < PRODUCT + CONSUME; k++)
		{
			if (pro[k].flag == p->flag && pro[k].PID == p->PID)
			{
				CopyProcess(&pro[k], p);
				break;
			}
		}
		
		// �ж��Ƿ��Ѿ�������ϣ�����رս���
		CloseProcess();
	}
}

//ģ�⴦����ָ��ִ��
void Processor(PCB* p)
{
	// �ڴ��ж�
	if (p->Address == -1)
	{
		if (memAllocation(p) != 1)
		{
			return;
		}
	}

	p->usage_count++;	// ����ʹ�ô�����һ
	if (p->flag == 0) //��ǰ����Ϊ������
		switch (p->breakp)
		{
		case 0:		// produce
			p->break_time = tp_time;		// ����ʱ��ϵ�

			if (count <= 0) { 				// ��������
				Look_DeQueue(run_queue, p);
				printf("\t* ������%d��������!\n", p->PID);
				strcpy(p->state, "Stop");
				strcpy(p->reason, "Null");

				p->break_time = tp_time;
				p->end_time = p->break_time;// �������ʱ��
				p->breakp = -1;
				memClear(p);				// �ڴ�������ý���
			}
			else
			{
				printf("\t* ��ʼ����%s %d\n", p->name, p->PID);
				p->start_time = p->break_time;// ��¼��ʼʱ�� 
				printf("\t* %s %d�������ַ�%c\n", p->name, p->PID, str[sp]);

				rec_p[p_l] = str[sp];		// ��ӵ�������¼
				p_l++;
				sp = (sp + 1) % len;
				count--; 					// ʣ���ַ�������1

				pc++;						// �����������¼λ��
				p->breakp++; 				// ����ϵ�
			}

			break;
		case 1: 	// ���� �����ٽ��� 
			pc++;						// �����������¼λ��
			p->breakp++; 				// ����ϵ�
			P(empty, p);

			break;
		case 2:
			// �������
			pc++;						// �����������¼λ��
			p->breakp++; 				// ����ϵ�
			P(rw_mux, p);
			break;
		case 3: 	// �����ٽ��� 
			p->break_time = tp_time;	// ����ʱ��ϵ�

			buffer[in] = rec_p[p_f]; 	// �ŵ�������
			printf("\t* %c�ַ��ɹ���פ�ջ���!\n", buffer[in]);

			in = (in + 1) % BUF;		// ����ͷָ��+1
			p_f++;						// ������βָ��+1
			pc++;						// �����������¼λ��
			p->breakp++; 				// ����ϵ�
			break;
		case 4: 	// �˳��ٽ��� 
			p->break_time = tp_time;	// ����ʱ��ϵ�
			pc++;						// �����������¼λ��
			p->breakp++; 				// ����ϵ�

			V(rw_mux, p);
			printf("\t* �ͷ�һ��%s�ź�\n", rw_mux->name);
			V(filled, p);
			printf("\t* �ͷ�һ��%s�ź�\n", filled->name);

			break;
		case 5:		// goto01  
			printf("\t* %s %d goto 0 ����\n", p->name, p->PID);
			pc = 0;						// �������������
			p->breakp = 0;
			Look_DeQueue(run_queue, p); // �����ж���ɾ���ý���
			printf("\t* ʣ���ַ�count=%d��\n", count);

			p->break_time = tp_time;	// ����ʱ��ϵ�
			p->end_time = p->break_time;// �������ʱ�� 
			p->zztime = p->end_time - p->start_time;		// ��תʱ��

			memClear(p);				// �ڴ�������ý���

			if (count <= 0) { 				// ��������
				printf("\t* ������%d��������!\n", p->PID);
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
	else  //��ǰ����Ϊ������
		switch (p->breakp)
		{
		case 0: 	// �жϻ������Ƿ��ж��� 
			printf("\t* ��ʼ����%s %d\n", p->name, p->PID);

			p->break_time = tp_time;		// ����ʱ��ϵ�
			p->start_time = p->break_time;	// ��¼��ʼʱ�� 
			pc++;							// �����������¼λ��
			p->breakp++;

			P(filled, p);
			break;
		case 1:
			// �������
			pc++;						// �����������¼λ��
			p->breakp++; 				// ����ϵ�
			P(rw_mux, p);
			break;
		case 2: 	// ���ַ�ȡ�������� 
			p->break_time = tp_time;	// ����ʱ��ϵ�

			printf("\t* %s %dȡ�ַ�!\n", p->name, p->PID);
			rec_c[c_l] = buffer[out];

			out = (out + 1) % BUF;		// ������ͷָ���һ
			c_l++;						// ���βָ��+1
			pc++;						// �����������¼λ��
			p->breakp++; 				// ����ϵ�

			break;
		case 3: 	// �ͷ��ź��� 
			p->break_time = tp_time;	// ����ʱ��ϵ�
			pc++;						// �����������¼λ��
			p->breakp++;				// ����ϵ�

			V(rw_mux, p);
			printf("\t* �ͷ�һ��%s\n", rw_mux->name);
			V(empty, p);
			printf("\t* �ͷ�һ��%s\n", empty->name);

			break;
		case 4: 	// �����ַ� 
			p->break_time = tp_time;		// ����ʱ��ϵ�
			printf("\t* �������ַ�%c\n", rec_c[c_f]);			// ��ӵ����Ѽ�¼
			c_f++;
			
			con_cnt++;
			if (con_cnt >= len) 
			{
				strcpy(p->state, "Stop");	// ���̬
				p->breakp = -1;
				DeQueue(run_queue);

				p->break_time = tp_time;	// ����ʱ��ϵ�
				p->end_time = p->break_time;// �������ʱ��
				p->zztime = p->end_time - p->start_time;		// ��תʱ��

				memClear(p);				// �ڴ�������ý���

				return;
			}

			pc++;						// �����������¼λ��
			p->breakp++; 				// ����ϵ�
			break;
		case 5: 	// goto0
			p->break_time = tp_time;	// ����ʱ��ϵ�
			printf("\t* ���ѽ���goto 0 ����\n");
			pc = 0;
			p->breakp = 0;				// ����ϵ�
			Look_DeQueue(run_queue, p);
			strcpy(p->state, "Ready");
			strcpy(p->reason, "NULL");
			p->start_time = 0;
			p->break_time = tp_time;	// ����ʱ��ϵ�
			p->end_time = p->break_time;// �������ʱ��
			p->zztime = p->end_time - p->start_time;		// ��תʱ��

			memClear(p);				// �ڴ�������ý���
			
			EnQueue(ready_queue, p);

			break;
		}

		p->dqzztime = (tp_time - p->start_time) / p->running_time;		// ��Ȩ��תʱ��
}

