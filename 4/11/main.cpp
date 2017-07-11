#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <ctime>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

class TreeNode {

	public:
		int data;
		TreeNode *left=nullptr;
		TreeNode *right=nullptr;
		int size = 0;

	TreeNode(int d) : data{d}, size{1} {}

	TreeNode* getIthNode(int i) {
		int leftSize = left == nullptr ? 0 : left->size;
		if (i < leftSize) {
			return left->getIthNode(i);
		}
		else if (i == leftSize) {
			return this;
		}
		else return right->getIthNode(i - (leftSize+1));
	}

	void insertInOrder(int d) {
		if (d <= data) {
			if (!left) left = new TreeNode(d);
			else left->insertInOrder(d);
		} else {
			if (!right) right = new TreeNode(d);
			else right->insertInOrder(d);
		}
		size++;
	}
};


class Tree {
	TreeNode *root = nullptr;

	int size() { return root == nullptr ? 0 : root->size; }
	
	public:
	TreeNode* getRandomNode() {
		if (!root) return NULL;

		int i = rand()%size();

		i = i % size();

		return root->getIthNode(i);
	}

	void insertInOrder(int value) {
		if (!root) root = new TreeNode(value);
		else root->insertInOrder(value);
	}
};



int main() {

	srand( time(NULL) );

	TreeNode *root = new TreeNode(5);
	
	Tree tree;
	tree.insertInOrder(5);
	tree.insertInOrder(10);
	tree.insertInOrder(1);


	TreeNode *randNode = tree.getRandomNode();

	cout << "Rand node val = " << randNode->data << endl;


	return 0;
}

