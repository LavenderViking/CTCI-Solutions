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
#include <unordered_set>
#include <vector>
#include <array>
#include <queue>
using namespace std;

vector<int> smallestKNumbers(vector<int> A, int K) {

	if (A.size() == 0 || K == 0) return {};

	// Priority queue to hold the smallest K elements:
	priority_queue<int,vector<int>,greater<int>> maxHeap;

	if (maxHeap.size() == 0) maxHeap.push(A[0]);

	for (int i = 1; i < A.size(); i++) {
		if (A[i] < maxHeap.top()) maxHeap.push(A[i]);

		if (maxHeap.size() > K) maxHeap.pop();
	}

	vector<int> res;

	for (int i = 0; i < K; i++) {
		int val = maxHeap.top();
		maxHeap.pop();
		res.push_back(val);
	}

	return res;
}

void printSmallestKNumbers(vector<int> A) {

	cout << "Smallest " << A.size() << " numbers are: " << endl;
	for (int i = 0; i < A.size(); i++) cout << A[i] << " ";
	cout << endl;
}

int main() {

	vector<int> A = {5,8,2,1,0,77,22,254,7243,2345,234,3};
	int K = 4;

	vector<int> sol = smallestKNumbers(A,K);

	printSmallestKNumbers(sol);

	return 0;
}


