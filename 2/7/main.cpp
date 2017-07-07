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

ListNode* intersect(ListNode *L1, ListNode *L2) {
	
	ListNode *intersection = nullptr;

	// Put all addresses of L1 into set:
	unordered_set<ListNode *> s;

	while (L1) {
		s.insert(L1);
		L1 = L1->next;
	}

	// Iterate through L2 to find if there is an intersection:
	while (L2) {
		if (s.count(L2) > 0) {
			return L2;
		}
		L2 = L2->next;
	}

	return intersection;
}

int main() {

	ifstream file;
	file.open("input.txt");

	int n1, n2;
	file >> n1 >> n2;

	int *A1 = new int[n1];
	int *A2 = new int[n2];

	fori(0,n1) file >> A1[i];
	fori(0,n2) file >> A2[i];

	// Build dummy head:
	ListNode *L1 = buildLinkedList(n1,A1);
	ListNode *L2 = buildLinkedList(n2,A2);

	printList(L1, "L1");
	printList(L2, "L2");

	// Make intersection:
	ListNode *temp = L1;
	temp = temp->next->next;
	temp->next = L2->next->next;

	ListNode *intersection = intersect(L1,L2);
	
	if (intersection != NULL)
		cout << "Intersection!" << endl;
	else
		cout << "No intersection" << endl;
		
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

