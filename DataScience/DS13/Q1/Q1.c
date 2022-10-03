#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 200

typedef struct {
	int key;
} element;

typedef struct {
	element heap[MAX_SIZE];
	int size;
} heap;

void push(heap* h, element item) {
	int i;
	i = ++(h->size);

	while ((i != 1) && (item.key > h->heap[i/2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

element pop(heap* h) {
	int parent, child;
	element item, temp;
	
	item = h->heap[1];
	temp = h->heap[(h->size)--];
	parent = 1;
	child = 2;

	while (child <= h->size) {
		if ((child < h->size) && ((h->heap[child].key) < (h->heap[child + 1].key)))
			child++;

		if (temp.key >= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];

		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;

	return item;
}

int stack[200];

void add(int* top, int index) {
	stack[++(*top)] = index;
}

int delete(int *top) {
	return stack[(*top)--];
}

void levelorder(heap* h) {
	int i = 1;
	while (i <= (*h).size) {
		if ((*h).heap[i].key != NULL)
			printf("%d ", (*h).heap[i].key);
		i++;
	}
}

void iterinorder(heap* h) {
	int top = -1;
	int index = 1;
	while (1) {
		while (index <= h->size) {
			add(&top, index);
			index *= 2;
		}

		index = delete(&top);
		if (top < -1)
			break;
		printf("%d ", h->heap[index].key);
		index = index * 2 + 1;
	}
}

int main() {
	FILE* f;
	heap max_heap;
	max_heap.size = 0;

	int i = 1;
	
	f = fopen("input.txt", "r");
	while (!feof(f)) {
		element temp;
		fscanf(f, "%d ", &temp.key);
		push(&max_heap, temp);
	}


	printf("Level Order: ");
	levelorder(&max_heap);
	printf("\nInorder: ");
	iterinorder(&max_heap);

	element temp = pop(&max_heap);
	printf("\nLevel Order: ");
	levelorder(&max_heap);
	printf("\nInorder: ");
	iterinorder(&max_heap);
	
	temp = pop(&max_heap);
	printf("\nLevel Order: ");
	levelorder(&max_heap);
	printf("\nInorder: ");
	iterinorder(&max_heap);
}