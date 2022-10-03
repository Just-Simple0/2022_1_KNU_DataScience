#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
} node;

void addNode(int data, node** head) {
	node* newnode = malloc(sizeof(node));
	newnode->data = data;

	if ((*head) != NULL) {
		newnode->next = (*head);
		(*head) = newnode;
	}
	else {
		(*head) = newnode;
		(*head)->next = NULL;
	}
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");

	int n, m;
	fscanf(f, "%d %d\n", &n, &m);

	node** seq = calloc(n, sizeof(node*));
	short* out = calloc(n, sizeof(short));

	for (int i = 0; i < m; i++) {
		int t1, t2;
		fscanf(f, "%d %d\n", &t1, &t2);
		addNode(t2, &seq[t1]);
		addNode(t1, &seq[t2]);
	}
	for (int i = 0; i < n; i++)
		out[i] = 1;

	int j = 0;
	node* temp; node* temp2; node* top = NULL;

	for (int i = 0; i < n; i++) {
		if (out[i]) {
			printf("New Class: %d", i);
			out[i] = 0;
			temp = seq[i];

			while (1) {
				while (temp) {
					j = temp->data;
					if (out[j]) {
						printf(" %d", j);
						out[j] = 0;
						temp2 = temp->next;
						temp->next = top;
						top = temp;
						temp = temp2;
					}
					else {
						temp = temp->next;
					}
				}
				if (!top)
					break;
				temp = seq[top->data];
				top = top->next;
			}
			printf("\n");
		}
	}

	free(seq);
	free(out);
	return 0;
}