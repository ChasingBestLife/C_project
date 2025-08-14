#include"DEFINITION.h"


/*------------------------------ Process -------------------------------*/
int alo = 0;							// 选择算法的标记:1为FCFS，2为短进程，3为优先级，4为时间片，5为高响应比
Semaphore* empty, * filled, * rw_mux;	// 初始化信号量 
int PRODUCT = 2;						// 生产者数量
int CONSUME = 3; 						// 消费者数量
PCB pro[MAX];							// 生产者进程 + 消费者进程 
int PROCESS = 2; 						// 进程最大并行数量
char str[MAX]; 							// 输入的字符串
char buffer[BUF]; 						// 缓冲池
int len; 								// 输入长度
int sp = 0; 							// string的指针
int in = 0; 							// 缓冲区的生产者指针
int out = 0; 							// 缓冲区的消费者指针
char temp; 								// 供打印的临时产品
char rec_p[MAX];						// 生产记录
int p_f = 0;							// 生产记录头指针
int p_l = 0;							// 生产记录尾指针
char rec_c[MAX];						// 消费记录
int c_f = 0;							// 消费记录头指针
int c_l = 0;							// 消费记录尾指针
PCBQueue* ready_queue;					// 就绪队列 
PCBQueue* block_queue;					// 阻塞队列 
PCBQueue* product_block_queue;			// 生产者阻塞队列 
PCBQueue* consume_block_queue;			// 消费者阻塞队列 
PCBQueue* run_queue;					// 运行队列 
int pc;									// 程序计数器
int count;								// 字符计数器
int con_cnt;							// 消费计数器
int tp_time = 0;						// 计时 


/*------------------------------ Memory -------------------------------*/
int mem = MMAX;							// 内存
int tp_mem;								// 临时内存
int* m;									// 内存数组
int memory_allocation_method = 0;		// 内存分配方式，1为固定分区方式，2为可变分区方式
int page_scheduling_alo = 0;			// 页面调度算法的表级，1为FIFO、2为LRU，3为LFU
int page_die_num[MPAGE] = {0};			// 淘汰页号
int page_pointer = 0;					// 淘汰页号数组指针
int page_miss_flag = 0;					// 缺页标识,1表示缺页
int pageFaults = 0;						// 缺页总次数


/*------------------------------ FileManage -------------------------------*/
int disk[1024][MAX_TRACKS] = { 0 };		// 磁盘
int Track_alo;							// 磁盘选择算法的标记：1为T_FCFS，2为T_SSTF，3为T_SCAN
int serviceOrder[MAX_TRACKS];			// 存储磁盘调度算法中的服务顺序
int totalTracks;						// 记录当前serviceOrder数组中已经存储的磁道数量