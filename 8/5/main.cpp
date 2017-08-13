#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


// Uses recursion to multiply numbers n1 and n2:
int recursiveMultiply(int n1, int n2, int *memo) {
	
	int smaller = n1 < n2 ? n1 : n2;
	int larger = n1 < n2 ? n2 : n1;

	if (smaller == 1) return larger;
	else if (memo[smaller-1] > 0) return memo[smaller-1];
	
	memo[smaller-1] = recursiveMultiply(smaller>>1,larger, memo)<<1;

	if (smaller % 2 == 1) memo[smaller-1] += larger;
	
	return memo[smaller-1];
}

int main() {

	int n1 = 15, n2 = 13;

	int smaller = n1 < n2 ? n1 : n2;

	int *memo = new int[smaller];
	for (int i = 0; i < smaller; i++) memo[i] = 0;

	cout << n1 << "*" << n2 << "=" << recursiveMultiply(n1,n2,memo) << endl;

	delete [] memo;

	return 0;
}

