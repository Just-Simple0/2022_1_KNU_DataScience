#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	
	int n;
	printf("N: ");
	scanf("%d", &n);

	int* arr = NULL;
	arr = (int*)malloc(sizeof(int) * n);
	long seconds = (long)time(NULL);
	srand(seconds);

	double start, end, result;
	
	FILE* f;
	if ((f = fopen("unsorted.txt", "w")) == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}


	for (int i = 0; i < n; i++) {
		arr[i] = rand();
		fprintf(f, "%d ", arr[i]);
	}
	
	fclose(f);

	start = (double)clock() /CLOCKS_PER_SEC;

	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] < arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

	end = (double)clock() / CLOCKS_PER_SEC;

	if ((f = fopen("sorted.txt", "w")) == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	for (int i = 0; i < n; i++)
		fprintf(f, "%d ", arr[i]);
	
	
	fclose(f);
	
	result = end - start;
	printf("Time : %.8f", result);

	free(arr);
	return 0;
}