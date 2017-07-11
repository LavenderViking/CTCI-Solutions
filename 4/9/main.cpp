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
#include <vector>
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

int numNodesBST(node *root) {
	if (root == NULL) return 0;
	return numNodesBST(root->left) + numNodesBST(root->right) + 1;
}

// Recursive function where all combinations of L1 and L2 is merged and added to res:
void weaveLists(vector<int> L1, vector<int> L2, vector<int> prefix, vector<vector<int>> &res) {
	// Take first out of L1 and mix rest and vice versa:

	if (L1.size() == 0 || L2.size() == 0) {
		vector<int> add;

		fori(0,prefix.size()) add.push_back(prefix[i]);
		fori(0,L1.size()) add.push_back(L1[i]);
		fori(0,L2.size()) add.push_back(L2[i]);

		res.push_back(add);
		return;
	}

	// Add front of L1 to the list and recurse:
	int value = L1.front();
	prefix.push_back(value);

	vector<int> temp = L1;

	temp.erase(temp.begin());
	weaveLists(temp,L2,prefix,res);

	prefix.erase(prefix.begin() + prefix.size()-1);

	// Add front of L2 to the list and recurse:
	value = L2.front();
	prefix.push_back(value);
	L2.erase(L2.begin());
	weaveLists(L1,L2,prefix,res);
}

void printVec(vector<vector<int>> vec) {
	cout << "Printing vector" << endl;

	fori(0,vec.size()) {
		cout << "i = " << i << endl;

		forj(0,vec[i].size()) {
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}

vector<vector<int>> BSTseq(node *root) {

	// Call weaveLists with root->left and root->right and prefix it with root->data
	vector<vector<int>> result;

	if (!root) {
		cout << "Calling BSTseq " << endl;
		vector<int> vec;
		result.push_back(vec);
		return result;
	}
	
	cout << "Calling BSTseq with val = " << root->data << endl;

	vector<int> prefix;
	prefix.push_back(root->data);

	vector<vector<int>> leftSeq = BSTseq(root->left);

	vector<vector<int>> rightSeq = BSTseq(root->right);

	for  (int i = 0; i < leftSeq.size(); i++) {
		for  (int j = 0; j < rightSeq.size(); j++) {
			vector<vector<int>> weaved;
	
			weaveLists(leftSeq[i], rightSeq[j], prefix, weaved);
			
			for (int k = 0; k < weaved.size(); k++) {
				result.push_back(weaved[k]);
			}
		}
	}

	cout << "Returning vectors: " << endl;
	printVec(result);
	cout << endl;
	
	return result;
}

void printBSTinorder(node *node, int level);

int main() {

	const int SIZE = 6;

	int arr[SIZE] = {10,20,25,50,60,70};

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

	printBSTinorder(root,0);

	vector<vector<int>> result = BSTseq(root);

	printVec(result);

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
	//if (begin != end) newNode->left->parent = newNode;
	newNode->right = balancedBST(arr, mid+1, end);
	//if (begin != end) newNode->right->parent = newNode;
	return newNode;
}



