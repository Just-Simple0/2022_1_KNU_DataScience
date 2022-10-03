#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int size;
int* ht;

int hash(int key) {
	return key % size;
}

void makeHashtable(int key) {
	int h = hash(key);
	while (ht[h])
		h++;
	ht[h] = key;
}

void printHashtable() {
	printf("Hash Table :\n");
	for (int i = 0; i < size; i++) {
		if (ht[i])
			printf("%d : %d\n", i, ht[i]);
		else
			printf("%d :\n", i);
	}
}

int search(int find) {
	int origin, curr;
	origin = hash(find);

	curr = origin;
	while (ht[curr] && ht[curr] != find) {
		curr = (curr + 1) % size;
		if (curr == origin)
			return NULL;
	}
	if (ht[curr] == find)
		return ht[curr];
	return NULL;
}

int main() {
	FILE* f;
	f = fopen("input.txt", "r");
	int num, snum;
	fscanf(f, "%d %d %d", &size, &num, &snum);

	ht = calloc(size, sizeof(int));

	for (int i = 0; i < num; i++) {
		int temp;
		fscanf(f, "%d", &temp);
		makeHashtable(temp);
	}
	printHashtable();

	printf("Search :\n");
	for (int i = 0; i < snum; i++) {
		int temp;
		fscanf(f, "%d", &temp);
		if (search(temp))
			printf("S");
		else
			printf("F");

	}

	return 0;
}