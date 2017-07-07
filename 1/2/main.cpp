#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

	ifstream file;
	file.open("input.txt");

	string s1="", s2="";
	
	getline(file, s1);
	getline(file, s2);

	int length1 = s1.length();
	int length2 = s2.length();

	// If lengths are not the same they cannot be a permutation of each other:
	if (length1 != length2) return false;

	// Int array to store frequencies:
	int arr[256] = {0};

	// Loop through first string and fill in frequencies:
	for (int i = 0; i < length1; i++) {
		int val = s1[i] - '0';
		arr[val]++;
	}


	// Loop through second string to deduct frequencies:
	for (int i = 0; i < length2; i++) {
		int val = s2[i] - '0';
		arr[val]--;
		if (arr[i] != 0) return false;
	}

	return true;
	
	file.close();

	return 0;
}
