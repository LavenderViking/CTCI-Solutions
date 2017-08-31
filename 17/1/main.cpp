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


int add(int a, int b) {
        while (b != 0 ) {
            int sum = a ^ b;
            int carry = (a & b) << 1;
            a = sum;
            b = carry;
        }
        return a;
}

int main() {

	int a,b;
	cin >> a >> b;

	cout << a << "+" << b << "=" << add(a,b) << endl;



	return 0;
}


