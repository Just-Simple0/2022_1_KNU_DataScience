#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
	int data;
	struct node* next;
}node;

void addNode(node** head, int data) {
	node* newnode = malloc(sizeof(node));
	newnode->data = data;

	if (*head) {
		node* curr = (*head);
		while (curr->next) {
			curr = curr->next;
		}
		newnode->next = NULL;
		curr->next = newnode;
	}
	else {
		(*head) = newnode;
		(*head)->next = NULL;
	}
}

int visited[MAX_SIZE] = { 0 };

void dfs(int v, node** adjList) {
	visited[v] = 1;
	printf("%d ", v);

	node* temp = adjList[v];
	while (temp) {
		if (!visited[temp->data])
			dfs(temp->data, adjList);
		temp = temp->next;
	}
}

typedef struct {
	int vertex;
	struct queue* next;
}queue;


void addq(int data, queue** front, queue** rear) {
	queue* temp = malloc(sizeof(queue));
	temp->vertex = data;
	temp->next = NULL;
	if (*front)
		(*rear)->next = temp;
	else
		(*front) = temp;
	(*rear) = temp;
}

int deleteq(queue** front, queue** rear) {
	queue* temp = (*front);
	int vertex;
	vertex = temp->vertex;
	(*front) = temp->next;
	free(temp);
	return vertex;
}

void bfs(int v, node** adjList) {
	node* temp;
	queue* front = NULL; queue* rear = NULL;
	printf("%d ", v);
	visited[v] = 1;
	addq(v, &front, &rear);
	while (front) {
		v = deleteq(&front, &rear);
		temp = adjList[v];
		while (temp) {
			if (!visited[temp->data]) {
				printf("%d ", temp->data);
				addq(temp->data, &front, &rear);
				visited[temp->data] = 1;
			}
			temp = temp->next;
		}
	}
}

int main() {
	FILE* f;
	int num;
	f = fopen("input.txt", "r");
	fscanf(f, "%d", &num);
	
	int** graph = calloc(num, sizeof(int));
	for (int i = 0; i < num; i++) {
		graph[i] = calloc(num, sizeof(int));
	}

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			fscanf(f, "%d", &graph[i][j]);
		}
	}

	node** adjList = calloc(num, sizeof(node*));
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (graph[i][j] == 1) {
				addNode(&adjList[i], j);
			}
		}
	}

	for (int i = 0; i < num; i++) {
		printf("Vertex %d: ", i);
		node* curr = adjList[i];
		while (curr) {
			printf("%d ", curr->data);
			curr = curr->next;
		}
		puts("");
	}

	printf("DFS: ");
	dfs(0, adjList);
	puts("");
	
	for (int i = 0; i < num; i++) {
		visited[i] = 0;
	}

	printf("BFS: ");
	bfs(0, adjList);

	/*
	for (int i = 0; i < num; i++) {
		free(graph[i]);
	}
	free(graph);
	for (int i = 0; i < num; i++) {
		node* curr = adjList[i];
		while (curr) {
			node* temp = curr->next;
			free(curr);
			curr = temp;
		}
	}
	free(adjList);
	*/
	return 0;
}