#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define MAX 100
typedef struct Node
{
	int data;
	Node* left;
	Node* right;
}Node;
Node* newNode(int data)
{
	Node* t = (Node*)malloc(sizeof(Node));
	t->data = data;
	t->left = nullptr;
	t->right = nullptr;
	return t;
}
typedef struct BTree
{
	Node* root=nullptr;
	void insert(int data)
	{
		if (!root)
		{
			root = newNode(data);
			return;
		}
		Node** p = &root;
		while (*p)
		{
			if (data < (*p)->data)
			{
				p = &((*p)->left);
				continue;
			}
			else if(data>(*p)->data)
			{
				p = &((*p)->right);
				continue;
			}
			return;
		}
		*p = newNode(data);
	}

	

	
	Node** find(int data)
	{
		Node** p = &root;
		while (*p&&p)
		{
			if ((*p)->data == data)return p;
			if (data < (*p)->data)
			{
				p = &((*p)->left);
				continue;
			}
			if (data > (*p)->data)
			{
				p = &((*p)->right);
				continue;
			}
		}
		return p;
	}
	Node** rightMost(Node** sroot)
	{
		Node** p = sroot;
		if (!p||!(*p))return p;
		while ((*p)->right)
		{
			p = &((*p)->right);
		}
		printf("rm:%d\n", (*p)->data);
		return p;
	}
	Node** leftMost(Node** sroot)
	{
		Node** p = sroot;
		if (!p||!(*p))return p;
		while ((*p)->left)
		{
			p = &((*p)->left);
		}
		printf("lm:%d\n", (*p)->data);
		return p;
	}
	void delNode(int data)
	{
		Node** c = find(data);
		if(!(*c))return;
		if ((*c)->left&&(*c)->right)
		{
			Node** l = leftMost(&((*c)->right));
			Node** r = rightMost(&((*c)->left));
			Node** t = ((*r)->data - (*c)->data < (*c)->data - (*l)->data) ? r : l;
			(*c)->data = (*t)->data;
			c = t;
			goto del;
		}
		else 
		{
del:		if ((*c)->left)
			{
				Node* t = (*c)->left;
				(*c)->data = t->data;
				(*c)->left = t->left;
				(*c)->right = t->right;
				free(t);
				return;
			}
			if ((*c)->right)
			{
				Node* t = (*c)->right;
				(*c)->data = t->data;
				(*c)->left = t->left;
				(*c)->right = t->right;
				free(t);
				return;
			}
			free(*c);
			*c = nullptr;
		}
	}
	~BTree()
	{
		Node* p = root;
		int top = -1;
		Node* t = nullptr;
		Node* s[MAX] = { 0 };
		do
		{
			while (p)
			{
				top++;
				s[top] = p;
				p = p->left;
			}
			if (top != -1)
			{
				p = s[top];
				if (p->right == nullptr || p->right==t)
				{
					top--;
					t = p;
					printf("%d freed\n", p->data);
					free(p);
					p = nullptr;
				}
				else
				{
					p = p->right;
				}

			}
		} while (p||top!=-1);
	}
}BTree;
void delTree(Node* root)
{
	if (!root)return;
	delTree(root->left);
	delTree(root->right);
	printf("%d freed\n", root->data);
	free(root);
	root = nullptr;
}
void newTree(Node** root)
{
	int data;
	if(scanf("%d",&data)!=1)
	{
		int c; while ((c = getchar()) != '\n'&&c != EOF);
		*root = nullptr;
		return;
	}
	*root = newNode(data);
	newTree(&((*root)->left));
	newTree(&((*root)->right));
}
void show(Node* root)
{
	if (!root)return;
	Node* a[10] = { 0 };
	int front=-1,rear = 0;
	Node* p = root;
	a[rear] = p;
	while (rear!=front)
	{
		front++;
		p = a[front];
		
		printf("%d,", p->data);
		if (p->left)
		{
			rear++;
			a[rear] = p->left;
		}
		if (p->right)
		{
			rear++;
			a[rear] = p->right;
		}

	}
}
void display(Node* root)
{
	if (!root)return;
	display(root->left);
	printf("%d,", root->data);
	
	display(root->right);
}
int maxDepth(Node* root)
{
	if (!root)return 0;
	int l = maxDepth(root->left);
	int r = maxDepth(root->right);
	return r > l ? (r + 1) : (l + 1);
}
int main()
{
	int a[]= { 5, 0, 10, -5, -8, -3, -4, -2 };
	BTree r;
	for (auto x : a)r.insert(x);
	display(r.root);
	show(r.root);
	printf("\n");
	r.delNode(-5);
	display(r.root);
	show(r.root);
	printf("%d\n", maxDepth(r.root));
	//Node* root = nullptr;
	//newTree(&root);
	//display(root);
	//delTree(r.root);
	system("pause");
	return 0;
}