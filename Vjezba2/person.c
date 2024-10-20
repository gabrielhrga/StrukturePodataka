#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

struct Person;
typedef struct Person* Position;
typedef struct Person{
    char name[MAX];
    char last_name[MAX];
    int year;

    Position next;
}Person;

int Display(Position p);
int InsertStart(Position p, const char* Name, const char* LastName, int Year);
int InsertEnd(Position p, const char* Name, const char* LastName, int Year);
Position Find(Position p, const char* LastName);
int Erase(Position p, const char* LastName);

int main(){

    Position head = (Position)malloc(sizeof(Person));
    head->next = NULL;

    InsertStart(head, "Marko", "Maric", 2000);    
    InsertStart(head, "Pero", "Peric", 1998);
    InsertEnd(head, "Ana", "Anic", 2010);

    Find(head->next, "maric");
    Find(head->next, "Peric");

    Erase(head, "Anic");
        
    Display(head->next);

    free(head);
    return 0;
}

int Display(Position p){
    printf("FIRST NAME\tLAST NAME\tBIRTH YEAR\n");
    while(p != NULL){
        printf("%s\t\t%s\t\t%d\n", p->name, p->last_name, p->year);
        p = p->next;
    }

    return 0;
}

int InsertStart(Position p, const char* Name, const char* LastName, int Year){
    Position new_person = (Position)malloc(sizeof(Person));
    if(new_person == NULL){
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

int InsertEnd(Position p, const char* Name, const char* LastName, int Year){
    Position new_person = (Position)malloc(sizeof(Person));
    if (new_person == NULL){
        printf("Memory allocation error...\n");
        return -1;
    }
    
    while(p->next != NULL){
        p = p->next;
    }

    new_person->next = p->next;
    p->next = new_person;

    strcpy(new_person->name, Name);
    strcpy(new_person->last_name, LastName);
    new_person->year = Year;

    return 0;
}

Position Find(Position p, const char* LastName){
    while(p->next != NULL && strcmp(p->last_name, LastName) != 0){
        p = p->next;
    }
    if(p->next != NULL){
        printf("Element found...\n");
        return p;
    }
    else{
        printf("Element not found...\n");
        return NULL;
    }

}

int Erase(Position p, const char* LastName){
    Position temp;

    while(p->next != NULL && strcmp(p->next->last_name, LastName)!= 0){
        p = p->next;
    }

    if(p->next != NULL){
        temp = p->next;
        p->next = p->next->next;
        free(temp);
    }

    return 0;
}