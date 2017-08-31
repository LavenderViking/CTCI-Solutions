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



class Line {
	double yIntercept = 0.0;
	double slope = 0.0;
	bool infiniteSlope = false;
	double epsilon = 0.0001;
	
	public:
	Line(Point a, Point b) {
		
		bool isAbove = a.x > 0;


		if (a.x == b.x) {
			infiniteSlope = true;
		} else {
			slope = ((b.y-a.y)/(b.x-a.x));
			// (y2-y1)/(x2-0) = slope
			// yIntercept = slope * x2 + y1;
			yIntercept = -slope * a.x + a.y;
		}
	}

	double getEpsilon() { return epsilon; }
	double getSlope() { return slope; }
	double getYintercept() { return yIntercept; }

	void printLine() {
//		printf("Point = (%.2f,%.2f)\nSlope = %.2f\n",p.x,p.y,slope);
	}
};

void printPoint(Point a) {
	printf("(%.2f,%.2f)\n",a.x,a.y);
}

double roundDown(Line line) {

	int r = line.getSlope() / line.getEpsilon();
	return r * line.getEpsilon();
}

unordered_map<string,int> getSlopeFrequency(vector<Point> points) {

	unordered_map<string,int> map;

	for (int i = 0; i < points.size(); i++) {
		for (int j = i+1;j  < points.size(); j++) {
			if (points[i].x == points[j].x) {
				map["x="+to_string(points[i].x)]++;
			} else {
				Line line = Line(points[i],points[j]);

				double slope = roundDown(line);

				double epsilon = line.getEpsilon();
				map["y="+to_string(line.getYintercept())+"slope="+to_string(slope)]++;
				map["y="+to_string(line.getYintercept())+"slope="+to_string(slope+epsilon)]++;
				map["y="+to_string(line.getYintercept())+"slope="+to_string(slope-epsilon)]++;
			}
		}
	}

	return map;
}

string mostFrequentLine(vector<Point> points) {
	unordered_map<string,int> slopeFreq = getSlopeFrequency(points);

	int max = 0;
	string maxString = "";


	for (auto const &it : slopeFreq) {
		if (it.second > max) {
			max = it.second;
			maxString = it.first;
		}
	}
	cout << "\nMAX freq = " << max << endl;
	return maxString;
}

void printPoints(vector<Point> points) {

	for (int y = 9; y >= 0; y--) {
		for (int x = 0; x < 10; x++) {
			bool found = false;
			for (int p = 0; p < points.size(); p++) {
				if (points[p].x == x && points[p].y == y) {
					cout << "X";
					found = true;
				}
			}

			if (!found) cout << " ";
			if (x == 9) cout << "|";
		}
		cout << endl;
	}
	cout << "__________";
}

int main() {

	Point a = Point(0.0,0.0);
	Point b = Point(2.0,2.0);
	Point c = Point(4.0,4.0);
	Point d = Point(7.0,5.0);
	Point e = Point(4.9,9.0);

	vector<Point> points = {a,b,c,d,e};
	
	printPoints(points);

	string bestLine = mostFrequentLine(points);

	cout << bestLine << endl;

	return 0;
}


