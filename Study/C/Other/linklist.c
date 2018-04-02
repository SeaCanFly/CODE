#include<stdio.h>
#include<memory.h>
#include <stdlib.h>
struct node
{
	int data; struct node *pnext;
};
struct node* NewNode(int data, struct node* pnext)
{
	struct node temp = { data,pnext };
	struct node* phead = (struct node*)malloc(sizeof(struct node*));
	*phead = temp;
	return phead;
}
struct node* LinkNode(int n, struct node* phead)
{
	phead = NULL;
	for (n;n >= 0;n--)
	{
		phead = NewNode(n, phead);
	}
	return phead;
}
struct node* DelLink(struct node* phead)
{
	struct node* Dtemp = phead;
	while (Dtemp != NULL)
	{
		phead = phead->pnext;
		free(Dtemp);
		Dtemp = phead;
	}
	return phead;
}
void ShowNode(struct node* phead)
{
	struct node* Stemp = phead;
	while (Stemp != NULL)
	{
		printf("data=%d,add=0x%X\n", Stemp->data, Stemp->pnext);
		Stemp = Stemp->pnext;
	}
}
struct node* InsertNode(struct node* p1, struct node* pnew, struct node* p2)
{
	if (p1) { p1->pnext = pnew; }
	 pnew->pnext=p2;
	 return pnew;
}
struct node* RemoveNode(struct node* pa, struct node* pr)
{
	struct node* Rtemp = NULL;
	if (pr) 
		{
			Rtemp = pr->pnext;
			free(pr);
		}
	if (pa) { pa->pnext = Rtemp; }
	return Rtemp;
}
int main()
{
	int n;
	printf("Creat n nodes linklist\nn=");
	scanf("%d", &n);
	struct node* ptail = NULL;
	struct node* phead = LinkNode(n, ptail);
	ShowNode(phead);
	printf("\n");

	struct node* pnew = NewNode(777, ptail);
	struct node* newnode=InsertNode(phead->pnext, pnew, phead->pnext->pnext);
	ShowNode(phead);
	printf("\n");

	RemoveNode(phead->pnext, pnew);
	ShowNode(phead);
	printf("\n");

	phead = DelLink(phead);
	return 0;
}
