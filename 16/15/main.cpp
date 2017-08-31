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


int colorCode(char color) {

	switch(color) {
		case 'R': return 0;
		case 'Y': return 1;
		case 'G': return 2;
		case 'B': return 3;
	}

	return -1;
}


void masterMind(string guess, string solution) {

	if (guess.size() != solution.size()) return;

	int hits = 0;

	bool colors[4] = {false};
	bool pHits[4] = {false};

	for (int i = 0; i < guess.size(); i++) {
		if (guess[i] == solution[i]) {
			hits++;
			solution[i] = ' ';
			guess[i] = ' ';
		} else {
			colors[colorCode(solution[i])] = true;
		}
	}

	for (int i = 0; i < guess.size(); i++) {
		if (guess[i] == ' ') continue;

		if (!pHits[colorCode(guess[i])]) {
			pHits[colorCode(guess[i])] = true;
		}
	}

	int pseudoHits = 0;

	for (int i = 0; i < 4; i++) if (pHits[i] && colors[i]) pseudoHits++;

	cout << "Hits = " << hits << " pHits = " << pseudoHits << endl;
}


int main() {
	
	string guess = "GGRR", solution = "RGBY";

	masterMind(guess,solution);

	return 0;
}


