//ЗАДАНИЕ 1.3
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <windows.h>

#define MAX_VERTICES 100

struct node {
	int vertex;
	struct node* next;
};

struct Graph {
	int numVertices;
	struct node** adjLists;
};

struct node* createNode(int v) {
	struct node* newNode = (node*)malloc(sizeof(struct node));
	newNode->vertex = v;
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
	struct node* temp = graph->adjLists[s];
	while (temp) {
		if (temp->vertex == d) {
			return;
		}
		temp = temp->next;
	}

	struct node* newNode = createNode(d);
	newNode->next = graph->adjLists[s];
	graph->adjLists[s] = newNode;

	temp = graph->adjLists[d];
	while (temp) {
		if (temp->vertex == s) {
			return;
		}
		temp = temp->next;
	}

	newNode = createNode(s);
	newNode->next = graph->adjLists[d];
	graph->adjLists[d] = newNode;
}


struct Graph* edges(int** G, int size) {
	struct Graph* graph = createAGraph(size);

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (G[i][j] == 1) {
				addEdge(graph, i, j);
			}
		}
	}
	return graph;
}

void printGraph(struct Graph* graph) {
	for (int v = 0; v < graph->numVertices; v++) {
		struct node* temp = graph->adjLists[v];
		printf("\nVertex %d: ", v + 1);
		while (temp) {
			printf("%d -> ", temp->vertex + 1);
			temp = temp->next;
		}
		printf("\n");
	}
	printf("\n");
}

int** createG(int size) {
	int** G = NULL;
	G = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		G[i] = (int*)malloc(size * sizeof(int));
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			G[i][j] = rand() % 2;
			if (i == j) G[i][j] = 0;
			G[j][i] = G[i][j];
		}
	}
	return G;
}

void printG(int** G, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void BFS(struct Graph* graph, int start) {
    bool visited[MAX_VERTICES] = { false };
	int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    printf("Результат обхода в ширину: : ", start + 1);

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex + 1);

        struct node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int sizeG1 = 0;
	int** G1 = NULL;

	printf("Введите количество вершин графа: ");
	scanf("%d", &sizeG1);
	G1 = createG(sizeG1);
	printf("1 graf\n");
	printG(G1, sizeG1);
	struct Graph* graph1 = edges(G1, sizeG1);
	printGraph(graph1);

	BFS(graph1, 0);
}

