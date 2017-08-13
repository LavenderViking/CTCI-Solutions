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

void mergeSorted(int *A, int *B, int elemA, int elemB);



// A has large enough buffer to hold B's elements:
void sortedMerge(int *A, int *B, int elemA, int elemB) {
	int sizeA = elemA + elemB;
	int sizeB = elemB;

	// Shift A's elements back by elemB number of elements:
	for (int i = sizeA-1; i >= elemB; i--) A[i] = A[i-sizeB];

	int indexA = elemB, indexB = 0;

	for (int i = 0; i < sizeA; i++) {
		if (indexA == sizeA) A[i] = B[indexB++];
		else if (indexB == sizeB) A[i] = A[indexA++];
		else {
			A[i] = A[indexA] < B[indexB] ? A[indexA++] : B[indexB++];
		}
	}
}



int main() {

	ifstream file;
	file.open("input.txt");

	int elemA, elemB;
	file >> elemA >> elemB;

	int *A = new int [elemA+elemB];
	int *B = new int [elemB];

	fori(0,elemA) file >> A[i];
	fori(0,elemB) file >> B[i];

//	mergeSorted(A,B,elemA,elemB);
	sortedMerge(A,B,elemA,elemB);

	cout << "Printing A\n";
	fori(0,elemA+elemB) {
		cout << A[i];
		cout << " ";
	}
	
	file.close();

	return 0;
}






void mergeSorted(int *A, int *B, int elemA, int elemB) {
	int sizeA = elemA + elemB;

	for (int i = elemA-1; i>=0; --i) {
		A[i+elemB] = A[i];
	}

	int indexA = elemB, indexB = 0;

	// Did not do if else if else and hence was overwriting. Also A goes with indexA and B with indexB
	for (int i = 0; i < sizeA; ++i) {
		if (indexA == sizeA) {
			A[i] = B[indexB++];
		}
		else if (indexB == elemB) {
			A[i] = A[indexA++];
		} else {
			A[i] = A[indexA] < B[indexB] ? A[indexA++] : B[indexB++];
		}
	}
}
