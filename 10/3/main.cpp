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

// 2 2 2 3 4 2

int searchRotated(int *A, int size, int x, int lo, int hi) {
	int mid = (lo+hi)/2;

	if (A[mid] == x) return mid;

	if (hi < lo) return -1;

	// If [mid:right] is increasing then we check if x is between those and if not we recurse on left:
	// If [left:mid-1] is increasing then we check if x is between those and if not we recurse on right:
	// Else x can be in both halves:

	if (A[mid] < A[hi] && A[mid] < x && x <= A[hi]) return searchRotated(A,size,x,mid+1,hi);
	else if (A[lo] < A[mid] && A[lo] <= x && x < A[hi]) return searchRotated(A,size,x,lo,mid-1);
	else {
		if (A[lo] == A[mid] && A[mid] != A[hi]) return searchRotated(A,size,x,mid+1,hi);
		else if (A[mid] == A[hi] && A[lo] != A[mid]) return searchRotated(A,size,x,lo,mid-1);
		else {
			int leftRes = searchRotated(A,size,x,lo,mid-1);
			if (leftRes != -1) return leftRes;
			
			int rightRes = searchRotated(A,size,x,mid+1,hi);
			return rightRes;
		}
	}
}

int main() {

	ifstream file;
	file.open("input.txt");

	int size; file >> size;

	int *A = new int[size];

	fori(0,size) file >> A[i];

	int searchFor = 3;

	int res = searchRotated(A,size,searchFor,0,size-1);

	cout << "A = " << res;
	
	file.close();

	return 0;
}


