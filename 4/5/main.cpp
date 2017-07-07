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

	node(int d, node *l, node *r) : data{d}, left{l}, right{r} {}
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

bool validBST(node *root, int min, int max) {
	if (root == NULL) {
		cout << "root==NULL" << endl;
		return true;
	}

	if (root->left == NULL && root->right==NULL) return true;

	bool validLeft, validRight;

	if (root->left) {
		cout << "1" << endl;
		int newMax = MIN(max, root->data);
		if (root->left->data > root->data || 
	            root->left->data < min) {
			cout << "1 return false" << endl;
			cout << "root->data = " << root->data << "min = " << min << " max = " << max << endl;
			return false;
		}
		validLeft = validBST(root->left, min, newMax);
	}

	if (root->right) {
		cout << "2" << endl;
		// Update min:
		int newMin = MAX(min, root->data);
		if (root->right->data < root->data ||
		    root->right->data > max) {
			cout << "2 return false" << endl;
			return false;
		}

		validRight = validBST(root->right, newMin, max);
	}
	return validLeft && validRight;
}

void copyBST(node *root, int *BST, int *index) {
	if (root == NULL) return;
	copyBST(root->left, BST, index);
	BST[*index] = root->data;
	(*index)++;
	copyBST(root->right, BST, index);
}

// Uses inorder traversal to verify BST:
bool validBST2(node *root, int size) {
	int *BST = new int[size];

	int ind = 0;
	copyBST(root, BST, &ind);

	cout << "Printing array " << endl;
	
	fori(0,size) cout << BST[i] << " ";

	for (int i = 1; i < size; i++) {
		if (BST[i] <= BST[i-1]) return false;
	}
	return true;
}

int main() {

	ifstream file;
	file.open("input.txt");

	int n1; file >> n1;

	int arr[7] = {1,2,3,4,5,6,7};

	node *root = balancedBST(arr, 0, 6);

	//root->left->right->data = 10;
	bool valid = validBST2(root,7);

	cout << "ValidBST2 = " << valid << endl;	




//	node *root2 = new node(0,nullptr,nullptr);
//	root2->right =new node(0,nullptr,nullptr);
//	root2->right->right =new node(0,nullptr,nullptr);

//	printBSTinorder(root, 0);

//	bool valid = validBST(root, INT_MIN, INT_MAX);

//	cout << "Valid BST = " << valid << endl;

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

	node *newNode = new node(arr[mid], nullptr, nullptr);

	newNode->left = balancedBST(arr, begin, mid-1); 
	newNode->right = balancedBST(arr, mid+1, end);
	return newNode;
}



