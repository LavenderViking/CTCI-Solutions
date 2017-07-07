#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>


using namespace std;

string binaryRep(double x);

int main() {

	ifstream file;
	file.open("input.txt");

	double x;
	file >> x;
	
	cout << binaryRep(x);
	
	file.close();

	return 0;
}


string binaryRep(double x) {
	string xBin = "0.000000000000000000000000000000";

	int index = 2;
	double deduct = 0.5;

	while (x > 0) {
		cout << "X = " << x << endl;
		if (x - deduct >= 0) {
			x -= deduct;
			xBin[index] = '1';
		}
		deduct /= 2;
		index++;
	}

	cout << "X = " << x << endl;
	if (x > 0) return "ERROR";
	else return xBin;
}

