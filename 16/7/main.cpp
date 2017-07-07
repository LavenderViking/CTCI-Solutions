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
using namespace std;


int max(int a, int b) {
	int c = a-b;

	bool isSmaller = (c>>31 & 1);

	return isSmaller * b + !isSmaller * a;
}

int main() {

	ifstream file;
	file.open("input.txt");

	int x,y;
	file >> x >> y;

	cout << max(x,y) << endl;	

	file.close();

	return 0;
}


