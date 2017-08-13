#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

int numberOfWays(int steps) {
	int *numWays = new int[steps];

	if (steps <= 0) return 0;
	else if (steps == 1) return 1;
	else if (steps == 2) return 2;
	else if (steps == 3) return 4;

	numWays[0] = 1;
	numWays[1] = 2;
	numWays[2] = 4;

	for (int i = 3; i < steps; ++i) {
		numWays[i] = (numWays[i-1] + numWays[i-2] + numWays[i-3]);
	}

	int result = numWays[steps-1];
	delete [] numWays;

	return result;
}


int main() {

	int steps = 12;

	cout << "Numways of " << steps << " is: " << numberOfWays(steps) << endl;

	return 0;
}


