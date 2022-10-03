#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int factorial(int x) {
	if (x == 0 || x == 1)
		return 1;
	else
		return x * factorial(x - 1);
}
int power(int x, int i) {
	int r = 1;
	for (int j = 0; j < i; j++) {
		r = r * x;
	}
	return r;
}

int main() {
	
	int num, knum, now, past = 0;  //입력 받을 수와 현재 무슨 수가 작동(?)중인지를 저장할 변수 선언
	int sum = 0;
	int count = 0;
	int n = 0;
	printf("N, K: ");
	scanf("%d %d", &num, &knum);

	while (1) {
		sum = 0;  //반복 할 때마다 sum 초기화
		now = num;  //현재 작동 중인 수 저장
		for (int i = 0; i < 7; i++) {
			if (num / power(10, (6 - i)) != 0 ){
				n = num / power(10, (6 - i));  
				num = num % power(10, (6 - i)); 
				past = n;
				n = factorial(n);
				sum += n;
			}	
		}
		if (sum == knum)
			break;
		num = sum;
		printf("%d ", now);
	}

	return 0;
}