#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 1024

int OpenFile(char* FileName);
int NumberOfRows(const char*);

int main(
	int numOfRows = 0;

	numOfRows = NumberOfRows("imedat.txt");

	return 0;
)

int NumberOfRows(const char* fileName) {
	FILE* fp = NULL;
	int numOfRows = 0;
	char buffer[MAX] = {};

	fp = fopen(fileName, "r");
	if (!fp)
	{
		return -1;
	}

	while (!feof(fp))
	{
		fgets(buffer, MAX, fp);
		numOfRows++;
	}
}