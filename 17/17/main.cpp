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

int getSquaredSum(int n) {
	int sum = 0;

	for (int i = 1; i <= n; i++) sum += i*i;

	return sum;
}

int getSum(vector<int> A, bool squared) {

	int sum = 0;
	for (int i = 0; i < A.size(); i++) sum += squared ? A[i]*A[i] : A[i];

	return sum;
}

int solveEquation(int a, int b, int c) {

	int d = b*b-4*a*c;
	
	// Figure which solution we will use:
	int numerator1 = -b - sqrt(d);
	int numerator2 = -b + sqrt(d);

	int denominator = 2*a;

	int sol1 = numerator1 / denominator;
	int sol2 = numerator2 / denominator;

	return sol1 > 0 ? sol1 : sol2;
}

array<int,2> missingTwo(vector<int> A) {

	int size = A.size();

	int n = size + 2;

	int sumWithout2 = getSum(A,false);
	int sumAll = (n)*(n+1)/2;
	// x + y:
	int sum = sumAll - sumWithout2;

	int sumSquaredWithout2 = getSum(A,true);
	int sumSquaredAll = getSquaredSum(n);
	// x*x + y*y:
	int sum2 = sumSquaredAll - sumSquaredWithout2;

	//    x + y = sum  => y = sum - x
	//    x*x + y*y = sum2
	// => x*x + (sum-x)*(sum-x) = sum2
	// => x*x + sum*sum - 2*sum*x + x*x = sum2
	// => 2*x*x - 2*sum*x + sum*sum - sum2 = 0
	// => a*x*x + b*x + c = 0  (a = 2, b = -2*sum, c = sum*sum - sum2)
	int a = 2, b = -2*sum, c = sum*sum - sum2;

	int first = solveEquation(a,b,c);
	int second = sum - first;

	return {first,second};		
}

int missingOne(vector<int> A) {

	int size = A.size();

	int n = size + 1;

	int sum = getSum(A,false);

	int sum1n = (n)*(n+1)/2;

	return sum1n-sum;
}


int main() {

	vector<int> A = {1,2,3,4,7,8};

	cout << "Missing number is " << get<0>(missingTwo(A)) << "," << get<1>(missingTwo(A)) << endl;

	return 0;
}


