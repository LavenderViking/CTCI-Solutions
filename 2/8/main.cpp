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

struct ListNode {
	int data;
	ListNode *next;
	ListNode() : data{0}, next{nullptr} {}
	ListNode (int d) : data{d}, next{nullptr} {}
};


void printList(ListNode *L, string s);

ListNode* buildLinkedList(int size, int *A);

// O(N) time O(1) space:
ListNode* isLoop2(ListNode *L) {

	ListNode *loopNode = nullptr;
	ListNode *r1=L, *r2=L;

	int collideSteps = 0;

	if (L == L->next) return L;

	while (true) {
		collideSteps++;
		r1 = r1->next;
		r2 = r2->next->next;

		if (r1 == r2) {
			loopNode = r1;
			break;
		}
	}

	// Find where they collide first:
	// When they collide r1 has taken p steps and r2
	// has taken 2p steps. Total dist traveled is
	// x + (p-x) + x + (2p-x) 
	int loopLength = 1;
	
	while (L != loopNode) {
		L = L->next;
		loopNode = loopNode->next;
	}
	
	return loopNode;
}

// O(N) time O(N) space solution
ListNode* isLoop(ListNode *L) {
	unordered_set<ListNode *> S;

	ListNode *loopNode = nullptr;

	while (L) {
		cout << "L->data = " << L->data << endl;
		if (S.count(L) == 1) {
			return loopNode;
		} else {
			S.insert(L);
		}

		L = L->next;
	}
	return loopNode;
}

int main() {

	ifstream file;
	file.open("input.txt");

	int n1;
	file >> n1;

	int *A1 = new int[n1];

	fori(0,n1) file >> A1[i];

	// Build dummy head:
	ListNode *L1 = buildLinkedList(n1,A1);

	printList(L1, "L1");

	// Make circular:
	ListNode *temp = L1;
	ListNode *temp2 = L1->next->next;
	temp = temp->next->next->next->next->next;
	temp->next = temp2;

	ListNode *loopNode = isLoop2(L1);

	if (loopNode != NULL) {
		cout << "Linked list is loop starting at node with value " << loopNode->data << endl;
	} else {
		cout << "Linked list is not a loop" << endl;
	}

	file.close();

	return 0;
}


void printList(ListNode *L, string s) {
	cout << "Printing list: " << s << endl;
	int i = 0;
	while (L) {
		cout << "i = " << i << " data = " << L->data << endl;		

		L = L->next;
		i++;
	}
}

ListNode* buildLinkedList(int size, int *A) {
	ListNode *L = new ListNode(A[0]), *head = L;
	
	fori(1,size) {
		ListNode* node = new ListNode(A[i]);
		L->next = node;
		L = node;
	}
	return head;
}

