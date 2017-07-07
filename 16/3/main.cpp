#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

typedef unordered_map<string,int> HT;

struct Point {
	double x,y;

	Point(double a, double b) : x{a}, y{b} {}

	void setPoint(double a, double b) {
		x = a;
		y = b;
	}
};

struct Line {
	double slope;
	double yintercept;

	Line(Point first, Point second) {
		double deltaX = second.x - first.x;
		double deltaY = second.y - first.y;

		if (deltaX == 0) slope = INT_MAX;
		else slope = deltaY / deltaX;

		yintercept = second.y - slope * second.x;
	}
};

void swap(Point a, Point b) {
	Point temp = a;

	a.setPoint(b.x, b.y);
	b.setPoint(temp.x, temp.y);
}

// Check if b is between a and c:
bool isBetween(double a, double b, double c) {
	return b >= a && b <= c;
}

Point intersection(Point a1, Point a2, Point b1, Point b2) {
	
	// Swap points if in reverse order:
	if (a1.x > a2.x) swap(a1,a2);
	if (b2.x > b2.x) swap(b1,b2);
	if (a1.x > b1.x) {
		swap(a1,b1);
		swap(a2,b2);
	}

	Line a(a1,a2);
	Line b(b1,b2);

	// Lines are parallel:
	if (a.slope == b.slope) {
		if (a.yintercept == b.yintercept) {
			if (isBetween(a1.x, a2.x, b1.x)) {
				return a2;
			}
		}
		return Point(0,0);
	}

	// Lines are not parallel:
	double x = (b.yintercept - a.yintercept) / (a.slope - b.slope);
	double y = x * a.slope + a.yintercept;

	// a.yintercept + x*a.slope = b.yintercept + x*b.slope
	// x* (a.slope - b.slope) = yintercept (b - a)

	Point intersection(x,y);

	if (isBetween(a1.x, x, a2.x) && isBetween(b1.x, x, b2.x)) {
		return intersection;
	}

	return Point(0,0);
}

int main() {

	ifstream file;
	file.open("input.txt");

	int x,y;
	file >> x >> y;

		


	file.close();

	return 0;
}


