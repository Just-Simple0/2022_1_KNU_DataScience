#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>;

int main() {
	char isbn[20];
	printf("ISBN : ");
	scanf("%s", isbn);
	int sum = 0;
	int place;
	for (int i = 0; i < 10; i++) {
		if (isbn[i] == '?')
			place = 10 - i;
		else if (isbn[i] == 'X')
			sum += (10 - i) * 10;
		else
			sum += (10 - i) * ((int)(isbn[i] - '0'));
	}
	
	int i = 1;
	int result;
	while (1) {
		if (sum <= (11 * i) && ((11*i) - sum) % place == 0) {
			result = ((11 * i) - sum) / place;
			if (result == 10)
				printf("Missing Digit : X");
			else
				printf("Missing Digit : %d", result);
			break;
		}
		i++;
	}

	return 0;
}