#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
using namespace std;

void swap(int x, int y) {

	cout << "Before x = " << x << " y = " << y << endl;

	for (int i = 0; i < 32; i++) {
		if (((x >> i) & 1) ^ ((y >> i) & 1)) {
			x = x ^ (1<<i);
			y = y ^ (1<<i);
			
		}
	}
	cout << "After x = " << x << " y = " << y << endl;
}

int main() {

	ifstream file;
	file.open("input.txt");

	int x,y;
	file >> x >> y;

	swap(x,y);	

	file.close();

	return 0;
}


