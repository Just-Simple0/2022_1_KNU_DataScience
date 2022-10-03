#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* leftChild, * rightChild;
} node;

node* makeNode(int data) {
	node* newnode = malloc(sizeof(node));
	newnode->data = data;
	newnode->leftChild = NULL;
	newnode->rightChild = NULL;
}

void linkLeft(node** parent, node** child) {
	if ((*parent) == NULL || (*child) == NULL)
		return;
	if ((*parent)->leftChild != NULL)
		return;
	(*parent)->leftChild = (*child);
}

void linkRight(node** parent, node** child) {
	if ((*parent) == NULL || (*child) == NULL)
		return;
	if ((*parent)->rightChild != NULL)
		return;
	(*parent)->rightChild = (*child);
}

void Preorderprint(node* curr) {
	if (curr) {
		if (curr->data != NULL)
			printf("%d ", curr->data);
		Preorderprint(curr->leftChild);
		Preorderprint(curr->rightChild);
	}
}

void Inorderprint(node* curr) {
	if (curr) {
		Inorderprint(curr->leftChild);
		if(curr->data != NULL)
			printf("%d ", curr->data);
		Inorderprint(curr->rightChild);
	}
}

void Postorderprint(node* curr) {
	if (curr) {
		Postorderprint(curr->leftChild);
		Postorderprint(curr->rightChild);
		if (curr->data != NULL)
			printf("%d ", curr->data);
	}
}

void freeNode(node* curr) {
	if (curr) {
		freeNode(curr->leftChild);
		freeNode(curr->rightChild);
		free(curr);
	}
}

int main() {
	FILE* f;
	int arr[100] = { 0 };

	f = fopen("input.txt", "r");
	int count = 1;
	while (!feof(f)) {
		int temp;
		fscanf(f, "%d ", &temp);
		if (temp == -1) {
			arr[count] = NULL;
			count++;
		}
		else if (temp < 0) {
			printf("0�� �ƴ� ���� ���� �Է�\n");
			exit(1);
		}
		else {
			arr[count] = temp;
			count++;
		}
	}

	node* narr[100] = { 0 };
	printf("Level Order: ");
	for (int i = 1; i < count; i++) {
		if(arr[i] != NULL)
			printf("%d ", arr[i]);
		narr[i] = makeNode(arr[i]);
	}

	for (int i = 2; i < count; i++) {
		if (i % 2 == 0) {
			linkLeft(&narr[i / 2], &narr[i]);
		}
		else {
			linkRight(&narr[i / 2], &narr[i]);
		}
	}

	printf("\nPreOrder: ");
	Preorderprint(narr[1]);
	printf("\nInOrder: ");
	Inorderprint(narr[1]);
	printf("\nPostOrder: ");
	Postorderprint(narr[1]);

	freeNode(narr[1]);
	return 0;
}