#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 1001 //Max defree of polynomial+1
typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} polynomial;

int main() {
	polynomial a;
	polynomial b;
	polynomial r;
	FILE* f;

	for (int i = 0; i < MAX_DEGREE; i++) {
		a.coef[i] = 0;
		b.coef[i] = 0;
		r.coef[i] = 0;
	}
	
	if ((f = fopen("a.txt", "r")) == NULL) {
		printf("File Error");
		exit(1);
	}

	fscanf(f, "%d", &a.degree);

	int count = 0;
	float n, m;
	
	while (1) {
		fscanf(f, "%f %f ", &n, &m);
		for (int i = 0; i < MAX_DEGREE; i++) {
			if (i == m)
				a.coef[i] = n;
		}
		count++;
		if (count == a.degree)
			break;
	}
	fclose(f);


	if ((f = fopen("b.txt", "r")) == NULL) {
		printf("File Error");
		exit(1);
	}

	fscanf(f, "%d", &b.degree);

	count = 0;
	
	while (1) {
		fscanf(f, "%f %f ", &n, &m);
		for (int i = 0; i < MAX_DEGREE; i++) {
			if (i == m)
				b.coef[i] = n;
		}
		count++;
		if (count == b.degree)
			break;
	}
	fclose(f);
	

	r.degree = a.degree > b.degree ? a.degree : b.degree;

	for (int i = 0; i < MAX_DEGREE; i++) {
		r.coef[i] = a.coef[i] + b.coef[i];
	}

	for (int i = 0; i < MAX_DEGREE; i++) {
		if (r.coef[MAX_DEGREE - (i + 1)] != 0) {
			printf("%.0f", r.coef[MAX_DEGREE - (i + 1)]);
			if (MAX_DEGREE - (i + 1) != 0)
				printf("x^%d + ", MAX_DEGREE - (i + 1));
		}
	}

	return 0;
}