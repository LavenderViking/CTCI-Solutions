#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <deque>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

struct node {
	int data;
	node *next;
	node *prev;

	node(int d) : data{d} {}
};


// Stack class:
class Stack {
	private:
		node *head;
		node *tail;
		int size;		
	public:
		Stack();
		~Stack();
		void push(int data);
		int peek();
		int pop();
		bool isEmpty();
};

Stack::Stack() {
	size = 0;
}

Stack::~Stack() {
	while (head) {		
		node *temp = head;
		head = head->prev;
		delete(temp);
	}
}

void Stack::push(int data) {

	node *new_node = new node(data);
	new_node->next = nullptr;
	new_node->prev = nullptr;

	if (size == 0) {
		head = new_node;
		tail = new_node;
	} else {
		new_node->prev = head;
		head = new_node;
	}
	size++;
}

int Stack::pop() {
	// Remove topmost node from list:
	node *remove_node = head;
	int value = head->data;
	head = head->prev;
	delete remove_node;
	size--;
	return value;
}

int Stack::peek() {
	if (head)
		return head->data;
	return INT_MAX;
}

bool Stack::isEmpty() {
	return head == nullptr;
}


class SortedStack {
	private:
		Stack s1,s2;
		int size;
	public:
		SortedStack() { size = 0; }

		~SortedStack() {
			while (!s1.isEmpty()) {
				s1.pop();
			}
		};

		void push(int data) {
			while (s1.peek() < data) {
				s2.push(s1.pop());
			}
			s1.push(data);
			while (!s2.isEmpty()) {
				s1.push(s2.pop());
			}

			size++;
		}

		int peek() {
			return s1.peek();
		}

		int pop() {
			size--;
			return s1.pop();
		}

		bool isEmpty() { return size == 0; }
};


int main() {

	ifstream file;
	file.open("input.txt");

	int n1;
	file >> n1;

	int *A1 = new int[n1];

	fori(0,n1) file >> A1[i];

	SortedStack s;
	s.push(5);
	s.push(19);
	s.push(1);
	s.push(3);
	s.pop();
	s.push(100);
	s.pop();
	s.push(11);

	while (!s.isEmpty()) {
		cout << s.pop() << endl;
	}

	file.close();

	return 0;
}

