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

void swap(int *A, int i, int j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

void bubbleSort(int *A, int size) {
	for (int i=0; i < size-1; i++) {
		for (int j=0; j < size-1; j++) {
			if (A[j+1] < A[j]) swap(A,j+1,j);
		}
	}
}

void selectionSort(int *A, int size) {
	fori(0,size) {
		int min = A[i], minIndex = i;
		forj(i+1,size) {
			if (A[j] < min) { min = A[j]; minIndex = j; }
		}
		swap(A,i,minIndex);
	}
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

	selectionSort(A,size);

	printArray(A,size,"After");

	delete [] A;

	file.close();

	return 0;
}




