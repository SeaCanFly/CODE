#include<stdio.h>
#include<malloc.h>
typedef struct Node
{
	int data;
	Node* next;
	Node(int i_data, Node* pnode)
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
			phead = new Node(num,phead);
		}
	}
	void setVal()
	{
		Node* p = phead;
		int data;
		printf("input [%d] numbers:", count);
		while (p)
		{
			scanf("%d", &data);
			p->data = data;
			p = p->next;
		}
	}
	void sortList()
	{
		Node* p = phead;
		Node* n = p;
		int t;
		while (p)
		{
			n = p->next;
			while (n)
			{
				if (n->data < p->data)
				{
					t = p->data;
					p->data = n->data;
					n->data = t;
				}
				n = n->next;
			}
			p = p->next;
		}

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
void merge(List* a, List* b, List** c)
{
	Node* pa = a->phead;
	Node* pb = b->phead;
	*c = new List(a->count+b->count);
	Node* pc = (*c)->phead;

	while (pa&&pb)
	{
		if (pa->data >= pb->data)
		{
			pc->data = pb->data;
			pb = pb->next;
			pc = pc->next;
		}
		else
		{
			pc->data = pa->data;
			pa = pa->next;
			pc = pc->next;
		}
	}
	while (pa)
	{
		pc->data = pa->data;
		pc = pc->next;
		pa = pa->next;
	} 
	while(pb)
	{
		pc->data = pb->data;
		pc = pc->next;
		pb = pb->next;
	}
}
int main()
{
	List a(4);
	List b(3);
	a.setVal();
	a.sortList();
	b.setVal();
	b.sortList();
	a.showList();
	b.showList();
	List* c = nullptr;
	merge(&a, &b, &c);
	c->showList();
	return 0;
}