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

class numbersToChars {
	
	private:
	vector<char> n0 = {};
	vector<char> n1 = {};
	vector<char> n2 = {'a','b','c'};
	vector<char> n3 = {'d','e','f'};
	vector<char> n4 = {'g','h','i'};
	vector<char> n5 = {'j','k','l'};
	vector<char> n6 = {'m','n','o'};
	vector<char> n7 = {'p','q','r','s'};
	vector<char> n8 = {'t','u','v'};
	vector<char> n9 = {'w','x','y','z'};

	vector<vector<char>> numbers;
	unordered_map<char,char> map;

	public:
	numbersToChars() {
		numbers.push_back(n0);
		numbers.push_back(n1);
		numbers.push_back(n2);
		numbers.push_back(n3);
		numbers.push_back(n4);
		numbers.push_back(n5);
		numbers.push_back(n6);
		numbers.push_back(n7);
		numbers.push_back(n8);
		numbers.push_back(n9);

		for (int i = 2; i < numbers.size(); i++) {
			for (int j = 0; j < numbers[i].size(); j++) {
				map[numbers[i][j]] = '0'+i;
			}
		}
	}

	char getNumber(char c) {
		return map[c];
	}

	string getNumberSeq(string s) {
		string numberSeq = "";

		for (int i = 0; i < s.length(); i++) numberSeq += getNumber(s[i]);

		return numberSeq;
	}

	vector<char> getChars(int number) {
		return numbers[number];
	}
};


void matchingWords(string input, unordered_set<string> &res, string str) {
	if (input == "") {
		res.insert(str);
		return;
	}
	numbersToChars n;

	int firstInt = int(input[0])-48;
	vector<char> chars = n.getChars(firstInt);

	for (int c = 0; c < chars.size(); c++) {
		string newInput = input.substr(1,input.size()-1);

		string newStr = str + chars[c];

		matchingWords(newInput,res,newStr);
	}
}

vector<string> matchingWords(string input, vector<string> validWords) {
	
	if (input.length() == 0) return {};

	unordered_set<string> allWords;
	vector<string> res;

	matchingWords(input,allWords,"");

	for (int i = 0; i < validWords.size(); i++) {
		if (allWords.count(validWords[i]) > 0) res.push_back(validWords[i]);
	}

	return res;
}


unordered_map<string,unordered_set<string>> buildHashTable(vector<string> validWords) {
	 // Put validWords into a hash table:
	unordered_map<string,unordered_set<string>> map;

	numbersToChars n;

	for (int i = 0; i < validWords.size(); i++) {
		string word = validWords[i];
		string numConv = n.getNumberSeq(word);
		map[numConv].insert(word);
	}

	return map;
}

void printMap(unordered_map<string,unordered_set<string>> map) {
	cout << "MAP:" << endl;

	for (auto it : map) {
		cout << it.first << "->";
		for (auto it2 : it.second) {
			cout << it2 << " ";
		}
	}
} 

// O(N) solution where N is the length of the input string:
// Prebuild a hash table that maps input number sequence to valid words with that sequence
// Performs a lookup in the hash table and returns the strings stored with the input value:
vector<string> getValidWords(string input, vector<string> validWords) {

	unordered_map<string,unordered_set<string>> map = buildHashTable(validWords);

	vector<string> res;

	if (map.count(input) > 0) {
		for (auto it : map[input]) res.push_back(it);
	}
	
	return res;
}


int main() {

	string input = "8733";

	vector<string> validWords = {"tree","used"};

	vector<string> words = matchingWords(input,validWords);
	vector<string> words2 = getValidWords(input,validWords);

	for (int i = 0; i < words.size(); i++) cout << words[i] << endl;
	for (int i = 0; i < words2.size(); i++) cout << words2[i] << endl;

	return 0;
}


