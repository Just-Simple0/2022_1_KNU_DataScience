#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int num, sum = 0;
	printf("Number : ");
	scanf("%d", &num);

	for (int i = 1; i < num; i++) {
		if (num % i == 0) {
			sum += i;
		}
	}

	if (sum == 1)
		printf("Prime");
	else
		printf("Not Prime");

	return 0;
}