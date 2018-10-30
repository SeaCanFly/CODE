#include<stdio.h>
typedef struct Node
{
	int data;
	Node* next;
	Node(Node*pnode, int i_data)
	{
		data = i_data;
		next = pnode;
	}
}Node;
typedef struct List
{	
	int count;
	Node* phead;
	List(int num)
	{
		phead = nullptr;
		count = num;
		while (--num>=0)
		{
			phead = new Node(phead, num + 1);
		}
	}
	int getCount()
	{
		return count;
	}
	void showList()
	{
		Node* p = phead;
		while (p)
		{
			printf("%p:%d,%p\n", p, p->data, p->next);
			p = p->next;
		}
		printf("\n");
	}
	~List()
	{
		Node* p = phead;
		while (phead)
		{
			p = p->next;
			delete phead;
			phead = p;
		}
	}
}List;
void alternate( List* a,List* b,List** c)
{
	Node* pa =a->phead;
	Node* pb =b->phead;
	*c = new List(a->getCount()+b->getCount());
	Node* pc = (*c)->phead;
	
	while (pa&&pb)
	{
		pc->data = pa->data;
		pc = pc->next;
		pa = pa->next;
		pc->data = pb->data;
		pc = pc->next;
		pb = pb->next;
	} 
	while (pa)
	{
		pc->data = pa->data;
		pc = pc->next;
		pa = pa->next;
	}
	while (pb) 
	{
		pc->data = pb->data;
		pc = pc->next;
		pb = pb->next;
	}
}
int main()
{
	List a(1);
	List b(3);
	List* c;
	a.showList();
	b.showList();
	alternate(&a,&b,&c);
	c->showList();
	return 0;
}