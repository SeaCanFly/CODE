#include<stdio.h>
#include<malloc.h>
typedef struct TNode
{
	int i_data;
	TNode* p_next;
	TNode(int data, TNode* p_node = nullptr)
	{
		i_data = data;
		p_next = p_node;
	}
}TNode;
typedef struct TList
{
	TNode* p_head;
	TList(int num)
	{
		p_head = nullptr;
		while (--num >= 0)
		{
			TNode t(num+1, p_head);
			p_head = (TNode*)malloc(sizeof(TNode));
			*p_head = t;
		}

	}
	void showList()
	{
		TNode* p = p_head;
		while (p)
		{
			printf("%p:%d,%p\n", p, p->i_data, p->p_next);
			p = p->p_next;
		}
		printf("\n");
	}
	~TList()
	{
		TNode* p = p_head;
		while (p_head)
		{
			p = p->p_next;
			free(p_head);
			p_head = p;
		}
	}
}TList;
void split(TList* a, TList* b, TList* c)
{
	printf("%p,%p,%p,%p\n", a,&a,a->p_head, &a->p_head);
	if (!c)return;
	TNode* pc = c->p_head;
	TNode* p_anode = nullptr;
	TNode* p_bnode = nullptr;
	TNode* pa = nullptr;
	TNode* pb = nullptr;
	int i = 1;
	int j = 1;
	while (pc)
	{
		if (pc)
		{
			TNode ta(pc->i_data, nullptr);
			p_anode = (TNode*)malloc(sizeof(TNode));
			*p_anode = ta;
			if (i)
			{
				a->p_head = p_anode;
				pa = a->p_head;
				i = 0;
			}
			else
			{
				 pa->p_next= p_anode;
				 pa = pa->p_next;
			}
			pc = pc->p_next;
		}

		if (pc)
		{
			TNode tb(pc->i_data, nullptr);
			p_bnode = (TNode*)malloc(sizeof(TNode));
			*p_bnode = tb;
			if (j)
			{
				b->p_head = p_bnode;
				pb = b->p_head;
				j = 0;
			}
			else
			{
				pb->p_next = p_bnode;
				pb = pb->p_next;
			}
			pc = pc->p_next;
		}
	}
}
int main()
{
	TList a(0);
	TList b(0);
	TList c(3);
	printf("%p,%p,%p\n",&a, a.p_head,&a.p_head);
	split(&a, &b, &c);
	c.showList();
	a.showList();
	b.showList();
	c.showList();
	return 0;
}