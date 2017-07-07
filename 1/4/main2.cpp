#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>

using namespace std;


int createBitvector(string s) {
	int bitVector = 0;

	// Loop through string and fill in bitvetor:
	for (int i = 0; i < s.length(); i++) {
		int val = s[i] - 'a';
		cout << "Inside for " << endl;
		if (val < 0) continue;

		bool bitSet = (bitVector & 1<<val) >> val;

		// Mask bit out:
		bitVector &= ~(1<<val);

		// Set bit again:
		bitVector |= !bitSet<<val;
	}
	
	int test = bitVector;

	while (test) {
		cout << (test & 1);
		test >>= 1;
	}
	cout << endl;

	return bitVector;
}

bool checkExactlyOneBitSet(int bitVector) {
	return ((bitVector == 0) || ((bitVector & bitVector-1) == 0));
}

bool isPermutationOfPalindrome(string s) {
	int bitVector = createBitvector(s);
	return bitVector == 0 || checkExactlyOneBitSet(bitVector);
}



int main() {

	ifstream file;
	file.open("input.txt");

	string s="";
	getline(file,s);

	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(s[i]);
	}

	file.close();
	
	return isPermutationOfPalindrome(s);
}
