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
#include <queue>
using namespace std;

// minHeap will always have same number of elements as maxHeap or 1 more:
class Median {
	
	priority_queue<int,vector<int>> maxHeap;
	priority_queue<int,vector<int>, greater<int>> minHeap;
	
	public:
	void addValue(int value) {
		if (minHeap.size() == 0 || value >= minHeap.top()) {
			minHeap.push(value);

			if (minHeap.size() == maxHeap.size() + 2) {
				int moveValue = minHeap.top();
				minHeap.pop();

				maxHeap.push(moveValue);
			}
		} else {
			maxHeap.push(value);

			if (minHeap.size() + 1 == maxHeap.size()) {
				int moveValue = maxHeap.top();
				maxHeap.pop();

				minHeap.push(moveValue);
			}
		}
	}

	double getMedian() {
		if (minHeap.size() == 0) return 0;

		// MinHeap will always have same number of elements as maxHeap or 1 more:
		if (minHeap.size() == maxHeap.size()) {
			return (minHeap.top() + maxHeap.top())/2.0;
		} else {
			return minHeap.top();
		}
	}
};



int main() {

	Median m;

	vector<int> values = {1,3,2,2,5,8,9,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,99,9,99,99,99,99,99};

	for (int i = 0; i< values.size(); i++) {
		m.addValue(values[i]);
		cout << m.getMedian() << endl;
	}

	return 0;
}


