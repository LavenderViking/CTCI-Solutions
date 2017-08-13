#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

#define SIZE 29

void initializeBitvector(int *bitvector, int size) {
	for (int i = 0; i < size; i++) bitvector[i] = 0;
}

int pow2(int n) {
	int sum = 1;

	for (int i = 0; i < n; i++) sum *= 2;

	return sum;
}

int* bitvector() {
	// Maximum number of positive numbers:
	int totalNums = pow2(SIZE) + 1;

	// Each int stores 32 0/1 values:
	int size = totalNums / 32 + 1;

	int *bv = new int[size];

	initializeBitvector(bv,size);

	return bv;
}

void setNumberTo1(int *bitvector, int number) {
	int index = number / 32;

	int mod = number % 32;

	bitvector[index] |= 1 << mod;
}


int missingInt(vector<int> ints) {
	int size = pow2(SIZE)+1;

	// Create bitvector with ints.size() many bits:
	int *bv = bitvector();

	// Set all numbers to 1 that are in ints:
	for (int i = 0; i < ints.size(); i++) setNumberTo1(bv,ints[i]);

	// Find first 0 in the bitvector:
	for (int i = 0; i < 10; i++) {
		cout << "Inside for with i = " << i << endl;
		int num = bv[i];

		int found = false;

		int shift = 0;
		while (shift < 32) {
			if ((num & 1) == 0) {
				found = true;
				break;
			}
			num >>= 1;
			shift++;
		}

		// If there was a 0 somewhere in the number then we return it:
		if (found) return i*32 + shift;
	}

	return -1;
}


int main() {

	vector<int> vec;
	fori(0,16) vec.push_back(i);
	fori(15,25) vec.push_back(i);

	int missing = missingInt(vec);

	cout << "Missing = " << missing << endl;

	return 0;
}


