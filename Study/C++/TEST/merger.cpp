#include<iostream>  
using namespace std;
#define error 0  
#define ok 1  
class Node
{
public:
	int data;
	Node *next;
	Node() { next = NULL; }
};
class List
{
public:
	Node *head;
	int len;
	List()
	{
		head = new Node;
		len = 0;
	}
	~List()
	{
		Node *p, *q;
		p = head;
		while (p != NULL)
		{
			q = p;
			p = p->next;
			delete[]q;
		}
		len = 0;
		head = NULL;
	}
	void InitList(int n)
	{
		int x, i;
		Node *tail;
		tail = head;
		for (i = 0; i<n; i++)
		{
			cin >> x;
			Node *s;
			s = new Node;
			s->data = x;
			tail->next = s;
			tail = s;
		}
		len += n;
	}
	void display()
	{
		Node *p;
		p = head->next;
		while (p)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
};
void LL_merge(Node *la, Node *lb, Node *lc)
{
	Node *p, *q, *t;
	t = lc;
	p = la->next;
	q = lb->next;
	while (p&&q)
	{
		if (p->data <= q->data)
		{
			t->next = p;
			t = p;
			p = p->next;
		}
		else
		{
			t->next = q;
			t = q;
			q = q->next;
		}
	}
	if (p)
	{
		t->next = p;
	}
	if (q)
	{
		t->next = q;
	}
	la->next = NULL; //±ÜÃâÖØ¸´Îö¹¹  
	lb->next = NULL; //±ÜÃâÖØ¸´Îö¹¹  

}
int main()
{
	int n1, n2;
	List ss1;
	List ss2;
	List ss3;
	//ss1.display();
	cin >> n1;
	ss1.InitList(n1);
	cin >> n2;
	ss2.InitList(n2);
	LL_merge(ss1.head, ss2.head, ss3.head);
	
	ss1.display();
	ss2.display();
	ss3.display();
	return 0;
}

