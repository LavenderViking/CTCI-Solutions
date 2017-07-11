#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <vector>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

struct node {
	int data;
	node *left;
	node *right;
	node *parent;

	node(int d, node *l, node *r, node *p) : data{d}, left{l}, right{r}, parent{p} {}
};



void findNode(node *root, node *find, node* &found) {

	if (found) return;

	if (!root) return;

	if (root->data == find->data) {
		found = find;
		return;
	}

	node *left=nullptr, *right=nullptr;

	if (root->left)  findNode(root->left, find, found);
	if (root->right) findNode(root->right, find, found);

	if (left && left->data == find->data) {
		found = left;
		return;
	} 
	else if (right && right->data == find->data) {
		found = right;
		return;
	}
}

bool isSame(node *T1, node *T2) {

	if (T1 == NULL && T2 == NULL) return true;

	if (T2->left == NULL && T1->left != NULL) return false;
	if (T2->right == NULL && T1->right != NULL) return false;

	if (T1->data != T2->data) {
		return false;
	}

	return isSame(T1->left, T2->left) && isSame(T1->right, T2->right);
}

// Solution that iterates over all nodes in T1 to find the node in T2.
// It does not consider that T1 could have many instances of potential T1 trees
bool isSubtree(node *T1, node *T2) {

	// Find root T2 in T1:
	node *find = nullptr;
	findNode(T1, T2, find);

	if (!find) return false;

	// Check each node in T2 and compare against each node in T1:
	return isSame(find, T2);
}



bool matchTree(node *T1, node *T2) {
	if (T1) cout << "Inside matchTree with T1 = " << T1->data << endl;
	if (T2) cout << "Inside matchTree with T2 = " << T2->data << endl;
	if (T1 == NULL && T2 == NULL) {
		cout << "1\n";
		return true;
	}
	else if (T1 == NULL || T2 == NULL) {
		cout << "2\n";
		return false;
	}
	else if (T1->data != T2->data) {
		cout << "3\n";
		return false;
	}
	else return matchTree(T1->left, T2->left) && matchTree(T1->right, T2->right);
}



bool subTree(node *T1, node *T2) {
	if (T1 == NULL) {
		cout << "3\n";
		return false;
	}
	else if (T1->data == T2->data && matchTree(T1, T2)) {
		cout << "4\n";
		return true;
	}
	cout << "5\n";
	return subTree(T1->left, T2) || subTree(T1->right, T2);
}


// This solution checks every node of the tree T1 and if it's the same as the root in 
// T2 then it fully checks the subtree. If it returns false then it keeps on checking until
// it has finished checking all nodes in T1:
bool containsTree(node *T1, node *T2) {
	if (T2 == NULL) return true;
	return subTree(T1,T2);
}



int main() {

	node *newNode6 = new node(5, nullptr, nullptr, nullptr);
	node *newNode7 = new node(15, nullptr, nullptr, nullptr);
	node *newNode8 = new node(65, nullptr, nullptr, nullptr);
	node *newNode9 = new node(80, nullptr, nullptr, nullptr);

	node *newNode3 = new node(10, newNode6, newNode7, nullptr);
	node *newNode4 = new node(25, nullptr, nullptr, nullptr);
	node *newNode5 = new node(70, newNode8, newNode9, nullptr);

	node *newNode1 = new node(20, newNode3, newNode4, nullptr);
	node *newNode2 = new node(60, nullptr, newNode5, nullptr);
	
	node *root = new node(50, newNode1, newNode2, nullptr);
	cout << "isSubtree = " << isSubtree(root, newNode3) << endl;

	bool c = containsTree(root, newNode3);
	
	cout << "containsTree = " << c << endl;

	return 0;
}


