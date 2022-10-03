#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, z) (z = x, x = y, y = z)

typedef struct {
	int key;
} element;

element** list;
int num;

void quicksort(int k, int left, int right) {
	element* temp;
	int i, j, pivot;
	if (left < right) {
		i = left + 1; j = right; pivot = list[left][k].key;
		do {
			while (list[i][k].key < pivot) {
				i++;
				if (i >= num)
					break;
			}

			while (list[j][k].key > pivot) {
				j--;
				if (j < 0)
					break;
			}

			if (i < j) {
				SWAP(list[i], list[j], temp);
			}
		} while (i < j);
		SWAP(list[left], list[j], temp);
		quicksort(k, left, j - 1);
		quicksort(k, j + 1, right);
	}
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");

	fscanf(f, "%d ", &num);

	list = calloc(num, sizeof(element*));
	for (int i = 0; i < num; i++) {
		list[i] = calloc(2, sizeof(element));
	}

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < 2; j++) {
			int temp; element newnode;
			fscanf(f, "%d ", &temp);
			newnode.key = temp;
			list[i][j] = newnode;
		}
	}

	quicksort(0, 0, num - 1);
	printf("Key : K1\n");
	for (int i = 0; i < num; i++) {
		printf("%d %d\n", list[i][0].key, list[i][1].key);
	}

	quicksort(1, 0, num - 1);
	printf("\nKey : K2\n");
	for (int i = 0; i < num; i++) {
		printf("%d %d\n", list[i][0].key, list[i][1].key);
	}

	return 0;
}