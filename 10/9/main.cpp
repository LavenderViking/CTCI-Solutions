#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)


vector<vector<int>> createMatrix(int rows, int cols) {
	vector<vector<int>> vec;

	fori(0,rows) {
		vector<int> nums;
		forj(0,cols) {
			nums.push_back(i*3 + j);
		}
		vec.push_back(nums);
	}
	return vec;
}

bool sortedMatrixFind(vector<vector<int>> vec,int target, int rL, int rH, int cL, int cH) {

	int rMid = (rL+rH)/2, cMid = (cL+cH)/2;
	
	int val = vec[rMid][cMid];
	
	if (rL == rH && cL == cH) {
		if (val == target) return true;
		else return false;
	}
	else if (rL == rH && cL+1 == cH) {
		if (vec[rMid][cL] == target && vec[rMid][cH] == target) return true;
		else return false;
	}
	else if (rL+1 == rH && cL == cH) {
		if (vec[rL][cMid] == target && vec[rH][cMid] == target) return true;
		else return false;
	}
	else if (rL+1 == rH && cL+1 == cH) {
		if (vec[rL][cL] == target && vec[rH][cL] == target && vec[rL][cH] == target && vec[rH][cH] == target) return true;
		else return false;
	}
	cout << rL << " " << rH << " " << cL << " " << cH << endl;

	bool upperLeft = false, upperRight = false, lowerLeft = false, lowerRight = false;
	
	if (val == target) return true;
	else {
		upperRight = sortedMatrixFind(vec,target,rL,rMid,cMid,cH);
		lowerLeft = sortedMatrixFind(vec,target,rMid,rH,cL,cMid);

		if (val < target) lowerRight = sortedMatrixFind(vec,target,rMid,rH,cMid,cH);
		if (val > target) upperLeft = sortedMatrixFind(vec,target,rMid,rH,cMid,cH);
	}

	return upperLeft || upperRight || lowerLeft || lowerRight;
}

void printMatrix(vector<vector<int>> M, int size) {
	cout << "Printing matrix:" << endl;
	fori(0,size) {
		forj(0,size) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {

	int size = 6;

	vector<vector<int>> vec = createMatrix(size,size);

	printMatrix(vec,size);

	bool res = sortedMatrixFind(vec,7,0,size-1,0,size-1);	

	cout << "res = " << res << endl;

	return 0;
}


