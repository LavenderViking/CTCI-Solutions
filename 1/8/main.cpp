#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>

using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)
#define fork(a,b) for(int k=a;k<b;k++)

void printMatrix(int **A, int N, int M);
void zeroMatrix(int **A, int N, int M);
void zeroMatrix2(int **A, int N, int M);

int main() {

	ifstream file;
	file.open("input.txt");

	clock_t begin = clock();

	// Read in size of matrix:
	int N;
	file >> N;

	int M;
	file >> M;

	// Initialize 2d array for matrix:
	int **arr = new int* [N];
	for (int i = 0; i < N; i++) {
		arr[i] = new int[M];
	} 

	// Read in matrix into 2d array:
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			file >> arr[i][j];
		}
	}

	zeroMatrix(arr,N,M);
	
	printMatrix(arr,N, M);

	clock_t end = clock();

	clock_t timeElapsed = ( end - begin );
	
	//cout << float( timeElapsed * 1000) / CLOCKS_PER_SEC << " ms" << endl;

	for (int i = 0; i < N; i++) delete [] arr[i];
	delete [] arr;
	
	file.close();

	return 0;
}

// O(1) space
void zeroMatrix2(int **A, int N, int M) {

	// Zero out elements in the copied matrix:
	fori(0,N) {
		forj(0,M) {
			if (A[i][j] == 0) {
				A[i][0] = 0;
				A[0][j] = 0;
			}
		}
	}

	fori(0,N) {
		if (A[i][0] == 0) {
			forj(0,M) {
				A[i][j] = 0;
			}
		}
	}

	forj(0,M) {
		if (A[0][j] == 0) {
			fori(0,N) {
				A[i][j] = 0;
			}
		}
	}
}



// O(N) space
void zeroMatrix(int **A, int N, int M) {

	// Make two arrays to store indexes that will be zeroed:
	int *Ai = new int[N];
	int *Aj = new int[M];

	// Initialize indexes as 1:
	fori(0,N) Ai[i] = 1;
	fori(0,M) Aj[i] = 1;

	// Zero out elements in the copied matrix:
	fori(0,N) {
		forj(0,M) {
			if (A[i][j] == 0) {
				Ai[i] = 0;
				Aj[j] = 0;
			}
		}
	}

	// Check both matrixes:
	fori(0,N) {
		forj(0,M) {
			if (Ai[i] == 0) A[i][j] = 0;
			if (Aj[j] == 0) A[i][j] = 0;
		}
	}
}

void printMatrix(int **A, int N, int M) {
	cout << "MATRIX:\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}

}



