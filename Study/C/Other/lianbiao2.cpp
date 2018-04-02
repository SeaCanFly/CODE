#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

struct node { int data; struct node* next; };
struct node* makenode(int data, struct node* pnext=NULL)
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
	}
	return NULL;
}
struct node* insernode(struct node* pnode1, struct node* pnode2,struct node* insernode)
{		  
	if (pnode1==NULL)
	{insernode->next = pnode2; return insernode;	}	
	else if(pnode1!=NULL)
	{ pnode1->next = insernode;insernode->next = pnode2; }
}
struct node* delnode(struct node* pnode1, struct node* pnode2)
{
	struct node* ptemp = NULL;
		/*if (pnode1==NULL){ ptemp = pnode2->next; free(pnode2); return ptemp;}	   				 
		else  { ptemp = pnode2->next; free(pnode2); pnode1->next=ptemp; }*/
	if(pnode2){
	ptemp=pnode2->next;
	free(pnode2);}
	if(pnode1)pnode1->next=ptemp;
	return ptemp;
}
int main()
{
	int n;
	printf("creat n node link\n>");
	scanf("%d", &n);
	struct node* pnext=NULL;
	struct node* phead = linknode(n, pnext);
	shownode(phead);
	printf("\n");
	struct node* pnew=insernode(phead, phead->next, makenode(77, pnext)); 
	printf("%d\n",pnew);
	shownode(phead);
	printf("\n");

	delnode(phead, pnew);	printf("%d\n",phead);
	shownode(phead);
	delnode(phead->next, NULL);printf("\n");
	shownode(phead);
	phead=dellink(phead);
	printf("%d\n",phead);
	return 0;	   
}