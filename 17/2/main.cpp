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

void swap(vector<int> &cards, int i, int j) {
	--i;--j;
	int temp = cards[i];
	cards[i] = cards[j];
	cards[j] = temp;
}

vector<int> shuffle(int N) {
	
	vector<int> sol;

	for (int i = 1; i <= N; i++) sol.push_back(i);

	int num = N;
	for (int i = 1; i <= N; i++) {
		int randomCard = (rand() % num) + 1;
		swap(sol,randomCard,num--);
	}

	return sol;
}


int main() {

	srand (time(NULL));
	int N = 52;

	vector<int> count = shuffle(N);
	for (int i = 1; i <= N; i++) count[i] = 0;

	for (int i = 1; i <= 5000; i++) shuffle(N);

	for (int i = 0; i < 100000; i++) {
		vector<int> cards = shuffle(N);
		for (int j = 1; j <= N; j++) {
			if (cards[j-1] == 2) count[j-1]++;
		}
	}

	//vector<int> cards = shuffle(N);

	int total = 0;
	for (int i = 0; i < count.size(); i++) total += count[i];

	for (int i = 0; i < count.size(); i++) {
		double perc = 100 * count[i]/(total*1.0);
		cout << perc << " ";
	}

	//for (int i = 0; i < count.size(); i++) cout << count[i] << " ";
	cout << endl;

	return 0;
}


