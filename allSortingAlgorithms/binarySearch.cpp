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

int binarySearch(int *A, int size, int x) {
	int lo = 0;
	int hi = size-1;
	int mid;

	while (lo <= hi) {
		mid = (lo+hi)/2;

		if (A[mid] == x) return mid;
		else if (x < A[mid]) hi = mid-1;
		else lo = mid;
	}

	return -1; // Not found:
}

void swap(int *A, int i, int j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

int partition(int *A, int size, int left, int right) {
	int pivot = A[(left+right)/2];

	while (left <= right) {
		while (A[left] < pivot) left++;
		while (A[right] > pivot) right--;

		if (left <= right) swap(A,left++,right--);
	}

	return left;
}

void quickSort(int *A, int size, int left, int right) {
	int index = partition(A,size,left,right);

	if (left < index - 1) quickSort(A,size,left,index-1);
	if (right > index) quickSort(A,size,index,right);
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

	int index = binarySearch(A,size,4);
	quickSort(A,size,0,size-1);

	cout << "Index = " << index << endl;
	printArray(A,size,"After");

	delete [] A;

	file.close();

	return 0;
}




