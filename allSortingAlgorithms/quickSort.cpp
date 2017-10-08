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

int partition(int *A, int left, int right) {
	int pivot = A[(left+right)/2];

	while (left <= right) {
		while (A[left] < pivot) left++;
		while (A[right] > pivot) right--;

		if (left <= right) swap(A[left++],A[right--]);
	}

	return left;
}

void quickSort(int *A, int left, int right) {
	int index = partition(A,left,right);

	if (left < index - 1) quickSort(A,left,index-1);
	if (right > index) quickSort(A,index,right);
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

	quickSort(A,0,size-1);

	printArray(A,size,"After");

	delete [] A;

	file.close();

	return 0;
}




