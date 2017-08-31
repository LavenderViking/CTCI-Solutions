#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>
using namespace std;


struct Position {
	int row, col;
	Position(int r, int c) : row{r}, col{c} {}
};

bool operator == (Position const& lhs, Position const& rhs) {
    return (lhs.row == rhs.row) && 
           (lhs.col == rhs.col);
}

enum Direction {left,up,right,down};

class Orientation {

	Direction dir = Direction::right;

	public:
	
	void turn(bool clockwise) {
		if (dir == Direction::left) {
			dir = clockwise ? Direction::up : Direction::down;
		} else if (dir == Direction::up) {
			dir = clockwise ? Direction::right : Direction::left;
		} else if (dir == Direction::right) {
			dir = clockwise ? Direction::down : Direction::up;
		} else {
			dir = clockwise ? Direction::left : Direction::right;
		}
	}

	Direction getDirection() {
		return dir;
	}
};


class Ant {
	Position position = Position(0,0);
	Orientation orientation = Orientation();

	public:
	void turn(bool clockwise) {
		orientation.turn(clockwise);
	}

	void move() {
		if (orientation.getDirection() == Direction::left) {
			position.col--;
		} else if (orientation.getDirection() == Direction::right) {
			position.col++;
		} else if (orientation.getDirection() == Direction::up) {
			position.row--;
		} else {
			position.row++;
		}
	}

	Position getPosition() {
		return position;
	}
};

struct Hash {
   size_t operator() (const Position &p) const {
	return p.row * 31 ^ p.col;
   }
};

class Board {

	private:
	unordered_set<Position,Hash> blacks;

	Ant ant;
	Position topLeftCorner = Position(0,0);
	Position bottomRightCorner = Position(0,0);

	void flip() {
		Position pos = ant.getPosition();
		if (blacks.count(pos) > 0) blacks.erase(pos);
		else blacks.insert(pos);
	}

	void ensureFit(Position pos) {
		int row = pos.row, col = pos.col;

		topLeftCorner.row = min(row,topLeftCorner.row);
		topLeftCorner.col = min(col,topLeftCorner.col);

		bottomRightCorner.row = max(row,bottomRightCorner.row);
		bottomRightCorner.col = max(col,bottomRightCorner.col);
	}

	public:
	void move() {
		ant.turn(blacks.count(ant.getPosition()) == 0);
		flip();
		ant.move();
		ensureFit(ant.getPosition());
	}

	void print(int k) {
		
		for (int i = 0; i < k; i++) move();

		int rowMin = topLeftCorner.row;
		int rowMax = bottomRightCorner.row;

		int colMin = topLeftCorner.col;
		int colMax = bottomRightCorner.col;

		for (int r = rowMin; r <= rowMax; r++) {
			for (int c = colMin; c <= colMax; c++) {
				if (blacks.count(Position(r,c)) > 0) {
					cout << "B";
				} else {
					cout << "W";
				}
			}
			cout << endl;
		}

	}
};



int main() {

	Board board;

//	int N; cin >> N;

	board.print(500);

	return 0;
}


