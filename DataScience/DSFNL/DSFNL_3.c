#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* tree;
int winner;

int CalcSize(int l) {
	int result = 1;
	for (int i = 0; i < l; i++) {
		result *= 2;
	}

	return ((result * 2) - 1);
}

void winnertree(int run, int size) {
	int index = run;
	while (index != 1) {
		for (int i = index; i < size; i = i + 2) {
			if (tree[i] <= tree[i + 1])
				tree[i / 2] = tree[i];
			else
				tree[i / 2] = tree[i + 1];
		}
		index /= 2;
		size /= 2;
	}
	winner = tree[1];
}

void losertree(int run, int size) {
	int w = 1;
	for (int i = 0; i < run; i++) {
		if (tree[i] != tree[i * 2])
			tree[i] = tree[i * 2];
		else if (tree[i] != tree[i * 2 + 1])
			tree[i] = tree[i * 2 + 1];
	}
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");
	int run, n;

	fscanf(f, "%d %d", &run, &n);
	int size = CalcSize(n);

	tree = calloc(size, sizeof(int));

	for (int i = run; i <= size; i++) {
		int temp;
		fscanf(f, "%d ", &temp);
		tree[i] = temp;
	}

	winnertree(run, size);

	printf("Winner : %d\n", winner);
	printf("Winner Tree Level Order : ");
	for (int i = 1; i < run; i++) {
		printf("%d ", tree[i]);
	}

	for (int i = run; i <= size; i++) {
		if (tree[i] == winner)
			tree[i] = INT_MAX / 2;
	}
	losertree(run, size);
	printf("\nLoser Tree Level Order : ");
	for (int i = 1; i < run; i++) {
		printf("%d ", tree[i]);
	}

	return 0;
}