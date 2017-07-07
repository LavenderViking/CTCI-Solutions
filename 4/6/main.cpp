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

void printBSTpreorder(node *node, int level);
void printBSTinorder(node *node, int level);
void printBSTpostorder(node *node, int level);
node* balancedBST(int *arr, int begin, int end);

node* leftMostChild(node *n) {
	if (n==NULL) return NULL;

	while (n->left != NULL) n = n->left;

	return n;
}

node* successor(node *n) {

	// if n has a right subtree return leftmost node in that tree
	// else while n is a right child of n.parent go up. Return n.parent

	if (n == NULL) return null;

	if (n->right) {
		return leftMostChild(n->right);
	} else {
		while (n->parent != NULL && n->parent->right == n) {
			n = n->parent;
		}
		return n->parent;
	}

}

int main() {

	ifstream file;
	file.open("input.txt");

	int n1; file >> n1;

	int arr[7] = {1,2,3,4,5,6,7};

	node *root = balancedBST(arr, 0, 6);

	node *n = root->right->right;

	node *node = successor(n);

	cout << "Successor of node " << n->data << " is " << node->data << endl;	

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



