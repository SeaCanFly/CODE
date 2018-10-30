/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_1
*/
#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct TId
{
	int i_number;
	char ca_text[20];
}TId;
int main()
{
	TId* text;
	text = (TId*)malloc(sizeof(TId));
	text->i_number = 100;
	strcpy(text->ca_text,"just testing");
	printf("%d,%s\n", text->i_number, text->ca_text);
	free(text);
	return 0;
}