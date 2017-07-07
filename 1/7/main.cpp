#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>

using namespace std;

void rotate(int **A, int N);

void printMatrix(int **A, int N);

int main() {

	ifstream file;
	file.open("input.txt");

	clock_t begin = clock();

	// Read in size of matrix:
	int N;
	file >> N;

	// Initialize 2d array for matrix:
	int **arr = new int* [N];
	for (int i = 0; i < N; i++) {
		arr[i] = new int[N];
	} 

	// Read in matrix into 2d array:
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			file >> arr[i][j];
		}
	}

	rotate(arr, N);
	
	printMatrix(arr,N);

	clock_t end = clock();

	clock_t timeElapsed = ( end - begin );
	
	//cout << float( timeElapsed * 1000) / CLOCKS_PER_SEC << " ms" << endl;

	file.close();

	return 0;
}


void printMatrix(int **A, int N) {
	cout << "MATRIX:\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}

}

void rotate(int **A, int N) {

	int temp;
	// Traverse matrix layer by layer:
	// l = layer
	for (int l = 0; l < N/2; l++) {
		for (int elem = l; elem < N - l - 1; elem++) {
			int temp = A[l][elem];
			A[l][elem] = A[N-elem-1][l];
			A[N-elem-1][l] = A[N-l-1][N-elem-1];
			A[N-l-1][N-elem-1] = A[elem][N-l-1];
			A[elem][N-l-1] = temp;
		}
	}
}





