#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

struct ListNode {
	int data;

	ListNode *next;
};


void insertAfter(ListNode* node,
		 ListNode* new_node) {
	new_node->next = node->next;
	node->next = new_node;
}

void removeDup(ListNode *L) {
	unordered_set<int> S;

	ListNode *head = L, *prev = L;

	L = L->next;

	while (L) {
		if (S.count(L->data) == 1) {
			L = L->next;
			prev->next = L;
		} else {
			S.insert(L->data);
			prev = L;
			L = L->next;
		}
	}
	L = head;
}

bool deleteNode2(ListNode *deleteNode) {

	if (deleteNode == NULL || deleteNode->next == NULL) return 0;

	deleteNode->data = deleteNode->next->data;

	deleteNode->next = deleteNode->next->next;

	return 1;
}

void deleteNode(ListNode *L, ListNode *deleteNode) {
	// Have two pointers. One behind the other.

	// Head -> n1 -> n2 -> ..
	ListNode *n1=L, *n2=L->next;
	
	while (n2) {
		if (n2 == deleteNode) {
			n1->next = n2->next;
			n2->next = NULL;
		}
		n1 = n1->next;
		n2 = n2->next;
	}
}


int main() {

	ifstream file;
	file.open("input.txt");

	int num;
	file >> num;

	int *A = new int[num];

	fori(0,num) file >> A[i];

	cout << "num = " << num << endl;

	// Build dummy head:
	ListNode *L = (new ListNode);
	L->next = NULL;
	L->data = 33;

	// Build linked list:
	fori(0,num) {
		ListNode* node = (new ListNode);
		node->next = NULL;
		node->data = A[i];
		insertAfter(L, node);		
	}
	

	ListNode *remove = L->next;

	deleteNode2(remove);

	int ii = 0;
	while(L) {
		cout << "Val = " << ii++ << ":" << L->data << endl;
		L = L->next;
	}

	file.close();

	return 0;
}
