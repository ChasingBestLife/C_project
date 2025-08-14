#include"DEFINITION.h"

void T_FCFS(int requests[], int numRequests) {
    // ��ӡ��ʼ����˳��
    printf("*ԭ�ŵ��������˳��: ");
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
    // ��ӡ��ʼ����˳��
    printf("*��ǰ�ӵ�%d���ŵ���ʼ�ƶ�\n", currentTrack);
    printf("*ԭ�ŵ��������˳��: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    int totalMovement = 0;
    int completedRequests = 0;

    while (completedRequests < numRequests) {
        int closestTrack = -1;
        int minDistance = MAX_TRACKS;

        // �����뵱ǰ�ŵ����������
        for (int i = 0; i < numRequests; i++) {
            if (requests[i] != -1) {  // �ҵ�һ��δ���������
                int distance = abs(requests[i] - currentTrack);
                if (distance < minDistance) {
                    closestTrack = requests[i];
                    minDistance = distance;
                }
            }
        }

        // ������ӽ�������
        if (closestTrack != -1) {
            serviceOrder[totalTracks++] = closestTrack;
            totalMovement += minDistance;
            currentTrack = closestTrack;

            // ���Ѵ����������Ϊ�����
            for (int i = 0; i < numRequests; i++) {
                if (requests[i] == closestTrack) {
                    requests[i] = -1;  // ���Ϊ�Ѵ���
                    break;
                }
            }

            completedRequests++;
        }
        else {
            break;  // û�и�������
        }
    }

    // ��ӡ����˳��
    printf("*SSTF Service Order: ");
    for (int i = 0; i < totalTracks; i++) {
        printf("%d ", serviceOrder[i]);
    }
    printf("\n*Total Movement: %d\n", totalMovement);
}

void T_SCAN(int requests[], int numRequests, int currentTrack, int direction) {
    // ��ӡ��ʼ����˳��
    printf("*��ǰ�ӵ�%d���ŵ���ʼ�ƶ�\n", currentTrack);
    printf("*ԭ�ŵ��������˳��: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");


    int totalMovement = 0;
    int minTrack = 10000, maxTrack = -1;

    // �ҵ���С�����������
    for (int i = 0; i < numRequests; i++) {
        if (requests[i] != -1) {
            if (requests[i] < minTrack) minTrack = requests[i];
            if (requests[i] > maxTrack) maxTrack = requests[i];
        }
    }

    // ִ��SCAN�㷨
    // 1. �����󰴹������������
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = i + 1; j < numRequests; j++) {
            if (requests[i] > requests[j] && requests[i] != -1 && requests[j] != -1) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // ִ��SCANɨ��
    while (1) {
        int moved = 0;

        if (direction == 1) {  // ��߹�������ƶ�
            // �ӵ�ǰλ�ÿ�ʼ��߹������ɨ��
            for (int i = 0; i < numRequests; i++) {
                if (requests[i] != -1 && requests[i] >= currentTrack) {
                    serviceOrder[totalTracks++] = requests[i];
                    totalMovement += abs(requests[i] - currentTrack);
                    currentTrack = requests[i];
                    requests[i] = -1;  // ��Ǹ����������
                    moved = 1;
                }
            }
            // ���û�����󱻴������Ҫô�ı䷽��Ҫô����ѭ��
            if (!moved) 
            {
                if (currentTrack == maxTrack) {
                    break;  // ������߹����û�и�������
                } 
                else {
                    direction = -1;  // �ı䷽��
                }
            }
        }
        else {  // ��͹�������ƶ�
            // �ӵ�ǰλ�ÿ�ʼ��͹������ɨ��
            for (int i = numRequests - 1; i >= 0; i--) {
                if (requests[i] != -1 && requests[i] <= currentTrack) {
                    serviceOrder[totalTracks++] = requests[i];
                    totalMovement += abs(requests[i] - currentTrack);
                    currentTrack = requests[i];
                    requests[i] = -1;  // ��Ǹ����������
                    moved = 1;
                }
            }
            // ���û�����󱻴������Ҫô�ı䷽��Ҫô����ѭ��
            if (!moved) 
            {
                if (currentTrack == minTrack) {
                    break;  // ������͹����û�и�������
                }
                else {
                    direction = 1;  // �ı䷽��
                }
            }
        }
    }

    // ��ӡ����˳������ƶ���
    printf("*SCAN Service Order: ");
    for (int i = 0; i < totalTracks; i++) {
        printf("%d ", serviceOrder[i]);
    }
    printf("\n*Total Movement: %d\n", totalMovement);
}
