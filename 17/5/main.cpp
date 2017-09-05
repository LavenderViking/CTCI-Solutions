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

bool isDigit(char c) {
	int num = c - '0';
	return num >= 0 && num <= 9;
}

// Brute force solution: O(N*N)
vector<char> longestSubarray(vector<char> A) {
	int len = A.size();

	if (len == 0) return {};

	int maxLen = 0, left = 0, right = 0;

	for (int i = 0; i < len - 1; i++) {
		int numDigits = 0;
		for (int j = i; j < len; j++) {
			if (isDigit(A[j])) numDigits++;
			else numDigits--;

			if (numDigits == 0) {
				int curLen = j - i + 1;

				if (curLen > maxLen) {
					maxLen = curLen;
					left = i;
					right = j;
				}
			}
		} 
	}

	vector<char> res;

	for (int i = left; i <= right; i++) res.push_back(A[i]);

	return res;
}


// Optimized solution O(N):
vector<char> longestSubarray2(vector<char> A) {
	int len = A.size();

	if (len == 0) return {};

	int maxLen = 0, left = 0, right = 0;

	// Hash table stores numDigits as a key and index as a value:
	unordered_map<int,int> map;

	int numDigits = 0;

	for (int i = 0; i <= len; i++) {

		if (map.count(numDigits) == 0) map[numDigits] = i;

		if (map.count(numDigits) > 0) {
			int curLen = i - 1 - map[numDigits];
			if (curLen > maxLen) {
				maxLen = curLen;
				left = map[numDigits];
				right = i - 1;
			}
		}

		if (i != len && isDigit(A[i])) numDigits++; else numDigits--;
	}

	vector<char> res;

	for (int i = left; i <= right; i++) res.push_back(A[i]);

	return res;
}

void print(vector<char> A) {
	cout << "Longest subarray with equal number of letters and numbers is: " << endl;
	for (int i = 0; i < A.size(); i++) cout << A[i];
	cout << endl << " with length: " << A.size() << endl;
}

int main() {

//	string str = "sdk2j23nr3n23n23n23jn23jn23jn23jb32jb4jb234jb23j4b23jn4j23njn23423jn23jb4j23b3b";
	string str = "aaaa8a8a888";
	vector<char> A;

	for (int i = 0; i < str.length(); i++) A.push_back(str[i]);

	vector<char> res = longestSubarray(A);
	vector<char> res2 = longestSubarray2(A);

	print(res);
	print(res2);

	return 0;
}

