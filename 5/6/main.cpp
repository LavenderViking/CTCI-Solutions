#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
using namespace std;

unsigned int conversion(int a, int b);

int main() {

	ifstream file;
	file.open("input.txt");

	int a, b;
	file >> a >> b;

	cout << conversion(a,b);
	
	file.close();

	return 0;
}


unsigned int conversion(int a, int b) {
	int diff = a ^ b;
	unsigned int numBits = 0;

	while (diff > 0) {
		if (diff & 1) {
			numBits++;
		}
		diff >>= 1;
	}
	return numBits;
}
