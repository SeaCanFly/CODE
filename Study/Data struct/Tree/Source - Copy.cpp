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
	void newBTree()
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
	void newBST()
	{
		int data = 0;
		while (std::cin >> data)
		{
			if (!root)
			{
				Node* p = newNode(data);
				root = p;
				continue;
			}
			Node** t = &root;
			while (*t)
			{
				if (data < (*t)->data)
				{
					t = &((*t)->left);
					continue;
				}
				if (data > (*t)->data)
				{
					t = &((*t)->right);
					continue;
				}
			}
			Node* p = newNode(data);
			*t = p;
		}
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
					printf("\n%d freed\n", p->data);
					free(p);
					p = nullptr;
				}
				else p = p->right;
			}
		} while (p || top != -1);
	}
};
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
	a.newBTree();
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
/*
#include<stdio.h>  
#include<stdlib.h>  

#define SIZE 8  

typedef struct BTree {
	char data;
	struct BTree *LChild;
	struct BTree *RChild;
}BTree;

typedef struct Stack {
	BTree *bt;
}Stack;
void createBTree() {
	BTree *bt, *root, *p, *q;
	char ch;
	int top = -1;
	Stack s[SIZE];
	ch = getchar();
	root = bt = (BTree*)malloc(sizeof(BTree)); //先创建根结点  
	bt->data = ch;
	top++;
	s[top].bt = bt;                      //根结点地址入栈  

	do {
		while (bt != NULL) {            //若当前结点不为空则,创建左孩子  
			ch = getchar();
			if (ch == ' ') {              //若输入空格,则代表结点为空  
				bt->LChild = NULL;
				bt = bt->LChild;
			}

			else {
				bt->LChild = (BTree*)malloc(sizeof(BTree));//若输入的不为空格  
				bt->LChild->data = ch;         //则分配空间,建立左结点  
				top++;
				s[top].bt = bt->LChild;        //并将创建的结点地址入栈  
				bt = bt->LChild;             //让bt指向当前刚创建的结点  
			}
		};                         // 若上面的循环结束,此时左孩子创建完毕/  
		if (top != -1) {              //出栈  
			bt = s[top].bt;
			top--;

			ch = getchar();
			if (ch == ' ') {
				bt->RChild = NULL;
				bt = bt->RChild;
			}
			else { //若输入的字符不是空格,则对刚出栈的结点创建右子树  
				bt->RChild = (BTree*)malloc(sizeof(BTree));
				bt->RChild->data = ch;
				top++;
				s[top].bt = bt->RChild; //并将刚创建的结点地址入栈  
				bt = bt->RChild;     //让bt指向当前刚创建的结点  
			}
		}     //只要bt不为空,或者top不等于-1,就继续做循环  
	} while (bt != NULL || top != -1);
	printf("二叉树创建完毕!\n");
	//中序非递归遍历  
	top = -1;  //创建完二叉树,栈已经为空了,故可以重复利用  
	printf("中序非递归遍历结果\n");
	p = root;  //将根结点赋给p  
	do {      //只要p不为空,或者top不等于-1,就继续做循环  
		while (p != NULL) {
			top++;
			s[top].bt = p;//结点入栈  
			p = p->LChild;//继续遍历,直到左孩子为空  
		};
		if (top != -1) {
			p = s[top].bt; //根出栈  
			top--;
			printf(" %c", p->data);//访问根结点  
			p = p->RChild;    //若有右孩子,则访问  
		}
	} while (p != NULL || top != -1);
	printf("\n");

	printf("前序非递归遍历结果\n");
	top = -1;
	p = root;
	do {
		while (p != NULL) {
			printf(" %c", p->data);//访问根结点  
			top++;
			s[top].bt = p;
			p = p->LChild; //中序遍历左子树  
		};
		if (top != -1) {
			p = s[top].bt;
			top--;
			p = p->RChild;//中序遍历右子树  
		}

	} while (p != NULL || top != -1);
	printf("\n");

	printf("后序非递归遍历结果\n"); //后序非递归遍历  
	top = -1;
	q = NULL;
	p = root;
	while (p != NULL || top != -1) {
		while (p != NULL) {
			top++;
			s[top].bt = p;
			p = p->LChild;
		};
		if (top != -1) {
			p = s[top].bt;
			if ((p->RChild == NULL) || (p->RChild == q)) {
				printf(" %c", p->data);
				q = p;
				top--;
				p = NULL;
			}
			else p = p->RChild;
		}
	};
	printf("\n");
}
*/