#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>

using namespace std;


void compressString(string s);
void compressString2(string s);
int lengthOfInt(int x);
string addToString(string s, char c, int count);


int main() {

	ifstream file;
	file.open("input.txt");

	string s="";
	file >> s;

	clock_t begin = clock();
	compressString2(s);
	clock_t end = clock();

	clock_t timeElapsed = ( end - begin );
	
	cout << float( timeElapsed * 1000) / CLOCKS_PER_SEC << " ms" << endl;

	file.close();

	return 0;
}


// Faster method:
// Instead of concatenating to a string every time this method 
// finds how many times each character is and then couts the string.
void compressString2(string s) {

	// Find how many characters are:
	int numChars = 1;
	char compChar = s[0];
	for (int i = 1; i < s.length(); i++) {
		if (s[i] != compChar) {
			numChars++;
			compChar = s[i];
		}
	}

	// Initialize array of size numChar
	char *arr = new char[numChars];

	// Fill in chars:
	int index = 0;
	arr[index++] = s[0];
	for (int i = 1; i < s.length(); i++) {
		if (s[i] != compChar) {
			arr[index++] = s[i];
			compChar = s[i];
		}
	}

	// Fill in counts:
	int *counts = new int[numChars];
	index = 0;
	compChar = s[0];
	int count = 1;
	for (int i = 1; i < s.length(); i++) {
		if (s[i] == compChar) {
			count++;
		} else {
			compChar = s[i];
			counts[index++] = count;
			count = 1;
		}

		if (i == s.length()-1) {
			counts[index] = count;
			index++;
		}
	}

	// Find length of string:
	int totalLen = 0;
	for (int i = 0; i < numChars; i++) {
		totalLen += 1;
		totalLen += lengthOfInt(counts[i]);
	}


	if (totalLen < s.length()) {
		for (int i = 0; i < numChars; i++) {
			cout << arr[i] << counts[i];
		}
	} else {
		cout << s;
	}

	delete [] counts;
	delete [] arr;
}

int lengthOfInt(int x) {
	int count = 0;

	while (x) {
		x /= 10;
		count++;
	}
	return count++;
}

void compressString(string s) {
	string returnString = "";

	if (s.length() == 1) {
		cout << s << endl;
		return;
	}

	// First character in string:
	char compareChar = s[0];
	int count = 1;

	for (int i = 1; i < s.length(); i++) {
		if (s[i] == compareChar) {
			count++;
		} else {
			returnString = addToString(returnString, compareChar, count);
			count = 1;
			
			compareChar = s[i];
		}

		if (i == s.length()-1) {
			returnString = addToString(returnString, compareChar, count);
		}
	}

	returnString.length() < s.length() ? cout << returnString << endl : cout << s << endl;
}


string addToString(string s, char c, int count) {
	string newS = s;
	return newS + c + to_string(count);
}
