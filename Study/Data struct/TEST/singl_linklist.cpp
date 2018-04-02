#include<stdio.h>
#include<malloc.h>
typedef struct Node
{
	int data;
	Node* pnext;
}Node;
Node* newNode(Node* pnode, int data)
{
	Node* phead=(Node*)malloc(sizeof(Node));
	phead->data=data;
	phead->pnext=pnode;
	return phead;
}
Node* linkList(int num)
{
	Node* phead=nullptr;
	while (--num>=0)
	{
		phead=newNode(phead,num);
	}
	return phead;
}
void showList(Node* phead)
{
	printf("\n");
	Node* p=phead;
	while (p)
	{
		printf("%d,%p,%p\n",p->data,p,p->pnext);
		p=p->pnext;
	}

}
Node* getNode(Node* phead,int pos)
{
	Node* p=phead;
	if(pos<=-1)return nullptr;
	while (pos)
	{
		if(!p)return p;
		p=p->pnext;
		pos--;
	}
	return p;
}
Node* addNode(Node*& phead, Node* pnode, int pos)
{
	Node* c=getNode(phead,pos);
	Node* p=getNode(phead,pos-1);
	if(p)
	{
		p->pnext=pnode;
		if(c)phead=pnode;
	}
	pnode->pnext=c;
	return phead;
}
Node* delNode(Node*& phead, int pos)
{
	Node* c=getNode(phead,pos);
	Node* p=getNode(phead,pos-1);
	Node* n=nullptr;
	if (c)
	{
		n=c->pnext;
		free(c);
		c=nullptr;
		if(!p)phead=n;
	}
	if(p)p->pnext=n;
	return phead;
}
Node* delLink(Node*& phead)
{
	Node* p=nullptr;
	while (phead)
	{
		p=phead;
		phead=phead->pnext;
		printf("%4d be freed\n", p->data);
		free(p);
	}
	return phead;
}
int main()
{
	Node* phead=linkList(3);
	Node* n1=newNode(0,7);
	addNode(phead,n1,3);
	showList(phead);

	delNode(phead,3);
	showList(phead);

	delLink(phead);
	showList(phead);


	return 0;
}