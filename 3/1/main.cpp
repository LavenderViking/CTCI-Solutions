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

// Queue class:
class Queue {
	private:
		node *head;
		node *tail;
		int size;
	public:
		Queue(int data) {
			node *new_node = new node(data);
			new_node->next = nullptr;
			new_node->prev = nullptr;
			head = new_node;
			tail = head;
			size = 1;
		}
		~Queue() {
			while (head) {
				node *temp = head;
				head = head->prev;
				delete temp;
			}
		}
		void push(int data) {
			node *new_node = new node(data);
			new_node->next = nullptr;
			new_node->prev = head;
			head->next = new_node;
			head = new_node;
			size++;
		}
		int pop() {
			node *del_node = tail;
			tail = tail->next;
			int value = del_node->data;
			delete del_node;
			size--;

			if (tail == nullptr) head = nullptr;

			return value;
		}
		bool empty() {
			return head == nullptr;
		}
};

// Stack class:
class Stack {
	private:
		node *head;
		node *tail;
		int size;		
	public:
		Stack(int data);
		~Stack();
		void push(int data);
		int pop();
		bool empty();
};

// Creates stack with one item in:
Stack::Stack(int data) {
	node *new_node = new node(data);
	new_node->next = nullptr;
	new_node->prev = nullptr;
	head = new_node;
	tail = new_node;
	size = 1;
}

Stack::~Stack() {
	while (head) {		
		node *temp = head;
		head = head->prev;
		delete(temp);
	}
}

void Stack::push(int data) {
	// Create new node:
	node *new_node = new node(data);
	new_node->prev = head;
	new_node->next = nullptr;
	head = new_node;
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

bool Stack::empty() {
	return head == nullptr;
}

class Stack2 {
	private:
		int numStacks = 3;
		int stackCapacity;
		int *storage;
		int *sizes;
	public:
		Stack2(int capacity) {
			this->stackCapacity = capacity;
			storage = new int[capacity * numStacks];
			sizes = new int[numStacks];
			fori(0,numStacks) sizes[i] = -1;
		}

		~Stack2() {
			delete [] storage;
			delete [] sizes;
		}

		void push(int stackNum, int data) {

			// Check if stack is full:
			if (isFull(stackNum)) {
				cout << "Stack is full!" << endl;
				return;
			}
			
			sizes[stackNum]++;
			storage[getIndexOfStack(stackNum)] = data;
			cout << "Pushed " << data << " sizes[0] = " << sizes[stackNum] << endl;
		}

		int pop(int stackNum) {

			// Check if stack is empty:
			if (isEmpty(stackNum)) {
				cout << "Stack is empty\n";
				return -1;
			}

			// Remove element and return it:
			int value = storage[getIndexOfStack(stackNum)];
			sizes[stackNum]--;

			return value;
		}
	
		int getIndexOfStack(int stackNum) {
			return stackNum * stackCapacity + sizes[stackNum];
		}

		bool isFull(int stackNum) {
			return sizes[stackNum] == stackCapacity-1;
		}

		bool isEmpty(int stackNum) {
			return sizes[stackNum] == -1;
		}
};

int main() {

	ifstream file;
	file.open("input.txt");

	int n1;
	file >> n1;

	int *A1 = new int[n1];

	fori(0,n1) file >> A1[i];

	Stack2 stack(3);
	stack.push(0, 1);	
	stack.push(0, 2);	
	stack.push(0, 3);	

	stack.push(1, 4);	
	stack.push(1, 5);	
	stack.push(1, 6);	
	stack.pop(1);
	stack.push(1,7);

	cout << "Printing stack 0\n" ;
	while (!stack.isEmpty(0)) {
		int val = stack.pop(0);
		cout << "Val = " << val << endl;
	}

	cout << "Printing stack 1\n" ;
	while (!stack.isEmpty(1)) {
		int val = stack.pop(1);
		cout << "Val = " << val << endl;
	}


	file.close();

	return 0;
}

