#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int vertex;
	struct node* link;
} node;

typedef struct {
	int count;
	node* link;
} hdnodes;

hdnodes* graph;

void topsort(hdnodes* graph, int n) {
	int top = -1;

	for (int i = 0; i < n; i++) {
		if (!graph[i].count) {
			graph[i].count = top;
			top = i;
		}
	}

	for (int i = 0; i < n; i++) {
		if (top == -1) {
			fprintf(stderr, "Network has a cycle. Sort terminated.\n");
			exit(1);
		}
		else {
			int v = top;
			top = graph[top].count;
			printf("%d ", v);
			node* curr = graph[v].link;
			while (curr) {
				int temp = curr->vertex;
				graph[temp].count--;
				if (!graph[temp].count) {
					graph[temp].count = top;
					top = temp;
				}
				curr = curr->link;
			}
		}
	}
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");

	int vertexNum;
	fscanf(f, "%d ", &vertexNum);

	int** input = malloc(sizeof(int*) * vertexNum);
	for (int i = 0; i < vertexNum; i++) {
		input[i] = calloc(vertexNum, sizeof(int));
	}

	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < vertexNum; j++) {
			fscanf(f, "%d ", &input[i][j]);
		}
	}

	graph = calloc(vertexNum, sizeof(hdnodes));

	node* tail = NULL;

	for (int i = 0; i < vertexNum; i++) {
		graph[i].link = NULL;
		for (int j = 0; j < vertexNum; j++) {
			if (input[i][j] == 1) {
				node* newnode = malloc(sizeof(node));
				newnode->vertex = j;
				if (!graph[i].link) {
					graph[i].link = newnode;
					tail = newnode;
					newnode->link = NULL;
				}
				else {
					newnode->link = tail->link;
					tail->link = newnode;
					tail = newnode;
				}
				graph[j].count++;
			}
		}
	}
	
	topsort(graph, vertexNum);

	return 0;
}