#include<stdio.h>
#include<malloc.h>
#include"1.h"
typedef struct Node
{
	int data;
	Node* pnext;
	Node* prev;
	Node* ptail;
}Node;
Node* newNode(Node* pnode, int data)
{
	Node* phead = (Node*)malloc(sizeof(Node));
	phead->data = data;
	phead->pnext = pnode;
	phead->prev = phead;
	if (pnode != nullptr)pnode->prev = phead;
	return phead;
}
Node* linkList(int num)
{
	Node* phead = nullptr;
	while (--num >= 0)
	{
		phead = newNode(phead, num);
	}
	Node* t=phead;
	Node* temp=t;
	while(t->pnext!=nullptr)
	{
		t=t->pnext;
	}
	while (temp)
	{
		temp->ptail=t;
		temp=temp->pnext;
	}
	return phead;
}
void showList(Node** phead)
{
	printf("\n");
	printf("n,p,        p->next,p->prev,p->ptail\n");
	Node* p = *phead;
	while (p)
	{
		printf("%d,%p,%p,%p,%p\n", p->data, p, p->pnext,p->prev,p->ptail);
		p = p->pnext;
	}

}
Node* getNode(Node* phead, int pos)
{
	Node* p = phead;
	if (pos <= -1)return nullptr;
	while (pos)
	{
		if (!p)return p;
		p = p->pnext;
		pos--;
	}
	return p;
}
void setPtail(Node* phead)
{
	Node* t = phead;
	Node* temp = t;
	while (t->pnext != nullptr)
	{
		t = t->pnext;
	}
	while (temp)
	{
		temp->ptail = t;
		temp = temp->pnext;
	}
}
Node* addNode(Node** phead, Node* pnode, int pos)
{
	Node* c = getNode(*phead, pos);
	Node* p = getNode(*phead, pos - 1);
	if (p)
	{
		p->pnext = pnode;	
	}
	pnode->pnext = c;
	if (c==*phead)*phead = pnode;
	setPtail(*phead);
	return *phead;
}
Node* delNode(Node** phead, int pos)
{
	Node* c = getNode(*phead, pos);
	Node* p = getNode(*phead, pos - 1);
	Node* n = nullptr;
	if (c)
	{
		n = c->pnext;
		free(c);
		c = nullptr;
		if (!p)*phead = n;
	}
	if (p)p->pnext = n;
	return *phead;
}
Node* delLink(Node*& phead)
{
	Node* p = nullptr;
	while (phead)
	{
		p = phead;
		phead = phead->pnext;
		printf("%4d be freed\n", p->data);
		free(p);
	}
	return phead;
}
int main()
{
	Node* phead = linkList(5);
    showList(&phead);

	Node* n1 = newNode(0, 7);
	addNode(&phead, n1, 5);
	showList(&phead);

	delNode(&phead, 5);
	showList(&phead);

	
	delLink(phead);
	printf("\nClass:");
	Link a;
	a.linkList(4);
	a.showList();
	a.addNode(a.createNode(0, 9), 0);
	a.showList();
	a.delNode(0);
	a.showList();
	
	return 0;
}