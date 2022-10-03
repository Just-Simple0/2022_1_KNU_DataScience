#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char arr[]) {
	int l = strlen(arr);
	for (int i = 0; i < (l / 2); i++) {
		int temp = arr[i];
		arr[i] = arr[l - i - 1];
		arr[l - i - 1] = temp;
	}
}

int main() {
	char a[1001] = { 0 }, b[1001] = { 0 }, r1[1002] = { 0 }, r2[1002] = { 0 };
	
	FILE* f1, * f2;
	if ((f1 = fopen("a.txt", "r")) == NULL) {
		printf("FILE NOT OPEN");
		exit(1);
	}
	if ((f2 = fopen("b.txt", "r")) == NULL) {
		printf("FILE NOT OPEN");
		exit(1);
	}

	fscanf(f1, "%s", a);
	fscanf(f2, "%s", b);
	fclose(f1);
	fclose(f2);

	reverse(a);
	reverse(b);
	
	int save = 0;
	int len = strlen(a);
	
	for (int i = 0; i < len; i++) {
		int sum = a[i] - '0' + b[i] - '0' + save;
		while (sum < 0)
			sum += '0';
		if (sum > 9)
			save = 1;
		else
			save = 0;
		r1[i] = sum % 10 + '0';
	}
	if (save == 1)
		r1[len] = '1';
	reverse(r1);
	printf("Addition : %s\n", r1);

	save = 0;
	for (int i = 0; i < len; i++) {
		int diff =  a[i] - '0' - b[i] - '0' + save;
		while (diff < 0)
			diff += '0';
		if (diff > 9) {
			diff = 10 - ('0' - diff);
			save = -1;
		}
		else
			save = 0;
		r2[i] = diff % 10 + '0';
	}
	for (int i = 0; i < len; i++) {
		if (r2[i] != '0' && r2[i + 1] == '0')
			save = i + 1;
	}
	for (int i = save; i < len; i++) {
		r2[i] = '\0';
	}
	reverse(r2);
	printf("Subtraction : %s", r2);

	return 0;
}