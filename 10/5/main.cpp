#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)


int sparseSearch(vector<string> strings, string target, int first, int last) {
	if (first > last) return -1;

	int mid = (first + last) / 2;

	if (strings[mid] == target) return mid;

	int left = mid, right = mid;
	
	// Move left until we find next non empty word:
	while (left >= first) {
		if (strings[left] != "") {
			if (strings[left] == target) return left;
			else if (strings[left] < target) {
				return sparseSearch(strings,target,mid+1,last);
			} else {
				return sparseSearch(strings,target,first,mid-1);
			}
		}
		left--;
	}

	// Move right until we find next non empty word:
	while (right <= last) {
		if (strings[right] != "") {
			if (strings[right] == target) return right;
			else if (strings[right] < target) {
				return sparseSearch(strings,target,mid+1,last);
			} else {
				return sparseSearch(strings,target,first,mid-1);
			}
		}
		right++;
	}

	// If we haven't found the word return -1:
	return -1;

}

int sparseSearch(vector<string> strings, string target) {
	if (strings.size() == 0 || target == "") return -1;
	return sparseSearch(strings,target,0,strings.size()-1);
}

int main() {

	vector<string> strings;
	strings.push_back("at");
	strings.push_back("");
	strings.push_back("");
	strings.push_back("");
	strings.push_back("ball");
	strings.push_back("");
	strings.push_back("");
	strings.push_back("car");
	strings.push_back("");
	strings.push_back("");
	strings.push_back("dad");
	strings.push_back("");
	strings.push_back("");

	string target = "ball";

	int index = sparseSearch(strings,target);

	cout << "Index of " << target << " is " << index << endl;

	return 0;
}


