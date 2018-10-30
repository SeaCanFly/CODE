#include<stdio.h>
#include<iostream>
#include<malloc.h>

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
void insertNode(Node*& root, int data)
{
	Node* p = newNode(data);
	if (!root)
	{
		root = p;
		return;
	}
	Node** t = &root;
	while (*t)
	{
		if ((*t)->data > data)
		{
			t = &((*t)->left);
			continue;
		}
		if ((*t)->data < data)
		{
			t = &((*t)->right);
			continue;
		}
	}
	*t = p;
}
void find(Node* root)
{
	if (!root)return;
	if (root->data == 8)printf("add:%p(%d)\n", root, root->data);
	find(root->left);
	find(root->right);
}
void print(Node* root)
{
	if (!root)return;
	if(root->left)printf("not terminal node:%d\n", root->data);
	print(root->left);
	print(root->right);
	if(!root->left)printf("terminal node:%d\n",root->data);
}
int maxDepth(Node* root)
{
	if (!root)return 0;
	int l = maxDepth(root->left);
	int r = maxDepth(root->right);
	return l > r ? (l + 1) : (r + 1);
}
void preOrder(Node* root)
{
	if (!root)return;
	printf("%d,", root->data);
	preOrder(root->left);
	preOrder(root->right);
}
void inOrder(Node* root)
{
	if (!root)return;
	inOrder(root->left);
	printf("%d,", root->data);
	inOrder(root->right);
}
void postOrder(Node* root)
{
	if (!root)return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d,", root->data);
}
void parent(int a[], int index)
{
	int* p = a;
	int t = index + 1;
	t = t >> 1;
	p = p + t-1;
	printf("%d-parent:%d\n",*(a+index), *p);
}
void child(int a[], int index)
{
	int* p = a;
	int t = index + 1;
	printf("%d-left:%d,",*(a+index), *(a + (t << 1) - 1));
	printf("%d-right:%d\n",*(a+index), *(a + (t << 1)));
}
int main()
{
	int a[] = { 5,3,7,2,4,6,9,1,8,10 };
	Node *root = nullptr;

	for (int i = 0; i < 10; i++)
	{
		insertNode(root, a[i]);
	}
	preOrder(root);
	printf("\n");
	inOrder(root);
	printf("\n");
	postOrder(root);
	printf("\n");
	printf("%d\n", maxDepth(root));
	print(root);
	find(root);
	int btree[] = { 5,3,7,2,4,6,9,1,'\0','\0','\0','\0','\0',8,10 };
	parent(btree, 4);
	child(btree, 0);
	system("pause");
	//O(n)
	return 0;
}