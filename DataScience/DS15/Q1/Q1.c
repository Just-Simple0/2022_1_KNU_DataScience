#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int winner = 0;

int Calsize(int run) {
	int size = 0;
	while (run > 0) {
		size = size + run;
		run /= 2;
	}
	return size;
}

void winnertree(int* arr, int run, int size) {
	int index = run;
	while (index != 1) {
		for (int i = index; i < size; i = i + 2) {
			if (arr[i] <= arr[i + 1])
				arr[i / 2] = arr[i];
			else
				arr[i / 2] = arr[i + 1];
		}
		index /= 2;
		size /= 2;
	}
	winner = arr[1];
	printf("Winner : %d", winner);
}

void levelorder(int* arr, int size) {
	printf("Level Order: ");
	for(int i = 1; i < size + 1; i++) {
		printf("%d ", arr[i]);
	}
}

int stack[1000];

void add(int* top, int index) {
	stack[++(*top)] = index;
}

int delete(int* top) {
	return stack[(*top)--];
}

void iterinorder(int* arr, int size) {
	printf("InOrder: ");
	int top = -1;
	int index = 1;
	while (1) {
		while (index <= size) {
			add(&top, index);
			index *= 2;
		}

		index = delete(&top);
		if (top < -1)
			break;
		printf("%d ", arr[index]);
		index = index * 2 + 1;
	}
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");
	int run;
	fscanf(f, "%d\n", &run);

	int** key = calloc(10, sizeof(int));
	for (int i = 0; i < run; i++) {
		key[i] = calloc(run, sizeof(int));
	}

	for (int i = 0; i < run; i++) {
		int temp = 0;
		int count = 0;
		while (temp != -1) {
			fscanf(f, "%d ", &temp);
			key[i][count++] = temp;
		}
	}

	int curr = 0;
	int arrsize = Calsize(run);
	int* selectree = malloc(sizeof(int) * arrsize + 1);
	for (int i = 0; i < run; i++) {
		selectree[run + i] = key[i][curr];
	}
	winnertree(selectree, run, arrsize);
	printf("\n");
	levelorder(selectree, arrsize);
	printf("\n");
	iterinorder(selectree, arrsize);

	for (int i = 0; i < run; i++) {
		if (key[i][curr] == winner)
			selectree[run + i] = key[i][curr + 1];
	}

	printf("\n");
	winnertree(selectree, run, arrsize);
	printf("\n");
	levelorder(selectree, arrsize);
	printf("\n");
	iterinorder(selectree, arrsize);

	return 0;
}