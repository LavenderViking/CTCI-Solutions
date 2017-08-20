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



vector<int> divingBoard(int s, int l, int k) {

	unordered_set<int> uniqueLengths;

	for (int i = 0; i <= k; i++) {
		int sLen = i * s;
		int lLen = (k-i)*s;

		int totalLen = sLen + lLen;

		uniqueLengths.insert(totalLen);
	}
	
	vector<int> lengths;

	for (auto const &it : uniqueLengths) lengths.push_back(it);

	return lengths;
}

void print(vector<int> solutions) {

	for (int i = 0; i < solutions.size(); i++) {
		cout << solutions[i] << endl;
	}
}

int main() {

	vector<int> solutions = divingBoard(2,7,5);

	print(solutions);

	return 0;
}


