#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)


// Merge [lo:mi] and [mi+1:hi]:
void merge(int *A, int *H, int size, int lo, int mid, int hi) {

	// Put right half elements in helper array:
	for (int i = mid+1; i <= hi; i++) H[i] = A[i];
	
	int indexL = lo, indexR = mid+1;

	// Fill in helper array:
	for (int i = lo; i <= hi; i++) {
		if (indexL == mid+1) H[i] = A[indexR++];
		else if (indexR == hi+1) H[i] = A[indexL++];
		else H[i] = A[indexL] < A[indexR] ? A[indexL++] : A[indexR++];
	}

	// Replace A's elements with helper array's elements:
	for (int i = lo; i <= hi; i++) A[i] = H[i];
}

void mergeSort(int *A, int *H, int size, int lo, int hi) {
	if (lo < hi) {
		int mid = (lo + hi) / 2;
		mergeSort(A,H,size,lo,mid);
		mergeSort(A,H,size,mid+1,hi);
		merge(A,H,size,lo,mid,hi);
	}
}

void mergeSort(int *A, int size) {
	int *H = new int[size];
	
	mergeSort(A,H,size,0,size-1);
}

void printArray(int *A, int size, string s) {
	cout << s << ":" << endl;

	for (int i = 0; i < size; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}

int main() {

	ifstream file;
	file.open("input.txt");

	int size;
	file >> size;

	int *A = new int [size];

	fori(0,size) file >> A[i];

	printArray(A,size,"Before");

	mergeSort(A,size);

	printArray(A,size,"After");

	delete [] A;

	file.close();

	return 0;
}




