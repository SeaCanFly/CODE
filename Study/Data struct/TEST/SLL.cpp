#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int T;

typedef struct node {
	T               data;
	struct node*    next;
} Node;

typedef struct list {
	Node*		head;
}  List;

Node* create_node(T data)
{
	Node* node = new Node();
	node->next = nullptr; node->data = data;

	return node;
}

void remove_node(Node* to_be_removed)
{
	if (!to_be_removed) return;
	to_be_removed->data = 0;
	to_be_removed->next = nullptr;
	delete to_be_removed;
	// 동적해제
}

List* create_list()
{
	// 리스트 동적 할당
	List *p = new List();
	p->head = nullptr;
	return p;
}

void show_list(const List *lst)
{
	if (!lst) return;

	Node *p = const_cast<List *>(lst)->head;
	while (p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


Node* find(const List* lst, T data)
{
	if (!lst) return nullptr;
	Node *p = const_cast<List *>(lst)->head;
	while (p) {
		if (p->data == data) return p;
		p = p->next;
	}
	return nullptr;
}

Node* find_prev(const List* lst, Node* node)
{
	if (!lst || !node) return nullptr;

	Node* p = const_cast<List *>(lst)->head;
	if (p == node) return p;
	while (p) {
		if (p->next == node) return p;
		p = p->next;
	}
	return nullptr;
}

Node* find_last(const List* lst)
{
	if (!lst) return nullptr;

	Node *p = const_cast<List *>(lst)->head;
	while (p) {
		if (p->next == nullptr) return p;
		p = p->next;
	}
	return nullptr;
}

void push_front(List *lst, Node* newNode)
{
	if (!lst || !newNode) return;

	if (!lst->head) {
		newNode->next = nullptr;
		lst->head = newNode;
		return;
	}
	newNode->next = lst->head;
	lst->head = newNode;
}

void push_back(List *lst, Node* newNode)
{
	if (!lst || !newNode) return;

	Node* tail = find_last(lst);
	if (!tail) {
		assert(lst->head == nullptr);
		newNode->next = nullptr;
		lst->head = newNode;
		return;
	}
	newNode->next = nullptr;
	tail->next = newNode;
}

void insert(List *lst, T data)
{
	if (!lst) return;
	push_front(lst, create_node(data));
}

bool pop_front(List *lst, T& out)
{
	if (!lst) return false;

	if (!lst->head) return false;

	Node *to_be_removed = lst->head;
	out = lst->head->data;
	lst->head = to_be_removed->next;
	remove_node(to_be_removed);
	return true;
}

bool pop_back(List *lst, T& out)
{
	if (!lst) return false;

	if (!lst->head) return false;
	Node* tail = find_last(lst);
	assert(tail != nullptr);
	Node* prev = find_prev(lst, tail);
	assert(prev != nullptr);
	if (prev == tail) {
		lst->head = nullptr;		
		out = tail->data;
		remove_node(tail);
		return true;
	}
	prev->next = nullptr;
	out = tail->data;
	remove_node(tail);
	return true;
}

void remove_in_list(List *lst, Node* to_be_removed)
{
	if (!lst || !to_be_removed) return;
	Node *prev = find_prev(lst, to_be_removed);
	if (!prev) return;
	if (prev == to_be_removed) {
		lst->head = to_be_removed->next;
	}
	else {
		prev->next = to_be_removed->next;
	}
	remove_node(to_be_removed);
}

void remove(List *lst, T data)
{
	Node* node = find(lst, data);
	remove_in_list(lst, node);
}

void remove_all(List* lst)
{
	if (!lst) return;
	T data;

	while (lst->head) {
		if (pop_back(lst, data) == true) {
			printf("removed : %d\n", data);
		}
	}
}

void remove_list(List* lst)
{
	if (!lst) return;

	remove_all(lst);
	
	lst->head = nullptr;
	delete lst;
}


int main()
{
	List *lst = create_list();
	remove(lst, 7);
	insert(lst, 2);
	insert(lst, 1);
	insert(lst, 3);
	insert(lst, 4);
	remove_all(lst); 	
	show_list(lst); // NOTHING

	insert(lst, 2);
	insert(lst, 1);
	insert(lst, 3);
	insert(lst, 4);
	show_list(lst); // 2134
	
	remove(lst, 3);
	show_list(lst); // 214

	remove(lst, 2);
	remove(lst, 5);
	show_list(lst); //14

	remove(lst, 4);
	show_list(lst); //1

	remove_all(lst);
	show_list(lst); //NOTHING

	remove_list(lst);


	return 0;
}