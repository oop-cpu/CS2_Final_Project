#include <iostream>
#include <string>
using namespace std;

class linkedList {
private:
	class node {
	public:
		int data;
		node* next;
		node(int x) {
			data = x;
			next = nullptr;
		}
	};
	node* head;
public:
	linkedList() {
		head = nullptr;
	}
	void push(int x) {
		node* p = new node(x);
		if (head == nullptr || head->data >= p->data) {
			p->next = head;
			head = p;
		}
		else {
			node* b = head;
			while (b->next != nullptr && b->next->data < p->data) {
				b = b->next;
			}
			p->next = b->next;
			b->next = p;
		}
	}
	int pop() {
		if (head == nullptr)
			cout << "List is empty.\n";
		else {
			node* b = head;
			int re = b->data;
			head = head->next;
			delete b;
			return re;
		}
		return -1;
	}
	void print() {
		if (head != nullptr) {
			node* b = head;
			while (b != nullptr) {
				cout << b->data << " ";
				b = b->next;
			}
			cout << endl;
		}
	}
	int size() {
		if (head == nullptr)
			return 0;
		node* b = head;
		int re = 0;
		while (b != nullptr) {
			re++;
			b = b->next;
		}
		return re;
	}
};

int main() {
	linkedList list;
	string opt;
	while (true) {
		cout << ">";
		cin >> opt;
		if (opt == "push") {
			int toPush;
			cin >> toPush;
			list.push(toPush);
		}
		else if (opt == "pop")
			cout << list.pop() << endl;
		else if (opt == "print")
			list.print();
		else if (opt == "size")
			cout << list.size() << endl;
		else if (opt == "exit")
			break;
		else if (opt == "help")
			cout << "COMMANDS:\npush <int>\npop\nprint\nsize\nexit\nhelp\n";
		else
			cout << "ERROR - INVALID INPUT" << endl;
	}
	return 0;
}