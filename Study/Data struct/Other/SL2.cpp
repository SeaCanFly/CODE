#include<stdio.h>
#include<malloc.h>
#include<iostream>
struct Node
{
	int data;
	Node* pnext;
};
Node* newNode(Node* pnode, int data)
{
	Node* phead = (Node*)malloc(sizeof(Node));
	phead->data = data;
	phead->pnext = pnode;
	return phead;
}
Node* linkNode(Node* pnode, int num)
{	
	int* data = (int *)malloc(sizeof(int)*num);

	for (int i = 0; i < num; i++)
	{
		scanf("%d", &data[i]);
	}

	while (--num>=0)
	{
		pnode = newNode(pnode, data[num]);
	}
	free(data);
	return pnode;
}
Node* listFind(Node* pnode, int check)
{
	Node* p = pnode;
	while (p)
	{
		if (p->data == check)return p;
		p = p->pnext;
	}
	return p;
}
void showNode(Node* phead)
{
	Node* ptemp = phead;
	while (ptemp)
	{
		printf("%d,%p,%p\n", ptemp->data, ptemp, ptemp->pnext);
		ptemp = ptemp->pnext;
	}
}

int main()
{
	int num;
	std::cin >> num;
	std::cout << num;
/*	Node* ptail = nullptr;
	Node* phead = linkNode(ptail, 5);
	showNode(phead);
	printf("%p\n", listFind(phead, 3))*/;
	return 0;
}