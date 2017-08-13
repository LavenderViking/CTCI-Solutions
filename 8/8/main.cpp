#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <set>
#include <unordered_map>
using namespace std;


unordered_map<char,int> getFrequencies(string s) {
	
	unordered_map<char, int> HT;

	for (int i = 0; i < s.size(); i++) HT[s[i]] = HT.count(s[i]) == 0 ? 1 : HT[s[i]] + 1;

	return HT;	
}

void constructAllPermutations(unordered_map<char,int> frequencies, string prefix, int remaining, set<string> &results) {

	if (remaining == 0) {
		results.insert(prefix);
		return;
	}

	for (auto &iter : frequencies) {
		int count = iter.second;

		if (count > 0) {
			frequencies[iter.first]--;
			constructAllPermutations(frequencies, prefix + iter.first, remaining - 1, results);
			frequencies[iter.first]++;
		}
	}
}

// Returns all permutations of a string. Uses a hash table to store frequencies of each character
// to speed up computation time for strings with many of the same character.
set<string> getAllPermutations(string s) {

	set<string> allPermutations;

	// Build a hash table of frequencies:
	unordered_map<char, int> frequencies = getFrequencies(s);

	constructAllPermutations(frequencies, "", s.size(), allPermutations);

	return allPermutations;
}

void printPermutations(set<string> allPermutations) {
	cout << "Total number of permutations: " << allPermutations.size() << endl;

	for (auto const &it : allPermutations) {
		cout << it << endl;
	}
}


int main() {

	string s = "ABCCD";

	set<string> allPermutations = getAllPermutations(s);

	printPermutations(allPermutations);
	
	return 0;
}

