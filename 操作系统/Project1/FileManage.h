#pragma once

#define MAX_TRACKS 100

/*------------------------------ 全局变量 -------------------------------*/
extern int disk[1024][MAX_TRACKS];		// 磁盘
extern int Track_alo;					// 磁盘选择算法的标记：1为T_FCFS，2为T_SSTF，3为T_SCAN
extern int serviceOrder[MAX_TRACKS];	// 存储磁盘调度算法中的服务顺序
extern int totalTracks;					// 记录当前serviceOrder数组中已经存储的磁道数量


/*------------------------------ 定义函数 -------------------------------*/
void fileManage();						// 磁盘调度
const char* readFile();					// 读取文件
void T_FCFS(int requests[], int numRequests);
void T_SSTF(int requests[], int numRequests, int currentTrack);
void T_SCAN(int requests[], int numRequests, int currentTrack, int direction);
