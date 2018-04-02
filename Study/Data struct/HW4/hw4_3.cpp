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
}Node;
typedef struct List
{
	Node* phead;
	List(int num)
	{
		phead = nullptr;
		Node* ptail = nullptr;
		int i = 1;
		while (num>=0)
		{
			phead = new Node(phead, num);
			if (i)
			{
				ptail = phead;
				i = 0;
			}
			num--;
		}
		ptail->next = phead;
	}
	void showList()
	{
		Node* p = phead;
		
		do{
			printf("%p:%d,%p\n", p, p->data, p->next);
			p = p->next;
		} while (p != phead);
		printf("\n");
	}
	~List()
	{
		Node* p = phead;
		Node* c = phead;
		
		do{
			p = p->next;
			printf("del:%p\n",phead);
			delete phead;
			phead = p;
		} while (phead != c);
	}
}List;
Node* search(List* plist, int data)
{
	Node* head = plist->phead;
	Node* current = head->next;
	head->data = data;
	while (current->data!=data)
	{
		current = current->next;
	}
	return ((current == head) ? nullptr : current);
}
int main()
{
	List a(2);
	a.showList();
	printf("%p\n", search(&a, 4));
	return 0;
}