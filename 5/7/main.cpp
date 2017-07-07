#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
using namespace std;

int swapOddEven(int x);

int main() {

	ifstream file;
	file.open("input.txt");

	int x;
	file >> x;

	cout << swapOddEven(x);	

	file.close();

	return 0;
}



int swapOddEven(int x) {
	unsigned int a = (-1/3) * 2;
	return (((x&a)>>1) | ((x & ~a) << 1));
}
