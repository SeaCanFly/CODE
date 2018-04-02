#include <stdio.h>
#include<stdio.h>
#include<malloc.h>

typedef struct Node
{
	int data;
	Node* next;
	Node* prev;
	Node():data(0),next(nullptr),prev(nullptr){}
}Node;
Node* newNode(Node* pnode, int data)
{
	Node* phead = (Node*)malloc(sizeof(Node));
	phead->data = data;
	phead->next = pnode;
	phead->prev = phead;
	if (pnode != nullptr)pnode->prev = phead;
	return phead;
}
typedef struct Link
{
	Node* phead;
	Node* ptail;
	int count;
	Link():phead(nullptr),ptail(nullptr),count(0){}
	Link(int num)
	{
		Node* phead = nullptr;
		Node* t=nullptr;
		this->count=num;
		int i=num;
		while (--num >= 0)
		{
			phead = newNode(phead, num + 1);
			if (num == i - 1)
			{
				t=phead;
			}
		}
		this->phead=phead;
		this->ptail=t;
	}
	void showList()
	{
		printf("\n");
		printf("cout:%d,phead:%p,ptail:%p\n",count,phead,ptail);
		printf("n,p,        p->next,p->prev\n");
		Node* p = phead;
		while (p)
		{
			printf("%d,%p,%p,%p\n", p->data, p, p->next, p->prev);
			p = p->next;
		}

	}
	int getCount()
	{
		return count;
	}
	Node* getNode(int pos)
	{
		Node* p = phead;
		if (pos <= -1||pos>count+1)
		{
			printf("Error,not in the list\n");
			return nullptr;
		}
		while (pos)
		{
			if (!p)return p;
			p = p->next;
			pos--;
		}
		return p;
	}
	void setPtail()
	{
		Node* t = phead;
		while (t->next != nullptr)
		{
			t = t->next;
		}
		ptail=t;
	}
	void insertNodeAt(Node* pnode, int pos)
	{
		if(!pnode||pos<0||pos>count+1)return;
		Node* c = getNode(pos);
		Node* p = c->prev;
		if (p)
			p->next = pnode;
		pnode->next = c;
		if (c == phead)
			phead = pnode;
		if (pos = count + 1)
			ptail=pnode;
		count++;
	}
	void removeNodeAt(int pos)
	{
		if(pos<0||pos>count)return;
		Node* c = getNode(pos);
		Node* p = c->prev;
		Node* n = c->next;
		if (c->prev==c)
			{
				p = next;
				phead = next;
			}
		if (!n) { p_tail = prev; }
		free(c);
		c = nullptr;
		if (p!= n)p->next = n;
		if (n)n->prev = p;
		count--;
		return;
	}
	Node* delLink()
	{
		Node* p = nullptr;
		while (phead)
		{
			p = phead;
			phead = phead->next;
			printf("%4d be freed\n", p->data);
			free(p);
		}
		return phead;
	}
	void push_back(Node* pnode)
	{
		if (!phead||!pnode)return;
		Node* t = ptail;
		t->next = pnode;
		pnode->next = nullptr;
		pnode->prev = t;
		ptail=pnode;
		count++;
	}
	void pop_back()
	{
		if (!phead)return;
		Node* t =ptail;
		Node* p = t->prev;
		ptail=p;
		free(t);
		p->next = nullptr;
		t = nullptr;
		count--;
	}
	void push_front(Node* pnode)
	{
		if (!phead || !pnode)return;
		pnode->prev = pnode;
		phead->prev = pnode;
		pnode->next = phead;
		phead = pnode;
		count++;
	}
	void pop_front()
	{
		if (!phead)return;
		Node* t = phead;
		if (t->next)
		{
			phead = t->next;
			free(t);
			t = nullptr;
			count--;
		}
		else
		{
			free(t);
			t = nullptr;
			phead = nullptr;
			ptail=nullptr;
			count--;
		}
	}
}Link;

int main()
{
	Link a(1);
	printf("list:");
	a.showList();

	Node* n1 = newNode(0, 7);
	printf("\npush_back:");
	a.push_back(n1);
	a.showList();

	
	printf("\npop_back:");
	a.pop_back();
	a.showList();

	Node* n2 = newNode(0, 9);
	printf("\npush_front:");
	a.push_front(n2);
	a.showList();

	printf("\npop_front:");
	a.pop_front();
	a.showList();
	
	/*Node* n3=newNode(0,9);
	a.insertNodeAt(n2,1);
	a.showList();*/

	a.delLink();


	return 0;
}