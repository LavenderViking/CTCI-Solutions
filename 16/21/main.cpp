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

int getSum(vector<int> v) {
	int sum = 0;
	for (int i = 0; i < v.size(); i++) sum += v[i];
	return sum;
}

array<int,2> sumSwap(vector<int> a, vector<int> b) {
	
	int sum_a = getSum(a), sum_b = getSum(b);
	int size_a = a.size(), size_b = b.size();

	int sum_diff = sum_b - sum_a;

	if ((size_a == 0 || size_b == 0) || (sum_diff % 2 != 0)) return {-1,-1};
	
	// Put b into hash table:
	unordered_set<int> set_b;
	for (int i = 0; i < size_b; i++) set_b.insert(b[i]);

	// Loop through a and check if we can a number that we can swap for a number in b
	// to get sum_diff to 0:
	for (int i = 0; i < size_a; i++) {

		// Diff has to be a multiply of 2:
		int req_diff = sum_diff/2 + a[i];

		int target = req_diff;

		if (set_b.count(target) > 0) return {a[i],target};
	}

	return {-1,-1};
}


int main() {

	vector<int> arr1 = {4,2,1,1,1,2};
	vector<int> arr2 = {3,6,3,3};

	array<int,2> res = sumSwap(arr1,arr2);

	cout << "Swap " << res[0] << " and " << res[1] << endl;

	return 0;
}


