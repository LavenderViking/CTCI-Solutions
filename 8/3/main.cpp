#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

int binarySearch(int *A, int lo, int hi, bool distinctElements) {

	if (lo > hi) return -1;

	int mid = (lo+hi) / 2;
	
	int diff = A[mid] - mid;

	int leftIndex = mid-1, rightIndex = mid+1;

	if (!distinctElements) leftIndex = MIN(mid-1, A[mid]);
	if (!distinctElements) rightIndex = MAX(mid+1, A[mid]);

	// If diff is + then we go to left, if diff is - we go to right:
	if (diff == 0) {
		return mid;
	}
	else if (diff < 0) {
		return binarySearch(A,leftIndex,hi,distinctElements);
	} else {
		return binarySearch(A,lo,rightIndex,distinctElements);
	}
}


// O(log(N)) solution if elements are distinct:
// O(N) solution if elements are not distinct:
int magicIndex(int *A, int size, bool distinctElements) {
	return binarySearch(A,0,size, distinctElements);
}



int main() {

	const int size = 10;

	int A[size] = {-4,-2,3,3,6,7,8,10,15,22};

	cout << "Magic index: " << magicIndex(A,size, false) << endl;

	return 0;
}


