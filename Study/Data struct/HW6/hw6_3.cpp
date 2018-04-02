#include<stdio.h>
#include<malloc.h>
typedef struct TNode
{
	int data;
	TNode* next;
}TNode;
TNode* createNode(int i_data, TNode* pnode=nullptr)
{
	TNode* p_head = (TNode*)malloc(sizeof(TNode));
	p_head->data = i_data;
	p_head->next = pnode;
	return p_head;
}
typedef struct List
{
	TNode* p_head;
	TNode* p_tail;
	int length;
	List(int i_num)
	{
		p_head = nullptr;
		length = i_num;
		int i = 1;
		while (i_num-->=0)
		{
			p_head = createNode(i_num+1, p_head);
			if (i)
			{
				p_tail = p_head;
				i = 0;
			}
		}
	}
	void insertNode(TNode* pos,TNode* pnode)
	{
		if (!pos || !pnode)return;
		TNode* p = p_head;
		while (p)
		{
			if (p == pos)
			{
				if (pos == p_tail)p_tail = pnode;
				pnode->next = pos->next;
				pos->next = pnode;
				length++;
				return;
			}
			p = p->next;
		}
		printf("the position[%p] is not in the list\n", pos);
	}
	void removeNode(TNode* pos)
	{
		if (!pos)return;
		TNode* p = p_head->next;
		TNode* t = p_head;
		while (p)
		{
			if (p == pos)
			{
				if (pos == p_tail)p_tail = t;
				t->next = pos->next;
				free(pos);
				pos = nullptr;
				length--;
				return;
			}
			t = p;
			p = p->next;
		}
		printf("this position[%p] is not in the list\n", pos);
	}
	int isEmpty()
	{
		if (!p_head->next)
		{
			printf("list is empty\n");
			return 0;
		}
		else
		{
			printf("list is not empty\n");
			return 1;
		}
	}
	int search(int i_data)
	{
		TNode* p = p_head->next;
		while (p)
		{
			if (p->data == i_data)
			{
				printf("%d[%p] in the list\n", p->data, p);
				return 1;
			}
			p = p->next;
		}
		printf("%d is not in the list\n", i_data);
		return 0;
	}
	void showList()
	{
		TNode* p = p_head->next;
		printf("headnode:%p,ptail:%p,length:%d\n", p_head, p_tail, length);
		while (p)
		{
			printf("%p:%d,%p\n", p, p->data,p->next);
			p = p->next;
		}
		printf("\n");
	}
}List;
int main()
{
	List a(2);
	a.showList();
	TNode* n1 = createNode(7);
	a.insertNode(a.p_head, n1);
	a.showList();
	a.search(2);
	a.search(9);
	a.removeNode(a.p_head->next);
	a.showList();
	a.removeNode(a.p_tail);
	a.showList();
	a.isEmpty();
	a.removeNode(a.p_tail);
	a.isEmpty();
	return 0;
}

