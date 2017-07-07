#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <stack>
#include <deque>
#include <queue>
#include <unordered_set>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)

struct node {
	int data;
	node *next;
	node *prev;

	node(int d) : data{d} {}
};

struct animal {
	string name;
	bool dog;
	int time;
	animal(string n, bool d) : name{n}, dog{d} {}
};

class animalShelter {
	private:
		queue<animal> dogs, cats;
		int time;
	public:
		animalShelter() { time = 0; }
		~animalShelter() {
			while (!dogs.empty()) {
				dogs.pop();
			}
			while (!cats.empty()) {
				cats.pop();
			}
		}

		void enqueue(string name, bool dog) {

			animal a(name, dog);
			a.time = time++;

			if (dog) dogs.push(a);
			else cats.push(a);
		}

		animal dequeueDog() {
			if (dogs.size() == 0) {
				animal ret("No animal left", true);
				return ret;
			}
			animal a = dogs.front();
			dogs.pop();
			return a;
		}
		animal dequeueCat() {
			if (cats.size() == 0) {
				animal ret("No animal left", false);
				return ret;
			}

			animal a = cats.front();
			cats.pop();
			return a;
		}

		animal dequeueAny() {
			if (dogs.size() == 0 && cats.size() == 0) {
				animal ret("No animal left", true);
				return ret;
			}

			int dogTime = dogs.front().time;
			int catTime = cats.front().time;

			if (dogTime < catTime && dogs.size() > 0) {
				animal a = dogs.front();
				dogs.pop();
				return a;
			} 

			animal a = cats.front();
			cats.pop();
			return a;
		}

		bool dogLeft() {
			return dogs.size() != 0
		}

		bool catLeft() {
			return cats.size() != 0
		}	

};

int main() {

	ifstream file;
	file.open("input.txt");

	int n1;
	file >> n1;

	int *A1 = new int[n1];

	fori(0,n1) file >> A1[i];

	file.close();

	animalShelter aS;

	aS.enqueue("Dog1", true);
	aS.enqueue("Dog2", true);

	aS.enqueue("Cat1", false);
	aS.enqueue("Cat2", false);

	animal a = aS.dequeueCat();
	animal b = aS.dequeueAny();
	animal c = aS.dequeueCat();
	cout << a.name << endl;
	cout << b.name << endl;
	cout << c.name << endl;

	return 0;
}

