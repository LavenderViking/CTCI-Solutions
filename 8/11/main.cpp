#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;



int numWays(int N) {

	int *DP = new int[N+1];
	for (int i = 0; i <= N; i++) DP[i] = 0;

	for (int i = 0; i <= 4; i++) DP[i] = 1;

	for (int i = 5; i <= N; i++) {
		if (i-5 >= 0)  DP[i] = DP[i] + DP[i-5] + 1;
		if (i-10 >= 0) DP[i] = DP[i] +  1;
		if (i-25 >= 0) DP[i] = DP[i] + 1;
		cout << "DP[" << i << "] :" << DP[i] << endl;
	}

	int returnValue = DP[N];

	delete [] DP;

	return returnValue;
}



int main() {

	int N; cin >> N;

	int num = numWays(N);

	cout << "Number of ways to represent " << N << " is " << num << endl;
	
	return 0;
}


