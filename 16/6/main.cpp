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
using namespace std;

typedef unordered_map<string,int> HT;

struct pair {
	int a,b;

	pair(int x, int y) : a{x}, b{y} {}
};

// Returns closest value in a to value:
int binSearch(vector<int> a, int value) {
	int size = a.size();

	if (value < a[0]) return a[0];

	if (value < a[size-1]) return a[size-1];

	int low = 0, high = size-1;

	while (low <= high) {
		
	}
}

int binarySearch(vector<int> a, int value, int &valueIndex) {
	int size = a.size();

	int diff = value - a[0];
	int indexL = 0; 
	int indexR = size-1;

	while (true) {
		int index = indexL + (indexL+indexR)/2;
		cout << "Binary search on index " << index << " with value " << value << endl;
		int newdiff = abs(a[index] - value);
		
		if (a[index] > value ) {
			indexL = index;
		} else {
			indexR = index;
		}

		if (newdiff < diff) {
			diff = newdiff;
			valueIndex = index;
		}

		if (indexL == indexR) break;
	}

	return diff;
}

// O(Alg(A) + Blg(B))
int smallestDifference2(vector<int> a, vector<int> b) {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	int i1=0;
	int i2=0;

	int diff = INT_MAX;

	while (i1 != a.size()-1 && i2 != b.size()-1) {
		int newDiff = a[i1] > b[i2] ? a[i1] - b[i2] : b[i2] - a[i1];

		if (newDiff < diff) diff = newDiff;

		if (a[i1] < b[i2]) i1++;
		else i2++;
	}

	return diff;
}


// min(O(Alg(B) + B, O(Blg(A)+A))
int smallestDifference(vector<int> a, vector<int> b) {

	bool aShorter = true;
	int size = a.size() <= b.size() ? a.size() : b.size();

	if (b.size() < a.size()) size = aShorter = false;
	
	// Sort shorter vector:
	if (aShorter) {
		sort(a.begin(), a.end());
	} else {
		sort(b.begin(), b.end());
	}

	// Loop through longer vector and find shortest value in shorter vector:
	int diff = INT_MAX;
	int ind = 0;
	int ind2 = 0;
	if (!aShorter) {
		for (int i = 0; i < a.size(); i++) {
			int index = 0;		
			int newdiff = abs(binarySearch(b,a[i],index));
			if (newdiff < diff) {
				diff = newdiff;
				ind = index;
				ind2 = i;
			}
		}
	} else {
		for (int i = 0; i < b.size(); i++) {
			int index = 0;
			int newdiff = abs(binarySearch(a,b[i],index));
			if (newdiff < diff) {
				diff = newdiff;
				ind = index;
				ind2 = i;
			}
		}	
	}
	cout << "Index is = " << ind << " and " << ind2 << endl;
	if (aShorter) {
		cout << "Values are " << a[ind] << " and " << b[ind2] << endl;
	} else {
		
		cout << "Values are " << b[ind] << " and " << a[ind2] << endl;
	}

	cout << "Printing vector a" << endl;

	for (int i=0; i < a.size(); i++) {
		cout << a[i] << endl;
	}

	cout << "Printing vector b" << endl;

	for (int i=0; i < b.size(); i++) {
		cout << b[i] << endl;
	}

	return diff;
}

int main() {

	ifstream file;
	file.open("input.txt");

	int x;
	file >> x;

	vector<int> a = {1,2,5,10,15,18};
	vector<int> b = {14,20,100,500,250,50,49};

//	int res2 = smallestDifference2(a,b);

	int res = smallestDifference(a,b);

	cout << res << endl;

	file.close();

	return 0;
}


