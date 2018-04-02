#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int T;

class List;

class Node {
	T   	data;
	Node 	*prev;
	Node 	*next;

	friend  List;

public:

	Node(T data) : data(data), prev(nullptr), next(nullptr) { }

	~Node() {
		data = 0;
		prev = nullptr;
		next = nullptr;
	}


};

class List {
	Node* head;

	Node* find(T data)
	{
		Node *p = head;
		while (p) {
			if (p->data == data) return p;
			p = p->next;
		}
		return nullptr;
	}

	Node* find_last() {
		Node *p = head;
		while (p) {
			if (p->next == nullptr) return p;
			p = p->next;
		}
		return nullptr;
	}

	Node* find_prev(Node* node) {
		if (!node) return nullptr;
		return node->prev;
	}



	void remove_in_list(Node* to_be_removed)
	{
		if (!to_be_removed) return;
		Node *prev = find_prev(to_be_removed);
		if (!prev) return;
		if (prev == to_be_removed) {
			T unused;
			pop_front(unused);
			return;
		}
		if (to_be_removed->next == nullptr) {
			prev->next = nullptr;
			delete to_be_removed;
			return;
		}
		to_be_removed->next->prev = prev;
		prev->next = to_be_removed->next;
		delete to_be_removed;
	}

public:
	List() : head(nullptr) {
	}

	void push_front(T data)
	{
		auto newNode = new Node(data);

		if (!head) {
			newNode->next = nullptr;
			newNode->prev = newNode;
			head = newNode;
			return;
		}
		newNode->next = head;
		newNode->prev = newNode;
		head->prev = newNode;
		head = newNode;
	}

	void push_back(T data)
	{
		auto newNode = new Node(data);

		Node* tail = find_last();
		if (!tail) {
			assert(head == nullptr);
			newNode->next = nullptr;
			newNode->prev = newNode;
			head = newNode;
			return;
		}
		newNode->next = nullptr;
		newNode->prev = tail;
		tail->next = newNode;
	}

	bool pop_back(T& out) {

		if (!head) return false;
		Node* tail = find_last();
		assert(tail != nullptr);
		Node* prev = find_prev(tail);
		assert(prev != nullptr);
		if (prev == tail) {
			head = nullptr;
			out = tail->data;
			delete tail;
			return true;
		}
		prev->next = nullptr;
		out = tail->data;
		delete tail;
		return true;
	}

	bool pop_front(T& out)
	{
		if (!head) return false;

		Node *to_be_removed = head;
		out = head->data;
		head = to_be_removed->next;
		if (head) {
			head->prev = head;
		}
		delete to_be_removed;
		return true;
	}

	void remove_all()
	{
		T data;

		while (head) {
			if (pop_back(data) == true) {
				printf("removed : %d\n", data);
			}
		}
		head = nullptr;
	}

	~List() {
		remove_all();
	}

	void insert(T data)
	{
		push_front(data);
	}

	void remove(T data)
	{
		Node* node = find(data);
		remove_in_list(node);
	}

	void show()
	{
		Node *p = head;
		printf("forward direction: ");
		while (p) {
			printf("%d ", p->data);
			p = p->next;
		}
		printf("\n");

		printf("backward direction: ");
		p = find_last();
		if (p) {
			while (p->prev != p) {
				printf("%d ", p->data);
				p = p->prev;
			}
			printf("%d ", p->data);
		}
		printf("\n");
	}

};

int main()
{
	List lst;

	lst.remove(7);
	lst.insert(2);
	lst.insert(1);
	lst.insert(3);
	lst.insert(4);
	lst.remove_all();
	lst.show();

	lst.insert(2);
	lst.insert(1);
	lst.insert(3);
	lst.insert(4);
	lst.show(); // 2134

	lst.remove(3);
	lst.show();

	lst.remove(2);
	lst.remove(5);
	lst.show(); //14

	lst.remove(4);
	lst.show(); //1

	lst.remove_all();
	lst.show(); //NOTHING

	return 0;
}



