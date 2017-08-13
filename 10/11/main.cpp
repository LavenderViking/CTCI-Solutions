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



void swap(vector<int> &A, int i, int j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

// O(Nlg(N)) solution:
void peaksAndValleys(vector<int> &A) {
	sort(A.begin(),A.end());
	for (int i = 1; i < A.size(); i+=2) swap(A,i-1,i);
}

int maxIndex(vector<int> A, int a, int b, int c) {
	int max = A[a], index = a;
	if (A[b] > max) {
		max = A[b];
		index = b;
	}
	if (A[c] > max) {
		max = A[c];
		index = c;
	}

	return index;
}

// O(N) solution:
void peaksAndValleys2(vector<int> &A) {
	// Run through A and make sure every other value is a peak.
	// Then the other values will automatically be valleys:
	for (int i = 1; i < A.size()-1; i+=2) {
		int biggestIndex = maxIndex(A,i-1,i,i+1);
		if (biggestIndex != i) swap(A,biggestIndex,i);
	}
}


int main() {

	vector<int> A = {1,5,8,2,-3,6,10,-7,4};

	peaksAndValleys2(A);

	fori(0,A.size()) cout << A[i] << " ";

	return 0;
}


