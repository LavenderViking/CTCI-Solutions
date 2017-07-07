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

void printList(ListNode *L) {
	cout << "Pringing list: " << endl;
	int i = 0;
	while (L) {
		cout << "i = " << i << " data = " << L->data << endl;		

		L = L->next;
		i++;
	}
}

ListNode* partitionList(ListNode *&L, int partition) {
	// Make two lists, one for smaller one for larger and merge them

	// smaller greater lists with small begina and great begin:
	ListNode *s=NULL, *g=NULL, *sBegin=NULL, *gBegin=NULL;

	while (L) {
		ListNode *next = L->next;
		cout << endl << endl << "Inside while L = " << L->data <<endl;
		
		if (L->data < partition) {
			if (s == NULL) {
				s = L;
				s->next = NULL;
				sBegin = s;
			} else {
				s->next = L;
				s = s->next;
				s->next = NULL;
			}
		} else {
			if (g == NULL) {
				g = L;
				g->next = NULL;
				gBegin = g;
			} else {
				g->next = L;
				g = g->next;
				g->next = NULL;
			}
		}
		printList(sBegin);
		printList(gBegin);
		L = next;
	}

	int ii = 0;

	// Merge lists:
	ListNode *head = sBegin;

	while (sBegin->next != NULL) {
		sBegin = sBegin->next;
	}
	sBegin->next = gBegin;

	L = head;

	cout << "INSIDE " << endl;
	printList(L);

	return head;
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
	ListNode *L = new ListNode;

	// Build linked list:
	fori(0,num) {
		if (i == 0) {
			L->next = NULL;
			L->data = A[i];
		} else {
			ListNode* node = (new ListNode);
			node->next = NULL;
			node->data = A[i];
			insertAfter(L, node);
		}
	}
	
	ListNode *ret = partitionList(L,5);

	cout << "FINAL\n";
	printList(ret);

	file.close();

	return 0;
}
