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


int getPondSize(vector<vector<int>> &pond, int rows, int cols, int rowIndex, int colIndex) {
	
	if (rowIndex < 0 || rowIndex == rows || colIndex < 0 || colIndex == cols) return 0;

	int pondSize = 0;

	if (pond[rowIndex][colIndex] == 0) {

		pond[rowIndex][colIndex] = -1;

		for (int dr = -1; dr <= 1; dr++) {
			for (int dc = -1; dc <= 1; dc++) {
				if (!(dr == 0 && dc == 0))pondSize += getPondSize(pond,rows,cols,rowIndex+dr,colIndex+dc);
			}
		}

		return 1 + pondSize;

		/*
		int left = getPondSize(pond,rows,cols,rowIndex,colIndex-1);
		int right = getPondSize(pond,rows,cols,rowIndex,colIndex+1);
		int up = getPondSize(pond,rows,cols,rowIndex-1,colIndex);
		int down = getPondSize(pond,rows,cols,rowIndex+1,colIndex);
		int upperLeft = getPondSize(pond,rows,cols,rowIndex-1,colIndex-1);
		int upperRight = getPondSize(pond,rows,cols,rowIndex-1,colIndex+1);
		int lowerLeft = getPondSize(pond,rows,cols,rowIndex+1,colIndex-1);
		int lowerRight = getPondSize(pond,rows,cols,rowIndex+1,colIndex+1);

		return 1 + left + right + up + down + upperLeft + upperRight + lowerLeft + lowerRight;*/
	}

	return pondSize;
}



vector<int> pondSizes(vector<vector<int>> pond) {

	int rows = pond.size();
	int cols = pond[0].size();

	vector<int> res;

	int indexRow = 0, indexCol = 0;

	while (true) {
		
		if (pond[indexRow][indexCol] == 0) {
			res.push_back(getPondSize(pond,rows,cols,indexRow,indexCol));
		}
		
		if (indexCol == cols - 1) {
			indexCol = 0;
			indexRow++;
		} else {
			indexCol++;
		}

		if (indexRow == rows - 1 && indexCol == cols - 1) break;
	}

	return res;
}






int main() {
	
	vector<vector<int>> pond;

	pond.push_back({0,2,1,0});
	pond.push_back({0,1,0,1});
	pond.push_back({1,1,0,1});
	pond.push_back({0,1,0,1});

	vector<int> sizes = pondSizes(pond);

	for (int i = 0; i < sizes.size(); i++) cout << sizes[i] << " ";
	cout << endl;

	return 0;
}


