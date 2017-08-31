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

bool validOp(char op) {
	if (op == '+' || op == '-' || op == '*' || op == '/') return true;
	return false;
}



double eval(string s) {
	int len = s.length();

	cout << "Calling eval with " << s << endl;
	if (len == 0) return 0;
	else if (len == 1) return s[0] - '0';
	
	int i = len - 1;
	char op = s[i];

	while (!validOp(op)) op = s[--i];

	double L = eval(s.substr(0,i));
	double R = eval(s.substr(i+1,len));

	if (op == '+') {cout << "Returning " << L+R << endl; return L + R;}
	else if (op == '-') return L - R;
	else if (op == '*') return L * R;
	else return L / R;
}


bool isMulOrDiv(char op) {
	if (op == '*' || op == '/') return true;
	return false;
}

bool isPlusOrMinus(char op) {
	if (op == '+' || op == '-') return true;
	return false;
}


char getNextPlusMinus(string s, int &i) {
	while (i < s.length() && !isPlusOrMinus(s[i])) i++;

	if (isPlusOrMinus(s[i])) {
		return s[i];
	}
	i = -1;
	return 'x';
}

double calculator(string s) {
	cout << "Inside calculator with s=" << s << endl;
	// Parse input:
	// Parse input separately in (+ and -) and (* and /):
	int len = s.length();

	if (len == 0) return 0;
	
	int i = 0;

	// Find first multiplication or division:
	char op = s[0];
	while (i < len && !isMulOrDiv(op)) op = s[++i];
cout << "i = " << i << endl;	
	if (i == len-1) {
		// Only + and -:
		return eval(s);
	} else {
		// Includes * and/or /:
		int nextOpIndex = i;
		i++;
		char nextOp = getNextPlusMinus(s,nextOpIndex);
		int left = nextOpIndex;
		while (i >= 0 && !isPlusOrMinus(s[left])) left--;

		int right = nextOpIndex;
		while (i < len && !isPlusOrMinus(s[left])) right++;

		cout << "left = " << left << " right = " << right << endl;
		double L = eval(s.substr(0,left-1));
		cout << "After L" << endl;
 		double R = calculator(s.substr(right+1,len));
		
		return eval(s.substr(0,i+1)) + L + R;
	}
	
	return 0;
}

int main() {

	string s = "2*3+5/6*3+5";
	
//	s = "2*3/3*6*3";
	cout << "s = " << s << endl;

	int res = calculator(s);

	cout << "res = " << res << endl;	

	return 0;
}


