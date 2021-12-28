#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define INF 100000
#define MAX 1000

bool visited[MAX] = { 0 }; // visited : 1, not visited : 0
FILE* fi;
int queue[MAX] = { 0 };
int distance[MAX] = { 0 };
char fileChar;
int count = 0;
int GraphNum = 1;
int route[MAX] = { 0 };
int stack[MAX];
int top = -1;

void searchDfs(int rowAndCol, int** arr, int start);

void searchBfs(int rowAndCol, int** arr, int start);

void searchDijkstra(int rowAndCol, int** arr, int start);

void reset() {
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
    }
}

void dfsBfs() {
    int rowAndCol = fileChar - '0';
    int** arr = malloc(sizeof(int*) * rowAndCol);
    for (int i = 0; i < rowAndCol; i++) {
        arr[i] = malloc(sizeof(int) * rowAndCol);
    }

    for (int i = 0; i < rowAndCol; i++) {
        for (int j = 0; j < rowAndCol; j++) {
            arr[i][j] = 0;
        }
    }
    fileChar = fgetc(fi);
    for (int i = 0; i < rowAndCol; i++) {
        fileChar = fgetc(fi);
        while (fileChar != '\n' && fileChar - '0' != -49) {
            arr[i][fileChar - '0' - 1] = 1;
            fileChar = fgetc(fi);
            if (fileChar == ' ')
                fileChar = fgetc(fi);
        }
    }

    for (int i = 0; i < rowAndCol; i++) {
        for (int j = 0; j < rowAndCol; j++) {
            if (i == j)
                arr[i][j] = 0;
        }
    }
    int start = 0;
    printf("Graph [%d]\n---------------\n", GraphNum++);
    printf("DFS : ");
    searchDfs(rowAndCol, arr, start);
    reset();
    count = 0;
    printf("\nBFS : ");
    searchBfs(rowAndCol, arr, start);
    printf("\n================\n");

    for (int i = 0; i < rowAndCol; i++)
        free(arr[i]);
    free(arr);
}

void searchDfs(int rowAndCol, int** arr, int start) {
    int there = 0;
    visited[start] = 1;
    count += 1;
    if (count != rowAndCol) {
        printf("%d - ", start + 1);
    }
    else if (count == rowAndCol) {
        printf("%d", start + 1);
    }

    for (int i = 0; i < rowAndCol; i++) {
        if (arr[start][i]) {
            there = i;
            if (!visited[there]) {
                searchDfs(rowAndCol, arr, there);
            }
        }
    }
}

void searchBfs(int rowAndCol, int** arr, int start) {
    int front = 0;
    int rear = 0; // queue pointer
    queue[rear++] = start;
    visited[start] = 1;
    while (front < rear) {
        visited[start] = 1;
        count += 1;
        if (count != rowAndCol) {
            printf("%d - ", queue[front++] + 1);
        }
        else if (count == rowAndCol) {
            printf("%d ", queue[front++] + 1);
        }

        for (int i = 0; i < rowAndCol; i++) {
            if (arr[start][i] == 1 && visited[i] != 1) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
        start = queue[front];
    }
}


// file read in main
int main() {
    reset();
    fi = fopen("./input.txt", "r");
    if (fi == NULL) {
        perror("fopen failed");
        return 1;
    }
    while ((fileChar = fgetc(fi)) != EOF) {
        reset();
        count = 0;
        dfsBfs();
        printf("\n");
    }
    fclose(fi);

    return 0;
}