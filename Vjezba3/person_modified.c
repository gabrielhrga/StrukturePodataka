#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define MAX_BUFFER 1024

struct Person;
typedef struct Person* Position;
typedef struct Person {
	char name[MAX];
	char last_name[MAX];
	int year;

	Position next;
}Person;

//VJEZBA2 FUNCTIONS
int Display(Position p);
int InsertStart(Position p, const char* Name, const char* LastName, int Year);
int InsertEnd(Position p, const char* Name, const char* LastName, int Year);
Position Find(Position p, const char* LastName);
int Erase(Position p, const char* LastName);

//VJEZBA3 FUNCTIONS
int InsertAfter(Position p, const char* AfterName, const char* Name, const char* LastName, int Year);
int InsertBefore(Position p, const char* BeforeName, const char* Name, const char* LastName, int Year);
int PrintInFile(Position p, const char* filename);
int ScanFromFile(Position p, const char* filename);
void Sort(Position p);

int main() {

	Position head = (Position)malloc(sizeof(Person));
	head->next = NULL;
	if (head == NULL) {
		printf("Memory allocation error...\n");
		return -1;
	}

	/*
	InsertEnd(head, "Ivica", "Lazaneo", 1998);
	InsertAfter(head, "Lazaneo", "Pero", "Peric", 1995);
	InsertBefore(head, "Peric", "Marko", "Maric", 1900);
	*/

	//radi
	//PrintInFile(head->next, "imedat.txt");

	//radi
	ScanFromFile(head, "imedat.txt");
	Sort(head);
	Display(head->next);

	free(head);
	return 0;
}

int Display(Position p) {
	printf("FIRST NAME\tLAST NAME\tBIRTH YEAR\n");
	while (p != NULL) {
		printf("%s\t\t%s\t\t%d\n", p->name, p->last_name, p->year);
		p = p->next;
	}

	return 0;
}

int InsertStart(Position p, const char* Name, const char* LastName, int Year) {
	Position new_person = (Position)malloc(sizeof(Person));
	if (new_person == NULL) {
		printf("Memory allocation error\n");
		return -1;
	}

	new_person->next = p->next;
	p->next = new_person;

	strcpy(new_person->name, Name);
	strcpy(new_person->last_name, LastName);
	new_person->year = Year;

	return 0;
}

int InsertEnd(Position p, const char* Name, const char* LastName, int Year) {
	Position new_person = (Position)malloc(sizeof(Person));
	if (new_person == NULL) {
		printf("Memory allocation error...\n");
		return -1;
	}

	while (p->next != NULL) {
		p = p->next;
	}

	new_person->next = p->next;
	p->next = new_person;

	strcpy(new_person->name, Name);
	strcpy(new_person->last_name, LastName);
	new_person->year = Year;

	return 0;
}

Position Find(Position p, const char* LastName) {
	while (p->next != NULL && strcmp(p->last_name, LastName) != 0) {
		p = p->next;
	}
	if (p->next != NULL) {
		printf("Element found...\n");
		return p;
	}
	else {
		printf("Element not found...\n");
		return NULL;
	}

}

int Erase(Position p, const char* LastName) {
	Position temp;

	while (p->next != NULL && strcmp(p->next->last_name, LastName) != 0) {
		p = p->next;
	}

	if (p->next != NULL) {
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}

	return 0;
}

int InsertAfter(Position p, const char* AfterName, const char* Name, const char* LastName, int Year) {
	Position new_person = (Position)malloc(sizeof(Person));
	if (new_person == NULL) {
		printf("Memory allocation error...\n");
		return -1;
	}

	while (p->next != NULL && strcmp(p->last_name, AfterName) != 0) {
		p = p->next;
	}

	strcpy(new_person->name, Name);
	strcpy(new_person->last_name, LastName);
	new_person->year = Year;

	new_person->next = p->next;
	p->next = new_person;

	return 0;
}

int InsertBefore(Position p, const char* BeforeName, const char* Name, const char* LastName, int Year) {
	Position new_person = (Position)malloc(sizeof(Person));
	if (new_person == NULL) {
		printf("Memory allocation error...\n");
		return -1;
	}

	while (p->next != NULL && strcmp(p->next->last_name, BeforeName) != 0) {
		p = p->next;
	}

	strcpy(new_person->name, Name);
	strcpy(new_person->last_name, LastName);
	new_person->year = Year;

	new_person->next = p->next;
	p->next = new_person;

	return 0;
}

int PrintInFile(Position p, const char* filename) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("File opening error...\n");
		return -2;
	}

	if(p == NULL){
		printf("The list is empty. Nothing to print.\n");
	}
	else{
		while (p != NULL) {
			fprintf(fp, "%s\t%s\t\t%d\n", p->name, p->last_name, p->year);
			p = p->next;
		}
	}

	fclose(fp);

	return 0;
}

int ScanFromFile(Position p, const char* filename) {

	char buffer[MAX_BUFFER];
	char Name[MAX];
	char LastName[MAX];
	int Year = 0;

	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("File opening error...\n");
		return -2;
	}

	while(!feof(fp)){
		fgets(buffer, 1024, fp);
		buffer[strcspn(buffer, "\n")] = 0;
		if(sscanf(buffer, "%s %s %d", Name, LastName, &Year) == 3){
			InsertEnd(p, Name, LastName, Year);
		}
	}

	fclose(fp);

	return 0;
}

void Sort(Position p) {

	Position j, prev_j, temp, end;

	end = NULL;
	while (p->next != end) {
		prev_j = p;
		j = p->next;

		while(j->next != end){
			if(strcmp(j->last_name, j->next->last_name) > 0){
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}

}