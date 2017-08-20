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

// Return -x:
int negate(int x) {
	int neg = 0;

	int newSign = x < 0 ? 1 : -1;

	while (x != 0) {
		neg += newSign;
		x += newSign;
	}

	return neg;
}

bool sameSign(int a, int b) { return (a > 0 && b > 0) || (a < 0 && b < 0); }

int negateFast(int x) {
	if (x == 0) return 0;

	int neg = 0;

	int newSign = x < 0 ? 1 : -1;

	int delta = newSign;

	while (x != 0) {
		if (x + delta != 0) {
			if (!(sameSign(x+delta,x))) {
				delta = newSign;
				continue;
			}
		}

		x += delta;
		neg += delta;
		delta += delta;
	}

	return neg;
}

// Return a/b:
// 6/3 = 2
// 6/4 = 1
// 6/5 = 1
// 6/6 = 1
// 6/7 = 0
int divv(int a, int b) {

	if (a == 0) return 0;
	else if (b == 1) return a;
	else if (b == 0) return -1;

	bool isPositive = sameSign(a,b);

	if (a < 0) a = negateFast(a);
	if (b < 0) b = negateFast(b);

	if (a == b) return 1;
	else if (a > b) {
		return divv(a-b,b) + (isPositive ? 1 : -1);
	} else {
		return 0;
	}
}

// Return a*b:
int mul(int a, int b) {
	if (a == 0 || b == 0) return 0;

	int sum = 0;

	bool isPositive = sameSign(a,b);

	if (a < 0) a = negateFast(a);
	if (b < 0) b = negateFast(b);

	for (int i = 0; i < b; i++) sum += a;

	return isPositive ? sum : negateFast(sum);
}

// Return a-b:
int sub(int a, int b) {
	return a + negateFast(b);
}


int main() {
	
	int s = mul(5,-6);
	int s1 = sub(5,-6);
	int s2 = divv(5,2);

	cout << "s = " << s << endl;
	cout << "s = " << s1 << endl;
	cout << "s = " << s2 << endl;

	

	return 0;
}


