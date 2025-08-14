#pragma once

#define BUF 3  			// 缓存的大小
#define MAX 30  		// 最大可以输入的字符

/*------------------------------ 结构体 --------------------------------*/
typedef struct PCB {
	char name[10];      // 进程名
	int PID;			// 进程PID 
	char state[10];    	// 运行状态
	int arrive_time;	// 到达时间
	int priority;		// 优先级
	int start_time;		// 实际到达时间
	int running_time;	// 运行时间 
	int end_time;		// 结束时间
	int copy_run_time;	// 用于时间片轮转
	int usage_count;	// 被使用次数
	int zztime;			// 周转时间 
	double dqzztime;	// 带权周转时间 
	char reason[10];    // 若阻塞，其原因
	int Address;		// 内存的位置
	int size;			// 进程大小

	int breakp;         // 断点保护
	int break_time;		// 断点时间

	int flag;			// 0为生产者，1为消费者 
	struct PCB* next;   // 阻塞时的顺序
}PCB, Process;

typedef struct semaphore
{
	char name[10];
	int num;
	int flag;			// 0为empty, 1为filled，2为rw_mux 
}Semaphore;

typedef struct PCBQueue
{
	PCB* first_pro;
	PCB* last_pro;
	int size;
}PCBQueue;

/*------------------------------ 全局变量 -------------------------------*/
extern int PRODUCT;								// 生产者数量
extern int CONSUME; 							// 消费者数量
extern PCB pro[MAX];							// 生产者进程 + 消费者进程 
extern int PROCESS; 							// 进程最大并行数量 
extern int pc;									// 程序计数器
extern int count;								// 字符计数器
extern int con_cnt;								// 消费计数器
extern int tp_time;								// 计时 
extern Semaphore* empty, * filled, * rw_mux;	// 初始化信号量

extern int len; 								// 输入长度
extern int sp; 									// string的指针
extern int in; 									// 生产者指针
extern int out; 								// 消费者指针
extern char temp; 								// 供打印的临时产品
extern char rec_p[MAX];							// 生产记录
extern int p_f;									// 生产记录头指针
extern int p_l;									// 生产记录尾指针
extern char rec_c[MAX];							// 消费记录
extern int c_f;									// 消费记录头指针
extern int c_l;									// 消费记录尾指针

extern PCBQueue* ready_queue;					// 就绪队列 
extern PCBQueue* block_queue;					// 阻塞队列 
extern PCBQueue* product_block_queue;			// 生产者阻塞队列 
extern PCBQueue* consume_block_queue;			// 消费者阻塞队列 
extern PCBQueue* run_queue;						// 运行队列 

/*------------------------------ 定义函数 -------------------------------*/
void Init();							// 初始化  
void CopyProcess(PCB* pro1, PCB* pro2);	// 将进程pro2的信息复制到进程pro1中
void EnQueue(PCBQueue* q, PCB* p);		// 插入队列 
void Clean_Queue(PCBQueue* q);			// 清空队列
void ReorderQueue(PCBQueue* q);			// 重排队列
int BlockProCount();					// 阻塞进程计数
PCB* DeQueue(PCBQueue* q);				// 输出队列
void P(Semaphore* mux, PCB* p);     	// P操作
void V(Semaphore* mux, PCB* p);    		// V操作
void Block(Semaphore* mux, PCB* p);		// 阻塞函数
void Wakeup(Semaphore* mux, PCB* p);	// 唤醒函数
void Control();   						// 处理机调度
void Processor(PCB* p);					// 处理机执行
void PrintStatus();  					// 打印函数
void CloseProcess();					// 关闭剩余进程
void DestroyQueue(PCBQueue* q);			// 释放队列
void Destroymaphore(Semaphore* mux);	// 释放信号量 
