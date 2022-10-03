#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodepointer;

typedef struct node {
	int coef;
	int expon;
	nodepointer next;
} node;


void addNode(node** head, node** tail, int coef, int expon) {
	node* newNode = malloc(sizeof(node));
	newNode->coef = coef;
	newNode->expon = expon;
	if ((*tail) != NULL) {
		newNode->next = (*tail)->next;
		(*tail)->next = newNode;
		(*tail) = newNode;
	}
	else {
		(*head) = newNode;
		(*tail) = newNode;
		(*tail)->next = NULL;
	}
}

void sum(node** h1, node** h2, node** rh, node** rt) {
	node* a_now = (*h1);
	node* b_now = (*h2);

	while (a_now || b_now) {
		if (a_now->expon > b_now->expon) {
			addNode(rh, rt, a_now->coef, a_now->expon);
			a_now = a_now->next;
		}
		else if (a_now->expon == b_now->expon) {
			int temp = a_now->coef + b_now->coef;
			if (temp)
				addNode(rh, rt, temp, a_now->expon);
			a_now = a_now->next;
			b_now = b_now->next;
		}
		else {
			addNode(rh, rt, b_now->coef, b_now->expon);
			b_now = b_now->next;
		}
	}

	while (a_now) {
		addNode(rh, rt, a_now->coef, a_now->expon);
		a_now = a_now->next;
	}
	while (b_now) {
		addNode(rh, rt, b_now->coef, b_now->expon);
		b_now = b_now->next;
	}
}

void sub(node** head, int k) {
	node* curr = (*head);
	while (curr) {
		curr->coef = curr->coef * k;
		curr = curr->next;
	}
}

int countlen(node** head) {
	int count = 0;
	node* curr = (*head);
	while (curr) {
		count++;
		curr = curr->next;
	}
	return count;
}

void printNode(node** head) {
	node* curr = (*head);
	while (curr) {
		printf("%d %d ", curr->coef, curr->expon);
		curr = curr->next;
	}
}

int main() {
	node* ah = NULL; node* at = NULL;
	node* bh = NULL; node* bt = NULL; 
	node* ch = NULL; node* ct = NULL;
	node* r1h = NULL; node* r1t = NULL;
	node* r2h = NULL; node* r2t = NULL;

	FILE* f;

	int n, c, e;
	f = fopen("a.txt", "r");
	fscanf(f, "%d ", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d %d ", &c, &e);
		addNode(&ah, &at, c, e);
	}
	fclose(f);

	f = fopen("b.txt", "r");
	fscanf(f, "%d ", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d %d ", &c, &e);
		addNode(&bh, &bt, c, e);
	}
	fclose(f);

	f = fopen("c.txt", "r");
	fscanf(f, "%d ", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d %d ", &c, &e);
		addNode(&ch, &ct, c, e);
	}
	fclose(f);

	int k;
	f = fopen("k.txt", "r");
	fscanf(f, "%d", &k);
	fclose(f);

	sub(&ah, k);
	sum(&ah, &bh, &r1h, &r1t);

	k = -1;
	sub(&ch, k);

	sum(&ch, &r1h, &r2h, &r2t);

	int count = countlen(&r2h);
	printf("%d ", count);
	printNode(&r2h);

	


	return 0;
}
