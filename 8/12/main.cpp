#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <set>
#include <unordered_map>
#include <vector>
#include <array>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

// Size of chess board:
//#define N 8

int N=8;

bool diagonalOK(bool **board, int row, int col, int rowInc, int colInc) {
	while (row >= 0 && row < N && col >= 0 && col < N) {
		if (board[row][col]) {
			return false;
		}
		row += rowInc;
		col += colInc;
	}
	return true;
}

bool diagonalsOK(bool **board, int row, int col) {
	return diagonalOK(board, row, col,  1,  1) && 
	       diagonalOK(board, row, col, -1,  1) && 
	       diagonalOK(board, row, col,  1, -1) && 
	       diagonalOK(board, row, col, -1, -1);
}

bool rowOK(bool **board, int row) {
	for (int j = 0; j < N; j++) {
		if (board[row][j]) return false;
	}
	return true;
}

bool colOK(bool **board, int col) {
	for (int i = 0; i < N; i++) {
		if (board[i][col]) return false;
	}
	return true;
}

bool queenOK(bool **board, int row, int col) {
	return rowOK(board,row) && colOK(board,col) && diagonalsOK(board,row,col);
}

void printBoards(vector<bool **> boards) {
	for (int board = 0; board < boards.size(); board++) {
		cout << "Board " << board+1 << ":" << endl;

		fori(0,N) {
			forj(0,N) {
				cout << boards[board][i][j] << " ";
			}	
			cout << endl;
		}
		cout << endl;
	}

	cout << "Total number of solutions: " << boards.size() << endl;
}

// Initializes a NxN chessboard with false values which means no queens places anywhere:
bool** initializeBoard() {
	bool** board = new bool*[N];
	fori(0,N) board[i] = new bool[N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << "here <" << endl;
			board[i][j] = false;
			cout << "here <" << endl;
		}
	}
	return board;
}

// Backtracks the queen by trying the previous column and increasing rows recursively.
// If it is unable to backtrack it returns false. Otherwise return true on success.
bool backtrack(bool** &board, int &row, int &col) {
	while (row == N) {
		// Go back one column:
		col--;

		fori(0,N) {
			// Assigning row one lower than it was previously assigned:
			if (board[i][col]) row = i+1;
			// Remove queen from previous placement:
			board[i][col] = false;
		}

		
		if (col == 0 && row == N) return false;
	}
	return true;
}

// This solution uses O(N^2) space:
vector<bool**> queens() {

	bool** board = initializeBoard();

	vector<bool**> solutions;

	int row = 0, col = 0;
	cout << "here" <<endl;
	while (!(row == N && col == 0)) {
		// Backtrack if we can't place the queen:
		if (row == N) {
			if (!backtrack(board,row,col)) break;
			continue;
		}

		// Try to place queen on (row,col):
		if (queenOK(board,row,col)) {
			board[row][col] = true;
		
			// If we are at the last column then we add this board to our solution:	
			if (col == N-1) {
				solutions.push_back(board);
				board[row][col] = false;
			} else {
				// Continue on to the next column:
				col++;
				row = -1; // Will be 0 after row++ below:
			}
		}
		row++;
	}

	fori(0,N) delete [] board[i];
	delete [] board;

	return solutions;
}

int ABS(int n) {
	if (n < 0) n = -n;
	return n;
}

bool isValid(int N, int rowNew, vector<int> rows) {

	int colNew = rows.size();

	for (int colOld = 0; colOld < rows.size(); colOld++) {
		int rowOld = rows[colOld];

		// Check if rowNew collides with rowOld:
		if (rowNew == rowOld) return false;

		// Check diagonal:
		int rowDist = ABS(rowNew-rowOld);
		int colDist = ABS(colNew - colOld);

		if (rowDist == colDist) return false;
	}

	return true;
}

void queens2(int N, int col, vector<int> rows, vector<vector<int>> &results) {
	cout << "Inside queens with col = " << col << endl;
	fori(0,rows.size()) {
		cout << rows[i] << " ";
	}
	cout << endl;
	if (col == N) {
		// Configuration was okay:
		results.push_back(rows);
	} else {
		// Check if it is okay to add a queen in each row in the given column:
		for (int row = 0; row < N; row++) {
			if (isValid(N,row,rows)) {
				cout << "Pushing " << row << endl;
				rows.push_back(row);
				queens2(N,col+1,rows,results);
				rows.erase(rows.end()-1);
			}
		}
	}
}

// This solution uses O(N) space because it only stores which row each queen is at:
vector<vector<int>> queens2(int N) {
	vector<vector<int>> results;
	queens2(N,0,vector<int>(),results);
	return results;
}

void printQueens(vector<vector<int>> queens) {
	for (int sol = 0; sol < queens.size(); sol++) {
		cout << "Solution " << sol << endl;

		for (int row = 0; row < queens[sol].size(); row++) {
			cout << queens[sol][row] << " ";
		}
		cout << endl;
	}
}

int main() {

//	vector<bool**> solutions = queens();

//	printBoards(solutions);

	vector<vector<int>> queensSolutions = queens2(N);

	printQueens(queensSolutions);

	return 0;
}
































