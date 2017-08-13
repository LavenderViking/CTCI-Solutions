#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

void swap(vector<string> &A, vector<string> &B, int i, int j) {
	string tempA = A[i], tempB = B[i];
	A[i] = A[j]; B[i] = B[j];
	A[j] = tempA; B[j] = tempB;
}

int partition(vector<string> &A, vector<string> &B, int left, int right) {
	string pivot = A[(left+right)/2];

	while (left <= right) {
		while (A[left] < pivot) left++;
		while (A[right] > pivot) right--;

		if (left <= right) swap(A,B,left++,right--);
	}

	return left;
}

void quickSort(vector<string> &A, vector<string> &B, int left, int right) {
	if (left <= right) {
		int index = partition(A,B,left,right);
		if (left < index-1) quickSort(A,B,left,index-1);
		if (right > index) quickSort(A,B,index,right);
	}	
}


//O(Nlog(N)) solution:
void sortAnagrams(vector<string> &strings) {

	// Make copy of strings:
	vector<string> stringsCopy = strings;

	// Sort individual strings within strings:
	for (int i = 0; i < strings.size(); i++) sort(stringsCopy[i].begin(), stringsCopy[i].end());

	// Sort vector of the strings copyStrings and keep same ordering for the vector strings:
	quickSort(stringsCopy,strings,0,strings.size()-1);
}

void print(vector<string> A) {
	fori(0,A.size()) {
		cout << A[i] << " ";
	}
	cout << endl;
}

// O(N) solution:
void sortAnagrams2(vector<string> &strings) {
	unordered_map<string,unordered_set<string>> map;
	unordered_map<string,int> mapCount;

	for (int i = 0; i < strings.size(); i++) {
		string old = strings[i];
		sort(strings[i].begin(),strings[i].end());
		string sortedOld = strings[i];

		map[sortedOld].insert(old);
		mapCount[old] = mapCount.count(old) > 0 ? mapCount[old]+1 : 1;
	}

	// Iterate over map and replace strings in vector strings:
	int index = 0;
	for (auto const &set : map) {
		for (auto const &s : set.second) {
			for (int count = 0; count < mapCount[s]; count++) {
				strings[index++] = s;
			}
		}
	}
}

int main() {

	ifstream file;
	file.open("input.txt");

	int size; file >> size;

	vector<string> A;

	fori(0,size) {
		string s;
		file >> s;
		A.push_back(s);
	}

	cout << "Printing A before\n";
	print(A);
	
	sortAnagrams2(A);

	cout << "Printing A after\n";
	print(A);
	
	file.close();

	return 0;
}


