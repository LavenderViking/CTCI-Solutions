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

// Outputs the indexes of the pairs:
vector<array<int,2>> pairsWithSumIndexes(vector<int> seq, int sum) {

	if (seq.size() <= 1) return {{-1,-1}};

	vector<array<int,2>> res;

	// Hash table stores value as key and array<int,2> as [count,index]:
	unordered_map<int,array<int,2>> map;

	for (int i = 0; i < seq.size(); i++) {
		int target = sum - seq[i];

		// Check if target is in the hash table:
		if (map[target][0] > 0) {
			res.push_back({map[target][1],i});
			map[target][0]--;
		} else {
			// Insert number into hash table:
			map[seq[i]][0]++;
			map[seq[i]][1] = i;
		}
	}

	return res;
}

// Outputs the numbers:
vector<array<int,2>> pairsWithSum(vector<int> seq, int sum) {

	if (seq.size() <= 1) return {{-1,-1}};

	vector<array<int,2>> res;

	unordered_map<int,int> map;

	for (int i = 0; i < seq.size(); i++) {
		int target = sum - seq[i];

		// Check if target is in the hash table:
		if (map[target] > 0) {
			res.push_back({target, seq[i]});
			map[target]--;
		} else {
			// Insert number into hash table:
			map[seq[i]]++;
		}
	}

	return res;
}


int main() {
	
	vector<int> seq = { 1,2,4,7,10,11,7,12,6,7,16,18,19 };


	vector<array<int,2>> res = pairsWithSum(seq,13);

	vector<array<int,2>> res2 = pairsWithSumIndexes(seq,13);

	for (int i = 0; i < res.size(); i++) {
		cout << "(" << res[i][0] << "," << res[i][1] << ") ";
	}
	
	cout << endl;
	for (int i = 0; i < res2.size(); i++) {
		cout << "(" << res2[i][0] << "," << res2[i][1] << ") ";
	}

	return 0;
}


