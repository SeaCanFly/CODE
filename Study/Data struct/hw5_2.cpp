#include<stdio.h>
#include<malloc.h>
typedef struct TNode
{
	int i_data;
	TNode* p_next;
	TNode(int i_dt, TNode* p_node)
	{
		
		this->i_data = i_dt;
		p_next = p_node;
	}
}TNode;
typedef struct TList
{
	TNode* p_head;
	TList(int num)
	{
		p_head = nullptr;
		int i = 1;
		TNode* p_tail = nullptr;
		while (--num>=0)
		{
			TNode t(num, p_head);
			p_head = (TNode*)malloc(sizeof(TNode));
			if (i) { p_tail = p_head; i = 0; }
			*p_head = t;
		}
		p_tail->p_next = p_head;
	}
	void showList()
	{
		TNode* p = p_head;
		do{
			if (p)
			{
				printf("%p:%d,%p\n", p, p->i_data, p->p_next);
				p = p->p_next;
			}
		} while (p != p_head);
		printf("\n");
	}
	TNode* getNode(int pos)
	{
		if (pos < 0)return nullptr;
		TNode* p = p_head;
		while (pos--)
		{
			p = p->p_next;
			if (p==p_head)return nullptr;
		}
		return p;
	}
	void remove_node2(int pos)
	{
		TNode* p_node = getNode(pos);
		if (!p_node)return;
		TNode* p_n = p_node->p_next;
		if (p_n == p_node) 
		{ 
			free(p_node);
			p_node = nullptr;
			p_head = nullptr;
			return;
		}
		p_node->i_data = p_n->i_data;
		p_node->p_next = p_n->p_next;
		if (p_n == p_head) { p_head =p_node; }
		free(p_n);
		p_n = nullptr;		
	}
	~TList()
	{
		TNode* p = p_head;
		TNode* t = p_head;
		do{
			if (p)
			{
				p = p->p_next;
				free(p_head);
				p_head = p;
			}
		} while (p_head != t);
		p_head = nullptr;
	}
}TList;
int main()
{
	TList a(2);
	a.showList();
	a.remove_node2(0);
	a.showList();
	return 0;
}