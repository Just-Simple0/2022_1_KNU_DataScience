#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* left, * right;
} node;

node* searchinput(node* head, int key) {
	node* temp = head;
	while (temp) {
		if (key == temp->data)
			return NULL;
		if (key < temp->data) {
			if (!(temp->left))
				return temp;
			temp = temp->left;
		}
		else {
			if (!(temp->right))
				return temp;
			temp = temp->right;
		}
	}
	return temp;
}

void insert(node** head, int num) {
	node* temp = searchinput((*head), num);
	node* newnode = malloc(sizeof(node));
	if (temp || !(*head)) {
		newnode->data = num;
		newnode->left = NULL;
		newnode->right = NULL;
		if ((*head)) {
			if (num < temp->data)
				temp->left = newnode;
			else
				temp->right = newnode;
		}
		else
			(*head) = newnode;
	}
}

int search(node* head, int key) {
	node* temp = head;
	while (temp) {
		if (key == temp->data)
			return 1;
		if (key < temp->data) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	return 0;
}

void Preorderprint(node* curr) {
	if (curr) {
		if (curr->data != NULL)
			printf("%d ", curr->data);
		Preorderprint(curr->left);
		Preorderprint(curr->right);
	}
}

void Inorderprint(node* curr) {
	if (curr) {
		Inorderprint(curr->left);
		if (curr->data != NULL)
			printf("%d ", curr->data);
		Inorderprint(curr->right);
	}
}

void Postorderprint(node* curr) {
	if (curr) {
		Postorderprint(curr->left);
		Postorderprint(curr->right);
		if (curr->data != NULL)
			printf("%d ", curr->data);
	}
}

int main() {
	FILE* f;
	node* tree = NULL;
	f = fopen("input1.txt", "r");

	while (!feof(f)) {
		int temp;
		fscanf(f, "%d ", &temp);
		insert(&tree, temp);
	}
	fclose(f);

	printf("Preorder: ");
	Preorderprint(tree);
	printf("\nInorder: ");
	Inorderprint(tree);
	printf("\nPostorder: ");
	Postorderprint(tree);

	f = fopen("input2.txt", "r");
	printf("\nSearch: ");
	while (!feof(f)) {
		int temp;
		fscanf(f, "%d ", &temp);
		printf("%d ", search(tree, temp));
	}

	return 0;
}