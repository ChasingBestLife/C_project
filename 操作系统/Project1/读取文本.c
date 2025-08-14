#include"DEFINITION.h"

void readRequests(const char* filename, int requests[], int* numRequests) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

	/*读取文本内容*/
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
    // 文件路径
    const char* filename = "..\\data\\预生产字符.txt";

    // 打开文件
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("无法打开文件");
        return NULL;  // 返回 NULL 表示打开文件失败
    }

    // 定义一个足够存放文件内容的字符数组
    static char buffer[100];  // 使用 static 确保返回时内存不被销毁

    // 使用 fscanf 读取文件内容到字符数组
    if (fscanf(file, "%99[^\n]", buffer) != 1) {  // 读取最多 99 个字符直到遇到换行符
        perror("读取文件内容失败");
        fclose(file);
        return NULL;  // 读取失败，返回 NULL
    }

    // 关闭文件
    fclose(file);

    return buffer;  // 返回读取到的内容
}

void fileManage()
{
    int requests[MAX_TRACKS];
    int numRequests;

    readRequests("..\\data\\磁道服务顺序.txt", requests, &numRequests);

    printf("\n******************************\n*请选择磁道调度算法:\n");
    printf("*\t1: 先来先服务(T_FCF)\n");
    printf("*\t2: 最短寻道优先(T_SSTF)\n");
    printf("*\t3: 电梯算法(T_SCAN)\n");
    printf("******************************\n");

    scanf("%d", &Track_alo);
	getchar();
	switch (Track_alo)
	{
	case 1:
		printf("\n******************************\n*按FCFS磁道调度算法重新排序!\n");
		T_FCFS(requests, numRequests);
        printf("******************************\n");
		break;
	case 2:
		printf("\n******************************\n*按SSTF磁道调度算法重新排序!\n");
		T_SSTF(requests, numRequests, 0);
        printf("******************************\n");
		break;
	case 3:
		printf("\n******************************\n*按SCAN磁道调度算法重新排序!\n");
        int tp_direction = 0;
        printf("*****************\n*选择移动方向: \n*0: 低轨道\n*1: 高轨道\n");
        printf("*****************\n");
        scanf("%d", &tp_direction);
        getchar();
		T_SCAN(requests, numRequests, 0, tp_direction);
        printf("******************************\n");
		break;
	default:
		printf("\n******************************\n*按FCFS磁道调度算法重新排序!\n");
		T_FCFS(requests, numRequests);
        printf("******************************\n");
		break;
	}

    strncpy(str, readFile(), sizeof(str) - 1);	 // 复制字符串，保留一个字符给空终止符
    str[sizeof(str) - 1] = '\0';				 // 确保字符串以空字符终止
    printf("\n预生产字符: %s\n", str);

    return 0;
}