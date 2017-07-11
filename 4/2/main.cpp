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

struct node {
	int data;
	node *left;
	node *right;

	node(int d, node *l, node *r) : data{d}, left{l}, right{r} {}
};


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

	node *newNode = new node(arr[mid], nullptr, nullptr);

	newNode->left = balancedBST(arr, begin, mid-1); 
	newNode->right = balancedBST(arr, mid+1, end);
	return newNode;
}


int main() {

	int arr[7] = {1,2,3,4,5,6,7};

	node *root = balancedBST(arr, 0, 6);

	printBSTpreorder(root, 0);	cout << endl;
	printBSTinorder(root, 0);	cout << endl;	
	printBSTpostorder(root, 0);	
	
	return 0;
}

