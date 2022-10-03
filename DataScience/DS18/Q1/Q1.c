#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100;

int** cost;
int* distance;
int* found;

int choose(int n) {
	int min = INT_MAX;
	int minpos = -1;
	for (int i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void shortestPath(int n, int sv) {
	for (int i = 0; i < n; i++) {
		found[i] = 0;
		distance[i] = cost[sv][i];
	}
	found[sv] = 1;
	distance[sv] = 0;

	for (int i = 0; i < n - 2; i++) {
		int k = choose(n);
		found[k] = 1;
		for (int j = 0; j < n; j++) {
			if (distance[k] + cost[k][j] < distance[j])
				distance[j] = distance[k] + cost[k][j];
		}
	}
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");
	
	int count, start;
	fscanf(f, "%d %d\n", &count, &start);
	cost = malloc(sizeof(int*) * count);
	for (int i = 0; i < count; i++) {
		cost[i] = calloc(count, sizeof(int));
	}

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			fscanf(f, "%d ", &cost[i][j]);
			if (cost[i][j] == 0)
				cost[i][j] = INT_MAX / 2;
		}
	}

	distance = calloc(count, sizeof(int));
	found = calloc(count, sizeof(int));

	shortestPath(count, start);

	for (int i = 0; i < count; i++) {
		printf("%d ", distance[i]);
	}

	return 0;
}