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
	int min;
	node *next;
	node *prev;

	node(int d) : data{d}, min{d} {}
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

	
	if (data < head->min) new_node->min = data;
	else new_node->min = head->min;

	head = new_node;
	size++;
}

int Stack::pop() {
	// Remove topmost node from list:
	node *remove_node = head;
	int value = head->data;
	int min = head->min;
	head = head->prev;
	delete remove_node;
	size--;
	return min;
}

bool Stack::empty() {
	return head == nullptr;
}

int main() {

	ifstream file;
	file.open("input.txt");

	int n1;
	file >> n1;

	int *A1 = new int[n1];

	fori(0,n1) file >> A1[i];

	Stack stack(3);

	stack.push(2);
	stack.push(1);



	cout << "Printing stack 0\n" ;
	while (!stack.empty()) {
		int val = stack.pop();
		cout << "Val = " << val << endl;
	}



	file.close();

	return 0;
}

