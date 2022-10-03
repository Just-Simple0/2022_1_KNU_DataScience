#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 1000
typedef struct {
	float coef;
	int expon;
} polynomial;

polynomial terms[MAX_TERMS];
int avail;

int compare(int a, int b) {
	if (a > b) return 1;
	else if (a == b) return 0;
	else return -1;
}

void attach(float coef, int expon) {
	if (avail >= MAX_TERMS) {
		printf("Too many terms in the polynomial\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++;
}

void padd(int sa, int fa, int sb, int fb, int* sd, int* fd) {
	float coef;
	*sd = avail;
	while (sa <= fa && sb <= fb) {
		switch (compare(terms[sa].expon , terms[sb].expon)) {
		case -1:
			attach(terms[sb].coef, terms[sb].expon);
			sb++;
			break;
		case 0:
			coef = terms[sb].coef + terms[sa].coef;
			if(coef)
				attach(coef, terms[sb].expon);
			sb++;
			sa++;
			break;
		case 1:
			attach(terms[sa].coef, terms[sa].expon);
			sa++;
			break;
		}
	}
	for (; sa <= fa; sa++) {
		attach(terms[sa].coef, terms[sa].expon);
	}
	for (; sb <= fb; sb++) {
		attach(terms[sb].coef, terms[sb].expon);
	}
	*fd = avail - 1;
}

int main() {
	
	FILE* f;
	int sa, fa, sb, fb, sd, fd;

	if ((f = fopen("a.txt", "r")) == NULL) {
		printf("File Error");
		exit(1);
	}
	
	fscanf(f, "%d", &fa);

	for (int i = 0; i < fa; i++) {
		fscanf(f, "%f %d", &terms[i].coef, &terms[i].expon);
	}
	sa = 0;
	fclose(f);

	if ((f = fopen("b.txt", "r")) == NULL) {
		printf("File Error");
		exit(1);
	}

	fscanf(f, "%d", &fb);

	for (int i = fa; i < fa + fb; i++) {
		fscanf(f, "%f %d", &terms[i].coef, &terms[i].expon);
	}
	fclose(f);
	
	sb = fa;
	fa = sb - 1;
	fb = sb + fb - 1;
	avail = fb + 1;

	padd(sa, fa, sb, fb, &sd, &fd);

	for (int i = sd; i <= fd; i++) {
		printf("%.0f", terms[i].coef);
		if (terms[i].expon != 0)
			printf("x^%d", terms[i].expon);
		if (terms[i + 1].coef > 0)
			printf(" + ");
	}
	
	return 0;
}