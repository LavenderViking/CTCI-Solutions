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

/*
void removeDup(shared_ptr<ListNode> L) {
	unordered_set<int> S;

	shared_ptr<ListNode> head = L, prev = L;

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
}*/

ListNode* kthToLast(ListNode *head, int k, int& i) {
	if (head == NULL) return NULL;

	ListNode* node = kthToLast(head->next, k, i);
	i++;
	if (i==k) return head;

	return node;
}

ListNode* kthToLast(ListNode* head, int k) {
	int i = 0;
	return kthToLast(head, k, i);
}

ListNode *nthToLast(ListNode* head, int k) {

	// Two pointers, one k ahead of the other:
	ListNode *p1=head, *p2=head;

	// Move p1 k ahead:
	fori(0,k-1) {
		p1 = p1->next;
		if (p1 == NULL) return 0;
	}

	// Move pointers until p1 is at the end:
	while (p1->next != NULL) {
		p1 = p1->next;
		p2 = p2->next;
	}
	return p2;
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
	
	removeDup(L);

	ListNode* ret = nthToLast(L, 3);
	cout << "DATA = " << ret->data << endl;	

	int ii = 0;
	while(L) {
		cout << "Val = " << ii++ << ":" << L->data << endl;
		L = L->next;
	}

	file.close();

	return 0;
}
