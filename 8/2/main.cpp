#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

int numberOfWays(int steps) {
	int *numWays = new int[steps];

	if (steps <= 0) return 0;
	else if (steps == 1) return 1;
	else if (steps == 2) return 2;
	else if (steps == 3) return 4;

	numWays[0] = 1;
	numWays[1] = 2;
	numWays[2] = 4;

	for (int i = 3; i < steps; ++i) {
		numWays[i] = (numWays[i-1] + numWays[i-2] + numWays[i-3]);
	}

	int result = numWays[steps-1];
	delete [] numWays;

	return result;
}

void printMatrixInt(int **matrix, int r, int c) {
	cout << "MatrixInt: " << endl;

	fori(0,r) {
		forj(0,c) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printMatrix(bool **matrix, int r, int c) {
	cout << "Matrix: " << endl;

	fori(0,r) {
		forj(0,c) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool **gridPath(bool **grid, int r, int c) {
	
	// Initialize path:
	bool **path = new bool* [r];
	for (int i = 0; i<r;i++) path[i] = new bool[c];
	
	// Initialize parent pointers:
	int **parentI = new int* [r];
	for (int i = 0; i<r;i++) parentI[i] = new int[c];
	int **parentJ = new int* [r];
	for (int i = 0; i<r;i++) parentJ[i] = new int[c];

	fori(0,r) {
		forj(0,c) {
			path[i][j] = false;
			parentI[i][j] = 0;
			parentJ[i][j] = 0;
			
		}
	}
	
	if (!grid[0][0]) return path;

	// Assume matrix[0][0] is where we begin: (upper left corner)
	path[0][0] = true;

	for (int j=1; j < c; j++) {
		path[0][j] = (path[0][j-1] && grid[0][j]);
		if (path[0][j]) parentJ[0][j] = j-1;
	}
	for (int i=1; i < r; i++) {
		path[i][0] = (path[i-1][0] && grid[i][0]);
		if (path[i][0]) parentI[i][0] = i-1;
	}
	for (int i=1; i < r; i++) {
		for (int j = 1; j < c; j++) {
			path[i][j] = ((path[i-1][j] || path[i][j-1]) && grid[i][j]);
			if (path[i][j]) {
				if (path[i-1][j]) {
					parentI[i][j] = i-1;
					parentJ[i][j] = j;
				} else {
					parentI[i][j] = i;
					parentJ[i][j] = j-1;

				}
			}
		}
	}
	
	if (!path[r-1][c-1]) return path;

	stack<int> I, J;
	I.push(r-1);
	J.push(c-1);
	
	// Extract one path out of the paths:
	int i = r-1, j = c-1;
	while (i != 0 || j != 0) {
		int oldI = i, oldJ = j;
		i = parentI[oldI][oldJ];
		j = parentJ[oldI][oldJ];
		
		I.push(i);
		J.push(j);
	}

	while (!I.empty()) {
		cout << "(" << I.top() << "," << J.top() << ")";
		I.pop(); J.pop();
		if (I.size() != 0) cout << "->";
	}
	cout << endl;


	return path;
}




int main() {


	// Build 2d matrix:
	int r = 3, c = 4;


	bool **matrix = new bool* [r];
	for (int i=0; i < r;i++)
		matrix[i] = new bool[c];

	// Assign values to matrix:
	fori(0,r) {
		forj(0,c) {
			matrix[i][j] = true;
		}
	}

	// Assign a few values that cannot be reached:
	matrix[2][0] = false;
	matrix[1][1] = false;
	matrix[1][2] = false;
	matrix[2][2] = false;

	printMatrix(matrix, r,c);
	cout << endl << endl;

	bool **path = gridPath(matrix, r, c);

	printMatrix(path, r,c);
	
	// Delete matrix:
	for (int i = 0; i < r; i++) delete [] matrix[i];
	delete [] matrix;

	return 0;
}


