#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

typedef unordered_map<string,int> HT;

HT freqDict(vector<string> words) {
	HT dict;

	for (int i = 0; i < words.size(); i++)
		dict[words[i]] = dict.count(words[i]) == 0 ? 1 : dict[words[i]]+1;

	return dict;
}

int wordFreq(HT dict, string word) {
	if (dict.empty() || word == "") return 0;

	for (HT::iterator it=dict.begin(); it != dict.end(); it++)
		cout << it->first << "=>" << it->second << endl;

	return dict[word];
}


int main() {

	ifstream file;
	file.open("input.txt");

	int x,y;
	file >> x >> y;

	swap(x,y);	

	vector<string> v = { "tomas", "arnar", "arnar", "tag", "bla"  };

	cout << wordFreq(freqDict(v), "arnar") << endl;

	file.close();

	return 0;
}


