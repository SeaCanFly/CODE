#include<stdio.h>
typedef struct Node
{
	int data;
	Node* next;
	Node(Node* pnode, int i_data)
	{
		data = i_data;
		next = pnode;
	}
};
typedef struct List
{
	Node* phead;
	List(int num)
	{
		phead = nullptr;
		while (--num>=0)
		{
			phead = new Node(phead,num+1);
		}
	}
	void delbyOdd()
	{
		Node* p = phead;
		Node* t = phead;
		Node* n=nullptr;
		int i = 1;
		while (t)
		{
			p = p->next;
			delete t;
			t = p;
			if (i)
			{
				phead = p;
				i = 0;
			}
			if (p)
			{
				n = p;
				p = p->next;
				t = t->next;
				if(t)n->next = t->next;
			}
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
};
int main()
{
	
	List a(8);
	a.showList();
	a.delbyOdd();
	a.showList();
	return 0;
}