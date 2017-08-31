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
#include <vector>
#include <array>
using namespace std;

struct Point {
	double x,y;
	Point(double a, double b) : x{a}, y{b} {}
};


// (0,0) is defined to be in the lower left corner:
// Square defined by lower left point and size:
class Square {
	Point lowerLeft = Point(0.0,0.0);
	Point middle = Point(0.0,0.0);
	double size = 0.0;

	public:
	Square(Point a, double s) {
		lowerLeft = a;
		size = s;

		middle = Point(a.x+size/2.0,a.y+size/2.0);
	}

	double getSize() { return size; }
	Point getMiddle() { return middle; }
	Point getLowerLeft() { return lowerLeft; }
};


class Line {
	Point p = Point(0.0,0.0);
	double slope = 0.0;
	bool infiniteSlope = false;
	
	public:
	Line(Point a, Point b) {
		p = a;
		if (a.x == b.x) {
			infiniteSlope = true;
		} else {
			slope = ((b.y-a.y)/(b.x-a.x));
		}
	}

	void printLine() {
		printf("Point = (%.2f,%.2f)\nSlope = %.2f\n",p.x,p.y,slope);
	}
};

void printPoint(Point a) {
	printf("(%.2f,%.2f)\n",a.x,a.y);
}


// Returns the point where the line that goes through the middle of 
// square1 and square2 intertercect square 1:
Point extend(Point mid1, Point mid2, int size) {

	double xdir = mid1.x < mid2.x ? -1 : 1;
	double ydir = mid1.y < mid2.y ? -1 : 1;

	// If squares have the same x coordinate then there is no slope to calculate
	// and the line goes through the mid y coordinates:
	if (mid1.x == mid2.x) return Point(mid1.x,mid1.y + ydir * size/2.0);

	double slope = abs((mid2.y - mid1.y) / (mid2.x - mid1.x));
	double x1 = 0.0, y1 = 0.0;

	if (abs(slope) == 1) {
		// Line hits the corner:
		return Point(mid1.x+xdir*size/2.0,mid1.y+ydir*size/2.0);
	} else if (abs(slope) < 1) {
		// Line hits vertical edge and hence x coordinate will be on that vertical line:
		x1 = mid1.x + xdir * size / 2.0;
		// We know x1 and that slope = (ymid-y1) / (xmid-x1):
		y1 = mid1.y - slope * (mid1.x - x1);
	} else {
		// Line hits horizontal edge and hence y coordinate will be on that horizontal line:
		y1 = mid1.y + ydir * size / 2.0;
		// We know y1 and that y1/x1 = mid1.y/mid1.x
		x1 = mid1.x - slope * (mid1.y - y1);
	}

	return Point(x1,y1);
}

Line bisectSquares(Square a, Square b) {

	Point p1 = extend(a.getMiddle(),b.getMiddle(),a.getSize());
	Point p2 = extend(b.getMiddle(),a.getMiddle(),b.getSize());

	cout << "Left = "; printPoint(p1);
	cout << "Right = "; printPoint(p2);

	return Line(p1,p2);
}

void printSquares(Square a, Square b) {

	char M[10][10];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			M[i][j] = ' ';
		}
	}

	for (int i = a.getLowerLeft().x; i < a.getLowerLeft().x + a.getSize(); i++) {
		for (int j = a.getLowerLeft().y; j < a.getLowerLeft().y + a.getSize(); j++) {
			M[j][i] = 'a';
		}
	}

	for (int i = b.getLowerLeft().x; i < b.getLowerLeft().x + b.getSize(); i++) {
		for (int j = b.getLowerLeft().y; j < b.getLowerLeft().y + b.getSize(); j++) {
			M[j][i] = 'b';
		}
	}

	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {

	Point a = Point(0.0,0.0);

	Point b = Point(4.0,0.0);

	Square s1 = Square(a,4.0);
	Square s2 = Square(b,5);

	Line l = bisectSquares(s1,s2);

	l.printLine();

	printSquares(s1,s2);

	return 0;
}


