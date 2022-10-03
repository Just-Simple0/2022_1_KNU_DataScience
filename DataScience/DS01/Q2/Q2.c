#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int n1, n2;
	printf("First number: ");
	scanf("%d", &n1);
	printf("Second number: ");
	scanf("%d", &n2);

	int sum1 = 0;
	int sum2 = 0;

	for (int i = 1; i < n1; i++) {
		if (n1 % i == 0) {
			sum1 += i;
		}
	}
	for (int i = 1; i < n2; i++) {
		if (n2 % i == 0) {
			sum2 += i;
		}
	}
	if (sum1 == n2 && sum2 == n1)
		printf("Amicable\n");
	else
		printf("Not Amicable");

	return 0;
}