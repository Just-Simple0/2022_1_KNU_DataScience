#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char string[1001];
char pat[1001];
int table[1000];

void failure(char* pat) {
	int length = strlen(pat);

	table[0] = -1;
	int j = 0;
	for (int i = 1; i < length; i++) {
		while (j > 0 && pat[i] != pat[j]) {
			j = table[j - 1];
		}
		if (pat[i] == pat[j]) {
			table[i] = ++j - 1;
		}
		else
			table[i] = -1;
	}
}

int pmatch(char* string, char* pat) {
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);

	while (i < lens && j < lenp) {
		if (string[i] == pat[j]) {
			i++;
			j++;
		}
		else if (j == 0)
			i++;
		else
			j = table[j - 1] + 1;
	}
	return ((j == lenp) ? (i - lenp) : -1);
}

int main() {
	FILE* f;
	

	if ((f = fopen("input.txt", "r")) == NULL) {
		printf("FILE ERROR");
		exit(1);
	}

	fscanf(f, "%s\n%s", string, pat);

	failure(pat);
	int place = pmatch(string, pat);

	int l = strlen(pat);
	printf("Failure function : \nj\t");
	for (int i = 0; i < l; i++) {
		printf("%d ", i);
	}
	printf("\npat\t");
	for (int i = 0; i < l; i++) {
		printf("%c ", pat[i]);
	}
	printf("\nf\t");
	for (int i = 0; i < l; i++) {
		printf("%d ", table[i]);
	}
	printf("\nThe pattern %s is found at the position %d", pat, place);

	return 0;
}