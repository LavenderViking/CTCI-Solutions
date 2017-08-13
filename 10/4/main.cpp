#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

struct Listy {
	int value;
	Listy *next;

	int elementAt(int index) {
		Listy *temp = this;

		for (int i = 0; i < index; i++) {
			if (temp) temp = temp->next;
		}
		if (temp) return temp->value;
		return -1;
	}

	Listy(int val) : value{val}, next{NULL} {}
};

Listy* createList(int N) {
	Listy *head = new Listy(N-1);

	Listy *iter = head;

	for (int i = 0; i < N; i++) {
		Listy *n = new Listy(i+49);
		iter->next = n;
		iter = n;
	}

	return head;
}


int binarySearch(Listy *head, int left, int right) {
	while (left + 1 < right) {
		int mid = (left+right)/2;
		if (head->elementAt(mid) < 0) right = mid;
		else left = mid;
	}
	return left;
}


int listSize(Listy *head) {
	int left = 0, right = 0;

	while (head->elementAt(right) > 0) {
		if (right == 0) right = 1;
		else right *= 2;
	}
	left = right / 2;

	// Now the size is somewhere between left and right:
	int size = binarySearch(head,left,right);
	return size;
}

int sortedSearch(Listy *head, int x) {
	int size = listSize(head);

	int lo = 0, hi = size-1;

	while (lo < hi) {
		int mid = (lo+hi)/2;

		int lookup = head->elementAt(mid);

		if (lookup == x) return mid;
		else if (lookup < x) {
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}

	return lo;
}

int main() {

	Listy *list = createList(49);

	cout << listSize(list) << endl;

	cout << "Searching for " << 58 << endl;

	cout << 58 << " found at: " << sortedSearch(list,58) << endl;

	return 0;
}


