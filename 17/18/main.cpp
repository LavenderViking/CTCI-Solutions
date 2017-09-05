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
#include <list>
using namespace std;

#define PRINT 0

// Checks if all elements in shorter appear in longer:
bool containsSubsequence(vector<int> shorter, vector<int> longer) {
	unordered_set<int> values;

	for (int i = 0; i < shorter.size(); i++) values.insert(shorter[i]);

	int valuesRemaining = shorter.size();

	for (int i = 0; i < longer.size(); i++) {
		if (values.count(longer[i]) > 0) {
			valuesRemaining--;
			values.erase(longer[i]);
		}

		if (valuesRemaining == 0) break;
	}

	return valuesRemaining == 0;
}

unordered_set<int> getValues(vector<int> A) {
	unordered_set<int> values;

	for (int i = 0; i < A.size(); i++) values.insert(A[i]);

	return values;
}

vector<int> shortestSubsequence(vector<int> shorter, vector<int> longer) {

	// If longer array does not contain all the values in the shorter array return:
	if (!containsSubsequence(shorter,longer)) return {-1,-1};
	
	unordered_set<int> values = getValues(shorter);
	unordered_set<int> valuesUnseen = values;
	unordered_map<int,list<int>> map;

	int left = 0, right = longer.size()-1;
	int leftMin = 0, rightMin = longer.size()-1, minLen = longer.size();

	int valuesCount = 0;

	for (int i = 0; i < longer.size(); i++) {
		
		// Value in longer not in shorter:
		if (values.count(longer[i]) == 0) continue;

		// Have not seen all values in shorter yet:
		if (valuesCount < shorter.size() && valuesUnseen.count(longer[i]) > 0) {
			valuesCount++;
			valuesUnseen.erase(longer[i]);
		}
		
		map[longer[i]].push_back(i);

		// Have seen all values in shorter in longer:
		if (valuesCount == shorter.size()) {
			cout << "valuescount == shorer.size() " << " i = " << i << endl;
			cout << "map[longer[left]].size() = " << map[longer[left]].size() << endl;
			// Check if we can move left pointer to make subarray size smaller:
			while (map[longer[left]].size() != 1) {
				cout << "Popping element: " << map[longer[left]].front() << endl;
				if (map[longer[left]].size() != 0) map[longer[left]].pop_front();
				++left;
			}
			right = i;
			int curLen = right - left + 1;
			if (curLen < minLen) {
				cout << "updated min len = " << curLen << endl;
				minLen = curLen;
				leftMin = left;
				rightMin = right;
			}
		}
	}

	vector<int> res;

	for (int i = leftMin; i <= rightMin; i++) res.push_back(longer[i]);

	return res;
}

void print(vector<int> shorter, vector<int> longer, vector<int> res) {
	cout << "Shortest subsequence from the array \n{ ";
	for (int i = 0; i < longer.size(); i++) cout << longer[i] << ",";
	cout << "}\n" << " that contains the elements in the array \n{";
	for (int i = 0; i < shorter.size(); i++) cout << shorter[i] << ",";
	cout << "}\n" << " is: {";
	for (int i = 0; i < res.size(); i++) cout << res[i] << ",";
	cout << "}\n";
}


int main() {

	vector<int> shorter = {1,5,9};
	vector<int> longer  = {7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7};

	vector<int> res = shortestSubsequence(shorter,longer);

	print(shorter,longer,res);

	return 0;
}

