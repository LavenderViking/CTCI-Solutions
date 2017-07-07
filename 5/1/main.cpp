#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>




using namespace std;

int insert(int N, int M, int i, int j);


int main() {

	ifstream file;
	file.open("input.txt");

	clock_t begin = clock();

	string Ns, Ms;
	unsigned int i, j;
	file >> Ns;
	file >> Ms;
	file >> i;
	file >> j;

	// Convert Ns and Ms to int:
	int N=0, M=0;
	
	cout << "Ns = " << Ns;
	cout << "Ms = " << Ms;

	for (int ind=0; ind < Ns.length(); ind++) {
		int bit = Ns[ind] - '0';
		N |= bit << (Ns.length() - ind - 1);
	}

	for (int ind=0; ind < Ms.length(); ind++) {
		int bit = Ms[ind] - '0';
		M |= bit << (Ms.length() - ind - 1);
	}

	cout << "N = " << N << " M = " << M << "i = " << i << " j = " << j << endl;

	unsigned int ret = insert(N, M, i, j);
	cout << "Return value is = " << ret << endl;
	
	stack <int> print;

	while (ret > 0) {
		print.push(ret&1);
		ret >>= 1;
	}

	while (!print.empty()) {
		int num = print.top();
		print.pop();
		cout << num;
	}
	
	clock_t end = clock();

	clock_t timeElapsed = ( end - begin );
	
	//cout << float( timeElapsed * 1000) / CLOCKS_PER_SEC << " ms" << endl;

	file.close();

	return 0;
}



int insert(int N, int M, int i, int j) {
	int maskj = (1 << (j+1)) - 1;
	int maski = (1 << i) - 1;
	int mask = ~(maskj ^ maski);
	N &= mask;
	N |= (M << i);
	return N;
}





