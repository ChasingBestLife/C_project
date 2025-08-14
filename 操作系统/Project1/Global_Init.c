#include"DEFINITION.h"


/*------------------------------ Process -------------------------------*/
int alo = 0;							// ѡ���㷨�ı��:1ΪFCFS��2Ϊ�̽��̣�3Ϊ���ȼ���4Ϊʱ��Ƭ��5Ϊ����Ӧ��
Semaphore* empty, * filled, * rw_mux;	// ��ʼ���ź��� 
int PRODUCT = 2;						// ����������
int CONSUME = 3; 						// ����������
PCB pro[MAX];							// �����߽��� + �����߽��� 
int PROCESS = 2; 						// �������������
char str[MAX]; 							// ������ַ���
char buffer[BUF]; 						// �����
int len; 								// ���볤��
int sp = 0; 							// string��ָ��
int in = 0; 							// ��������������ָ��
int out = 0; 							// ��������������ָ��
char temp; 								// ����ӡ����ʱ��Ʒ
char rec_p[MAX];						// ������¼
int p_f = 0;							// ������¼ͷָ��
int p_l = 0;							// ������¼βָ��
char rec_c[MAX];						// ���Ѽ�¼
int c_f = 0;							// ���Ѽ�¼ͷָ��
int c_l = 0;							// ���Ѽ�¼βָ��
PCBQueue* ready_queue;					// �������� 
PCBQueue* block_queue;					// �������� 
PCBQueue* product_block_queue;			// �������������� 
PCBQueue* consume_block_queue;			// �������������� 
PCBQueue* run_queue;					// ���ж��� 
int pc;									// ���������
int count;								// �ַ�������
int con_cnt;							// ���Ѽ�����
int tp_time = 0;						// ��ʱ 


/*------------------------------ Memory -------------------------------*/
int mem = MMAX;							// �ڴ�
int tp_mem;								// ��ʱ�ڴ�
int* m;									// �ڴ�����
int memory_allocation_method = 0;		// �ڴ���䷽ʽ��1Ϊ�̶�������ʽ��2Ϊ�ɱ������ʽ
int page_scheduling_alo = 0;			// ҳ������㷨�ı���1ΪFIFO��2ΪLRU��3ΪLFU
int page_die_num[MPAGE] = {0};			// ��̭ҳ��
int page_pointer = 0;					// ��̭ҳ������ָ��
int page_miss_flag = 0;					// ȱҳ��ʶ,1��ʾȱҳ
int pageFaults = 0;						// ȱҳ�ܴ���


/*------------------------------ FileManage -------------------------------*/
int disk[1024][MAX_TRACKS] = { 0 };		// ����
int Track_alo;							// ����ѡ���㷨�ı�ǣ�1ΪT_FCFS��2ΪT_SSTF��3ΪT_SCAN
int serviceOrder[MAX_TRACKS];			// �洢���̵����㷨�еķ���˳��
int totalTracks;						// ��¼��ǰserviceOrder�������Ѿ��洢�Ĵŵ�����