#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

int main() {
	FILE* f;
	f = fopen("input.txt", "r");
	int a, b;
	fscanf(f, "%d %d", &a, &b);
	fclose(f);


	if (a > MAX || b > MAX) {
		printf("Too Big Number");
		exit(3);
	}

	int a_sum = 0;
	for (int i = 1; i < a; i++) {
		if ((a % i) == 0)
			a_sum += i;
	}
	int b_sum = 0;
	for (int i = 1; i < b; i++) {
		if ((b % i) == 0)
			b_sum += i;
	}

	if (a == b_sum && b == a_sum)
		printf("Amicable");
	else
		printf("Not Amicable");

	return 0;
}