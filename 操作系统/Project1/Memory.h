#pragma once
#include"Process.h"

#define MMAX 128		// Ĭ���ڴ��С��K
#define MPAGE 1024		// ���ҳ���

/*------------------------------ ȫ�ֱ��� -------------------------------*/
extern int mem;							// �ڴ�
extern int tp_mem;						// ��ʱ�ڴ�
extern int* m;							// �ڴ�����
extern int memory_allocation_method;	// �ڴ���䷽ʽ��1Ϊ�̶�������ʽ��2Ϊ�ɱ������ʽ

extern int alo;							// ѡ����̵����㷨�ı�ǣ�1ΪFCFS��2Ϊ�̽��̣�3Ϊ���ȼ���4Ϊʱ��Ƭ��5Ϊ����Ӧ��
extern int page_scheduling_alo;			// ҳ������㷨�ı���1ΪFIFO��2ΪLRU��3ΪLFU
extern int page_die_num[MPAGE];			// ��̭ҳ��
extern int page_pointer;				// ��̭ҳ������ָ��
extern int page_miss_flag;				// ȱҳ��ʶ��1��ʾȱҳ
extern int pageFaults;					// ȱҳ�ܴ���

/*------------------------------ ���庯�� -------------------------------*/
void setMem();							// ��ʼ���ڴ�
int memAllocation(PCB* p);				// �ڴ��Ƿ����㹻�ռ�
void memClear(PCB* p);					// �ڴ������ָ������
void memCloseProcess();					// �ڴ����

void FCFS(PCB** arr, int n);			// �Ƚ��ȳ������㷨 
void SPF(PCB** arr, int n);				// ����ռʽ�̽������ȵ����㷨
void PRIORITY(PCB** arr, int n);		// ��̬���ȼ������㷨
void HRRN(PCB** arr, int n);			// ����Ӧ�����ȵ����㷨
void Alogorithm();						// �㷨

void FIFOPageScheduling(PCBQueue* pageQueue, PCB* newProcess);	// FIFOҳ������㷨
void LRUPageScheduling(PCBQueue* pageQueue, PCB* newProcess);	// LRUҳ������㷨
void LFUPageScheduling(PCBQueue* pageQueue, PCB* newProcess);	// LFUҳ������㷨
void PageScheduling(PCBQueue* q);