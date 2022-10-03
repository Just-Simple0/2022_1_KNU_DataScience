#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* f1;
	if ((f1 = fopen("input.txt", "r")) == NULL)
	{
		printf("File Error\n");
		exit(1);
	}

	int min, max, num;

	fscanf(f1, "%d ", &num);
	min = num;
	max = num;

	for (int i = 0; i < 9; i++) {
		fscanf(f1, "%d ", &num);

		if (num < min) {
			min = num;
		}

		if (num > max) {
			max = num;
		}
	}

	printf("Min: %d\nMax: %d", min, max);

	return 0;
}