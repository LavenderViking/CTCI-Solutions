#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>


using namespace std;

bool getBitAtIndex(int i, int x);
int maxBits(int x);
int maxBits2(int x);


int main() {

	ifstream file;
	file.open("input.txt");

	int x;
	file >> x;
	
	cout << maxBits2(x);
	
	file.close();

	return 0;
}


bool getBitAtIndex(int i, int x) {
	return (x >> i) & 1;
}

// O(1) space
// Keep track of previous sequence and current sequence:
int maxBits2(int x) {
	int prevSeq = 0, currSeq = 0;

	int max = 0;

	for (int i = 0; i < 32; i++) {
		bool bit = x & 1;

		x >>= 1;

		if (bit) {
			currSeq++;
		} else {
			prevSeq = currSeq;
			currSeq = 0;
		}

		if (currSeq + prevSeq + 1 > max) max = currSeq + prevSeq + 1;
	}
	return max;
}

// O(b) space
int maxBits(int x) {
	int max1s = 0;

	for (int i = 0; i < 32; i++) {
		bool is1 = getBitAtIndex(i,x);

		if (!is1) {
			int xTemp = x | (1 << i);

			int count = 0;

			while (xTemp > 0) {
				if (xTemp & 1) {
					count++;
				} else {
					count = 0;
				}

				if (count > max1s) max1s = count;
				xTemp >>= 1;
			}
		}
	}
	return max1s;
}


