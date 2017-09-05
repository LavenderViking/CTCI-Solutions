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
#include <unordered_set>
#include <vector>
#include <array>
using namespace std;

void swap(vector<int> &A, int i, int j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

vector<int> randomSet(vector<int> A, int n, int m) {

	vector<int> indexes;
	for (int i = 0; i < n; i++) indexes.push_back(i);

	int lastIndex = n-1;
	for (int i = 0; i < m; i++) {
		int randomIndex = (rand() % lastIndex) + 1;
		swap(indexes,randomIndex,lastIndex--);
	}

	// Last m indexes are what we want:
	vector<int> sol;
	for (int i = 0; i < m; i++) sol.push_back(A[indexes[n-1-i]]);

	return sol;
}

void print(vector<int> A, vector<int> sol, int n, int m) {
	cout << "Random " << m << " elements from the array { ";
	for (int i = 0; i < A.size(); i++) cout << A[i] << " ";
	cout << "} are: { ";
	for (int i = 0; i < sol.size(); i++) cout << sol[i] << " ";
	cout << "}\n";
}

int main() {

	srand (time(NULL));

	vector<int> A = {5,8,1,4,14,93,58,19,51};

	int n = A.size();
	int m = 3;

	vector<int> sol = randomSet(A,n,m);

	print(A,sol,n,m);

	return 0;
}


