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
	root = bt = (BTree*)malloc(sizeof(BTree)); //�ȴ��������  
	bt->data = ch;
	top++;
	s[top].bt = bt;                      //������ַ��ջ  

	do {
		while (bt != NULL) {            //����ǰ��㲻Ϊ����,��������  
			ch = getchar();
			if (ch == ' ') {              //������ո�,�������Ϊ��  
				bt->LChild = NULL;
				bt = bt->LChild;
			}

			else {
				bt->LChild = (BTree*)malloc(sizeof(BTree));//������Ĳ�Ϊ�ո�  
				bt->LChild->data = ch;         //�����ռ�,��������  
				top++;
				s[top].bt = bt->LChild;        //���������Ľ���ַ��ջ  
				bt = bt->LChild;             //��btָ��ǰ�մ����Ľ��  
			}
		};                         // �������ѭ������,��ʱ���Ӵ������/  
		if (top != -1) {              //��ջ  
			bt = s[top].bt;
			top--;

			ch = getchar();
			if (ch == ' ') {
				bt->RChild = NULL;
				bt = bt->RChild;
			}
			else { //��������ַ����ǿո�,��Ըճ�ջ�Ľ�㴴��������  
				bt->RChild = (BTree*)malloc(sizeof(BTree));
				bt->RChild->data = ch;
				top++;
				s[top].bt = bt->RChild; //�����մ����Ľ���ַ��ջ  
				bt = bt->RChild;     //��btָ��ǰ�մ����Ľ��  
			}
		}     //ֻҪbt��Ϊ��,����top������-1,�ͼ�����ѭ��  
	} while (bt != NULL || top != -1);
	printf("�������������!\n");
	//����ǵݹ����  
	top = -1;  //�����������,ջ�Ѿ�Ϊ����,�ʿ����ظ�����  
	printf("����ǵݹ�������\n");
	p = root;  //������㸳��p  
	do {      //ֻҪp��Ϊ��,����top������-1,�ͼ�����ѭ��  
		while (p != NULL) {
			top++;
			s[top].bt = p;//�����ջ  
			p = p->LChild;//��������,ֱ������Ϊ��  
		};
		if (top != -1) {
			p = s[top].bt; //����ջ  
			top--;
			printf(" %c", p->data);//���ʸ����  
			p = p->RChild;    //�����Һ���,�����  
		}
	} while (p != NULL || top != -1);
	printf("\n");

	printf("ǰ��ǵݹ�������\n");
	top = -1;
	p = root;
	do {
		while (p != NULL) {
			printf(" %c", p->data);//���ʸ����  
			top++;
			s[top].bt = p;
			p = p->LChild; //�������������  
		};
		if (top != -1) {
			p = s[top].bt;
			top--;
			p = p->RChild;//�������������  
		}

	} while (p != NULL || top != -1);
	printf("\n");

	printf("����ǵݹ�������\n"); //����ǵݹ����  
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