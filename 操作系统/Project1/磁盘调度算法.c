#include"DEFINITION.h"

void T_FCFS(int requests[], int numRequests) {
    // 打印初始服务顺序
    printf("*原磁道请求服务顺序: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    int totalMovement = 0;
    int currentTrack = 0;

    for (int i = 0; i < numRequests; i++) {
        serviceOrder[totalTracks++] = requests[i];
        totalMovement += abs(requests[i] - currentTrack);
        currentTrack = requests[i];
    }

    printf("*FCFS Service Order: ");
    for (int i = 0; i < totalTracks; i++) {
        printf("%d ", serviceOrder[i]);
    }
    printf("\n*Total Movement: %d\n", totalMovement);
}

void T_SSTF(int requests[], int numRequests, int currentTrack) {
    // 打印初始服务顺序
    printf("*当前从第%d条磁道开始移动\n", currentTrack);
    printf("*原磁道请求服务顺序: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    int totalMovement = 0;
    int completedRequests = 0;

    while (completedRequests < numRequests) {
        int closestTrack = -1;
        int minDistance = MAX_TRACKS;

        // 查找离当前磁道最近的请求
        for (int i = 0; i < numRequests; i++) {
            if (requests[i] != -1) {  // 找到一个未处理的请求
                int distance = abs(requests[i] - currentTrack);
                if (distance < minDistance) {
                    closestTrack = requests[i];
                    minDistance = distance;
                }
            }
        }

        // 处理最接近的请求
        if (closestTrack != -1) {
            serviceOrder[totalTracks++] = closestTrack;
            totalMovement += minDistance;
            currentTrack = closestTrack;

            // 将已处理的请求标记为已完成
            for (int i = 0; i < numRequests; i++) {
                if (requests[i] == closestTrack) {
                    requests[i] = -1;  // 标记为已处理
                    break;
                }
            }

            completedRequests++;
        }
        else {
            break;  // 没有更多请求
        }
    }

    // 打印服务顺序
    printf("*SSTF Service Order: ");
    for (int i = 0; i < totalTracks; i++) {
        printf("%d ", serviceOrder[i]);
    }
    printf("\n*Total Movement: %d\n", totalMovement);
}

void T_SCAN(int requests[], int numRequests, int currentTrack, int direction) {
    // 打印初始服务顺序
    printf("*当前从第%d条磁道开始移动\n", currentTrack);
    printf("*原磁道请求服务顺序: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");


    int totalMovement = 0;
    int minTrack = 10000, maxTrack = -1;

    // 找到最小和最大轨道请求
    for (int i = 0; i < numRequests; i++) {
        if (requests[i] != -1) {
            if (requests[i] < minTrack) minTrack = requests[i];
            if (requests[i] > maxTrack) maxTrack = requests[i];
        }
    }

    // 执行SCAN算法
    // 1. 将请求按轨道号升序排序
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = i + 1; j < numRequests; j++) {
            if (requests[i] > requests[j] && requests[i] != -1 && requests[j] != -1) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // 执行SCAN扫描
    while (1) {
        int moved = 0;

        if (direction == 1) {  // 向高轨道方向移动
            // 从当前位置开始向高轨道方向扫描
            for (int i = 0; i < numRequests; i++) {
                if (requests[i] != -1 && requests[i] >= currentTrack) {
                    serviceOrder[totalTracks++] = requests[i];
                    totalMovement += abs(requests[i] - currentTrack);
                    currentTrack = requests[i];
                    requests[i] = -1;  // 标记该请求已完成
                    moved = 1;
                }
            }
            // 如果没有请求被处理过，要么改变方向，要么跳出循环
            if (!moved) 
            {
                if (currentTrack == maxTrack) {
                    break;  // 到达最高轨道且没有更多请求
                } 
                else {
                    direction = -1;  // 改变方向
                }
            }
        }
        else {  // 向低轨道方向移动
            // 从当前位置开始向低轨道方向扫描
            for (int i = numRequests - 1; i >= 0; i--) {
                if (requests[i] != -1 && requests[i] <= currentTrack) {
                    serviceOrder[totalTracks++] = requests[i];
                    totalMovement += abs(requests[i] - currentTrack);
                    currentTrack = requests[i];
                    requests[i] = -1;  // 标记该请求已完成
                    moved = 1;
                }
            }
            // 如果没有请求被处理过，要么改变方向，要么跳出循环
            if (!moved) 
            {
                if (currentTrack == minTrack) {
                    break;  // 到达最低轨道且没有更多请求
                }
                else {
                    direction = 1;  // 改变方向
                }
            }
        }
    }

    // 打印服务顺序和总移动量
    printf("*SCAN Service Order: ");
    for (int i = 0; i < totalTracks; i++) {
        printf("%d ", serviceOrder[i]);
    }
    printf("\n*Total Movement: %d\n", totalMovement);
}
