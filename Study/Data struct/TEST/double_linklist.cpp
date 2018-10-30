#include<stdio.h>
#include<malloc.h>
struct Node
{
	int data;
	Node* next;
	Node* prev;
};
Node* newNode(Node* pnode, int data)
{
	Node * p=(Node*)malloc(sizeof(Node));
	p->data=data;
	p->next=pnode;
	p->prev=p;
	if(pnode!=nullptr)pnode->prev=p;
	return p;
}
Node* linkNode(Node* pnode, int num)
{
	while (--num >= 0)
	{
		pnode=newNode(pnode,num);
	}
	return pnode;
}
void showNode(Node* phead)
{
	Node* p=phead;
	while (p)
	{
		printf("%d,%p,%p,%p\n",p->data,p,p->prev,p->next);
		p=p->next;
	}
}
//void setPrev(Node* phead)
//{
//	Node* p=phead;
//	while (p)
//	{
//		if (p == phead)p->prev=phead;
//		Node *pt=p;
//		p=p->next;
//		if(p!=nullptr)p->prev=pt;	
//	}
//}
int main()
{
	Node* phead=linkNode(0,4);
	//setPrev(phead);
	showNode(phead);

	return 0;
}