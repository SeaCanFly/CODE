#include<stdio.h>
#include<malloc.h>
typedef struct TNode
{
	int data;
	TNode* next;
	TNode* prev;
};
TNode* createNode(int i_data, TNode* pnode = nullptr)
{
	TNode* p_head = (TNode*)malloc(sizeof(TNode));
	p_head->data = i_data;
	p_head->next = pnode;
	p_head->prev = p_head;
	if (pnode)pnode->prev = p_head;
	return p_head;
}
typedef struct TSortedList
{
	TNode* p_head;
	TNode* p_tail;
	int count;
	TSortedList(int i_num)
	{
		p_head = nullptr;
		p_tail = nullptr;
		count = i_num;
		int i = 1;
		while (i_num--)
		{
			p_head = createNode(i_num + 1, p_head);
			if (i)
			{
				p_tail = p_head;
				i = 0;
			}
		}
	}
	void showList()
	{
		TNode* p = p_head;
		if (!p)printf("list is empty\n");
		printf("phead:%p,ptail:%p,count:%d\n", p_head, p_tail, count);
		while (p)
		{
			printf("%p:%d,%p,%p\n", p, p->data, p->prev, p->next);
			p = p->next;
		}
		printf("\n");
	}
	void add(int i_data)
	{
		TNode* p = p_head;

		while (p)
		{
			if (p->data >= i_data)
			{
				TNode* pnode = createNode(i_data);
				TNode* prv = p->prev;
				if (prv == p_head)
				{
					prv = pnode;
					p_head = pnode;
				}
				pnode->next = p;
				if (prv != p_head)prv->next = pnode;
				p->prev = pnode;
				pnode->prev = prv;
				count++;
				return;
			}
			p = p->next;
		}
		TNode* pnode = createNode(i_data);
		if (!p_head)p_head = pnode;
		else
		{
			p_tail->next = pnode;
			pnode->prev = p_tail;
		}
		p_tail = pnode;
		count++;
	}
	void del(int i_data)
	{
		TNode* p = p_head;
		while (p)
		{
			if (p->data == i_data)
			{
				TNode* prev = p->prev;
				TNode* next = p->next;
				if (p->prev == p)
				{
					prev = next;
					p_head = next;
				}
				if (!next) { p_tail = prev; }
				free(p);
				p = nullptr;
				if (prev != next)prev->next = next;
				if (next)next->prev = prev;
				count--;
				return;
			}
			p = p->next;
		}
	}
	void clear()
	{
		TNode* p = p_head;
		while (p_head)
		{
			p = p->next;
			free(p_head);
			p_head = p;
		}
		p_tail = nullptr;
		count = 0;
	}
	void isInList(int i_data)
	{
		TNode* p = p_head;
		while (p)
		{
			if (p->data == i_data)
			{
				printf("[%d] in the list\n", p->data);
				return;
			}
			p = p->next;
		}
		printf("[%d] not in the list\n", i_data);
	}
	int getLength()
	{
		return count;
	}
	void isEmpty()
	{
		if (!p_head)printf("list is empty\n");
		else printf("list not empty\n");
	}
	~TSortedList()
	{
		TNode* p = p_head;
		while (p_head)
		{
			p = p->next;
			free(p_head);
			p_head = p;
		}
		p_tail = nullptr;
		count = 0;
	}
}TSortedLsit;
int main()
{
	TSortedList a(0);
	a.showList();
	a.add(0);
	a.showList();
	a.add(4);
	a.showList();
	a.add(7);
	a.showList();

	a.del(1);
	a.showList();
	a.del(0);
	a.showList();
	a.del(7);
	a.showList();
	a.del(4);

	a.showList();
	a.isInList(0);
	a.clear();
	a.showList();
	return 0;
}