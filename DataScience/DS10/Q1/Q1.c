#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct pol {
	int expon;
	int coef;
	struct pol* next;
}pol;


//linked list 생성함수
void addPol(int expon, int coef, pol** head, pol** tail) {
	pol* newpol = malloc(sizeof(pol));
	newpol->expon = expon;
	newpol->coef = coef;
	if ((*tail) != NULL) {
		newpol->next = (*tail)->next;
		(*tail)->next = newpol;
		(*tail) = newpol;
	}
	else {
		(*head) = newpol;
		(*tail) = newpol;
		(*tail)->next = NULL;
	}
}

void padd(pol** h1, pol** h2, pol** hr, pol** tr) {
	pol* c1 = (*h1);
	pol* c2 = (*h2);
	
	while (c1 != NULL && c2 != NULL) {
		if (c1->coef > c2->coef) {
			addPol(c1->expon, c1->coef, hr, tr);
			c1 = c1->next;
		}
		else if (c1->coef == c2->coef) {
			int temp = c1->expon + c2->expon;
			if(temp != 0)
				addPol(temp, c1->coef, hr, tr);
			c1 = c1->next;
			c2 = c2->next;
		}
		else {
			addPol(c2->expon, c2->coef, hr, tr);
			c2 = c2->next;
		}
	}
	//뒤에 남은 linked list 처리 (c2가 NULL이 될 경우 c1의 뒷부분이 처리 안되기에 작성)
	while (c1 != NULL) {
		addPol(c1->expon, c1->coef, hr, tr);
		c1 = c1->next;
	}
	while (c2 != NULL) {
		addPol(c2->expon, c2->coef, hr, tr);
		c2 = c2->next;
	}
	
}

int main() {
	FILE* f;
	pol* h1 = NULL; pol* t1 = NULL;
	pol* h2 = NULL; pol* t2 = NULL;
	pol* hr = NULL; pol* tr = NULL;


	f = fopen("a.txt", "r");
	int n;
	fscanf(f, "%d ", &n);
	for (int i = 0; i < n; i++) {
		int c, e;
		fscanf(f, "%d %d ", &c, &e);
		addPol(c, e, &h1, &t1);
	}
	fclose(f);

	f = fopen("b.txt", "r");
	fscanf(f, "%d ", &n);
	for (int i = 0; i < n; i++) {
		int c, e;
		fscanf(f, "%d %d ", &c, &e);
		addPol(c, e, &h2, &t2);
	}
	fclose(f);

	padd(&h1, &h2, &hr, &tr);
	pol* curr = hr;

	if (curr == NULL)
		printf("0");
	else {
		while (curr != NULL) {
			printf("%d", abs(curr->expon));
			if (curr->coef != 0)
				printf("x^%d", curr->coef);
			if (curr->next != NULL) {
				if (curr->next->expon > 0)
					printf(" + ");
				else if (curr->next->expon < 0)
					printf(" - ");
			}
			curr = curr->next;
		}
	}
	

	curr = h1;
	while (curr != NULL) {
		pol* next = curr->next;
		free(curr);
		curr = next;
	}
	curr = h2;
	while (curr != NULL) {
		pol* next = curr->next;
		free(curr);
		curr = next;
	}
	curr = hr;
	while (curr != NULL) {
		pol* next = curr->next;
		free(curr);
		curr = next;
	} 

	return 0;
}