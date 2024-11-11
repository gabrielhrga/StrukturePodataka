#include <stdio.h>
#include <stdlib.h>

struct Polynomial;
typedef struct Polynomial* Position;
typedef struct Polynomial {
	int coeff;
	int exp;
	Position next;
}Polynomial;

Position CreateNew(int coeff, int exp);
int InsertSorted(Position p, int coeff, int exp);
int Display(Position p);
void FreePolynomial(Position p);
Position AddPolynomials(Position p1, Position p2);
Position MultiplyPolynomials(Position p1, Position p2);
Position ReadFromFile(const char* filename);

int main() {

	Position head1 = NULL;
	head1 = (Position)malloc(sizeof(Polynomial));
	head1->next = NULL;

	Position head2 = NULL;
	head2 = (Position)malloc(sizeof(Polynomial));
	head2->next = NULL;

	Position result = NULL;

	InsertSorted(head1, 3, 2);
	InsertSorted(head1, 4, 5);

	InsertSorted(head2, 5, 3);
	InsertSorted(head2, 1, 2);

	Display(head1);
	Display(head2);

	result = AddPolynomials(head1, head2);

	Display(result);

	result = MultiplyPolynomials(head1, head2);
	Display(result);

	return 0;
}

Position CreateNew(int coeff, int exp) {
	Position new = (Position)malloc(sizeof(Polynomial));
	if (new == NULL) {
		printf("Memory allocation error...\n");
		return NULL;
	}

	new->coeff = coeff;
	new->exp = exp;
	new->next = NULL;

	return new;
}

int InsertSorted(Position p, int coeff, int exp) {
	Position new_node = CreateNew(coeff, exp);
	if (new_node == NULL) {
		printf("Memory allocation error...\n");
		return -1;
	}

	if (p->next == NULL || p->next->exp < exp) {
		new_node->next = p->next;
		p->next = new_node;
	}
	else {
		while (p->next != NULL && p->next->exp > exp) {
			p = p->next;
		}
		//koef 0 provjera
		if (p->next != NULL && p->next->exp == exp) {
			p->next->coeff += coeff;
			free(new_node);
		}
		else {
			new_node->next = p->next;
			p->next = new_node;
		}
	}

	return 0;
}

int Display(Position p) {
	if (p == NULL) {
		printf("Empty list. Nothing to print...\n");
		return -2;
	}

	while (p != NULL) {
		if (p->coeff != 0 && p->exp >= 0) {
			printf("%dx^%d", p->coeff, p->exp);
			p = p->next;
			if (p != NULL) {
				printf(" + ");
			}
		}
	}
	printf("\n");

	return 0;
}

void FreePolynomial(Position p) {
	Position temp;
	while (p != NULL) {
		temp = p;
		p = p->next;
		free(temp);
	}
}

Position AddPolynomials(Position p1, Position p2) {
	Position result = (Position)malloc(sizeof(Polynomial));
	if (result == NULL) {
		printf("Memory allocation error...\n");
		return NULL;
	}
	result->next = NULL;

	while (p1 != NULL && p2 != NULL) {
		if (p1->exp > p2->exp) {
			InsertSorted(result, p1->coeff, p1->exp);
			p1 = p1->next;
		}
		else if (p1->exp < p2->exp) {
			InsertSorted(result, p2->coeff, p2->exp);
			p2 = p2->next;
		}
		else {
			int sum_coeff = p1->coeff + p2->coeff;
			if (sum_coeff != 0) {
				InsertSorted(result, sum_coeff, p1->exp);
			}
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	while (p1 != NULL) {
		InsertSorted(result, p1->coeff, p1->exp);
		p1 = p1->next;
	}
	while (p2 != NULL) {
		InsertSorted(result, p2->coeff, p2->exp);
		p2 = p2->next;
	}

	return result;
}

Position MultiplyPolynomials(Position p1, Position p2) {
	Position result = NULL;
	Position temp1 = p1;
	Position temp2 = p2;

	int new_coeff = 0;
	int new_exp = 0;

	while (temp1 != NULL) {
		while (temp2 != NULL) {
			new_coeff = temp1->coeff * temp2->coeff;
			new_exp = temp1->exp + temp2->exp;
			InsertSorted(result, new_coeff, new_exp);
			temp2 = temp2->next;
		}
		//vrati temp2 na pocetak
		temp1 = temp1->next;
	}

	return result;
}

Position ReadFromFile(const char* filename) {
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Memory allocation error...\n");
		return NULL;
	}

	Position new = NULL;
	int coeff, exp, num_bytes = 0;

	while (fscanf(fp, "%d %d %n", coeff, exp, num_bytes) == 2) {
		InsertSorted(new, coeff, exp);
	}

	fclose(fp);

	return new;
}