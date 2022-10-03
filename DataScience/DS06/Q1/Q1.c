#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 1001
typedef struct {
	int row;
	int col;
	int value;
} term;

term plus[MAX_TERMS] = { NULL }, trans[MAX_TERMS] = { NULL };
void RMO(term* rmo, int row, int col, int** arr) {
	int count = 1;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (arr[i][j] != 0) {
				rmo[count].row = i;
				rmo[count].col = j;
				rmo[count].value = arr[i][j];
				rmo[0].value = count++;
			}
		}
	}
}

void fastTranspose(term* a, term* b) {
	int rowTerms[MAX_TERMS], startingPos[MAX_TERMS];
	int numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols; b[0].col = a[0].row;
	b[0].value = numTerms;
	if (numTerms > 0) {
		for (int i = 0; i < numCols; i++)
			rowTerms[i] = 0;
		for (int i = 1; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		startingPos[0] = 1;
		for (int i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (int i = 1; i <= numTerms; i++) {
			int j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

int main() {
	int r1, c1, r2, c2;
	FILE* f;

	if ((f = fopen("mat1.txt", "r")) == NULL) {
		printf("FILE OPEN ERROR");
		exit(1);
	}

	fscanf(f, "%d %d\n", &r1, &c1);
	int** a = calloc(r1, sizeof(int));
	for (int i = 0; i < r1; i++) {
		a[i] = calloc(c1, sizeof(int));
	}

	int k = 0;
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			fscanf(f, "%d ", &k);
			a[i][j] = k;
		}
	}
	fclose(f);

	if ((f = fopen("mat2.txt", "r")) == NULL) {
		printf("FILE OPEN ERROR");
		exit(1);
	}

	fscanf(f, "%d %d\n", &r2, &c2);
	int** b = calloc(r2, sizeof(int));
	for (int i = 0; i < r2; i++) {
		b[i] = calloc(c2, sizeof(int));
	}

	k = 0;
	for (int i = 0; i < r2; i++) {
		for (int j = 0; j < c2; j++) {
			fscanf(f, "%d ", &k);
			b[i][j] = k;
		}
	}
	fclose(f);

	plus[0].row = (r1 > r2) ? r1 : r2;
	int sr = plus[0].row;
	plus[0].col = (c1 > c2) ? c1 : c2;
	int sc = plus[0].col;
	plus[0].value = 0;

	int** s = calloc(sr, sizeof(int));
	for (int i = 0; i < r2; i++) {
		s[i] = calloc(sc, sizeof(int));
	}

	int count = 1;
	for (int i = 0; i < sr; i++) {
		for (int j = 0; j < sc; j++) {
				s[i][j] = a[i][j] + b[i][j];
		}
	}
	RMO(plus, sc, sr, s);

	printf("Matrix Addition :\n");
	for (int i = 0; i < ((plus[0].value) + 1); i++) {
		printf("%d %d %d\n", plus[i].row, plus[i].col, plus[i].value);
	}

	fastTranspose(plus, trans);

	printf("Transpose Matrix :\n");
	for (int i = 0; i < ((trans[0].value) + 1); i++) {
		printf("%d %d %d\n", trans[i].row, trans[i].col, trans[i].value);
	}

	return 0;
}