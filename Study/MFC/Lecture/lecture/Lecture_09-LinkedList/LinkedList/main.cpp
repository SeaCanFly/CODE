#include <iostream>
#include <afxtempl.h>	// CList ����� ���� �ʿ�

using namespace std;

struct List
{
	int id;
	List *p;	// �ڱ��ڽ��� ����Ű�� ������
};

void main ()
{
	List item;
	item.id = 20;
	item.p = &item;

	cout << "item.id: " << item.id << "\n";
	cout << "item.p->id: " << item.p->id << "\n";
	cout << "item.p->p->id: " << item.p->p->id << "\n" << endl;

	List a, b, c;
	a.id = 1;  a.p = &b;
	b.id = 2;  b.p = &c;
	c.id = 3;  c.p = &a;

	cout << "a.id: " << a.id << "\n";
	cout << "b.id: " << a.p->id<< "\n";
	cout << "c.id: " << a.p->p->id<< "\n" << endl;

	// ����: Linked List

	List A, B, C, D;
	
	A.id = 10;		A.p = &B;
	B.id = 20;		B.p = &C;
	C.id = 30;		C.p = &D;
	D.id = 40;		D.p = NULL;

	cout << A.id << endl << B.id << endl << C.id << endl << D.id << endl << endl;
	cout << A.id << endl << A.p->id << endl << B.p->id << endl << B.p->p->id << " " << A.p->p->p->id << endl << endl;

	cout << "While ������ A, B, C, D ���ʷ� ����ϱ�" << endl;

	List *ppp = &A;
	int num = 1;

	while(ppp != NULL || num == 4) {
		cout << ppp->id << endl;
		ppp = ppp->p;

		num ++; 
	}

	// CList
	
	cout << endl << "CList�� �� ��忡 10, 20, 30 ���ʷ� ����ϱ�" << endl;

	CList <int> clist;
	clist.AddTail(10);
	clist.AddTail(20);
	clist.AddTail(30);

	POSITION pos = clist.GetHeadPosition();	// ù ������ ��ġ ��ȯ

	while (pos != NULL) {
		int value = clist.GetNext(pos);		// pos ��ġ�� ������ ��ȯ ��, pos�� list�� ���� ��ġ�� ����Ŵ
		cout << value << endl;
	}

	pos = clist.GetHeadPosition();	// ù ������ ��ġ ���ȯ (����: ������ pos�� list�� ���� ����)

	int bb = clist.GetAt(pos);
	int &cc = clist.GetAt(pos);

	cout << bb << endl;
	cout << cc << endl;
}