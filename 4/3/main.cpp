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



struct object {
	node *node;
	int level;
	object(struct node *n, int l) : node{n}, level{l} {}
};


int depthBST(node *root) {
	
	int maxDepth = 0;

	queue<object> q;
	object obj {root,0};
	q.push(obj);

	while (!q.empty()) {
		object o = q.front(); q.pop();

		if (o.node->left || o.node->right) {
			if (o.node->left)  q.emplace(o.node->left, o.level+1);
			if (o.node->right) q.emplace(o.node->right, o.level+1);
			
			if (o.level+1 > maxDepth) maxDepth = o.level+1;
		}
	}
	return maxDepth;
}

int depthBSTR(node *root, int d) {
	int dL=d, dR=d;
	if (root->left) dL = depthBSTR(root->left, d+1);
	if (root->right)dR = depthBSTR(root->right, d+1);
	
	return dL > dR ? dL : dR; 
}

struct ListNode {
	int value;
	ListNode *next;
	ListNode(int l, ListNode *n) : value{l}, next{n} {}
};


vector<ListNode *> getLinkedLists(node *root, int depth) {
	vector<ListNode *> vec(depth);

	int level = 0;

	// Traverse tree:
	queue<object> q;
	q.emplace(root, level);

	while (!q.empty()) {
		object o = q.front(); q.pop();
		level = o.level;

		ListNode *newNode = new ListNode(o.node->data, nullptr);
		
		if (!vec[level]) {
			vec[level] = newNode;
		} else {
			if (level % 2 == 0) {
				newNode->next = vec[level];
				vec[level] = newNode;	
			} else {
				while (vec[level]->next) {
					vec[level] = vec[level]->next;
				}
				vec[level]->next = newNode;
			}
		}

		if (o.node->left) q.emplace(o.node->left, level+1);
		if (o.node->right) q.emplace(o.node->right, level+1);
	}
	return vec;
}

void printBSTpreorder(node *node, int level);
void printBSTinorder(node *node, int level);
void printBSTpostorder(node *node, int level);
node* balancedBST(int *arr, int begin, int end);

void printVec(vector<ListNode *> vec, int depth) {
	for (int i = 0; i <= depth; i++) {
		cout << "Level = " << i << " ||| ";
		ListNode *head = vec[i];
		while (head) {
			cout << head->value << " ";
			head = head->next;
		}
		cout << endl;
	}
}

int main() {

	int arr[7] = {1,2,3,4,5,6,7};

	node *root = balancedBST(arr, 0, 6);

	int depth = depthBST(root);

	vector<ListNode *> vec = getLinkedLists(root, depth+1);
	
	printVec(vec, depth);	
	
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

