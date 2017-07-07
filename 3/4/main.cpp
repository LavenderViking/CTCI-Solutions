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

bool Stack::isEmpty() {
	return head == nullptr;
}



// Queue class:
class Queue {
	private:
		Stack s1, s2;
		bool popped;
		int size;
	public:
		Queue() {
			popped = false;
			size = 0;
		}

		~Queue() {
			if (popped) {
				while (!s2.isEmpty()) {
					s2.pop();
				}
			} else {
				while (!s1.isEmpty()) {
					s1.pop();
				}
			}			
		}
		void push(int data) {

			if (popped) {
				// Move all items from s2 to s1;
				while (!s2.isEmpty()) {
					int s2Val = s2.pop();
					s1.push(s2Val);
				}
			}

			popped = false;
			s1.push(data);
			size++;
		}
		int pop() {
			if (!popped) {
				popped = true;
				
				// Move everything from s1 to s2 and pop s2:
				while (!s1.isEmpty()) {
					int data = s1.pop();
					s2.push(data);
				}
			}
			size--;
			return s2.pop();
		}		
		bool isEmpty() {
			return size == 0;
		}
};



int main() {

	ifstream file;
	file.open("input.txt");

	int n1;
	file >> n1;

	int *A1 = new int[n1];

	fori(0,n1) file >> A1[i];

	Queue q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.pop();
	q.push(1);	
	q.pop();

	while (!q.isEmpty()) {
		cout << q.pop() << endl;
	}


	file.close();

	return 0;
}

