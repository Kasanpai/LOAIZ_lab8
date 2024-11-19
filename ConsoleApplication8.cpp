//ЗАДАНИЕ 1.1-2

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

vector<vector<int>> generateG(int versh) {
	vector<vector<int>> G(versh, vector<int>(versh, 0));

	for (int i = 0; i < versh; i++) {
		for (int j = i+1; j < versh; j++) {
			if (rand() % 2 == 1) {
				G[i][j] = 1;
				G[j][i] = 1;
			}
		}
	}
	return G;
}

void printG(vector<vector<int>>& G) {
	cout << "Матрица смежности: " << endl;
	for (int i = 0; i < G.size(); i++) {
		for (int val : G[i]) {
			cout << val << " ";
		}
		cout << endl;
	}
}

void BFS(vector<vector<int>> G, int start) {
	int n = G.size();
	vector<bool> visited(n, false);
	queue<int> Q;

	Q.push(start);
	visited[start] = true;

	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		cout << v+1 << " ";

		for (int i = 0; i < n; ++i) {
			if (G[v][i] == 1 && !visited[i]) {
				Q.push(i);
				visited[i] = true;
			}
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(5435234623462343726);

	int versh;
	cout << "Введите количество вершин: ";
	cin >> versh;

	vector<vector<int>> G1 = generateG(versh);
	printG(G1);

	cout << endl << "Пройденные вершины:" << endl;
	BFS(G1, 0);
	cout << endl;
}
