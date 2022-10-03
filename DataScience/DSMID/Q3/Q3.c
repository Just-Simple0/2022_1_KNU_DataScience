#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

int arr[MAX] = { NULL };
avail = -1;

void push(int a) {
	arr[++avail] = a;
}

int pop() {
	return arr[avail--];
}


int isNum(char a) {
	if (a >= '0' && a <= '9')
		return 1;
	else
		return 0;
}

int eval(char *p) {
	int op1, op2;
	int n = 0;
	int r = 0;
	int top = -1;
	char token = p[n];
	while (token != NULL) {
		if (isNum(token))
			push(token - '0');
		else {
			op2 = pop();
			op1 = pop();

			switch (token) {
			case '+':
				push(op1 + op2);
				break;
			case '-':
				push(op1 - op2);
				break;
			case '/':
				push(op1 / op2);
				break;
			case '*':
				push(op1 * op2);
				break;
			case '%':
				push(op1 % op2);
				break;
			case '^':
				r = 1;
				for (int i = 0; i < op2; i++) {
					r = r * op1;
				}
				push(r);
				break;
			case '=':
				if (op1 == op2)
					push(1);
				else
					push(0);
				break;
			case '~':
				push(abs(op1 - op2));
				break;
			}
		}
		token = p[++n];
	}
	return pop();
}

int main() {
	FILE* f;
	char post[MAX] = { NULL };
	f = fopen("input.txt", "r");
	fscanf(f, "%s", post);
	
	int r = 0;
	r = eval(post);

	printf("%d", r);
	
	return 0;
}