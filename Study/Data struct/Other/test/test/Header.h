#pragma once
#include<stdio.h>
#include<malloc.h>

typedef struct Node
{
	int data;
	Node* next;
}Node;
Node* newNode(Node* pnode, int data)
{
	Node* phead = (Node*)malloc(sizeof(Node));
	phead->data = data;
	phead->next = pnode;
	return phead;
}
Node* linkList(int num)
{
	Node* phead = nullptr;
	while (--num >= 0)
	{
		phead = newNode(phead, num);
	}
	return phead;
}
Node* getPos(Node* phead,int pos)
{
	Node* p = phead;
	if (pos == -1)return nullptr;
	while (pos)
	{
		p = p->next;
		pos--;
	}
	return p;
}
Node* insertNode(Node* phead, Node* pnode, int pos)
{
	Node* c = getPos(phead,pos);
	Node* p = getPos(phead, pos - 1);
	if(p)p->next = pnode;
	pnode->next = c;
	if (!p)phead = pnode;
	
	return pnode;
}
Node* removeNode(Node* phead, int pos)
{
	Node* p = getPos(phead, pos - 1);
	Node* c = getPos(phead,pos);
	//struct Node* Rtemp = NULL;
	//if (p2)
	//{
	//	Rtemp = p2->next;
	//	free(p2);
	//	p2 = NULL;
	//}
	//if (p1) { p1->next = Rtemp; }
	//return Rtemp;
	Node* n = nullptr;
	n = c->next;
	free(c);
	c = nullptr;
	if (p) p->next = n; 
	else phead = n;
	return phead;
}
void showList(Node* phead)
{
	printf("\n");
	Node* p = phead;
	while (p)
	{
		printf("%d,%p,%p\n", p->data, p, p->next);
		p = p->next;
	}
}