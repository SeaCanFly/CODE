#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<string.h>
#include"Header.h"
typedef struct
{
	char data[200][100];
	int count;
}ArrayList;
void initAList(ArrayList* al)
{
	memset(al->data, 0, sizeof(al->data));
	al->count = 0;
}
void printAList(ArrayList* al)
{
	if (!al)return;
	int num = al->count;
	for (int i = 0; i < num; i++)
	{
		printf("[%d]:%s\n", i, al->data[i]);
	}
}
void addElmt(ArrayList* al, int pos, char* data)
{
	if (!al || !data)return;
	if (pos >= 0 && pos <= al->count&&al->count < 200)
	{
		int i = al->count - 1;
		for (i; i >= pos; i--)
		{
			strcpy(al->data[i + 1], al->data[i]);
		}
		strcpy(al->data[pos], data);
		al->count++;
	}
	else
	{
		printf("addElmt:position error\n");
		return;
	}
}
void delElmt(ArrayList* al, int pos)
{
	if (!al)return;
	if (pos >= 0 && pos < al->count)
	{
		int i = pos;
		for (i; i<al->count; i++)
		{
			strcpy(al->data[i], al->data[i+1]);
		}
		al->count--;
	}
	else
	{
		printf("delElmt:position error\n");
		return;
	}
}
int main()
{
	//ArrayList a;
	//initAList(&a);
	//addElmt(&a, 0, "1");
	//addElmt(&a, 1, "2");
	//addElmt(&a, 2, "3");
	//addElmt(&a, 3, "4");
	//delElmt(&a, 0);
	//printAList(&a);

	Node* phead = linkList(5);
	showList(phead);
	Node* n1 = newNode(0,999);
	insertNode(phead, n1, 5);
	showList(phead);
	removeNode(phead, 5);
	showList(phead);



	return 0;
}