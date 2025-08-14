#pragma once

#define BUF 3  			// ����Ĵ�С
#define MAX 30  		// ������������ַ�

/*------------------------------ �ṹ�� --------------------------------*/
typedef struct PCB {
	char name[10];      // ������
	int PID;			// ����PID 
	char state[10];    	// ����״̬
	int arrive_time;	// ����ʱ��
	int priority;		// ���ȼ�
	int start_time;		// ʵ�ʵ���ʱ��
	int running_time;	// ����ʱ�� 
	int end_time;		// ����ʱ��
	int copy_run_time;	// ����ʱ��Ƭ��ת
	int usage_count;	// ��ʹ�ô���
	int zztime;			// ��תʱ�� 
	double dqzztime;	// ��Ȩ��תʱ�� 
	char reason[10];    // ����������ԭ��
	int Address;		// �ڴ��λ��
	int size;			// ���̴�С

	int breakp;         // �ϵ㱣��
	int break_time;		// �ϵ�ʱ��

	int flag;			// 0Ϊ�����ߣ�1Ϊ������ 
	struct PCB* next;   // ����ʱ��˳��
}PCB, Process;

typedef struct semaphore
{
	char name[10];
	int num;
	int flag;			// 0Ϊempty, 1Ϊfilled��2Ϊrw_mux 
}Semaphore;

typedef struct PCBQueue
{
	PCB* first_pro;
	PCB* last_pro;
	int size;
}PCBQueue;

/*------------------------------ ȫ�ֱ��� -------------------------------*/
extern int PRODUCT;								// ����������
extern int CONSUME; 							// ����������
extern PCB pro[MAX];							// �����߽��� + �����߽��� 
extern int PROCESS; 							// ������������� 
extern int pc;									// ���������
extern int count;								// �ַ�������
extern int con_cnt;								// ���Ѽ�����
extern int tp_time;								// ��ʱ 
extern Semaphore* empty, * filled, * rw_mux;	// ��ʼ���ź���

extern int len; 								// ���볤��
extern int sp; 									// string��ָ��
extern int in; 									// ������ָ��
extern int out; 								// ������ָ��
extern char temp; 								// ����ӡ����ʱ��Ʒ
extern char rec_p[MAX];							// ������¼
extern int p_f;									// ������¼ͷָ��
extern int p_l;									// ������¼βָ��
extern char rec_c[MAX];							// ���Ѽ�¼
extern int c_f;									// ���Ѽ�¼ͷָ��
extern int c_l;									// ���Ѽ�¼βָ��

extern PCBQueue* ready_queue;					// �������� 
extern PCBQueue* block_queue;					// �������� 
extern PCBQueue* product_block_queue;			// �������������� 
extern PCBQueue* consume_block_queue;			// �������������� 
extern PCBQueue* run_queue;						// ���ж��� 

/*------------------------------ ���庯�� -------------------------------*/
void Init();							// ��ʼ��  
void CopyProcess(PCB* pro1, PCB* pro2);	// ������pro2����Ϣ���Ƶ�����pro1��
void EnQueue(PCBQueue* q, PCB* p);		// ������� 
void Clean_Queue(PCBQueue* q);			// ��ն���
void ReorderQueue(PCBQueue* q);			// ���Ŷ���
int BlockProCount();					// �������̼���
PCB* DeQueue(PCBQueue* q);				// �������
void P(Semaphore* mux, PCB* p);     	// P����
void V(Semaphore* mux, PCB* p);    		// V����
void Block(Semaphore* mux, PCB* p);		// ��������
void Wakeup(Semaphore* mux, PCB* p);	// ���Ѻ���
void Control();   						// ���������
void Processor(PCB* p);					// �����ִ��
void PrintStatus();  					// ��ӡ����
void CloseProcess();					// �ر�ʣ�����
void DestroyQueue(PCBQueue* q);			// �ͷŶ���
void Destroymaphore(Semaphore* mux);	// �ͷ��ź��� 
