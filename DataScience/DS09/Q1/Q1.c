#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
}node;

void addNode(int data, node** head, node** tail) {
	node* newnode = malloc(sizeof(node));	
	newnode->data = data;
	if ((*tail) != NULL) {
		newnode->next = (*tail)->next;
		(*tail)->next = newnode;
		(*tail) = newnode;
	}
	else {
		(*head) = newnode;
		(*tail) = newnode;
		(*tail)->next = NULL;
	}
}

void printNode(node** head) {
	node* curr = (*head);
	while (curr != NULL) {
		printf("(%p, %d, %p)", curr, curr->data, curr->next);
		curr = curr->next;
	}
}

void concatenate(node** t1, node** h2) {
	(*t1)->next = (*h2);
}

void invert(node** head) {
	node* lead = (*head);
	node* middle = NULL;
	node* trail;
	while(lead) {
		trail = middle;
		middle = lead;
		lead = lead->next;
		middle->next = trail;
	}
	(*head) = middle;
}

int main() {
	FILE* f;
	node* h1 = NULL;
	node* t1 = NULL;
	node* h2 = NULL;
	node* t2 = NULL;

	f = fopen("input1.txt", "r");
	for (int i = 0; i < 100; i++) {
		if (feof(f))
			break;
		int temp;
		fscanf(f, "%d ", &temp);
		addNode(temp, &h1, &t1);
	}
	fclose(f);
	printf("First :\n");
	printNode(&h1);

	f = fopen("input2.txt", "r");
	for (int i = 0; i < 100; i++) {
		if (feof(f))
			break;
		int temp;
		fscanf(f, "%d ", &temp);
		addNode(temp, &h2, &t2);
	}
	fclose(f);
	printf("\n\nSecond :\n");
	printNode(&h2);

	concatenate(&t1, &h2);
	printf("\n\nConcatenate : \n");
	printNode(&h1);

	invert(&h1);
	printf("\n\nInvert : \n");
	printNode(&h1);

	node* curr = h1;
	while (curr != NULL) {
		node* next = curr->next;
		free(curr);
		curr = next;
	}
	return 0;
}