#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 1000
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key;
}element;

element heap[MAX_ELEMENTS] = { NULL };
int n = 0;

void push(element item) {
	if (HEAP_FULL(n)) {
		fprintf(stderr, "The heap is full. \n");
		exit(EXIT_FAILURE);
	}
	int i = ++n;
	while ((i != 1) && (item.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element pop() {
	int parent, child;
	element item, temp;
	if (HEAP_FULL(n)) {
		fprintf(stderr, "The heap is full. \n");
		exit(EXIT_FAILURE);
	}

	item = heap[1];
	temp = heap[n--];
	parent = 1;
	child = 2;
	
	while (child <= n) {
		if ((child < n) && (heap[child].key > heap[child + 1].key))
			child++;
		if (temp.key <= heap[child].key)
			break;
		
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;

	return item;
}

int CalcH() {
	int i = n;
	int cnt = 0;
	while (i >= 1) {
		i /= 2;
		cnt++;
	}

	return cnt;
}

int CalcL() {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if ((heap[i * 2].key == NULL) && (heap[i * 2].key == NULL))
			cnt++;
	}

	return cnt;
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");

	while (!feof(f)) {
		int temp;
		fscanf(f, "%d", &temp);
		element new;
		new.key = temp;
		push(new, &n);
	}

	printf("Level order : ");
	for (int i = 1; i <= n; i++) {
		printf("%d ", heap[i].key);
	}

	printf("\nHeight : %d", CalcH());
	printf("\nLeaf : %d", CalcL());

	

	return 0;
}