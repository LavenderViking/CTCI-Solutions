#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <set>
using namespace std;

void permutations(string s, set<string> &allPermutations) {

	if (!allPermutations.insert(s).second) return;
	
	for (int i = 1; i < s.size(); i++) {
		string t = s;

		t[0] = t[i];
		t[i] = s[0];

		permutations(t,allPermutations);
	}
}

void printPermutations(set<string> allPermutations) {
	cout << "Total number of permutations: " << allPermutations.size() << endl;

	for (auto const &it : allPermutations) {
		cout << it << endl;
	}
}


int main() {

	string s = "ABCC";
	set<string> allPermutations;

	permutations(s, allPermutations);

	printPermutations(allPermutations);
	
	return 0;
}

