#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <vector>
#include <array>
using namespace std;


// O(n) space
array<int,2> subSort(vector<int> seq) {

	vector<int> maxSeq = seq, minSeq = seq;

	for (int i = 0; i < seq.size(); i++) {
		if (i != 0 && maxSeq[i] < maxSeq[i-1]) maxSeq[i] = maxSeq[i-1];
		int revI = seq.size()-1-i;
		if (revI != seq.size()-1 && minSeq[revI] > minSeq[revI+1]) minSeq[revI] = minSeq[revI+1];
	}

	// Find m:
	int m = 0;

	for (int i = 0; i < seq.size(); i++) {
		if (maxSeq[i] != minSeq[i]) {
			m = i;
			break;
		}
	}
	
	// Find n:
	int n = seq.size()-1;

	for (int i = seq.size()-1; i >= 0; i--) {
		if (maxSeq[i] != minSeq[i]) {
			n = i;
			break;
		}
	}

	return {m,n};
}

int findEndOfLeftSubsequence(vector<int> seq) {
	for (int i = 1; i < seq.size(); i++) {
		if (seq[i] < seq[i-1]) return i-1;
	}

	return seq.size()-1;
}

int findStartOfRightSubsequence(vector<int> seq) {
	for (int i = seq.size()-2; i >= 0; i--) {
		if (seq[i] > seq[i+1]) return i+1;
	}

	return 0;
}

int shrinkLeft(vector<int> seq, int minIndex, int start) {
	int comp = seq[minIndex];
	for (int i = start; i >= 0; i--) {
		if (seq[i] <= comp) return i+1;
	}
	return 0;
}

int shrinkRight(vector<int> seq, int maxIndex, int start) {
	int comp = seq[maxIndex];
	for (int i = start; i < seq.size(); i++) {
		if (seq[i] >= comp) return i-1;
	}
	return seq.size()-1;
}

array<int,2> subSort2(vector<int> seq) {

	int endLeft = findEndOfLeftSubsequence(seq);
	if (endLeft >= seq.size()-1) return {-1,-1};

	int startRight = findStartOfRightSubsequence(seq);

	int maxIndex = endLeft;
	int minIndex = startRight;

	for (int i = endLeft+1; i < startRight; i++) {
		if (seq[i] < seq[minIndex]) minIndex = i;
		if (seq[i] > seq[maxIndex]) maxIndex = i;
	}

	// Slide left until less than array[min_index]:
	int leftIndex = shrinkLeft(seq,minIndex,endLeft);
	
	// Slide right until more than array[min_index]:
	int rightIndex = shrinkRight(seq,maxIndex,startRight);

	return {leftIndex,rightIndex};
}





int main() {
	
	vector<int> seq = { 1,2,4,7,10,11,7,12,6,7,16,18,19 };

	array<int,2> sol = subSort(seq);
	array<int,2> sol2 = subSort2(seq);

	cout << "(" << sol[0] << "," << sol[1] << ")" << endl;
	cout << "(" << sol2[0] << "," << sol2[1] << ")" << endl;

	return 0;
}


