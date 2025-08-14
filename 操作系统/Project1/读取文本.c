#include"DEFINITION.h"

void readRequests(const char* filename, int requests[], int* numRequests) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

	/*��ȡ�ı�����*/
    // *numRequests = fread(requests, sizeof(int), MAX_TRACKS, file);
	// printf("\nnumRequests:%d\n", *numRequests);
	int index = 0;
	while (fscanf(file, "%d", &requests[index]) == 1) {
		index++;
	}
	*numRequests = index;

    fclose(file);
}

const char* readFile() {
    // �ļ�·��
    const char* filename = "..\\data\\Ԥ�����ַ�.txt";

    // ���ļ�
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        return NULL;  // ���� NULL ��ʾ���ļ�ʧ��
    }

    // ����һ���㹻����ļ����ݵ��ַ�����
    static char buffer[100];  // ʹ�� static ȷ������ʱ�ڴ治������

    // ʹ�� fscanf ��ȡ�ļ����ݵ��ַ�����
    if (fscanf(file, "%99[^\n]", buffer) != 1) {  // ��ȡ��� 99 ���ַ�ֱ���������з�
        perror("��ȡ�ļ�����ʧ��");
        fclose(file);
        return NULL;  // ��ȡʧ�ܣ����� NULL
    }

    // �ر��ļ�
    fclose(file);

    return buffer;  // ���ض�ȡ��������
}

void fileManage()
{
    int requests[MAX_TRACKS];
    int numRequests;

    readRequests("..\\data\\�ŵ�����˳��.txt", requests, &numRequests);

    printf("\n******************************\n*��ѡ��ŵ������㷨:\n");
    printf("*\t1: �����ȷ���(T_FCF)\n");
    printf("*\t2: ���Ѱ������(T_SSTF)\n");
    printf("*\t3: �����㷨(T_SCAN)\n");
    printf("******************************\n");

    scanf("%d", &Track_alo);
	getchar();
	switch (Track_alo)
	{
	case 1:
		printf("\n******************************\n*��FCFS�ŵ������㷨��������!\n");
		T_FCFS(requests, numRequests);
        printf("******************************\n");
		break;
	case 2:
		printf("\n******************************\n*��SSTF�ŵ������㷨��������!\n");
		T_SSTF(requests, numRequests, 0);
        printf("******************************\n");
		break;
	case 3:
		printf("\n******************************\n*��SCAN�ŵ������㷨��������!\n");
        int tp_direction = 0;
        printf("*****************\n*ѡ���ƶ�����: \n*0: �͹��\n*1: �߹��\n");
        printf("*****************\n");
        scanf("%d", &tp_direction);
        getchar();
		T_SCAN(requests, numRequests, 0, tp_direction);
        printf("******************************\n");
		break;
	default:
		printf("\n******************************\n*��FCFS�ŵ������㷨��������!\n");
		T_FCFS(requests, numRequests);
        printf("******************************\n");
		break;
	}

    strncpy(str, readFile(), sizeof(str) - 1);	 // �����ַ���������һ���ַ�������ֹ��
    str[sizeof(str) - 1] = '\0';				 // ȷ���ַ����Կ��ַ���ֹ
    printf("\nԤ�����ַ�: %s\n", str);

    return 0;
}