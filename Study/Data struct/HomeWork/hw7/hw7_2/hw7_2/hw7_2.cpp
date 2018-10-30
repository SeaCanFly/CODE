#include<stdio.h>
#include<iostream>
#include<malloc.h>
using namespace std;
#define MAX 300
typedef struct Node
{
	char data;
	Node* left;
	Node* right;
	Node* parent;
}Node;
Node* newNode(char data)
{
	Node* t = (Node*)malloc(sizeof(Node));
	t->data = data;
	t->left = nullptr;
	t->right = nullptr;
	t->parent = t;
	return t;
}
typedef struct BTree
{
	Node* root;
	Node* s[MAX];
	int top = -1;
	void newBTree()
	{
		char data;
		printf("root:");
		cin >> data;
		if (data == '#')
		{
			root = nullptr;
			return;
		}
		root = newNode(data);
		Node* t = root;
		top++;
		s[top] = t;
		do {
			while (t)
			{
				printf("%c left:", t->data);
				cin >> data;
				if (data == '#')
				{
					t->left = nullptr;
					t = t->left;
				}
				else
				{
					t->left = newNode(data);
					t->left->parent = t;
					top++;
					s[top] = t->left;
					t = t->left;
				}
			}
			if (top != -1)
			{
				t = s[top];
				top--;
				printf("%c right:", t->data);
				cin >> data;
				if (data == '#')
				{
					t->right = nullptr;
					t = t->right;
				}
				else
				{
					t->right = newNode(data);
					t->right->parent = t;
					top++;
					s[top] = t->right;
					t = t->right;
				}
			}
		} while (t || top != -1);
	}
}BTree;

void inOrder(Node* root)
{
	if (!root)return;
	inOrder(root->left);
	cout << root << '-' << root->data << ',' << root->parent << endl;
	inOrder(root->right);
}
int main()
{
	BTree a;
	a.newBTree();
	inOrder(a.root);
	system("pause");
	return 0;
}