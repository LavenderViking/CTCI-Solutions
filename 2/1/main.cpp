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

	shared_ptr<ListNode> next;
};


void insertAfter(const shared_ptr<ListNode>&node,
		 const shared_ptr<ListNode>&new_node) {
	new_node->next = node->next;
	node->next = new_node;
}

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
	shared_ptr<ListNode> L(new ListNode);

	// Build linked list:
	fori(0,num) {
		shared_ptr<ListNode> node(new ListNode);
		node->data = A[i];
		insertAfter(L, node);		
	}

	removeDup(L);

	// Search List:
	// Print list:
	int ii = 0;
	while(L) {
		cout << "Val = " << ii++ << ":" << L->data << endl;
		L = L->next;
	}

	file.close();

	return 0;
}
