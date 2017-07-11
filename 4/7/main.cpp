#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define fori(a,b) for(int i=a;i<b;i++)
#define forj(a,b) for(int j=a;j<b;j++)


// Example:
//	Projects: a,b,c,d,e,f
//	Dependencies: (a,d), (f,b), (b,d), (f,a), (d,c)
//	Output: f,e,a,b,d,c



// Graph class to hold information about projects and their dependencies:
class Graph {
	private:
	int size = 0;
	
	unordered_set<string> projects;
	unordered_map<string, unordered_set<string>> adjacencyList;
	unordered_map<string,int> dependencies;
	
	public:
	Graph() {}

	void addNode(string node) {
		if (projects.count(node) == 0) {
			++size;
			projects.insert(node);
			dependencies[node] = 0;
		}
	}

	void addEdge(string from, string to) {
		adjacencyList[from].insert(to);
		increaseDependencyOfNode(to);
	}

	void removeEdge(string from, string to) {
		adjacencyList[from].erase(to);
		dependencies[to]--;
	}

	int getSize() { return size; }

	int getNodeDependency(string node) { return dependencies.count(node) == 0 ? 0 : dependencies[node]; }
	
	unordered_set<string> getProjects() { return projects; }
	unordered_set<string> getAdjacencyListOfNode(string node) { return adjacencyList[node]; }
	unordered_map<string, int> getDependencies() { return dependencies; }

	void decreaseDependencyOfNode(string node) { dependencies[node]--; }
	void increaseDependencyOfNode(string node) { dependencies[node]++; }

	void printGraph() {
		cout << "Projects : ";
		for (auto const &node : projects) cout << node << " ";
		cout << endl << "Dependencies: " << endl;

		for (auto const &tuple : adjacencyList) {
			cout << tuple.first << " -> ";
			
			for (auto const &adjNode : tuple.second) cout << adjNode << " ";
			cout << endl;
		}
	}
};

// Returns build order of graph. If not possible to build all projects it returns an empty build order:
// Running time is O(|Projects| + |Edges|)
vector<string> getBuildOrder(string projects[], string dependencies[][2], int numProjects, int numDependencies) {
	Graph G;
	for (int i = 0; i < numProjects; i++) G.addNode(projects[i]);
	for (int i = 0; i < numDependencies; i++) G.addEdge(dependencies[i][0], dependencies[i][1]);

	int numBuildProjects = 0;
	G.printGraph();
	vector<string> buildOrder;

	// Add projects until we have all projects. If we don't have all projects then we abort:
	while (numBuildProjects < G.getSize()) {
		// If no node is added then we return empty build order since it's not possible to build all projects:
		bool nodeAdded = false;

		// Add projects with 0 dependencies:	
		for (auto const &it : G.getDependencies()) {
			if (it.second == 0) {
				buildOrder.push_back(it.first);
				numBuildProjects++;
				// Set dependency count to -1 so it won't be added twice:
				G.decreaseDependencyOfNode(it.first);
				nodeAdded = true;

				// Remove edges from this node:
				unordered_set<string> adjacencyList = G.getAdjacencyListOfNode(it.first);

				for (auto const &node: adjacencyList) G.decreaseDependencyOfNode(node);
			}
		}
		if (!nodeAdded) return vector<string>();
	}

	return buildOrder;
}

void printBuildOrder(vector<string> buildOrder) {
	cout << "Build order: ";
	fori(0,buildOrder.size()) cout << buildOrder[i] << " ";
	cout << endl;
}

int main() {
	
	const int numProjects = 6;
	const int numDependencies = 5;

	string projects[numProjects] = {"a","b","c","d","e","f"};
	string dependencies[numDependencies][2] = {{"a","d"}, {"f","b"}, {"b","d"}, {"f","a"}, {"d","c"}};		
	vector<string> buildOrder = getBuildOrder(projects, dependencies, numProjects, numDependencies);

	printBuildOrder(buildOrder);	

	return 0;
}


