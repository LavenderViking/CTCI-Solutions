#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
using namespace std;

// Move all plates from s1 to s2:
void towerOfHanoi(int N, stack<int> &source, stack<int> &target, stack<int> &auxillary, int &moves) {
	
	if (N > 0) {
		moves++;
		towerOfHanoi(N-1, source, auxillary, target, moves);

		int value = source.top();
		source.pop();

		target.push(value);

		towerOfHanoi(N-1, auxillary, target, source, moves);
	}
}

int main() {

	stack<int> source;
	for (int i = 10; i > 0; i--) source.push(i);

	stack<int> target, auxillary;

	int moves = 0;

	towerOfHanoi(10,source,target,auxillary,moves);

	cout << "Total number of moves = " << moves << endl;

	while (!target.empty()) {
		int val = target.top();
		target.pop();
		cout << val << " ";
	}
	cout << endl;
	
	return 0;
}

