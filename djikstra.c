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


void searchDijkstra(int rowAndCol, int** arr, int start);

void reset() {
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
    }
}

void dijkstra() {
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
        fileChar = fgetc(fi);
        if (fileChar == '\n')
            continue;
        fileChar = fgetc(fi);
        while (fileChar != '\n' && fileChar - '0' != -49) {
            char tmp = fileChar;
            fileChar = fgetc(fi);
            if (fileChar == '\n')
                break;
            fileChar = fgetc(fi);
            int num[5] = { 0 };
            int number = 0;
            int numcount = 0;
            int sum = 0;
            while (fileChar != ' ') {
                if (fileChar == '\n' || fileChar == EOF)
                    break;
                num[number] = fileChar - '0';
                number++;
                numcount++;
                fileChar = fgetc(fi);
                //                printf("%c\n", fileChar);
            }
            for (int k = 0; k < number; k++) {
                sum += num[k] * pow(10, (--numcount));
                //                printf("%d\n", sum);
            }
            arr[i][tmp - '0' - 1] = sum;
            if (fileChar == ' ')
                fileChar = fgetc(fi);
            //            printf("%c\n", fileChar);
        }
    }

    int start = 0;
    printf("Graph [%d]\n---------------\n", GraphNum++);
    printf("������: %d\n", start+1);
    searchDijkstra(rowAndCol, arr, start);
    printf("\n================\n");

    for (int i = 0; i < rowAndCol; i++)
        free(arr[i]);
    free(arr);
}

int isEmpty() {
    if (top == -1) {
        return 1;
    }
    return 0;
}

int isFull() {
    if (top >= MAX)
        return true;
    else
        return 0;
}

void push(data) {
    if (isFull())
        printf("�� ��");
    else {
        top++;
        stack[top] = data;
    }
}

int pop() {
    if (isEmpty())
        printf(" ");
    else
        return stack[top--];
}

void printStack() {
    if (!isEmpty()) {
        for (int i = 0; i <= top; i++) {
            printf("%d - ", pop());
        }
    }
}
void searchDijkstra(int rowAndCol, int** arr, int start) {

    for (int i = 0; i < rowAndCol; i++)
        distance[i] = MAX, visited[i] = false;

    distance[start] = 0;
    route[start] = " ";
    route[0] = 0;

    for (int count = 0; count < rowAndCol - 1; count++)
    {
        int min = MAX, index;

        for (int v = 0; v < rowAndCol; v++)
        {
            if (!visited[v] && min > distance[v])
            {
                index = v;
                min = distance[v];
            }
        }
        int u = index;

        for (int v = 0; v < rowAndCol; v++)
        {
            if (!visited[v] && arr[u][v] && distance[u] != MAX && distance[v] > distance[u] + arr[u][v])
            {
                distance[v] = distance[u] + arr[u][v]; //�ִ� �Ÿ� ����
                route[v] = u; //��Ʈ ����
            }
        }

        visited[u] = true;

    }
    for (int i = 1; i < rowAndCol; i++) {
        printf("���� [%d] : ", i + 1);

        if (distance[i]) {
            int a = route[i];
            while (a != 0) {
                push(a + 1);
                a = route[a];
                if (a == 0) {
                    push(route[a] + 1);
                }
            }
            if (!isEmpty())
            {
                printStack();
                top = -1;
            }
            printf("%d - ", route[i] + 1);
        }
        printf("%d, ", i + 1);
        printf("����: %d\n", distance[i]);

    }
}


// file read in main
int main() {
    reset();
    fi = fopen("./input2.txt", "r");
    if (fi == NULL) {
        perror("fopen failed");
        return 1;
    }
    while ((fileChar = fgetc(fi)) != EOF) {
        reset();
        count = 0;
        dijkstra();
        printf("\n");
    }
    fclose(fi);

    return 0;
}
