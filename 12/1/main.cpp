#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Uses two reads of the input file but requires O(1) space:
void printLastKLines2(string filename, int K) {
	ifstream file;
	file.open(filename);

	string *strArr = new string[K];

	int size = 0;

	string line = "";
	while (getline(file,line)) {
		strArr[size++ % K] = line;
	}

	int start = size > K ? size % K : 0;
	int count = min(K,size);

	for (int i = 0; i < count; i++) {
		cout << strArr[(start + i) % K] << endl;
	}

	delete [] strArr;

	file.close();
}

// Uses two reads of the input file but requires O(1) space:
void printLastKLines(string filename, int K) {
	ifstream file;
	file.open(filename);

	int lineCount = 0;

	string line = "";
	while (getline(file,line)) {
		lineCount++;
	}

	file.close();
	file.open(filename);

	// Print last K lines:
	if (K >= lineCount) {
		while (getline(file,line)) {
			cout << line << endl;
		}
	} else {
		for (int i = 0; i < lineCount - K; i++) {
			getline(file,line);
		}

		while (getline(file,line)) {
			cout << line << endl;
		}
	}

	file.close();
}

int main() {

	string filename = "input.txt";
	int K = 3;
	printLastKLines2(filename, K);

	return 0;
}
