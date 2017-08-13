#include <iostream>
#include <stdio.h>
#include <set>
using namespace std;

struct item {
	int val, count;

	item(int v, int c) : val{v}, count{c} {}

};

bool operator<(const item &a, const item &b) {
		return a.val < b.val;
}


class DS {

	set<item> S;

	public:
	void notWorking(int x) {
		for (auto &it : S) {
			if (it.val < x) it.count++;
		}
	}
};


int main() {

	return 0;
}


