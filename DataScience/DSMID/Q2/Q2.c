#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUM 1001

void reverse(char *s) {
	int l = strlen(s);
	for (int i = 0; i < (l / 2); i++) {
		char temp = s[i];
		s[i] = s[l - i - 1];
		s[l - i - 1] = temp;
	}
}

int main() {
	FILE* f;
	char a[MAX_NUM] = { NULL }, result[MAX_NUM] = { NULL };
	int b;

	f = fopen("a.txt", "r");
	fscanf(f, "%s", a);
	fclose(f);

	f = fopen("b.txt", "r");
	fscanf(f, "%d", &b);
	fclose(f);


	reverse(a);

	int save = 0;
	for (int i = 0; i < strlen(a); i++) {
		int t = ((a[i] - '0') * b) + save;
		while (t < 0)
			t += '0';
		if (t > 9)
			save = t / 10;
		else
			save = 0;
		result[i] = (t % 10) + '0';
	}
	if (save)
		result[strlen(a)] = save + '0';

	reverse(result);
	printf("\n%s", result);

	return 0;
}