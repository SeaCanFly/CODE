#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
struct node{ int data;struct node* next;};
struct node* makenode (int data, struct node* pnext);
struct node* linknode(int n,struct node* pnext);
void shownode (struct node* phead);
struct node* dellink(struct node* phead);
struct node* makenode (int data, struct node* pnext)
{
	struct node = {data,pnext};	
	struct node* phead=(struct node*)malloc(sizeof(struct node));
	*phead=n;	printf("makenode:%d,%d,%d",phead->data,phead->next,phead);printf("---%d,%d,%d\n",n.data,n.next,n);
	return phead;
}
struct node* linknode(int n,struct node* phead)
{
	int i; phead=NULL;
	for(i=n-1;i>=0;i--)
		{phead=makenode(i,phead);}
	return phead;
}
void shownode (struct node* phead)
{
	struct node* temp=phead;
	while(temp!=NULL)
	{
		printf("shownode:%d,%d\n",temp->data,temp);
		temp=temp->next;
	}
}
struct node* dellink(struct node* phead)
{
	
	struct node* delnode=phead;
	while(delnode!=NULL)
	{
		phead=phead->next;    printf("%d,%d,%d",delnode,delnode->data,delnode->next);
		free(delnode);        printf("--%d---\n",phead);
		delnode=phead;	      printf("%d",phead);	printf("----%d\n",delnode);	
	}

	printf("\n");
	printf("%d\n",delnode);
	printf("%d\n\n",phead);
	return phead;
}
int main()
{
	int n;
	printf("%d\n",sizeof(struct node));
	printf("creat n node link\n>");
	scanf("%d",&n);
	
	struct node* pnext=NULL;
	struct node* phead=linknode(n,pnext);
	shownode(phead);
	phead=dellink(phead);
	printf("%d",phead);
	return 0;
}