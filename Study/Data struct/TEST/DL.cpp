#include<stdio.h>
#include<malloc.h>
typedef struct Node
{
	int data;
	Node* prev;
	Node* next;
}Noda;
Node* createNode(int data, Node* pnode)
{
	Node* phead = (Node*)malloc(sizeof(Node));
	phead->data = data;
	phead->next = pnode;
	phead->prev = phead;
	if (pnode)pnode->prev = phead;
	return phead;
}
typedef struct List
{
	int count;
	Node* phead;
	Node* ptail;
	List(int num)
	{
		phead = nullptr;
		count = num;
		int i = 1;
		while (num)
		{
			phead = createNode(num, phead);
			num--;
			if (i)
			{
				ptail = phead;
				i = 0;
			}
		}
	}
	void showList()
	{
		Node* p = phead;
		if(p)printf("%d,%p,%p\n", count, phead, ptail);
		else printf("list is empty\n");
		while (p)
		{
			printf("%p:%d,%p,%p\n", p, p->data, p->next, p->prev);
			p = p->next;
		}
		printf("\n");
	}
	Node* getNode(int pos)
	{
		if (pos<=-1 || pos>count)return nullptr;
		Node* p = phead;
		while (pos)
		{
			p = p->next;
			pos--;
		}
		return p;
	}
	void insertNode(int pos,int data)
	{
		if (pos<0 || pos>count)return;
		Node* c = getNode(pos);	
		Node* p = getNode(pos-1);
		Node* t = createNode(data, nullptr);
		if (c!=phead&&p)
		{
			p->next = t;
			t->prev = p;
		}
		t->next = c;
		if(c)c->prev = t;
		if (c == phead)phead = t;
		if (p == ptail)ptail = t;
		count++;
	}
	void removeNode(int pos)
	{
		if (pos<0 || pos>=count)return;
		Node* c = getNode(pos);
		Node* p = c->prev;
		Node* n = c->next;		
		if (c == phead)phead = n;
		if (c == ptail)ptail = p;
		if(p)p->next = c->next;
		if (n)
		{
			n->prev = c->prev;
			free(c);
			c = nullptr;
		}
		count--;
	}
	void push_back(Node* pnode)
	{
		if (!pnode)return;
		if (!phead)
		{
			phead = pnode;
			ptail = pnode;
			count++;
			return;
		}
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
		if (t == p)
		{
			free(t);
			t = nullptr;
			phead = nullptr;
			ptail = nullptr;
			count--;
			return;
		}
		free(t);
		t = nullptr;
		p->next = nullptr;
		count--;
	}
	void push_front(Node* pnode)
	{
		if (!pnode)return;
		if (!phead)
		{
			phead = pnode;
			ptail = pnode;
			count++;
			return;
		}
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
			ptail = nullptr;
			count--;
		}
	}
	~List()
	{
		Node* p = phead;
		while (phead)
		{
			p = p->next;		
			free(phead);
			phead = p;	
		}
	}
}List;
int main()
{
	List a(1);
	a.showList();
	//printf("%p,%p\n", a.getNode(0), a.getNode(3));
	a.insertNode(0, 8);
	a.showList();
	a.removeNode(1);
	a.showList();
	Node* n1 = createNode(6,0);
	Node* n2 = createNode(9, 0);
	a.pop_back();
	a.showList();
	a.push_back(n1);
	a.showList();
	a.pop_front();
	a.showList();
	a.push_front(n2);
	a.showList();
	return 0;
}