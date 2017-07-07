#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

struct node {
	int data;
	node *left;
	node *right;
	node *parent;

	node(int d, node *l, node *r, node *p) : data{d}, left{l}, right{r}, parent{p} {}
};

int depthBSTR(node *root, int d) {
	int dL=d, dR=d;
	if (root->left) dL = depthBSTR(root->left, d+1);
	if (root->right)dR = depthBSTR(root->right, d+1);
	
	return dL > dR ? dL : dR; 
}

node* balancedBST(int *arr, int begin, int end);


// Sol 1 with parent links:
// With links to parents:
// O(log(N)) running time
node* firstCommonAncestor(node *n1, node *n2) {
	
	int h1=0, h2=0;

	node *n1temp = n1;
	while (n1temp->parent != NULL) {
		h1++;
		n1temp = n1temp->parent;
	}
	node *n2temp = n2;
	while (n2temp->parent != NULL) {
		h2++;
		n2temp = n2temp->parent;
	}

	while (h2 > h1) {
		n2 = n2->parent;
		h2--;
	}
	while (h1 > h2) {
		n1 = n1->parent;
		h1--;
	}

	while (n1 != n2) {
		n1 = n1->parent;
		n2 = n2->parent;
	}

	return n1;
}


///////// Sol 2: Without parent links:
bool covers(node *root, node *n) {
	if (root == NULL) return false;

	if (n==root) return true;

	return covers(root->left,n) || covers(root->right,n);
}

node* FCAHelper(node *root, node *p, node *q) {
	if (root == NULL || root == p || root == q) return root;

	bool pIsOnLeft = covers(root->left,p);
	bool qIsOnLeft = covers(root->left,q);

	if (pIsOnLeft != qIsOnLeft) return root;

	if (pIsOnLeft) {
		return FCAHelper(root->left, p, q);
	} else {
		return FCAHelper(root->right, p, q);
	}
}

// Solution without parent links:
// O(n) time since covers checks the whole tree
node* FCA(node *root, node *n1, node *n2) {
	if (!covers(root,n1) || !covers(root,n2)) return NULL;

	return FCAHelper(root,n1,n2);
}

int main() {

	ifstream file;
	file.open("input.txt");

	int arr[7] = {1,2,3,4,5,6,7};

	node *root = balancedBST(arr, 0, 6);

	node *n1 = root->left->left;
	node *n2 = root->left->right;

	node *ret = firstCommonAncestor(n1,n2);
	cout << "FCA->data = " << ret->data << endl;

	node *ret1 = FCA(root,n1,n2);
	cout << "FCA->data = " << ret1->data << endl;
	

	file.close();

	return 0;
}







void printBSTpreorder(node *node, int level) {
	cout << node->data << "level = " << level << endl;	
	if (node->left != NULL) printBSTpreorder(node->left, level+1);
	if (node->right != NULL) printBSTpreorder(node->right, level+1);
}

void printBSTinorder(node *node, int level) {
	if (node->left != NULL) printBSTinorder(node->left, level+1);
	cout << node->data << "level = " << level << endl;	
	if (node->right != NULL) printBSTinorder(node->right, level+1);
}

void printBSTpostorder(node *node, int level) {
	if (node->left != NULL) printBSTpostorder(node->left, level+1);
	if (node->right != NULL) printBSTpostorder(node->right, level+1);
	cout << node->data << "level = " << level << endl;	
}

node* balancedBST(int *arr, int begin, int end) {

	if (end < begin) return NULL;

	int mid = (begin + end) / 2;

	node *newNode = new node(arr[mid], nullptr, nullptr, nullptr);

	newNode->left = balancedBST(arr, begin, mid-1);
	if (begin != end) newNode->left->parent = newNode;
	newNode->right = balancedBST(arr, mid+1, end);
	if (begin != end) newNode->right->parent = newNode;
	return newNode;
}



