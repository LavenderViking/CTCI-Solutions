#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <set>
#include <unordered_map>
#include <vector>
#include <array>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

// Symbols:
// 0 1 & | ^

bool charToBool(char c) {
	return c == '1' ? true : false;
}

string boolToString(bool b) {
	return b ? "1" : "0";
}

int countEval(string s, bool eval, unordered_map<string,int> memo) {
	
	string evalString = boolToString(eval);

	if (memo.count(s+evalString) > 0) return memo[s+evalString];

	int len = s.length();

	if (len == 0) return false;
	if (len == 1) return charToBool(s[0]) == eval ? 1 : 0;

	int count = 0;

	for (int i = 1; i < len; i+=2) {
		char op = s[i];
		
		string leftS = s.substr(0,i);
		string rightS = s.substr(i+1,len);

		int leftTrue = countEval(leftS,true,memo);
		int leftFalse = countEval(leftS,false,memo);

		int rightTrue = countEval(rightS,true,memo);
		int rightFalse = countEval(rightS,false,memo);
	
		int subWays = 0;

		int total = (leftTrue + leftFalse) * (rightTrue + rightFalse);

		if (op == '&') {
			subWays += leftTrue * rightTrue;
		} else if (op == '|') {
			subWays = subWays + leftTrue * rightTrue
			        + leftTrue * rightFalse
			        + leftFalse * rightTrue;
		} else if (op == '^') {
			subWays = subWays +  leftTrue * rightFalse
			        + leftFalse * rightTrue;
		} else {
			cout << "ERROR. INVALID OP" << endl;
		}

		count += eval ? subWays : total - subWays;
	}

	memo[s+evalString] = count;

	return count;
}

int countEval(string s, bool eval) {
	unordered_map<string,int> memo;

	return countEval(s,eval,memo);
}

int main() {

	string s = "1^0|0|1";
	string s2 = "0&0&0&1^1|0";
	bool eval = false;
	bool eval2 = true;

	int count = countEval(s,eval);
	int count2 = countEval(s2,eval2);

	cout << "Count = " << count << endl;
	cout << "Count = " << count2 << endl;

	return 0;
}

