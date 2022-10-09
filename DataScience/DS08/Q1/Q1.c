#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAXSTACK 100
#define EOS 0
char stack[MAXSTACK];
int top = -1;

int pop() {
	if (top < 0) {
		printf("stack empty");
		return top;
	}
	return stack[top--];
}
char push(char token) {
	if (MAXSTACK - 1 == top) {
		printf("stack full");
		return 0;
	}
	stack[++top] = token;
}

void postfix(char* infix, char* postfix) {
	int cnt = 0;
	char token;
	push(EOS);
	for (int i = 0; infix[i] != 0; i++) {
		token = infix[i];
		if (isDigit(token))
			postfix[cnt++] = token;
		else {
			if (token == ')') {
				do {
					postfix[cnt++] = pop();
				} while (postfix[cnt - 1] != '(');
				cnt--;
				continue;
			}
			while (getPriorityInStack(stack[top]) >= getPriority(token)) {
				postfix[cnt++] = pop();
			}  
			push(token);
		}
	}
	do {
		postfix[cnt++] = pop();
	} while (postfix[cnt - 1] != EOS);	
}

int isDigit(char token) {
	if ('0' <= token && token <= '9')
		return 1;
	else
		return 0;
}
int getPriority(char token) {
	switch (token) {
	case'(':case')':
		return 10;
	case'*': case'/': case '%':
		return 5;
	case'+': case'-':
		return 2;
	}
}
int getPriorityInStack(char token) {
	switch (token) {
	case'(':
		return 1;
	case')':
		return 10;
	case'*': case'/': case '%':
		return 5;
	case'+': case'-':
		return 2;
	}
}

int eval(char* postfix) {
	char token, op1, op2;
	for (int i = 0; postfix[i] != 0; i++) {
		token = postfix[i];
		if (isDigit(token))
			push(token - '0');
		else {
			op1 = pop(); op2 = pop();
			switch (token) {
			case '*':
				push(op2 * op1);
				break;
			case '/':
				push(op2 / op1);
				break;
			case'%':
				push(op2 % op1);
				break;
			case '+': 
				push(op2 + op1);
				break;
			case '-':
				push(op2 - op1);
			}
		}
	}
	return pop();
}

int main() {
	FILE* f;
	int i = 0;
	char in[MAXSTACK] = { NULL };
	char post[MAXSTACK] = { NULL };

	f = fopen("input.txt", "r");
	
	fscanf(f, "%s", in);
	postfix(in, post);

	printf("Postfix : ");
	for (int i = 0; i < 100; i++) {
		if (post[i] != NULL) {
			printf("%c", post[i]);
		}
	}

	int result = eval(post);
	printf("\nResult : %d", result);

	fclose(f);
	return 0;
}
