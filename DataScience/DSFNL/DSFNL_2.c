#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, z) (z = x, x = y, y = z)

int** arr;
int*** result;

void MSD(int record, int n) {
	int* temp;
	for (int i = 0; i < record; i++) {
		for (int j = 0; j < record - 1; j++) {
			if (arr[j][n] < arr[j + 1][n]) {
				SWAP(arr[j], arr[j + 1], temp);
			}
		}
	}
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");
	int record, field;
	fscanf(f, "%d %d\n", &record, &field);

	arr = calloc(record, sizeof(int*));
	for (int i = 0; i < record; i++) {
		arr[i] = calloc(field, sizeof(int));
	}

	for (int i = 0; i < record; i++) {
		for (int j = 0; j < field; j++) {
			int temp;
			fscanf(f, "%d ", &temp);
			arr[i][j] = temp;
		}
	}

	for (int i = field; i >= 0; i--) {
		MSD(record, i);
	}

	for (int i = 0; i < record; i++) {
		for (int j = 0; j < field; j++) {
			printf("%d ", arr[i][j]);
		}
		puts("");
	}

	return 0;
}