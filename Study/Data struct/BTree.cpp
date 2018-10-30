#include<stdio.h>
#include<iostream>
#include<malloc.h>
#include<stdlib.h>
using namespace std;
#define MAX 300
typedef struct Node
{
	char data;
	Node* left;
	Node* right;
};
Node* newNode(char i_data)
{
	Node* t = (Node*)malloc(sizeof(Node));
	t->data = i_data;
	t->left = nullptr;
	t->right = nullptr;
	return t;
}
typedef struct Tree
{
	Node* root;
	Node* s[MAX];
	int top = -1;
	void newTree()
	{
		char c;
		printf("input root data:");
		cin >> c;
		root = newNode(c);
		Node* cn = root;
		top++;
		s[top] = cn;
		do
		{
			while (cn)
			{
				printf("input %c left:",cn->data);
				cin >> c;
				if (c == '#')
				{
					cn->left = nullptr;
					cn = cn->left;
				}
				else
				{
					cn->left = newNode(c);
					top++;
					s[top] = cn->left;
					cn = cn->left;
				}
			}
			if (top != -1)
			{
				cn = s[top];
				top--;
				printf("input %c right:", cn->data);
				cin >> c;
				if (c == '#')
				{
					cn->right = nullptr;
					cn = cn->right;
				}
				else
				{
					cn->right = newNode(c);
					top++;
					s[top] = cn->right;
					cn = cn->right;
				}
			}
		} while (cn||top!=-1);
	}
	void pShow()
	{	
		Node* p = root;
		do {
			while (p)
			{
				printf("%c,", p->data);
				top++;
				s[top] = p;
				p = p->left;
			}
			if (top != -1)
			{
				p = s[top];
				top--;

				p = p->right;
			}
		} while (p!=nullptr || top != -1);
		printf("\n");
	}
	void iShow()
	{
		Node* p = root;
		do {
			while (p)
			{
				top++;
				s[top] = p;
				p = p->left;
			}
			if (top != -1)
			{
				p = s[top];
				top--;
				printf("%c,", p->data);
				p = p->right;
			}
		} while (p || top != -1);
		printf("\n");
	}
	void lShow()
	{
		Node* p = root;
		Node* t = nullptr;
		do {
			while (p)
			{
				top++;
				s[top] = p;
				p = p->left;
			}
			if (top != -1)
			{
				p = s[top];
				if (p->right == nullptr || p->right == t)
				{
					printf("%c,", p->data);
					top--;
					t = p;
					p = nullptr;
				}
				else
				{
					p = p->right;
				}
			}
		} while (p || top != -1);
		printf("\n");
	}
	~Tree()
	{
		Node* p = root;
		Node* t = nullptr;
		do {
			while (p)
			{
				top++;
				s[top] = p;
				p = p->left;
			}
			if (top != -1)
			{
				p = s[top];
				if (p->right == nullptr || p->right == t)
				{
					top--;
					t = p;
					free(p);
					p = nullptr;
				}
			}
		} while (p || top != -1);
	}
};
void repShow(Node* a)
{
	if (!a)return;
	printf("%c,", a->data);
	repShow(a->left);
	repShow(a->right);
}
void reiShow(Node* a)
{
	if (!a)return;
	reiShow(a->left);
	printf("%c,", a->data);
	reiShow(a->right);
}
void relShow(Node* a)
{
	if (!a)return;
	relShow(a->left);
	relShow(a->right);
	printf("%c,", a->data);
}
int main()
{
	Tree a;
	a.newTree();
	a.pShow();
	a.iShow();
	a.lShow();	

	repShow(a.root);
	printf("\n");
	reiShow(a.root);
	printf("\n");
	relShow(a.root);
	printf("\n");
	system("pause");
	return 0;
}