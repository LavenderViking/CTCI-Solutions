#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {

	ifstream file;
	file.open("input.txt");

	string s1="", s2="";

	int numComparisons;
	file >> numComparisons;

	for (int i = 0; i < numComparisons; i++) {
		file >> s1 >> s2;
	
		int len1 = s1.length(), len2 = s2.length();
	
		bool same = true, oneDiff = false;
	
		if (len1 == len2) {
			for (int i = 0; i < len1; i++) {
				if (s1[i] != s2[i]) {
					if (oneDiff) {
						same = false;
						break;
					}

					oneDiff = true;
				}
			}
		} else if (len1 == len2-1 || len2 == len1-1) {

			string longer = len2 == len1-1 ? s1 : s2;
			string shorter = len2 == len1-1 ? s2 : s1;

			int longerLen = max(len1, len2);

			// Keep track of where we are in the shorter string:
			int index = 0;

			// Loop through longer string:
			for (int i = 0; i < longerLen; i++) {
				if (shorter[index] != longer[i]) {
					// 2 Are different:
					if (oneDiff) {
						same = false;
						break;
					}
					oneDiff = true;
					index--;
				}

				index++;
			}
		
		} else {
			same = false;
		}

		same ? cout << "1\n" : cout << "0\n";
	}
	file.close();

	return 0;
}
