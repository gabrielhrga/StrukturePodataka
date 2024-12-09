#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_LENTGH 10
#define ARTICLE_NAME_LENGTH 20
#define MAX_BUFFER 1024
#define RECEIPT_NAME_LENGTH 20
#define FILE_OPEN_ERROR -1
#define MEMORY_ALLOCATION_ERROR -2
#define FIRST_BEFORE 1
#define SECOND_BEFORE -1
#define SAME_DATE 0

struct _article;
typedef struct _article* ArticlePosition;
typedef struct _article{
    char article_name[ARTICLE_NAME_LENGTH];
    int quantity;
    double price;
    ArticlePosition next;
}Article;

struct _receipt;
typedef struct _receipt* ReceiptPosition;
typedef struct _receipt{
    char receipt_date[DATE_LENTGH];
    ReceiptPosition next;
    ArticlePosition article_head;
}Receipt;

int ReadReceipts(char* filename, ReceiptPosition head_receipt);
ReceiptPosition FillReceipt(char* receipt_name, ReceiptPosition p);
int AddArticle(ArticlePosition p, char* name, int quantity, double price);
int InsertReceiptSorted(ReceiptPosition head_receipt, ReceiptPosition new_receipt);
int CompareDates(ReceiptPosition receipt1, ReceiptPosition receipt2);
int FindArticle(ReceiptPosition receipts_head, char* article);

int main(){
    char search_article[ARTICLE_NAME_LENGTH];
    printf("Find article: ");
    scanf("%s", search_article);

    return 0;
}

int ReadReceipts(char* filename, ReceiptPosition head_receipt){ //ReceiptPosition je head racuna
    char buffer[MAX_BUFFER];
    ReceiptPosition temp_receipt = NULL;

    FILE* fp = NULL;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Could not open file...\n");
        return FILE_OPEN_ERROR;
    }

    while(!feof(fp)){
        fgets(buffer, MAX_BUFFER, fp);
        buffer[strcspn(buffer, "\n")] = 0;
        temp_receipt = FillReceipt(buffer, head_receipt);
        InsertReceiptSorted(head_receipt, temp_receipt);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

ReceiptPosition FillReceipt(char* receipt_name, ReceiptPosition p){
    char temp_name[ARTICLE_NAME_LENGTH];
    int temp_quantity;
    double temp_price;

    FILE* fp = NULL;
    fp = fopen(receipt_name, "r");
    if(fp == NULL){
        printf("Could not open file...\n");
        return FILE_OPEN_ERROR;
    }

    ReceiptPosition new_receipt = NULL;
    new_receipt = (ReceiptPosition)malloc(sizeof(Receipt));
    new_receipt->article_head = NULL;
    new_receipt->next = NULL;

    if(new_receipt == NULL){
        printf("Memory allocation error...\n");
        return NULL;
    }

    fscanf(fp, "%s", new_receipt->receipt_date);
    
    while(!feof(fp)){
        if(fscanf(fp, "%s %d %lf", temp_name, temp_quantity, temp_quantity) == 3){
            AddArticle(new_receipt->article_head, temp_name, temp_quantity, temp_price);
        }
    }

    fclose(fp);
    return new_receipt;

}

int AddArticle(ArticlePosition p, char* name, int quantity, double price){
    ArticlePosition new_article = NULL;
    new_article = (ArticlePosition)malloc(sizeof(Article));
    if(new_article == NULL){
        printf("Memory allocation error...\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    new_article->price = price;
    strcpy(new_article->article_name, name);

    if(p->next == NULL || strcmp(p->next->article_name, name) > 0){
        new_article->next = p->next;
        p->next = new_article;
        new_article->quantity = quantity;
    }
    else{
        while(p->next != NULL && strcmp(p->next->article_name, name) < 0){
            p = p->next;
        }
        if(p->next != NULL && strcmp(p->next->article_name, name) == 0){
            p->next->quantity += quantity;
            free(new_article);
        }
        else{
            new_article->next = p->next;
            p->next = new_article;
            new_article->quantity = quantity;
        }
    }

    return EXIT_SUCCESS;
}

int CompareDates(ReceiptPosition receipt1, ReceiptPosition receipt2){
    char* date1, date2;

    strcpy(date1, receipt1->receipt_date);
    strcpy(date2, receipt1->receipt_date);

    int year1, month1, day1;
    int year2, month2, day2;
    
    if(sscanf(date1, "%d-%d-%d", &year1, &month1, &day1) == 3 && sscanf(date2, "%d-%d-%d", &year2, &month2, &day2) == 3){
        if(year1 < year2){
            return FIRST_BEFORE;
        }
        else if(year1 == year2 && month1 < month2){
            return FIRST_BEFORE;
        }
        else if(year1 == year2 && month1 == month2 && day1 < day2){
            return FIRST_BEFORE;
        }
        else if(year1 == year2 && month1 == month2 && day1 == day2){
            return SAME_DATE;
        }
        else{
            return SECOND_BEFORE;
        } 
        
    }
    else{
        printf("Invalid date format...\n");
        return EXIT_FAILURE;
    }
    
}

int InsertReceiptSorted(ReceiptPosition head_receipt, ReceiptPosition new_receipt){

    if(head_receipt->next = NULL || CompareDates(new_receipt, head_receipt->next) == FIRST_BEFORE){
        new_receipt->next = head_receipt->next;
        head_receipt->next = new_receipt;
    }
    else{
        while(head_receipt->next != NULL && CompareDates(new_receipt, head_receipt->next) != FIRST_BEFORE){
            head_receipt = head_receipt->next;
        }
        if(head_receipt->next != NULL && CompareDates(new_receipt, head_receipt->next) == SAME_DATE){
            //MergeReceipts(new_receipt, head_receipt)
        }
        else{
            new_receipt->next = head_receipt->next;
            head_receipt->next = new_receipt;
        }
    }

    return EXIT_SUCCESS;
}

int FindArticle(ReceiptPosition receipts_head, char* article){
    double money_spent = 0.0;
    int quantity_sum = 0;

    while(receipts_head != NULL){
        while(receipts_head->next->article_head != NULL){
            if(strcmp(article, receipts_head->next->article_head->article_name) == 0){
                quantity_sum += receipts_head->next->article_head->quantity;
                money_spent += receipts_head->next->article_head->price;
            }
            receipts_head->next->article_head = receipts_head->next->article_head->next;
        }
        receipts_head = receipts_head->next;
    }

    printf("Article name: %s\nMoney spent: %lf\nQuantity: %d\n", article, money_spent, quantity_sum);

    return EXIT_SUCCESS;
}