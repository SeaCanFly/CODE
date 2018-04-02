#include<stdio.h>
#include<malloc.h>
struct Node
{
	int data;
	Node* pnext;
};
Node* newNode(Node* pnew, int data)
{
	Node temp = { data,pnew };
	Node *p = (Node*)malloc(sizeof(Node));
	*p = temp;
	return p;
}
Node* linkNode(Node* pnode, int num)
{
	while (--num>=0)
	{
		pnode = newNode(pnode, num);
	}
	printf("linknode phead=%p\n", pnode);
	return pnode;
}
void display(Node* phead)
{
	Node* p = phead;
	while (p)
	{
		printf("data=%d,p=%p,p->next=%p\n", p->data,p,p->pnext);
		p = p->pnext;
	}
}
Node* list_find(Node* head, int data)
{
	Node* p = head;
	while (p)
	{
		if (p->data == data)
		{
			return p;
		}
		p = p->pnext;
	}
	return nullptr;
}
int main()
{
	Node* ptail=nullptr;
	Node *phead = linkNode(ptail, 4);
	printf("main phead=%p\n", phead);
	display(phead);
	Node * f = list_find(phead, 3);
	printf("%d,", f->data);
	return 0;
}