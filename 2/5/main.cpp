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
	ListNode() : data{0}, next{nullptr} {}
	ListNode (int d) : data{d}, next{nullptr} {}
};


void insertAfter(ListNode* node,
		 ListNode* new_node);

void printList(ListNode *L, string s);

ListNode* buildLinkedList(int size, int *A);

int getNumberLength(int num) {
	int count = 0;

	while (num) {
		count++;
		num = num / 10;
	}
	return count;
}

// O(n) time O(1) space:
ListNode* sumLists(ListNode *L1, ListNode *L2) {
	int sum = 0;

	ListNode *L1Begin=L1, *L2Begin=L2, *sumList=nullptr;

	int power10 = 1;
	while (L1 != NULL || L2 != NULL) {
		cout << "Inside while" << endl;
		if (L1 == NULL) {
			sum += L2->data * power10;
			L2 = L2->next;
		}
		else if (L2 == NULL) {
			sum += L1->data * power10;
			L1 = L1->next;
		}
		else {
			sum = sum + L1->data * power10 + L2->data * power10;
			power10 *= 10;
			L1 = L1->next;
			L2 = L2->next;
		}
	}

	// Build linked list:
	while (sum) {
		cout << "Inside while sum = " << sum << endl;
		int digit = sum % 10;

		// First node
		if (sumList == nullptr) {
			ListNode *L1next = L1Begin->next;
			L1Begin->data = digit;
			sumList = L1Begin;
			sumList->next = NULL;
			L1Begin = L1next;
		}
		else if (L1Begin) {
			cout << "Inside L1 " << endl;
			ListNode *L1next = L1Begin->next;
			L1Begin->data = digit;
			L1Begin->next = sumList;
			sumList = L1Begin;
			L1Begin = L1next;
		} else {
			cout << "Inside L2 " << endl;
			ListNode *L2next = L2Begin->next;
			L2Begin->data = digit;
			L2Begin->next = sumList;
			sumList = L2Begin;
			L2Begin = L2next;
		}

		sum /= 10;
	}
	return sumList;
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

	ListNode *sumList = sumLists(L1,L2);

	printList(sumList, "L1+L2");

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
	ListNode *L = new ListNode();
	fori(0,size) {
		if (i == 0) {
			L->data = A[i];
		} else {
			ListNode* node = new ListNode(A[i]);
			insertAfter(L, node);
		}
	}
	return L;
}
void insertAfter(ListNode* node,
		 ListNode* new_node) {
	new_node->next = node->next;
	node->next = new_node;
}

