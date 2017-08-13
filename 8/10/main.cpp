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


enum Color { Black, White, Red, Green };


void paintFill(Color **screen, int size, int row, int col, Color oColor, Color nColor) {

	if (row < 0 || col < 0 || row >= size || col >= size) return;

	if (screen[row][col] == oColor) {
		screen[row][col] = nColor;

		// Recurse:
		paintFill(screen, size, row-1, col, oColor, nColor);
		paintFill(screen, size, row+1, col, oColor, nColor);
		paintFill(screen, size, row, col-1, oColor, nColor);
		paintFill(screen, size, row, col+1, oColor, nColor);
	}
}

void paintFill(Color **screen, int size, int row, int col, Color nColor) {
	if (screen[row][col] == nColor) return;

	return paintFill(screen, size, row, col, screen[row][col], nColor);
}


void printScreen(Color **screen, int size) {
	cout << "Screen:" << endl;

	fori(0,size) {
		forj(0,size) {
			cout << screen[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {

	const int size = 5;

	Color **screen = new Color*[size];
	fori(0,size) screen[i] = new Color[size];

	// First row:
	fori(0,size) screen[0][i] = Color::Black;

	// First col:
	fori(0,size) screen[i][0] = Color::Black;
	
	// Last row:
	fori(0,size) screen[size-1][i] = Color::Black;

	// Last col:
	fori(0,size) screen[i][size-1] = Color::Black;

	// Middle:
	screen[1][1] = White;
	screen[1][2] = White;
	screen[1][3] = White;
	screen[2][1] = White;
	screen[2][2] = White;
	screen[2][3] = White;
	screen[3][1] = White;
	screen[3][2] = White;
	screen[3][3] = White;

	printScreen(screen, size);

	paintFill(screen, size, 2, 2, Red);

	printScreen(screen, size);

	paintFill(screen, size, 0, 4, Green);

	printScreen(screen, size);
	return 0;
}

