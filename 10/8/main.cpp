#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)


class BitSet {
	int *bitvector;

	public:
	BitSet(int N) {
		int size = N/32 + 1;
		bitvector = new int [size]; 
		for (int i = 0; i < size; i++) bitvector[i] = 0;
	}

	bool get(int pos) {
		int index = pos / 32, mod = pos % 32;

		return (bitvector[index] >> mod) & 1;
	}

	void set(int pos) {
		int index = pos / 32, mod = pos % 32;

		bitvector[index] |= (1 << mod);
	}
};

// Uses class BitSet:
void findDuplicates2(vector<int> nums) {
	int size = 1024;

	BitSet BS(size);

	for (int i = 0; i < nums.size(); i++) {
		if (BS.get(nums[i])) cout << nums[i] << " ";
		else BS.set(nums[i]);
	}
}

void findDuplicates(vector<int> nums) {

	int size = 1024;

	// Create bitvector for 1024 * 32 = 32768 numbers:
	int *bitvector = new int[size];

	for (int i = 0; i < size; i++) bitvector[i] = 0;

	// Loop through nums and when we see a number we assign 1 to it's
	// position in the bitvector:
	for (int i = 0; i < nums.size(); i++) {
		int pos = nums[i] / 32, mod = nums[i] % 32;

		if (((bitvector[pos] & (1<<mod)) >> mod) & 1) cout << nums[i] << " ";

		bitvector[pos] |= (1<<mod);
	}
	
	delete [] bitvector;
}


int main() {

	int size = 6;

	vector<int> nums = {1,4,6,3,7,7,2,2,2,2,35,643,57,568,5,84,5,3,52,4,324,34,43,43,23,45,2345,23,453,45,3};

	findDuplicates(nums);
	
	findDuplicates2(nums);

	return 0;
}


