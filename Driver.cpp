#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
	ifstream infile("HW3.txt");
	Graph graph;
	graph.buildGraph(infile);
	graph.findShortestPath();
	graph.displayAll();
	cout << endl << endl;
	graph.display(2, 3);
	cout << "any key to exit." << endl;
	cin.get();
	return(0);
}