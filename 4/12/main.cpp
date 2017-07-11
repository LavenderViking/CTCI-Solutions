#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <ctime>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <vector>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

struct Node {
	int data;
	Node *left, *right;
	Node (int d, Node *l, Node *r) : data{d}, left{l}, right{r} {}
};


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  1  // ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

void getPathsWithSumFromNode(int sum, Node *node, vector<vector<int>> &finalPaths) {
	if (!node) return;

	if (node->data == sum) {
		vector<int> temp;
		temp.push_back(node->data);
		finalPaths.push_back(temp);
		return;
	}

	unordered_map<Node *, vector<int>> HT;
	unordered_map<Node *, int> HT_sum;

	vector<int> initial;
	HT[node]=initial;
	HT_sum[node] = 0;

	initial.push_back(node->data);
	if (node->left) {
		HT[node->left] = initial;
		HT_sum[node->left] = node->data;
	}
	if (node->right) {
		HT[node->right] = initial;
		HT_sum[node->right] = node->data;
	}

	queue<Node *> q;
	q.push(node);

	while (!q.empty()) {
		Node *curr = q.front(); q.pop();
		
		if (curr != node) {
			if (curr->left) {
				HT[curr->left] = HT[curr];
				HT[curr->left].push_back(curr->data);
			}
			if (curr->right) {
				HT[curr->right] = HT[curr];
				HT[curr->right].push_back(curr->data);
			}
			if (curr->left) HT_sum[curr->left] = HT_sum[curr] + curr->data;
			if (curr->right) HT_sum[curr->right] = HT_sum[curr] + curr->data;
			
			// Path found:
			if (HT_sum[curr] + curr->data == sum) {
				HT[curr].push_back(curr->data);
				finalPaths.push_back(HT[curr]);

			}

		}

		if (curr->left) q.push(curr->left);
		if (curr->right) q.push(curr->right);
	}

}


vector<vector<int>> getPathsWithSumFromAllNodes(int sum, Node *node) {
	if (!node) {
		vector<vector<int>> ret;
		return ret;
	}

	// Store all paths:
	vector<vector<int>> vec;

	queue<Node *> q;
	q.push(node);

	while (!q.empty()) {
		Node *curr = q.front();
		q.pop();

		getPathsWithSumFromNode(sum, curr, vec);
				
		if (curr->left) q.push(curr->left);
		if (curr->right) q.push(curr->right);
	}

	return vec;
}

void printPaths(vector<vector<int>> paths) {
	for (int i = 0; i < paths.size(); i++) {
		cout << "Printing path " << i << endl;
		for (int j = 0; j < paths[i].size(); j++) {
			cout << paths[i][j] << " ";
		}
		cout << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  2  ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


int countPathsWithSumFromNode(Node *node, int targetSum) {
	if (!node) return 0;

	targetSum -= node->data;

	int totalPaths = 0;

	if (targetSum == 0) totalPaths++;

	totalPaths += countPathsWithSumFromNode(node->left, targetSum);
	totalPaths += countPathsWithSumFromNode(node->right, targetSum);

	return totalPaths;
}



// O(Nlog(N)) solution.
// Goes down the whole tree from each node and adds it to the sum.
int countPathsWithSum(Node *node, int targetSum) {
	if (!node) return 0;

	int pathsFromRoot = countPathsWithSumFromNode(node, targetSum);

	int pathsOnLeft = 0, pathsOnRight = 0;
	if (node->left) pathsOnLeft = countPathsWithSum(node->left, targetSum);
	if (node->right) pathsOnRight = countPathsWithSum(node->right, targetSum);

	return pathsFromRoot + pathsOnLeft + pathsOnRight;
}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  3  ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



void incrementHashTable(unordered_map<int,int> &HT, int key, int delta) {
	int newCount = HT.count(key) > 0 ? HT.count(key) + delta : delta;

	if (newCount == 0) HT.erase(key);
	else HT[key] = newCount;
}


int countPathsWithSum2(Node *node, int targetSum, int runningSum, unordered_map<int,int> pathCount) {

	if (!node) return 0;


	runningSum += node->data;

	int sum = runningSum - targetSum;

	int totalPaths = pathCount.count(sum) > 0 ? pathCount[sum] : 0;

	if (sum == 0) totalPaths++;

	incrementHashTable(pathCount, runningSum, 1);

	totalPaths += countPathsWithSum2(node->left, targetSum, runningSum, pathCount);
	totalPaths += countPathsWithSum2(node->right, targetSum, runningSum, pathCount);
	
	incrementHashTable(pathCount, runningSum, -1);

	return totalPaths;
}




// O(N) solution. Uses a hash table to avoid traversins the tree multiple times from same nodes.
// Stores all the running sums at each node.
int countPathsWithSum2(Node *node, int targetSum) {
	unordered_map<int,int> pathCount;
	return countPathsWithSum2(node, targetSum, 0, pathCount);
}




int main() {

	Node *leftleftleft = new Node(3, nullptr, nullptr);
	Node *leftleftright = new Node(-2, nullptr, nullptr);
	Node *leftrightright = new Node(2, nullptr, nullptr);

	Node *leftleft = new Node(3, leftleftleft, leftleftright);
	Node *leftright = new Node(1, nullptr, leftrightright);
	Node *rightright = new Node(11, nullptr, nullptr);

	Node *left = new Node(5, leftleft, leftright);
	Node *right = new Node(-3, nullptr, rightright);

	Node *root = new Node(10, left, right);

	vector<vector<int>> paths = getPathsWithSumFromAllNodes(8, root);

	printPaths(paths);

	cout << "Num paths = " << countPathsWithSum(root, 8) << endl;
	cout << "Num paths = " << countPathsWithSum2(root, 8) << endl;

	return 0;
}

