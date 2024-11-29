#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <list>

using namespace std;

// Определение структуры для очереди на основе списка
struct node {
    int inf;
    struct node* next;
};

// Глобальные указатели для очереди
struct node* head = NULL, * last = NULL;

// Функция для обхода графа в ширину с использованием стандартной очереди
void BFSqueue(int** G, int n, int start) {
    int* visited = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) visited[i] = 0;

    // Очередь
    queue<int> Q;
    Q.push(start);
    visited[start] = 1;

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        printf("%d ", v + 1);

        for (int i = 0; i < n; ++i) {
            if (G[v][i] == 1 && !visited[i]) {
                Q.push(i);
                visited[i] = 1;
            }
        }
    }
    free(visited);
}

struct Graph {
    int numVertices;
    struct node** adjLists;
};

struct node* createNode(int v) {
    struct node* newNode = (node*)malloc(sizeof(struct node));
    newNode->inf = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createAGraph(int vertices) {
    struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (node**)malloc(vertices * sizeof(struct node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}
void addEdge(struct Graph* graph, int s, int d) {
    struct node* newNode = createNode(d);
    struct node* temp = graph->adjLists[s];

    if (temp == NULL || temp->inf > d) {
        newNode->next = temp;
        graph->adjLists[s] = newNode;
    }
    else {
        while (temp->next != NULL && temp->next->inf < d) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    newNode = createNode(s);
    temp = graph->adjLists[d];

    if (temp == NULL || temp->inf > s) {
        newNode->next = temp;
        graph->adjLists[d] = newNode;
    }
    else {
        while (temp->next != NULL && temp->next->inf < s) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Функции для работы с очередью на основе списка
void enqueue(int value) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if (p == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }
    p->inf = value;
    p->next = NULL;

    if (last == NULL) {
        head = p;
        last = p;
    }
    else {
        last->next = p;
        last = p;
    }
}

int isQueueEmpty(void) {
    return head == NULL;
}

int dequeue(void) {
    if (isQueueEmpty()) {
        printf("Очередь пуста\n");
        return -1;
    }
    struct node* temp = head;
    int value = temp->inf;
    head = head->next;
    if (head == NULL) {
        last = NULL;
    }
    free(temp);
    return value;
}

// Функция для обхода графа в ширину с использованием очереди на основе списка
void BFS(int** G, int n, int start) {
    int* visited = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) visited[i] = 0;

    enqueue(start);
    visited[start] = 1;

    while (!isQueueEmpty()) {
        int v = dequeue();
        printf("%d ", v + 1);

        for (int i = 0; i < n; i++) {
            if (G[v][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    free(visited);
}

// Функция для генерации матрицы смежности
int** generateG(int versh) {
    int** G = (int**)malloc(versh * sizeof(int*));
    for (int i = 0; i < versh; i++) {
        G[i] = (int*)malloc(versh * sizeof(int));
        for (int j = 0; j < versh; j++) {
            G[i][j] = 0;
        }
    }

    for (int i = 0; i < versh; i++) {
        for (int j = i + 1; j < versh; j++) {
            if (rand() % 2 == 1) {
                G[i][j] = 1;
                G[j][i] = 1;
            }
        }
    }
    return G;
}

// Функция для создания графа из матрицы смежности
struct Graph* edges(int** G, int size) {
    struct Graph* graph = createAGraph(size);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (G[i][j] == 1) {
                addEdge(graph, i, j);
            }
        }
    }
    return graph;
}
// Функция для печати матрицы смежности
void printG(int** G, int versh) {
    printf("Матрица смежности: \n");
    for (int i = 0; i < versh; i++) {
        for (int j = 0; j < versh; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}
// Обход в ширину с использованием очереди на основе списка
void BFSlists(int** G, int n, int start) {
    int* visited = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) visited[i] = 0;

    enqueue(start);
    visited[start] = 1;

    while (!isQueueEmpty()) {
        int v = dequeue();
        printf("%d ", v + 1);

        for (int i = 0; i < n; i++) {
            if (G[v][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    free(visited);
}

// Обход в ширину с использованием очереди стандартной библиотеки
void BFSqueueLists(int** G, int n, int start) {
    int* visited = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) visited[i] = 0;

    queue<int> Q;
    Q.push(start);
    visited[start] = 1;

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        printf("%d ", v + 1);

        for (int i = 0; i < n; i++) {
            if (G[v][i] == 1 && !visited[i]) {
                Q.push(i);
                visited[i] = 1;
            }
        }
    }
    free(visited);
}

void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        printf("\nVertex %d: ", v + 1);
        while (temp) {
            printf("%d -> ", temp->inf + 1);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    SetConsoleCP(1251);  // Установка кодировки для ввода
    SetConsoleOutputCP(1251);  // Установка кодировки для вывода

    srand(7686546);  // Инициализация генератора случайных чисел

    int versh;
    printf("Введите количество вершин графа: ");
    scanf("%d", &versh);

    // Генерация и печать матрицы смежности
    int** G = generateG(versh);
    printG(G, versh);

    // Обход в ширину с использованием очереди на основе списка
    printf("\nОбход в ширину (Очередь на основе списка из лабы 3):\n");
    clock_t start, end;

    start = clock();
    BFS(G, versh, 0);  // Обход в ширину с помощью списка
    end = clock();

    float bfs = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения (Очередь на основе списка из лабы 3): %f секунд\n", bfs);

    // Обход в ширину с использованием стандартной очереди
    printf("\nОбход в ширину (Queue):\n");

    start = clock();
    BFSqueue(G, versh, 0);  // Обход в ширину с помощью стандартной очереди
    end = clock();

    float bfsQ = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения (Queue): %f секунд\n", bfsQ);

    printf("\nРазница во времени выполнения (Queue - Очередь на основе списка): %f секунд\n", bfsQ - bfs);

    printf("\n1-й граф (представление через списки):\n");
    struct Graph* graph1 = edges(G, versh);
    printGraph(graph1);

    printf("\nОбход в ширину (Очередь на основе списка):\n");
    clock_t start2, end2;

    start2 = clock();
    BFSlists(G, versh, 0);
    end2 = clock();
    float bfs2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения (Очередь на основе списка): %f секунд\n", bfs2);

    printf("\nОбход в ширину (Queue):\n");
    start2 = clock();
    BFSqueueLists(G, versh, 0);
    end2 = clock();
    float bfsQ2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\nВремя выполнения (Queue): %f секунд\n", bfsQ2);
    printf("\nВремя выполнения (Queue - Очередь на основе списка): %f секунд\n", bfsQ2 - bfs2);



    // Освобождение памяти
    for (int i = 0; i < versh; i++) {
        free(G[i]);
    }
    free(G);

    return 0;
}