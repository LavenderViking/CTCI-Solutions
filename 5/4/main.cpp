#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>


using namespace std;

int getFirst0Index(int x);
int getFirst1Index(int x);
int getNum1sAfter(int x, int index);


int nextSmallest(int x);
int nextLargest(int x);

int nextSmallest2(int x);
int nextLargest2(int x);


int num1s(int x);

int main() {

	ifstream file;
	file.open("input.txt");

	int x;
	file >> x;
	
	cout << nextSmallest(x) << endl;
	cout << nextSmallest2(x) << endl;
	cout << nextLargest2(x) << endl;
	cout << nextLargest(x) << endl;

	file.close();

	return 0;
}

int getFirst0Index(int x) {
	int i = 0;
	bool seen1 = false;
	while (i < 32) {
		if (x & 1) seen1 = true;
		else {
			if (seen1) break;
		}
		i++;
		x >>= 1;
	}
	if (i==32) return -1;
	else return i;
}

int getFirst1Index(int x) {
	int i = 0;
	bool seen0 = false;
	while (i < 32) {
		if ((x & 1) == 0) seen0 = true;
		else {
			if (seen0) break;
		}
		i++;
		x >>= 1;
	}
	if (i==32) return -1;
	else return i;
}


int getNum1sAfter(int x, int index) {
	int num1s = 0;
	while (index > 0) {
		if (x & 1) num1s++;
		x >>= 1;
		index--;
	}
	return num1s;
}


int nextSmallest2(int x) {
	int index = getFirst1Index(x);
	if (index == -1) return -1;
	int num1s = getNum1sAfter(x,index) + 1;
	x &= ~(1<<index);
	x |= ((1<<index)-1);
	x &= ~((1 << (index-num1s))-1);
	return x;
}

int nextLargest2(int x) {
	int index = getFirst0Index(x);
	if (index == -1) return -1;
	int num1s = getNum1sAfter(x,index) - 1;
	x |= (1<<index);
	x &= ~((1<<index) - 1);
	x |= ((1 << num1s) - 1);
	return x;
}


int nextSmallest(int x) {
	int num1sX = num1s(x);
	int largest = x/2;

	while (x > largest) {
		x--;
		if (num1s(x) == num1sX) {
			largest = x;
			break;
		}
	}
	return largest;
}


int nextLargest(int x) {
	int num1sX = num1s(x);
	int smallest = x*2;

	while (x < smallest) {
		x++;
		if (num1s(x) == num1sX) {
			smallest = x;
			break;
		}
	}
	return smallest;
}


int num1s(int x) {
	int c = 0;
	while (x) {
		if (x & 1) {
			c++;
		}
		x >>= 1;
	}
	return c;
}
