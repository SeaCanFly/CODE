#include<stdio.h>
#include<iostream>
#include<malloc.h>
#define MAX 300
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
typedef struct S
{
	Node* s[MAX] = { 0 };
	int top = -1;
	void push(Node* t)
	{
		if (top == MAX - 1)return;
		s[++top] = t;
	}
	Node* pop()
	{
		if (top == -1)return nullptr;
		return s[top--];
	}
	Node* getTop()
	{
		if (top == -1)return nullptr;
		return s[top];
	}
}S;
typedef struct BTree
{
	Node* root = nullptr;
	S s;
	void newBTree()
	{
		int data;
		if (root)return;
		printf("root:");
		if (scanf("%d", &data) != 1)
		{
			int c;
			while ((c = getchar()) != '\n'&&c != EOF);
			return;
		}
		root = newNode(data);
		Node* p = root;
		s.push(p);
		do {
			while (p)
			{
				printf("%d left:", p->data);
				if (scanf("%d", &data) != 1)
				{
					p->left = nullptr;
					p = p->left;
					int c; while ((c = getchar()) != '\n'&&c != EOF);
				}
				else
				{
					p->left = newNode(data);
					s.push(p->left);
					p = p->left;
				}
			}
			if (s.top != -1)
			{
				p = s.pop();
				printf("%d right:", p->data);
				if (scanf("%d", &data) != 1)
				{
					p->right = nullptr;
					p = p->right;
					int c; while ((c = getchar()) != '\n'&&c != EOF);
				}
				else
				{
					p->right = newNode(data);
					s.push(p->right);
					p = p->right;
				}
			}
		} while (p || s.top != -1);
	}
	void inOrder()
	{
		Node* p = root;
		do {
			while (p)
			{
				s.push(p);
				p = p->left;
			}
			if (s.top != -1)
			{
				p = s.pop();
				printf("%d,", p->data);
				p = p->right;
			}
		} while (p || s.top != -1);
	}
	~BTree()
	{
		Node* p = root;
		Node* t = nullptr;
		do {
			while (p)
			{
				s.push(p);
				p = p->left;
			}
			if (s.top != -1)
			{
				p = s.getTop();
				if (p->right == nullptr || p->right == t)
				{
					s.top--;
					t = p;
					printf("\n%d freed\n", p->data);
					free(p);
					p = nullptr;
				}
				else p = p->right;
			}
		} while (p || s.top != -1);
	}
}BTree;
int max(Node* root)
{

	if (!root->left && !root->right)
	{
		return root->data;
	}
	else
	{
		if (root->left && root->right)
		{
			return root->data > max(root->left) ? (root->data > max(root->right) ? root->data : max(root->right)) : (max(root->left) > max(root->right) ? max(root->left) : max(root->right));
		}
		else if (!root->left  && root->right)
		{
			return root->data > max(root->right) ? root->data : max(root->right);
		}
		else
		{
			return root->data > max(root->left) ? root->data : max(root->left);
		}
	}
}
int min(Node* root)
{
	if (!root->left && !root->right)
	{
		return root->data;
	}
	else
	{
		if (root->left&&root->right)
		{
			return root->data < min(root->left) ? (root->data < min(root->right) ? root->data : min(root->right)) : (min(root->left) < min(root->right) ? min(root->left) : min(root->right));
		}
		else if (!root->left&&root->right)
		{
			return root->data < min(root->right) ? root->data : min(root->right);
		}
		else
		{
			return root->data < min(root->left) ? root->data : min(root->left);
		}
	}
}
int main()
{
	BTree a;
	a.newBTree();
	a.inOrder();
	printf("\nmax:%d\n", max(a.root));
	printf("min:%d\n", min(a.root));
	system("pause");
	return 0;
}