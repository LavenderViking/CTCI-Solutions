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
#include <random>
#include <time.h> 

using namespace std;

int rand5() { return rand() % 5; }

int rand7() {

	int row = rand5(), col = rand5();

	// Calculate value from 2d matrix:
	int i = 0, j = 0;

	int val = 0;		
	
	while (true) {
		for (int k = 0; k < 3; k++) {
			if (i == row && j == col) return val;
			if (j < 4) j++;
			else {
				j = 0;
				i++;
			}
		}
		val++;
	}

	return -1;
}



int main() {

	srand (time(NULL));

	int A[7];

	for (int i = 0; i < 10000; i++) {
		int randomNumber = rand7();
		//cout << randomNumber << endl;
		A[randomNumber]++;
	}

	for (int i =0; i < 7; i++) cout << A[i] << endl;

	return 0;
}


