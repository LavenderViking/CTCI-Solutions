#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <vector>
#include <set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

struct item {
	int val;
	mutable int count, rank;

	item() : val{0}, count{0}, rank{0} {}
	item(int v, int c, int r) : val{v}, count{c}, rank{r} {}

};

bool operator<(const item &a, const item &b) {
		return a.val < b.val;
}



class DS {

	set<item> S;

	public:
	void track(int x) {

		bool doesExist = false;

		for (auto it : S) {
			if (it.val == x) {
				doesExist = true;
				break;
			}
		}

		if (!doesExist) {
			// x does not exist. Insert x
			
			// Check if x is the smallest element so far:
			bool isSmallest = true;

			for (auto it : S) {
				if (it.val < x) {
					isSmallest = false;
					break;
				}
			}

			if (isSmallest) {
				item newItem(x,1,0);

				// Increase rank of all other elements:
				for (auto &it : S) it.rank++;
				
				S.insert(newItem);
			} else {
				item smallerItem;

				for (auto &it : S) {
					if (it.val < x) smallerItem = it;
					else it.rank++;
				}

				item newItem(x,1,smallerItem.rank + smallerItem.count);
				S.insert(newItem);



			// x exists: increase rank of all elements higher than it:
			
			for (auto &it : S) {
				if (it.val < x) continue;
				else if (it.val == x) it.count++;
				else it.rank++;
			}
			}
		}
	}

	int getRankOfNumber(int x) {
		for (auto it : S) {
			if (it.val == x) {
				return it.rank + it.count - 1;
			}
		}
		return 0;
	}
};



// Finds the rank by building a binary search tree and stores how
// many nodes are to the left of each node:
class RankNode {
	public:
	int data = 0;
	int left_size = 0;
	RankNode *left=NULL, *right=NULL;

	RankNode(int d) { data = d; }

	void insert(int d) {
		if (d <= data) {
			if (left != NULL) {
				left->insert(d);
			} else {
				left = new RankNode(d);
			}
			left_size++;
		} else {
			if (right != NULL) {
				right->insert(d);
			} else {
				right = new RankNode(d);
			}
		}
	}

	int getRank(int d) {
		if (d == data) {
			return left_size;
		} else if (d < data) {
			if (left == NULL) return -1;
			else return left->getRank(d);
		} else {
			if (right == NULL) {
				return -1;
			} else {
				int rightRank = right->getRank(d);
				if (rightRank == -1) return -1;
				else return rightRank + left_size + 1;
			}
		}
	}
};


class RankTree {
	RankNode *root = NULL;

	public:
	void track(int d) {
		if (root == NULL) {
			root = new RankNode(d);
		} else {
			root->insert(d);
		}
	}

	int getRankOfNumber(int number) {
		if (root == NULL) return -1;
		return root->getRank(number);
	}
};


int main() {

	RankTree *tree = new RankTree();

	tree->track(1);

	cout << tree->getRankOfNumber(1) << endl;


/*
	DS tag;

	int A[9] = {5,1,4,4,5,9,7,13,3};

	for (int i =0; i < 9; i++) {
		tag.track(A[i]);
	}

	cout << tag.getRankOfNumber(1) << endl;
	cout << tag.getRankOfNumber(3) << endl;
	cout << tag.getRankOfNumber(4) << endl;
*/
	return 0;
}


