#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//'A' = 65, 'Z' = 90,  'a' = 97, 'z' = 122, '0' = 48, '9' = 57

int lsb, n;

int Calckey(char* s, int len) {
	int result = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] >= 48 && s[i] <= 57)
			result += (s[i] - 48);
		else if (s[i] >= 65 && s[i] <= 90)
			result += (s[i] - 'A' + 36);
		else if (s[i] >= 97 && s[i] <= 122) {
			result += (s[i] - 'a' + 10);
		}
	}

	return result;
}

int* Calcn(int key) {
	int i = 1;
	int count = 1;
	while (1) {
		if ((key / i) < 1)
			break;
		i *= 2;
		count++;
	}
	int temp = key;

	int* arr = calloc(count, sizeof(int));
	for (int j = count - 1; j > 0; j--) {
		arr[j] = temp % 2;
		temp = temp / 2;
	}

	for (int j = lsb; j <= n; j++) {
		printf("%d ", arr[j]);
	}
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");

	fscanf(f, "%d %d\n", &lsb, &n);
	char string[101] = { "\0" };
	fscanf(f, "%s", string);

	int key = Calckey(string, strlen(string));

	printf("Division : %d\n", key % (n * 12 - lsb));
	Calcn(key);

	return 0;
}