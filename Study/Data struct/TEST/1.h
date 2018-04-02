#pragma once
#include<stdio.h>
class Link
{
private:
		int data;
		Link* phead;
		Link* pnext;
		Link* prev;
		Link* ptail;
public:
	Link(){}
	Link(int data):data(data=0),phead(0),pnext(0),prev(0),ptail(0){}
	Link* createNode(Link* pnode, int data)
	{
		Link* p= new Link(data);
		p->data = data;
		p->pnext = pnode;
		p->prev = p;
		if (pnode != nullptr)pnode->prev = p;
		return p;
	}
	void linkList(int num)
	{
		phead = nullptr;
		while (--num >= 0)
		{
			phead = createNode(phead, num);
		}
		Link* t = phead;
		Link* temp = t;
		while (t->pnext != nullptr)
		{
			t = t->pnext;
		}
		while (temp)
		{
			temp->ptail = t;
			temp = temp->pnext;
		}
	}
	void showList()
	{
		printf("\n");
		printf("n,p,        p->next,p->prev,p->ptail\n");
		Link* p = phead;
		while (p)
		{
			printf("%d,%p,%p,%p,%p\n", p->data, p, p->pnext, p->prev,p->ptail);
			p = p->pnext;
		}

	}
	Link* getNodePtr(int pos)
	{
		Link* p = phead;
		if (pos <= -1)return nullptr;
		while (pos)
		{
			if (!p)return p;
			p = p->pnext;
			pos--;
		}
		return p;
	}
	void addNode(Link* pnode, int pos)
	{
		Link* c = getNodePtr(pos);
		Link* p = getNodePtr(pos - 1);
		if (p)
		{
			p->pnext = pnode;
		}
		pnode->pnext = c;
		if (c == phead)phead = pnode;

		Link* t = phead;
		Link* temp = t;
		while (t->pnext != nullptr)
		{
			t = t->pnext;
		}
		while (temp)
		{
			temp->ptail = t;
			temp = temp->pnext;
		}
	}
	void delNode(int pos)
	{
		Link* c = getNodePtr(pos);
		Link* p = getNodePtr(pos - 1);
		Link* n = nullptr;
		if (c)
		{
			n = c->pnext;
			free(c);
			c = nullptr;
			if (!p)phead = n;
		}
		if (p)p->pnext = n;
	}
	~Link()
	{
		Link* p = nullptr;
		while (phead)
		{
			p = phead;
			phead = phead->pnext;
			printf("%4d be deleted\n", p->data);
			delete(p);
		}
	}

};