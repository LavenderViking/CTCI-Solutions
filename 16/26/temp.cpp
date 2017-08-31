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

double calc(string s) {
	int len = s.length();

	cout << "Calling calc with " << s << endl;
	if (len == 0) return 0;
	else if (len == 1) return s[0] - '0';

	int i = len - 1;
	char op = s[i];

	while (!validOp(op)) op = s[--i];

	double L = calc(s.substr(0,i));
	double R = calc(s.substr(i+1,len));

	if (op == '+') {cout << "Returning " << L+R << endl; return L + R;}
	else if (op == '-') return L - R;
	else if (op == '*') return L * R;
	else return L / R;
}

char getNextOp(string s, int i, bool plusMinus) {
	i+=2;
	while (i < s.length() && !validOp(s[i])) ++i;
	
	if (plusMinus) {
		if (s[i] == '*' || s[i] == '/') return getNextOp(s,i,plusMinus);
		else return s[i];
	} else {
		if (s[i] == '+' || s[i] == '-') return getNextOp(s,i,plusMinus);
		else return s[i];
	}
	return 'x';
}

char getNextOpIndex(string s, int i, bool plusMinus) {
	i+=2;
	while (i < s.length() && !validOp(s[i])) ++i;
	
	if (plusMinus) {
		if (s[i] == '*' || s[i] == '/') return getNextOpIndex(s,i,plusMinus);
		else return i;
	} else {
		if (s[i] == '+' || s[i] == '-') return getNextOpIndex(s,i,plusMinus);
		else return i;
	}
	return -1;
}


double calculator(string s) {

	// Parse input:
	// Parse input separately in (+ and -) and (* and /):
	int len = s.length();

	if (len == 0) return 0;
	else if (len == 1) return s[0];

	int i = 1;

	char op = s[1];
	while (!validOp(op)) op = s[++i];

	cout << "Inside calculator with " << s << endl;



	cout << "op = " << op << endl;
	if (op == '+' || op == '-') {
		int nextOpIndex = getNextOpIndex(s,i,false);
		char nextOp = getNextOp(s,i,false);
		if (nextOpIndex == -1) {
			return calc(s);
		} else {
			if (nextOp == '*') {
				return calc(s.substr(0,nextOpIndex)) * calculator(s.substr(nextOpIndex+1,len));
			} else {
				return calc(s.substr(0,nextOpIndex)) / calculator(s.substr(nextOpIndex+1,len));
			} 		
		}
	} else {
		int nextOpIndex = getNextOpIndex(s,i,true);
		char nextOp = getNextOp(s,i,true);
		
		cout << "index = " << nextOpIndex << " op = " << nextOp << endl;
		if (nextOpIndex == -1) {
			return calc(s);
		} else {
			if (nextOp == '+') {
				return calc(s.substr(0,nextOpIndex)) + calculator(s.substr(nextOpIndex+1,len));
			} else {
				return calc(s.substr(0,nextOpIndex)) - calculator(s.substr(nextOpIndex+1,len));
			} 		
		}
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


