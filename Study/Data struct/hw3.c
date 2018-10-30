/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define MAX 200
typedef struct
{
	int count;
	char list[MAX][100];
} ArrayList;
void init_list(ArrayList* a_list)
{
	if (!a_list)return;
	a_list->count = 0;
}
void print_list(ArrayList* a_list)
{
	if (!a_list)return;
	int i = 0;
	printf("list:\n");
	for (i; i < a_list->count; i++)
	{
		printf("[%d]:%s\n", i, a_list->list[i]);
	}
}
void add_first(ArrayList* a_list, char* str)
{
	if (!a_list||!str)return;
	if (a_list->count >= MAX)
	{
		printf("list has already full\n");
		return;
	}
	else if (a_list->count == 0)
	{
		strcpy(a_list->list[0], str);
		a_list->count = 1;
		return;
	}
	else 
	{
		int i = a_list->count;
		for (i; i > 0; i--)
		{
			strcpy(a_list->list[i], a_list->list[i - 1]);
		}
		a_list->count++;
	}
}
void add(ArrayList* a_list, int pos, char* str)
{
	if (!a_list||!str)return;
	if (pos >= 0 && pos <= a_list->count && a_list->count < MAX)
	{
		int i = a_list->count-1;
		for (i; i >=pos; i--)
		{
			strcpy(a_list->list[i+1], a_list->list[i]);
		}
		strcpy(a_list->list[pos], str);
		a_list->count++;
	}
	else
	{
		printf("add: error occurred\n");
	}
}
void add_last(ArrayList* a_list, char* str)
{
	if (!a_list||!str)return;
	if (a_list->count < MAX)
	{
		int i = a_list->count;
		strcpy(a_list->list[i], str);
		a_list->count++;
	}
	else
	{
		printf("add_last: error occurred\n");
	}
}
void delete_elmt(ArrayList* a_list, int pos)
{
	if (!a_list)return;
	if (pos >= 0 && pos < a_list->count)
	{
		int i = pos;
		for (i; i < a_list->count-1; i++)
		{
			strcpy(a_list->list[i], a_list->list[i + 1]);
		}
		a_list->count--;
	}
	else
	{
		printf("delete: error occurred\n");
	}
}
void replace_elmt(ArrayList* a_list, int pos, char* str)
{
	if (!a_list||!str)return;
	if (pos >= 0 && pos < a_list->count)
	{
		strcpy(a_list->list[pos], str);
	}
	else
	{
		printf("replace: error occurred\n");
	}
}
int is_empty(ArrayList* a_list)
{
	if (a_list->count == 0)
	{
		printf("empty\n");
		return 1;
	}
	else
	{
		printf("not empty\n");
		return 0;
	}
}
int is_full(ArrayList* a_list)
{
	if (!a_list)return -1;
	if (a_list->count == MAX)
	{
		printf("full\n");
		return 1;
	}
	else
	{
		printf("not full\n");
		return 0;
	}
}
char* get_entry(ArrayList* a_list, int pos)
{
	if (!a_list)return 0;
	if (pos >= 0 && pos < a_list->count)
	{
		printf("get_entry: [%d],%s\n", pos, a_list->list[pos]);
		return a_list->list[pos];
	}
	else
	{
		printf("get_entry: error occurred\n");
		return 0;
	}
}
int get_length(ArrayList* a_list)
{
	if (!a_list)return -1;
	return a_list->count;
}
int is_in_list(ArrayList* a_list, char* str)
{
	if (!a_list||!str)return -1;
	int i = 0;
	for (i; i < a_list->count; i++)
	{
		if (!strcmp(a_list->list[i], str))
		{
			printf("\"%s\" in the list of [%d]\n",str,i);
			return 1;
		}
	}
	printf("\"%s\" is not in the list\n", str);
	return 0;
}
void clear_list(ArrayList* a_list)
{
	if (!a_list)return;
	a_list->count = 0;
}
int main()
{

	ArrayList* A = (ArrayList*)malloc(sizeof(ArrayList));
	init_list(A);
	is_full(A);
	is_empty(A);
	add_first(A, "first");
	add(A, 1, "second");
	add_last(A, "third");
	add(A, 2, "fourth");
	add(A, 4, "fifth");
	is_empty(A);
	is_full(A);
	delete_elmt(A, 2);
	delete_elmt(A, 2);
	replace_elmt(A, 1, "sixth");
	print_list(A);
	printf("length:%d\n", get_length(A));
	get_entry(A, 2);
	is_in_list(A, "first");
	clear_list(A);
	print_list(A);
	free(A);
	return 0;
}