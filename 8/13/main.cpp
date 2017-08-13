#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


struct Box {
	int W,H,D;

	Box(int w,int h,int d) : W{w}, H{h}, D{d} {}
};


bool compareBoxesAsc(const Box &a, const Box &b) { return a.W < b.W; }
bool compareBoxesDesc(const Box &a, const Box &b) { return a.W > b.W; }


int highestStack(vector<Box> boxes) {

	int size = boxes.size();

	// Sort boxes in ascending order:
	sort(boxes.begin(), boxes.end(), compareBoxesAsc);

	int *DP = new int[size];

	for (int i = 0; i < size; i++) DP[i] = boxes[i].H;

	for (int i = 1; i < size; i++) {
		for (int j = 0; j < i; j++) {
			if (boxes[i].W > boxes[j].W && boxes[i].H > boxes[j].H && boxes[i].D > boxes[j].D) {
				if (DP[j] + boxes[i].H > DP[i]) DP[i] = DP[j] + boxes[i].H;
			}
		}
		cout << "DP[" << i << "] = " << DP[i] << endl;
	}

	int result = DP[0];

	for (int i = 0; i < size; i++) if (DP[i] > result) result = DP[i];
	
	delete [] DP;

	return result;
}

int recursiveStack(vector<Box> boxes, int bottomIndex, int *stackMap) {

	if (stackMap[bottomIndex] > 0) return stackMap[bottomIndex];

	int maxHeight = 0, size = boxes.size();

	for (int i = bottomIndex+1; i < size; i++) {
		if (boxes[i].W < boxes[bottomIndex].W && boxes[i].H < boxes[bottomIndex].H && boxes[i].D < boxes[bottomIndex].D) {
			int height = recursiveStack(boxes, i, stackMap);
			if (height > maxHeight) maxHeight = height;
		}
	}

	maxHeight += boxes[bottomIndex].H;
	stackMap[bottomIndex] = maxHeight;

	return maxHeight;
}

int recursiveStack(vector<Box> boxes) {
	sort(boxes.begin(), boxes.end(), compareBoxesDesc);

	int maxHeight = 0, size = boxes.size();

	int *stackMap = new int[size];
	for (int i = 0; i < size; i++) stackMap[i] = 0;

	for (int i = 0; i < size; i++) {
		int height = recursiveStack(boxes, i, stackMap);
		if (height > maxHeight) maxHeight = height;
	}

	delete [] stackMap;

	return maxHeight;
}



int main() {

	int N; cin >> N;

	vector<Box> boxes;

	for (int i = 0; i < N; i++) {
		int W,H,D;
		cin >> W >> H >> D;
		Box box(W,H,D);
		boxes.push_back(box);
	}

	int max = highestStack(boxes);

	int max2 = recursiveStack(boxes);
	
	int max3 = recursiveStack(boxes);

	cout << "Highest stack = " << max << endl;
	cout << "Highest stack recursive = " << max2 << endl;
	cout << "Highest stack recursive = " << max3 << endl;
	
	return 0;
}


