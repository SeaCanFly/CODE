#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
struct node* makenode(int data, struct node* pnext);
struct node* linknode(int n, struct node* pnext);
void shownode(struct node* phead);
struct node* dellink(struct node* phead);

struct node { int data; struct node* next; };
struct node* makenode(int data, struct node* pnext)
{
	struct node n = { data,pnext };
	struct node* phead = (struct node*)malloc(sizeof(struct node));
	*phead = n;	
	return phead;
}
struct node* linknode(int n, struct node* phead)
{
	int i; phead = NULL;
	for (i = n - 1; i >= 0; i--)
	{
		phead = makenode(i, phead);
	}
	return phead;
}
void shownode(struct node* phead)
{
	struct node* temp = phead;
	while (temp != NULL)
	{
		printf("%d,%d\n", temp->data, temp);
		temp = temp->next;
	}
}
struct node* dellink(struct node* phead)
{

	struct node* temp = phead;
	while (temp != NULL)
	{
		struct node* delnode =temp;
		temp = temp->next;
		free(delnode);
	printf("%d----",delnode);
	printf("%d,\n",temp);
		
	}
	printf("\n");
	//printf("%d,\n",delnode);
	printf("%d,\n",temp);
	printf("%d,\n",phead);
	return NULL;
}

int main()
{
	int n;
	printf("creat n node link\n>");
	scanf("%d", &n);
	struct node* pnext = NULL;
	struct node* phead = linknode(n, pnext);

	shownode(phead);
	phead=dellink(phead);
	
	return 0;	   
}
