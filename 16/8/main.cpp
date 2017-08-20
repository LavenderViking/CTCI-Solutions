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

class strings {
	public:
	array<string,20> smalls = {"Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fiveteen","Sixteen","Seventeen","Eighteen","Nineteen"};
	array<string,10> tens = {"","Ten","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
	array<string,4> bigs = {"","Thousand","Million","Billion"};
	string hundred = "Hundred";
	string negative = "Negative";	
};

string listToString(vector<string> parts) {
	string returnString = "";
	for (int i = 0; i < parts.size(); i++) {
		returnString += parts[i];
		if (i != parts.size()-1) returnString += "-";
	}	
	return returnString;
}

string convertChunk(int n) {
	vector<string> parts;

	strings s;

	if (n >= 100) {
		parts.push_back(s.smalls[n/100]);
		parts.push_back(s.hundred);
		n %= 100;
	}

	if (n >= 20) {
		parts.push_back(s.tens[n/10]);
		n %= 10;
	}
	if (n >= 1) {
		parts.push_back(s.smalls[n]);
	}

	return listToString(parts);
}

string englishInt(int N) {
	
	strings s;

	if (N == 0) return s.smalls[0];
	else if (N < 0) return s.negative + " " + englishInt(-N);

	vector<string> parts;

	int chunkCount = 0;

	while (N > 0) {
		parts.push_back(convertChunk(N%1000));

		if (N/1000 > 0) parts.push_back(s.bigs[++chunkCount]);

		N /= 1000;
	}

	reverse(parts.begin(),parts.end());

	return listToString(parts);
}



int main() {
	int N;
	cin >> N;

	cout << englishInt(N) << endl;

	return 0;
}


