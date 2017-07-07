#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

	ifstream file;
	file.open("input.txt");

	//freopen("input.txt", "r", stdin);
	string s="";
	getline(file, s);
	
	// Check if length is more than 256 and return false:
	int length = s.length();

	if (length > 256) return false;

	// Bool array to store frequencies:
	bool arr[256] = {false};

	// Loop through string to fill in boolean array:
	for (int i = 0; i < length; i++) {
		int val = s[i] - '0';

		if (arr[val]) return false;
		
		arr[val] = true;
	}

	return true;
	
	file.close();

	return 0;
}
