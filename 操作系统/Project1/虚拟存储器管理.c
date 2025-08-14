#include"DEFINITION.h"


void FIFOPageScheduling(PCBQueue* pageQueue, PCB* newProcess) {
    // �ж��ڴ��Ƿ�����
    if (mem >= tp_mem) {
        // �ڴ������������滻
        PCB* firstProcess = pageQueue->first_pro;
        printf("FIFO�滻���� %d\n", firstProcess->PID);

        // ����������ڴ�Ľ��̴Ӷ������Ƴ�
        pageQueue->first_pro = firstProcess->next;
        free(firstProcess);  // �ͷ��ڴ�

        mem -= firstProcess->size;  // �����ڴ�ʹ�����
    }

    // ���½��̼��ص��ڴ�
    newProcess->Address = mem;
    mem += newProcess->size;  // �����ڴ�ʹ�����

    // ���½��̼������
    if (pageQueue->size == 0) {
        pageQueue->first_pro = newProcess;
        pageQueue->last_pro = newProcess;
    }
    else {
        pageQueue->last_pro->next = newProcess;
        pageQueue->last_pro = newProcess;
    }

    pageQueue->size++;
    printf("�½��� %d ���ص��ڴ�\n", newProcess->PID);
}

void LRUPageScheduling(PCBQueue* pageQueue, PCB* newProcess) {
    
    // �ж��ڴ��Ƿ�����
    if (mem >= tp_mem) {
        // �ڴ������������滻
        PCB* prevProcess = NULL;
        PCB* oldestProcess = pageQueue->first_pro;
        int new_last_used = tp_time - newProcess->arrive_time;   // ����last_usedΪ��ǰʱ���
        int old_last_used = tp_time - oldestProcess->arrive_time;   // ����last_usedΪ��ǰʱ���cbl

        // Ѱ�����δʹ�õĽ��̣����������һ��last_used�ֶα�ʾ�ϴ�ʹ�õ�ʱ�����
        for (PCB* process = pageQueue->first_pro; process != NULL; process = process->next) {
            if (new_last_used < old_last_used) {
                oldestProcess = process;
                prevProcess = process;
            }
        }

        printf("LRU�滻���� %d\n", oldestProcess->PID);

        // �����δʹ�õĽ��̴Ӷ������Ƴ�
        if (prevProcess) {
            prevProcess->next = oldestProcess->next;
        }
        else {
            pageQueue->first_pro = oldestProcess->next;
        }

        free(oldestProcess);  // �ͷ��ڴ�
        mem -= oldestProcess->size;  // �����ڴ�ʹ�����
    }

    // ���½��̼��ص��ڴ�
    newProcess->Address = mem;
    mem += newProcess->size;  // �����ڴ�ʹ�����

    // ���½��̼������

    if (pageQueue->size == 0) {
        pageQueue->first_pro = newProcess;
        pageQueue->last_pro = newProcess;
    }
    else {
        pageQueue->last_pro->next = newProcess;
        pageQueue->last_pro = newProcess;
    }

    pageQueue->size++;
    printf("�½��� %d ���ص��ڴ�\n", newProcess->PID);
}

void LFUPageScheduling(PCBQueue* pageQueue, PCB* newProcess) {
    // �ж��ڴ��Ƿ�����
    if (mem >= tp_mem) {
        // �ڴ������������滻
        PCB* prevProcess = NULL;
        PCB* lfuProcess = pageQueue->first_pro;

        // Ѱ������ʹ�õĽ��̣�������һ��usage_count�ֶα�ʾʹ��Ƶ�ʣ�
        for (PCB* process = pageQueue->first_pro; process != NULL; process = process->next) {
            if (process->usage_count < lfuProcess->usage_count) {
                lfuProcess = process;
                prevProcess = process;
            }
        }

        printf("LFU�滻���� %d\n", lfuProcess->PID);

        // ������ʹ�õĽ��̴Ӷ������Ƴ�
        if (prevProcess) {
            prevProcess->next = lfuProcess->next;
        }
        else {
            pageQueue->first_pro = lfuProcess->next;
        }

        free(lfuProcess);  // �ͷ��ڴ�
        mem -= lfuProcess->size;  // �����ڴ�ʹ�����
    }

    // ���½��̼��ص��ڴ�
    newProcess->Address = mem;
    mem += newProcess->size;  // �����ڴ�ʹ�����

    // ���½��̼������
    newProcess->usage_count = 1;  // ��ʼ��ʹ�ü���
    if (pageQueue->size == 0) {
        pageQueue->first_pro = newProcess;
        pageQueue->last_pro = newProcess;
    }
    else {
        pageQueue->last_pro->next = newProcess;
        pageQueue->last_pro = newProcess;
    }

    pageQueue->size++;
    printf("�½��� %d ���ص��ڴ�\n", newProcess->PID);
}

// ���Ŷ���
void PageScheduling(PCBQueue* q)
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

        switch (page_scheduling_alo)
        {
        case 1:
            printf("��FIFOҳ������㷨��������!\n");
            FCFS(tp_arr, n);
            break;
        case 2:
            printf("��LRUҳ������㷨��������!\n");
            SPF(tp_arr, n);
            break;
        case 3:
            printf("��LFUҳ������㷨��������!\n");
            PRIORITY(tp_arr, n);
            break;
        default:
            printf("��FIFOҳ������㷨��������!\n");
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