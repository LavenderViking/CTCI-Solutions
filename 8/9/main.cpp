#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <set>
#include <unordered_map>
using namespace std;



// 1 : 1
// ()

// 2 : 2
// ()()
// (())

// 3 : 5
// ()()()
// ()(())
// (())()
// (()())
// ((()))


// Method:

// create all binary strings of length 2N and find which ones are OK:

int pow2(int N) {
	int res = 1;

	for (int i = 0; i < N; i++) res *= 2;

	return res;
}


// Returns all valid parenthesis of length 2N.
// Uses binary shifting and Works for N <= 32
set<string> allValidParenthesis(int N) {
	
	int len = 2 * N;

	int numParenthesis = pow2(len);

	string *allParenthesis = new string[numParenthesis];

	for (int i = 0; i < numParenthesis; i++) allParenthesis[i] = "";

	for (int i = 0; i < numParenthesis; i++) {
		// Get binary rep of i:
		for (int j = 0; j < len; j++) {
			if (i >> j & 1) {
				allParenthesis[i] += '(';
			} else {
				allParenthesis[i] += ')';
			}
		}
	}

	// Remove invalid parenthesis:
	for (int i = 0; i < numParenthesis; i++) {
		string parenthesis = allParenthesis[i];

		int leftCount = 0, rightCount = 0;

		for (int j = 0; j < len; j++) {
			if (parenthesis[j] == '(') leftCount++;
			else rightCount++;

			if (rightCount > leftCount) { allParenthesis[i] = ""; break; }
		}

		if (leftCount != rightCount) allParenthesis[i] = "";
	}

	set<string> S;

	for (int i = 0; i < numParenthesis; i++) {
		if (allParenthesis[i] != "") {
			S.insert(allParenthesis[i]);
		}
	}

	delete [] allParenthesis;
	
	return S;
}


void printParenthesis(set<string> S) {
	cout << "Printing all valid parenthesis: " << endl;
	for (auto &it : S) {
		cout << it << " ";
	}
	cout << endl;
}



// Returns all valid parenthesis with a mix of N parenthesis:
set<string> validP(int N) {
	set<string> S;

	S.insert("()");

	for (int i = 1; i < N; i++) {

		set<string> newS;
		for (auto const &p : S) {
			string newP;

			newS.insert("()" + p);

			for (int j = 1; j < p.length(); j++) {
				string firstPart="", lastPart="";

				for (int k = 0; k < j; k++) firstPart += p[k];
				for (int k = j; k < p.length(); k++) lastPart += p[k];

				newS.insert(firstPart + "()" + lastPart);
			};

			
		}

		S = newS;
	}

	return S;
}





int main() {

	int N = 5;

//	printParenthesis(allValidParenthesis(N));
	
	printParenthesis(validP(N));

	return 0;
}




