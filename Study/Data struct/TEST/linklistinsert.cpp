#include<stdio.h>
#include<malloc.h>
typedef struct Node
{
	int data;
	Node* next;
	Node* prev;
}Node;
Node* newNode(Node* pnode, int data)
{
	Node* phead=(Node*)malloc(sizeof(Node));
	phead->data=data;
	phead->next=pnode;
	phead->prev=phead;
	if(pnode)pnode->prev=phead;
	return phead;
}
Node* linkNode(Node* pnode, int num)
{
	while (--num>=0)
	{
		pnode=newNode(pnode,num);
	}
	return pnode;
}
Node* insertNode(Node* phead, Node* pnode, int pos)
{
	Node* p=phead;
	while (pos)
	{
		p=p->next;
		pos--;
	}
	pnode->next=p;
	pnode->prev=p->prev;
	//p->prev=pnode;
	
	if(p!=phead)
	{
		
		p->prev->next=pnode;
		return phead;
	}
	else{return pnode;}
}
void showNode(Node* phead)
{
	Node* p=phead;
	while (p)
	{
		printf("%d,%p,%p,%p\n",p->data,p,p->next,p->prev);
		p=p->next;
	}
}

int main()
{
	Node* phead=linkNode(nullptr,4);
	showNode(phead);
	Node a;
	a.data=9;
	printf("%p\n",phead=insertNode(phead,&a,1));
	showNode(phead);
	return 0;
}