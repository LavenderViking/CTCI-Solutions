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

int countOf(string pattern, char c) {
	int count = 0;

	for (int i = 0; i < pattern.length(); i++) if (pattern[i] == c) count++;

	return count;
}

string buildFromPattern(string pattern, string a, string b) {
	string s = "";

	for (int i = 0; i < pattern.size(); i++) s += pattern[i] == 'a' ? a : b;

	return s;
}

int firstAltIndex(string pattern, char alt) {
	int index = 0;

	for (index = 0; index < pattern.size(); index++) {
		if (pattern[index] == alt) return index;
	}

	// Not found:
	return -1;
}

// O(N^2) solution:
// Tries O(N) possibilities for first string:
// For each of those possibilities it calculates what the second
// string is according to the pattern and builds the whole string
// and compares it to value to see if it is the same:
bool doesMatch(string pattern, string value) {

	int size = value.length();
	
	if (pattern.length() == 0) return value.length() == 0;
	else if (size == 0) return false;

	char mainChar = pattern[0], altChar = mainChar == 'a' ? 'b' : 'a';
	int firstAlt = firstAltIndex(pattern,altChar);

	int countOfMain = countOf(pattern,mainChar), countOfAlt = pattern.size() - countOfMain;

	int maxMainSize = size / countOfMain;

	for (int mainSize = 0; mainSize <= maxMainSize; mainSize++) {
		int remainingLength = size - countOfMain * mainSize;

		string first = value.substr(0,mainSize);
		if (countOfAlt == 0 || remainingLength % countOfAlt == 0) {
			int altIndex = firstAlt * mainSize;
			int altSize = countOfAlt == 0 ? 0 : remainingLength / countOfAlt;

			string second = countOfAlt == 0 ? "" : value.substr(altIndex,altSize);

			string cand = buildFromPattern(pattern,first,second);

			if (cand == value) {
				return true;
			}
		}
	}
	return false;
}

bool sameStrings(string s1, string s2) {
	if (s1.length() != s2.length()) {
		return false;
	}

	for (int i = 0; i < s1.length(); i++) {
		if (s1[i] != s2[i]) return false;
	}

	return true;
}

bool matches(string pattern, string value, string first, string second, char altChar) {
	
	int firstLen = first.length(), secondLen = second.length();

	int indexValue = 0, indexPattern = 0;

	while (indexValue < value.length()) {
		int len = firstLen;

		string str = first;

		if (pattern[indexPattern++] == altChar) {
			str = second;
			len = secondLen;
		}

		if (!(sameStrings(value.substr(indexValue,len),str))) {
			return false;
		}
		
		indexValue += len;
	}

	return true;
}

// O(N^2) solution:
// Tries O(N) possibilities for first string:
// For each of those possibilities it calculates what the second
// string is according to the pattern and builds the string in 
// chunks and compares on the way. Faster because it doesn't built the
// whole string unless it's a match.
bool doesMatchFast(string pattern, string value) {

	int size = value.length();
	
	if (pattern.length() == 0) return value.length() == 0;
	else if (size == 0) return false;

	char mainChar = pattern[0], altChar = mainChar == 'a' ? 'b' : 'a';
	int firstAlt = firstAltIndex(pattern,altChar);

	int countOfMain = countOf(pattern,mainChar), countOfAlt = pattern.size() - countOfMain;

	int maxMainSize = size / countOfMain;

	for (int mainSize = 0; mainSize <= maxMainSize; mainSize++) {
		int remainingLength = size - countOfMain * mainSize;

		int altIndex = firstAlt * mainSize;
		
		string first = value.substr(0,mainSize);
		if (countOfAlt == 0 || remainingLength % countOfAlt == 0) {
			int altSize = countOfAlt == 0 ? 0 : remainingLength / countOfAlt;

			string second = countOfAlt == 0 ? "" : value.substr(altIndex,altSize);

			if (matches(pattern,value,first,second,altChar)) return true;
		}
	}
	return false;
}



int main() {
	
	//string value = "catcatgocatgocatgogogogogogogo", pattern = "aabababbbbbbb";
	string value = "abraabrakkkkabra", pattern = "bbaaaab";

	cout << "Same = " << doesMatchFast(pattern,value) << endl;

	return 0;
}


