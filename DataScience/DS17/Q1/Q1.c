#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

int check[MAX_SIZE][MAX_SIZE] = { 0 };
int row, col;

//������ ���� edge �� �ּڰ� ã��
void find_small(int n, int m) {
	int min = 10000;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (check[i][j] > 0 && check[i][j] <= min) {
				min = check[i][j];
				row = i;
				col = j;
			}
		}
	}
	check[row][col] = -1;
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");
	
	//�־��� �׷����� vertex ���� ��������
	int vercnt;
	fscanf(f, "%d", &vercnt);

	int** graph = calloc(vercnt, sizeof(int*));
	for (int i = 0; i < vercnt; i++) {
		graph[i] = calloc(vercnt, sizeof(int));
	}

	//�־��� �׷��� �޾ƿ��� edge�� ���� ����
	int edgecnt = 0;
	for (int i = 0; i < vercnt; i++) {
		for (int j = 0; j < vercnt; j++) {
			int temp;
			fscanf(f, "%d", &temp);
			if ((j > i) && temp)
				edgecnt++;
			graph[i][j] = temp;
		}
	}

	//find_small �Լ����� ���� �� ó���� ���� check ����
	for (int i = 0; i < vercnt; i++) {
		for (int j = i; j < vercnt; j++) {
			check[i][j] = graph[i][j];
		}
	}

	//edge�� row, col ���� �迭 ����
	int** edge = calloc(2, sizeof(int*));
	for (int i = 0; i < 2; i++) {
		edge[i] = calloc(vercnt, sizeof(int));
	}

	//edge �������� ����
	for (int i = 0; i < edgecnt; i++) {
		find_small(vercnt, vercnt);
		edge[0][i] = row;
		edge[1][i] = col;
	}

	//cycle table ����
	int* cycle = malloc(sizeof(int) * vercnt);
	for (int i = 0; i < vercnt; i++) {
		cycle[i] = i;
	}

	//���õ� edge ���� �迭 ����
	int** result = malloc(sizeof(int*) * 2);
	for (int i = 0; i < 2; i++) {
		result[i] = malloc(sizeof(int) * (vercnt - 1));
	}

	//Kruskal's Algorithm
	int cnt = 0;
	int n = 0;
	int sum = 0;
	while (cnt < vercnt - 1) {
		int v1 = edge[0][n];
		int v2 = edge[1][n];
		int c1 = cycle[v1];
		int c2 = cycle[v2];

		if (c1 != c2) {
			for (int i = 0; i < vercnt; i++) {
				if (cycle[i] == c2)
					cycle[i] = c1;
			}
			result[0][cnt] = v1;
			result[1][cnt++] = v2;
			sum += graph[v1][v2];
		}
		n++;
	}

	printf("Selected Edges: ");
	for (int i = 0; i < cnt; i++) {
		if (i == vercnt - 2)
			printf("(%d, %d)", result[0][i], result[1][i]);
		else
			printf("(%d, %d), ", result[0][i], result[1][i]);
	}
	printf("\nCost: %d", sum);

	

	return 0;
}