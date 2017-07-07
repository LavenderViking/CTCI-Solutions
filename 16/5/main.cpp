#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

typedef unordered_map<string,int> HT;

int factorial(int n) {
	int ret = 1;
	for (int i = 1; i<= n; i++) {
		ret *= i;
	}
	return ret;
}

int factorialZeros2(int n) {
	int count = 0;

	if (num < 0) {
		return 0;
	}

	for (int i = 5; num / i > 0; i *= 5) {
		count += num / i;
	}

	return count;
}

// Edit do not need to count number of 2s since there are always fewer number of 5s:
int factorialZeros(int n) {
	// Find how many pairs of 2s and 5s are in n factorial:

	int num5s=0;

	for (int i = 1; i <= n; i++) {
		int t = i;
		while (t) {
			if (t%5==0) {
				t /= 5;
				num5s++;
			 else {
				break;
			}
		}
	}

	return num5s;
}


int main() {

	ifstream file;
	file.open("input.txt");

	int x;
	file >> x;

	cout << "Number: " << x << " which has factorial(x) = " << factorial(x) << " has " << factorialZeros(x) << " number of zeros"  << endl;

	file.close();

	return 0;
}


