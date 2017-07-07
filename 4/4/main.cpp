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

int getHeight(node *root) {
	if (root == NULL) return -1;

	return max(getHeight(root->left), getHeight(root->right))+1;
}

bool isBalanced(node *root) {
	if (root == NULL) return true;

	int leftH  = getHeight(root->left);
	int rightH = getHeight(root->right);

	if (abs(leftH-rightH) > 1) return false;

	return isBalanced(root->left) && isBalanced(root->right);
}

// Returns INT_MIN if tree is not balanced:
// More efficient than the solution above:
int getHeight2(node *root) {
	if (root==NULL) return -1;

	int heightL = getHeight(root->left);
	int heightR = getHeight(root->right);

	if (abs(heightL-heightR) > 1) {
		return INT_MIN;
	}
	return max(heightL, heightR)+1;
}


bool isBalanced2(node *root) {
	if (root == NULL) return true;

	return getHeight2(root) != INT_MIN;
}


int main() {

	ifstream file;
	file.open("input.txt");

	int n1; file >> n1;

	int arr[7] = {1,2,3,4,5,6,7};

	node *root = balancedBST(arr, 0, 6);

	node *root2 = new node(0,nullptr,nullptr);
	root2->right =new node(0,nullptr,nullptr);
	root2->right->right =new node(0,nullptr,nullptr);

	cout << "Balanced = " << isBalanced2(root) << endl;

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

