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

bool verifyMajorityElement(vector<int> A, int majEl) {

	int count = 0;

	for (int i = 0; i < A.size(); i++) {
		if (A[i] == majEl) count++;
	}

	return count > A.size() / 2;
}

int majorityElement(vector<int> A) {

	int size = A.size();

	if (size == 0) return -1;
	
	int majEl = A[0];
	int count = 1;

	for (int i = 1; i < size; i++) {
		if (A[i] == majEl) count++;
		else if (count == 1) {
			majEl = A[i];
		} else {
			count--;
		}
	}

	return verifyMajorityElement(A,majEl) ? majEl : -1;
}


int main() {

	vector<int> A = {1,2,5,9,5,9,5,5,5};

	int majEl = majorityElement(A);

	if (majEl == -1) {
		cout << "There is no majority element\n";
	} else {
		cout << "The majority element is " << majEl << endl;
	}

	return 0;
}


