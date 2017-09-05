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
using namespace std;

#define PRINT 0

bool fetchBit(int num, int bit) { return (num >> bit) & 1; }

int getIntFromBits(vector<int> A) {

	int res = 0, pow2 = 1;

	for (int i = 0; i < A.size(); i++) {
		if (A[i]) res += pow2;
		pow2 *= 2;
	}

	return res;
}

int missingNumber(vector<int> A) {

	int n = A.size(), bitIndex = 0;

	// Store the bits of the missing number:
	vector<int> res;

	while (A.size() > 0) {
		if (PRINT) {
			for (int i = 0; i < res.size(); i++) cout << res[i] << " "; cout << endl;
			//for (int i = 0; i < A.size(); i++) cout << A[i] << " ";
		}

		// Number of 0s of numbers in A is always equal to number of 1s or 1 more:
		int count0s = 0, count1s = 0;
		
		for (int i = 0; i < A.size(); i++) {
			if (fetchBit(A[i],bitIndex) == 0) count0s++;
			else count1s++;
		}

		count0s <= count1s ? res.push_back(0) : res.push_back(1);

		// Remove numbers that don't have same digit as we just pushed:
		bool digit = res.back();

		vector<int> temp;
		for (int i = 0; i < A.size(); i++) {
			if (fetchBit(A[i],bitIndex) == digit) temp.push_back(A[i]);
		}

		A = temp;
		bitIndex++;
	}

	return getIntFromBits(res);
}



int main() {

	vector<int> A;

	int N = 15000;

	int missingNum = 5234;

	for (int i = 0; i <= N; i++) if (i != missingNum) A.push_back(i);

	cout << "Missing number is " << missingNumber(A) << endl;

	return 0;
}

