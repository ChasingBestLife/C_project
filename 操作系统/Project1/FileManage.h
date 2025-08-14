#pragma once

#define MAX_TRACKS 100

/*------------------------------ ȫ�ֱ��� -------------------------------*/
extern int disk[1024][MAX_TRACKS];		// ����
extern int Track_alo;					// ����ѡ���㷨�ı�ǣ�1ΪT_FCFS��2ΪT_SSTF��3ΪT_SCAN
extern int serviceOrder[MAX_TRACKS];	// �洢���̵����㷨�еķ���˳��
extern int totalTracks;					// ��¼��ǰserviceOrder�������Ѿ��洢�Ĵŵ�����


/*------------------------------ ���庯�� -------------------------------*/
void fileManage();						// ���̵���
const char* readFile();					// ��ȡ�ļ�
void T_FCFS(int requests[], int numRequests);
void T_SSTF(int requests[], int numRequests, int currentTrack);
void T_SCAN(int requests[], int numRequests, int currentTrack, int direction);
