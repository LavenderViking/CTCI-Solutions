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



int mostAlive(vector<array<int,2>> years) {

	int size = 2000-1900+1;

	int *born = new int[size]();
	int *dead = new int[size]();

	for (int i = 0; i < years.size(); i++) {
		int bornYear = years[i][0];
		int deadYear = years[i][1];

		born[bornYear-1900]++;
		dead[deadYear-1900]++;
	}

	int aliveMax = 0, alive = 0;

	for (int i = 0; i < size; i++) {
		alive += born[i];
		if (i != 0) alive -= dead[i-1];

		if (alive > aliveMax) aliveMax = alive;
	}
	
	delete [] born;
	delete [] dead;

	return aliveMax;
}



int main() {

	vector<array<int,2>> years = {{1908,1909},{1900,1950},{1930,1940},{1945,1970},{1960,1970},{1980,1999}};

	cout << "Max alive: " << mostAlive(years) << endl;
	

	return 0;
}


