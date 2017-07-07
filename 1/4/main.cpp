#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>

using namespace std;

int main() {

	ifstream file;
	file.open("input.txt");

	string s="";
	getline(file,s);

	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(s[i]);
	}

	// Arr for character count: ASCII 256
	int arr[256];

	// Loop through string and fill in counts:
	for (int i = 0; i < s.length(); i++) {
		int val = s[i];
		// Ignore spaces:
		if (s[i] != ' ')
			arr[val]++;
	}
	
	bool foundSingleChar = false;
	// Loop through character count array check if there is at most one character with 1 count:
	for (int i = 0; i < 256; i++) {
		if (arr[i] % 2 == 1) {
			if (foundSingleChar) return false;
			foundSingleChar = true;
		}
	}

	return true;

	file.close();

	return 0;
}
