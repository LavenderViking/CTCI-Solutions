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

bool isPalindrome(ListNode *L) {
	
	bool isPalindrome = true;

	// Add all values to a dequeue:
	deque<int> q;

	while (L) {
		q.push_back(L->data);
		L = L->next;
	}

	// Pop front and back from queue:
	while (q.size() > 1) {
		int left = q.front();
		int right = q.back();

		if (left != right) {
			isPalindrome = false; 
			break;
		}
		q.pop_front();
		q.pop_back();
	}

	return isPalindrome;
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

	fori(0,n1) cout << A1[i];

	printList(L1, "L1");
	
	cout << "IsPalindrome: " << isPalindrome(L1);

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

