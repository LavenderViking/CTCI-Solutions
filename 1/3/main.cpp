#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

	ifstream file;
	file.open("input.txt");

	string s="";
	int num;
	
	getline(file,s);

	file >> num;

	int index = s.length();

	while (index > 0) {

		// Space found:
		if (s[num-1] == ' ') {
			s[index-1] = '0';
			s[index-2] = '2';
			s[index-3] = '%';
			index -= 3;
		} else {
			s[index-1] = s[num-1];
			index--;
		}
		num--;
	}

	cout << s << endl;

	file.close();

	return 0;
}
