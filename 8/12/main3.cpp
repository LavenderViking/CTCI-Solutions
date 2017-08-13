#include <iostream>
#include <vector>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

class Solution {
public:
    bool diagonalOK(bool **board, int row, int col, int rowInc, int colInc, int N) {
        while (row >= 0 && row < N && col >= 0 && col < N) {
                if (board[row][col]) {
                        return false;
                }
                row += rowInc;
                col += colInc;
        }
        return true;
    }

    bool diagonalsOK(bool **board, int row, int col, int N) {
            return diagonalOK(board, row, col,  1,  1, N) && 
                   diagonalOK(board, row, col, -1,  1, N) && 
                   diagonalOK(board, row, col,  1, -1, N) && 
                   diagonalOK(board, row, col, -1, -1, N);
    }

    bool rowOK(bool **board, int row, int N) {
            for (int j = 0; j < N; j++) {
                    if (board[row][j]) return false;
            }
            return true;
    }

    bool colOK(bool **board, int col, int N) {
            for (int i = 0; i < N; i++) {
                    if (board[i][col]) return false;
            }
            return true;
    }

    bool queenOK(bool **board, int row, int col, int N) {
            return rowOK(board,row, N) && colOK(board,col, N) && diagonalsOK(board,row,col, N);
    }

    void printBoards(vector<bool **> boards, int N) {
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
    bool** initializeBoard(int N) {
            bool** board = new bool*[N];
            fori(0,N) board[i] = new bool[N];
            for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                            board[i][j] = false;
                    }
            }
            return board;
    }

    // Backtracks the queen by trying the previous column and increasing rows recursively.
    // If it is unable to backtrack it returns false. Otherwise return true on success.
    bool backtrack(bool** &board, int &row, int &col, int N) {
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

    vector<bool**> queens(int N) {

        bool** board = initializeBoard(N);

        vector<bool**> solutions;

        int row = 0, col = 0;
        
        while (!(row == N && col == 0)) {
                // Backtrack if we can't place the queen:
                if (row == N) {
                        if (!backtrack(board,row,col,N)) break;
                        continue;
                }

                // Try to place queen on (row,col):
                if (queenOK(board,row,col, N)) {
                        board[row][col] = true;

                        // If we are at the last column then we add this board to our solution: 
                        if (col == N-1) {
                            
                                bool **board2 = initializeBoard(N);
                                fori(0,N) {
                                    forj(0,N) {
                                        board2[i][j] = board[i][j];
                                    }
                                }
                            
                                solutions.push_back(board2);
                            
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
    
    vector<vector<string>> configurations(vector<bool**> queens, int N) {
        
        vector<vector<string>> configs;
        
        for (int board = 0; board < queens.size(); board++) {
            vector<string> v;
            fori(0,N) {
                string s;
                forj(0,N) {
                    if (queens[board][i][j]) {
                        s += 'Q';
                    } else {
                        s += '.';
                    }
                }
                v.push_back(s);
            }
            configs.push_back(v);
        }
        return configs;
    }
    
    vector<vector<string>> solveNQueens(int N) {
        return configurations(queens(N),N);
    }
};

int main() {
	vector<vector<string>> solutions = Solution().solveNQueens(8);

	return solutions.size();
}
