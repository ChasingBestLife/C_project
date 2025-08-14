#pragma once
#include"Process.h"

#define MMAX 128		// 默认内存大小，K
#define MPAGE 1024		// 最大页面号

/*------------------------------ 全局变量 -------------------------------*/
extern int mem;							// 内存
extern int tp_mem;						// 临时内存
extern int* m;							// 内存数组
extern int memory_allocation_method;	// 内存分配方式，1为固定分区方式，2为可变分区方式

extern int alo;							// 选择进程调度算法的标记：1为FCFS，2为短进程，3为优先级，4为时间片，5为高响应比
extern int page_scheduling_alo;			// 页面调度算法的表级，1为FIFO、2为LRU，3为LFU
extern int page_die_num[MPAGE];			// 淘汰页号
extern int page_pointer;				// 淘汰页号数组指针
extern int page_miss_flag;				// 缺页标识，1表示缺页
extern int pageFaults;					// 缺页总次数

/*------------------------------ 定义函数 -------------------------------*/
void setMem();							// 初始化内存
int memAllocation(PCB* p);				// 内存是否有足够空间
void memClear(PCB* p);					// 内存中清除指定进程
void memCloseProcess();					// 内存清空

void FCFS(PCB** arr, int n);			// 先进先出调度算法 
void SPF(PCB** arr, int n);				// 非抢占式短进程优先调度算法
void PRIORITY(PCB** arr, int n);		// 静态优先级调度算法
void HRRN(PCB** arr, int n);			// 高响应比优先调度算法
void Alogorithm();						// 算法

void FIFOPageScheduling(PCBQueue* pageQueue, PCB* newProcess);	// FIFO页面调度算法
void LRUPageScheduling(PCBQueue* pageQueue, PCB* newProcess);	// LRU页面调度算法
void LFUPageScheduling(PCBQueue* pageQueue, PCB* newProcess);	// LFU页面调度算法
void PageScheduling(PCBQueue* q);