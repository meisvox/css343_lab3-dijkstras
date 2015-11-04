// Graph.h			Author: Sam Hoover
// contains the declarations for the Graph class.
//
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <fstream>
#include <string>
#include "GraphData.h"
using namespace std;

// Graph		Author: Sam Hoover
//
// Description:
// A class representing a number, n, of single-source, weighted graphs, 
// where 0 < n < 100. The primary purpose of this class is to build a graph and
// then perform Dijkstra's Algorithm on it to determine the shortest paths. The
// graph's vertices and edges are stored in an adjacency list, m_vertices. All 
// shortest paths are stored in a matrix of size 100x100, m_table, where each row
// corresponds to one set of shortest paths, and each column corresponds to a 
// vertex in the graph. 
//
// Functionality:
// A Graph object must be built from a properly formated file using the class's
// buildGraph(ifsteam&) method. Once a Graph object is built, Edges can be 
// inserted or removed, if they exist, using the insertEdge(int, int, int) and 
// removeEdge(int, int) methods, respectively. Inserting an edge between two 
// vertices where an edge already exists replaces the existing edge's weight
// with the new edge's weight. Once a graph is built as desired, the
// findShortestPath() method can be called to instantiate and fill the m_table
// matrix. After findShortestPath() has been called, any changes to m_vertices 
// will not be recorded in m_table until findShortestPath() is called again. When 
// findShortestPath() has been called at least once, the shortest paths can be
// displayed using the displayAll() and display(int, int) methods. The displayAll()
// method displays all shortest paths, with each vertex as the source. The
// display(int source, int dest) method displays a single shortest path from
// source to dest, along with data stored at those locations. For display to 
// show the most current shortest paths, findShortestPath() must be called
// after any changes have been made to the graph.
//
// Assumptions:	
// This class assumes the following:
//		-file input is entered in the proper format, as outlined in the HW3
//		 assignment specification.
//		-buildGraph(ifstream&) is called to properly build a Graph object
//
class Graph {
public:
	static const int MAX_VERTICES = 100;
	static const int INFINITY = INT_MAX;

	// default constructor
	// create a Graph object with m_size equal to 0
	// preconditions:	none
	// postconditions:	m_size = 0
	//
	Graph();

	// copy constructor (deep copy)
	// creates a Graph object with m_size equal to graph.m_size, m_vertices equal
	// to graph.m_vertices, and m_table equal to graph.m_table. Creates new data.
	// preconditions:	graph must be a valid Graph object (must not reference
	//					a dereferenced nullptr)
	// postconditions:	m_size = graph.m_size; m_vertices = graph.m_vertices;
	//					m_table = graph.m_table.
	//
	Graph(const Graph &graph);

	// destructor
	// deletes the contents of m_vertices and sets m_size equal to 0
	// preconditions:	none
	// postconditions:	all vertices removed and m_size = 0
	//
	~Graph();

	// buildGraph
	// reads graph information from inFile and sets this to the corresponding values.
	// precondition:	inFile must be properly formated to the specifications
	//					in HW3.pdf. inFile must be a valid ifsteam object.
	// postconditions:	m_size set to the size read in from inFile. m_vertices
	//					set with the data and edges read in from inFile.
	//
	void buildGraph(ifstream &inFile);

	// insertEdge
	// inserts an edge into m_vertices[source]'s edge linked list with m_weight
	// equal to cost and m_adjVertex equal to dest. If an edge from source to 
	// dest already exists, than that edge's m_weight is set to cost.
	// preconditions:	source and dest must be the numerical-order value of the
	//					edge's they represent (not the index value)
	// postconditions:	a new Edge with m_weight = cost and m_adjVertex = dest is
	//					inserted into m_vertices[source]'s edge linked list
	//
	void insertEdge(int source, int dest, int cost);

	// removeEdge
	// removes the Edge between m_vertices[source] and m_vertices[dest], if it
	// exists.
	// preconditions:	this not equal to nullptr
	// postconditions:	the Edge between m_vertices[source] and m_vertices[dest]
	//					is removed, if it exists
	//
	void removeEdge(int source, int dest);

	// findShortestPath
	// set m_table with the appropriate values of the shortest paths between
	// each vertex, corresponding to the contents of m_vertices.
	// preconditions:	buildGraph has been called or m_size and m_vertices are
	//					all set with valid information
	// postconditions:	m_table's fields are set to the values corresponding to
	//					the shortest path's between vertices
	//
	void findShortestPath();

	// displayAll
	// displays all shortest paths for all vertices in m_vertices
	// preconditions:	none
	// postconditions:	all shortest paths for all vertices in m_vertices are
	//					displayed to the console
	//
	void displayAll() const;

	// display
	// displays the path, including Vertex title's, between source and dest
	// preconditions:	none
	// postconditions:	the path, including Vertex title's, between source and 
	//					dest is displayed to the console
	//
	void display(int source, int dest) const;

private:

	// Edge
	// represent an edge in a weighted graph. Contains the weight, adjacent 
	// vertex, and a pointer to the next edge.
	//
	struct Edge {
		// default constructor
		// creates an Edge with m_weight and m_adjVertex equal to -1 and 
		// m_edgeHead equal to nullptr
		// preconditions:	none
		// postconditions:	m_weight = -1; m_adjVertex = -1; m_edgeHead = nullptr
		//
		Edge();

		// constructor(int, int)
		// creates an Edge with m_weight equal to weight, m_adjVertex equal to 
		// adj, and m_edgeHead equal to nullptr
		// preconditions:	none
		// postconditions:	m_weight = weight; m_adjVertex = adj; m_edgeHead = nullptr
		//
		Edge(int weight, int adj);

		int m_weight;
		int m_adjVertex;
		Edge* m_nextEdge;
	};

	// Vertex
	// represents a vertex in a weighted graph. Contains a pointer to a GraphData
	// object and a pointer to an Edge representing the head of an edge linked list
	//
	struct Vertex {
		// default constructor
		// creates a Vertex with m_data and m_edgeHead equal to nullptr
		// preconditions:	none
		// postconditions:	m_data = nullptr; m_edgeHead = nullptr;
		//
		Vertex();

		// constructor(GraphData)
		// creates a Vertex with m_data equal to data and m_edgeHead equal to
		// nullptr
		// preconditions:	data must be a valid GraphData pointer
		// postconidtions:	m_data = data; m_edgeHead = nullptr;
		//
		Vertex(GraphData *data);
		GraphData *m_data;
		Edge *m_edgeHead;
	};

	// Table
	// represents the shortest path to a given vertex in a weighted graph.
	// 
	struct Table {
		bool m_visited;
		int m_path;
		int m_dist;
	};

	int m_size;
	Vertex m_vertices[MAX_VERTICES];
	Table m_table[MAX_VERTICES][MAX_VERTICES];


	// copyVertices: copy constructor helper
	// copies all Vertex data in graph.m_vertices into m_vertices. creates new data
	// preconditions:	graph must be a valid Graph object (must not reference a
	//					dereferenced nullptr)
	// postconditions:	m_vertices is equal to the contents of graph.m_vertices
	//
	void copyVertices(const Graph &graph);

	// copyEdge: copyVertives helper
	// to becomes a new Edge with m_weight, m_adjVertex, and m_nextEdge equal
	// to the corresponding values in from.
	// preconditions:	none
	// postconditions:	to becomes an identical copy of from
	//
	void copyEdge(Edge *&to, Edge *from);

	// copyTable: copy contructor helper
	// copies all data in graph.m_table to m_table
	// preconditions:	graph must be a valid Graph object (must not reference a
	//					dereferenced nullptr)
	// postconditions:	m_table = graph.m_table
	//
	void copyTable(const Graph &graph);

	// empty
	// removes all data from m_vertices and sets all pointers to nullptr
	// preconditions:	none
	// postconditions:	all data from m_vertices removed and pointers set to nullptr
	//
	void empty();

	// insertEdge helper
	// inserts an edge into m_vertices[]'s edge linked list with m_weight
	// equal to cost and m_adjVertex equal to dest. If an edge from source to 
	// dest already exists, than that edge's m_weight is set to cost.
	// preconditions:	source and dest must be the numerical-order value of the
	//					edge's they represent (not the index value)
	// postconditions:	a new Edge with m_weight = cost and m_adjVertex = dest is
	//					inserted into m_vertices[]'s edge linked list
	//
	void insertEdge(int dest, int cost, Edge *&edge);
	
	// findShortestPath helper
	// set m_table with the appropriate values of the shortest paths between
	// each vertex, corresponding to the contents of m_vertices.
	// preconditions:	buildGraph has been called or m_size and m_vertices are
	//					all set with valid information
	// postconditions:	m_table's fields are set to the values corresponding to
	//					the shortest path's between vertices
	//
	void findShortestPath(int source);

	// findLowestMove
	// finds the next shortest path in m_table
	// preconditions:	source must be the index value of the desired source vertex
	// postconditions:	returns an in representing the shortest path in m_table
	//
	int findLowestMove(int source) const;

	// setSource
	// sets the source vetex's values and nest shortest paths in m_table.
	// preconditions:	source must be the index value of the desired source vertex
	// postconditions:	m_table[source][source].m_visited = true, 
	//					m_table[source][source].m_path = 0,
	//					m_table[source][source].m_dist = 0. 
	//
	void setSource(int source);

	// visitVertex
	// marks m_table[source][dest].m_visited as true and sets any new shortest
	// paths in m_table
	// preconditions:	source and dest must be the index value of the desired 
	//					vertices
	// postconditions:	m_table[source][dest].m_visited = true; any new shortest
	//					paths set in m_table
	//
	void visitVertex(int source, int dest);

	// resetTable
	// for all cells in m_table, sets m_visited to false, and m_path and m_dist
	// to INFINITY
	// preconditions:	none
	// postconditions:	for all cells in m_table, m_visited = false, m_path = 
	//					INFINITY, m_dist = INFINITY
	//
	void resetTable();

	// displayPath
	// displays the shortest path from source to dest.
	// preconditions:	source must be the index value of the desired source vertex
	// postconditions:	shortest path from source to dest sent to console
	//
	void displayPath(int source, int dest) const;

	// displayPathHelper
	// displays the shortest path from source to dest.
	// preconditions:	source must be the index value of the desired source vertex
	// postconditions:	shortest path from source to dest sent to console
	//
	void displayPathHelper(int source, int dest) const;

	// displayLocations
	// displays the titles of locations visited in the shortest path between source
	// and dest
	// preconditions:	source must be the index value of the desired source vertex
	// postconditions:	locations visited in shortest path between source and dest sent
	//					to console
	//
	void displayLocations(int source, int dest) const;

	// displayHeader: DisplayAll Helper
	// Displays a header containing the field names for the fields displayed in the
	// displayAll() method
	// preconditions:	none
	// postconditions:	field names sent to console
	//
	void displayHeader() const;
};

#endif