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


int maxContiguousSum(vector<int> seq) {
	int sum = 0, maxSum = 0;

	for (int i = 0; i < seq.size(); i++) {
		if (sum + seq[i] > 0) sum += seq[i];
		else sum = 0;

		if (sum > maxSum) maxSum = sum;
	}

	return maxSum;
}




int main() {
	
	vector<int> seq = {-8,3,-2,4,-10};

	cout << "subSum = " << maxContiguousSum(seq) << endl;

	return 0;
}


