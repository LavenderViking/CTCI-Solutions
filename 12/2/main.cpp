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

void reverse(char *str) {

	char *start = str, *end = str;

	if (str == NULL) return;

	while (*end) end++;
	end--; // Go back from null character:

	while (start < end) {
		std::swap(*start,*end);
		start++;
		end--;
	}
}

int main() {

	char buf[100] = "tomas arnar";
	char *str = buf;

	cout << "Before = " << str << endl;

	reverse(str);

	cout << "After = " << str << endl;
	

	return 0;
}


