#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include <stack>
#include <unordered_set>
#include <set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)


// Adds all permutations of the set currentSet to allSets:
void permutations(set<int> currentSet, set<set<int>> &allSets) {
	allSets.insert(currentSet);

	if (currentSet.size() == 0) return;

	// Take one item out of the set and recurse:
	for (int i = 0; i < currentSet.size(); i++) {
		set<int> temp = currentSet;
		auto it = temp.begin();
		advance(it,i);
		temp.erase(*it);
		permutations(temp, allSets);
	}
}

// Returns all subsets of a set S:
set<set<int>> powerSet(set<int> S) {

	set<set<int>> allSets;

	permutations(S, allSets);

	return allSets;
}

void printSets(set<set<int>> S) {
	cout << "Printing permutations: " << endl;
	for (auto it1 = S.begin(); it1 != S.end(); ++it1) {
		set<int> s = *it1;

		for (auto it2 = s.begin(); it2 != s.end(); ++it2) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
	cout << "Total number of permutations: " << S.size() << endl;
}

int pow2(int num) {
	int res = 1;

	while (num) {
		res *= 2;
		num--;
	}
	return res;
}

// Returns all subsets of a set S:
// Uses binary representation of 2^(size set) and adds corresponding numbers
// in the set if there is  1 at that spot in the binary representation:
set<set<int>> allSetsCombinatorics(vector<int> S) {

	set<set<int>> allSets;

	for (int i = 0; i < pow2(S.size()); i++) {
		set<int> newSet;
		
		// Add to set where 1 is in binary rep:
		int temp = i, c = 0;
		while (temp > 0) {
			if (temp & 1) newSet.insert(S[c]);
			temp >>= 1;
			c++;
		}
		allSets.insert(newSet);
	}
	return allSets;
}

int main() {

//	set<int> S = {1,2,3,4,5,6,7,8,9,10};
	vector<int> S2 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

//	set<set<int>> allSets = powerSet(S);
	set<set<int>> allSets2 = allSetsCombinatorics(S2);

//	printSets(allSets);
	printSets(allSets2);

	return 0;
}

