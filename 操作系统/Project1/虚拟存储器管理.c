#include"DEFINITION.h"


void FIFOPageScheduling(PCBQueue* pageQueue, PCB* newProcess) {
    // 判断内存是否已满
    if (mem >= tp_mem) {
        // 内存已满，进行替换
        PCB* firstProcess = pageQueue->first_pro;
        printf("FIFO替换进程 %d\n", firstProcess->PID);

        // 将最早进入内存的进程从队列中移除
        pageQueue->first_pro = firstProcess->next;
        free(firstProcess);  // 释放内存

        mem -= firstProcess->size;  // 更新内存使用情况
    }

    // 将新进程加载到内存
    newProcess->Address = mem;
    mem += newProcess->size;  // 更新内存使用情况

    // 将新进程加入队列
    if (pageQueue->size == 0) {
        pageQueue->first_pro = newProcess;
        pageQueue->last_pro = newProcess;
    }
    else {
        pageQueue->last_pro->next = newProcess;
        pageQueue->last_pro = newProcess;
    }

    pageQueue->size++;
    printf("新进程 %d 加载到内存\n", newProcess->PID);
}

void LRUPageScheduling(PCBQueue* pageQueue, PCB* newProcess) {
    
    // 判断内存是否已满
    if (mem >= tp_mem) {
        // 内存已满，进行替换
        PCB* prevProcess = NULL;
        PCB* oldestProcess = pageQueue->first_pro;
        int new_last_used = tp_time - newProcess->arrive_time;   // 假设last_used为当前时间戳
        int old_last_used = tp_time - oldestProcess->arrive_time;   // 假设last_used为当前时间戳cbl

        // 寻找最久未使用的进程（这里假设有一个last_used字段表示上次使用的时间戳）
        for (PCB* process = pageQueue->first_pro; process != NULL; process = process->next) {
            if (new_last_used < old_last_used) {
                oldestProcess = process;
                prevProcess = process;
            }
        }

        printf("LRU替换进程 %d\n", oldestProcess->PID);

        // 将最久未使用的进程从队列中移除
        if (prevProcess) {
            prevProcess->next = oldestProcess->next;
        }
        else {
            pageQueue->first_pro = oldestProcess->next;
        }

        free(oldestProcess);  // 释放内存
        mem -= oldestProcess->size;  // 更新内存使用情况
    }

    // 将新进程加载到内存
    newProcess->Address = mem;
    mem += newProcess->size;  // 更新内存使用情况

    // 将新进程加入队列

    if (pageQueue->size == 0) {
        pageQueue->first_pro = newProcess;
        pageQueue->last_pro = newProcess;
    }
    else {
        pageQueue->last_pro->next = newProcess;
        pageQueue->last_pro = newProcess;
    }

    pageQueue->size++;
    printf("新进程 %d 加载到内存\n", newProcess->PID);
}

void LFUPageScheduling(PCBQueue* pageQueue, PCB* newProcess) {
    // 判断内存是否已满
    if (mem >= tp_mem) {
        // 内存已满，进行替换
        PCB* prevProcess = NULL;
        PCB* lfuProcess = pageQueue->first_pro;

        // 寻找最少使用的进程（假设有一个usage_count字段表示使用频率）
        for (PCB* process = pageQueue->first_pro; process != NULL; process = process->next) {
            if (process->usage_count < lfuProcess->usage_count) {
                lfuProcess = process;
                prevProcess = process;
            }
        }

        printf("LFU替换进程 %d\n", lfuProcess->PID);

        // 将最少使用的进程从队列中移除
        if (prevProcess) {
            prevProcess->next = lfuProcess->next;
        }
        else {
            pageQueue->first_pro = lfuProcess->next;
        }

        free(lfuProcess);  // 释放内存
        mem -= lfuProcess->size;  // 更新内存使用情况
    }

    // 将新进程加载到内存
    newProcess->Address = mem;
    mem += newProcess->size;  // 更新内存使用情况

    // 将新进程加入队列
    newProcess->usage_count = 1;  // 初始化使用计数
    if (pageQueue->size == 0) {
        pageQueue->first_pro = newProcess;
        pageQueue->last_pro = newProcess;
    }
    else {
        pageQueue->last_pro->next = newProcess;
        pageQueue->last_pro = newProcess;
    }

    pageQueue->size++;
    printf("新进程 %d 加载到内存\n", newProcess->PID);
}

// 重排队列
void PageScheduling(PCBQueue* q)
{
    if (NULL == q)
    {
        return;
    }

    int n = q->size;

    if (n != 0)
    {
        PCB* tp_p;			// 临时PCB
        PCB* tp_arr[MAX];	// 临时PCB数组

        tp_p = q->first_pro->next;
        for (int i = 0; i < n; i++)
        {
            //tp_arr[i] = DeQueue(q, tp_p);
            tp_arr[i] = DeQueue(q);
        }

        switch (page_scheduling_alo)
        {
        case 1:
            printf("按FIFO页面调度算法重新排序!\n");
            FCFS(tp_arr, n);
            break;
        case 2:
            printf("按LRU页面调度算法重新排序!\n");
            SPF(tp_arr, n);
            break;
        case 3:
            printf("按LFU页面调度算法重新排序!\n");
            PRIORITY(tp_arr, n);
            break;
        default:
            printf("按FIFO页面调度算法重新排序!\n");
            FCFS(tp_arr, n);
            break;
        }

        //printf("\n每次淘汰的页面号：");
        for (int i = 0; i < n; i++)
        {
            //printf("%d ", tp_arr[i]->PID); // 输出每次淘汰的页面号
            EnQueue(q, tp_arr[i]);
        }
        //printf("\n淘汰总页面数：");
    }
}