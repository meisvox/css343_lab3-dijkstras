// Graph.cpp		Author: Sam Hoover
// contains the definitions for the Graph class.
//
// Graph		Author: Sam Hoover
//
// Description:
// A class representing a number, n, of single-source, weighted graphs, 
// where 0 < n < 100. The graph's vertices and edges are stored in an adjacency
// list, m_vertices. All shortest paths are stored in a matrix of size 100x100,
// m_table, where each row corresponds to one set of shortest paths, and each 
// column corresponds to a vertex in the graph. 
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
#ifndef GRAPH_CPP
#define GRAPH_CPP
#include "Graph.h"

// Vertex default constructor
// creates a Vertex with m_data and m_edgeHead equal to nullptr
// preconditions:	none
// postconditions:	m_data = nullptr; m_edgeHead = nullptr;
//
Graph::Vertex::Vertex() : m_data(nullptr), m_edgeHead(nullptr) {}


// Vertex constructor(GraphData)
// creates a Vertex with m_data equal to data and m_edgeHead equal to
// nullptr
// preconditions:	data must be a valid GraphData pointer
// postconidtions:	m_data = data; m_edgeHead = nullptr;
//
Graph::Vertex::Vertex(GraphData *data) : m_data(data), m_edgeHead(nullptr) {}


// Edge default constructor
// creates an Edge with m_weight and m_adjVertex equal to -1 and 
// m_edgeHead equal to nullptr
// preconditions:	none
// postconditions:	m_weight = -1; m_adjVertex = -1; m_edgeHead = nullptr
//
Graph::Edge::Edge() : m_weight(-1), m_adjVertex(-1), m_nextEdge(nullptr) {}


// Edge constructor(int, int)
// creates an Edge with m_weight equal to weight, m_adjVertex equal to 
// adj, and m_edgeHead equal to nullptr
// preconditions:	none
// postconditions:	m_weight = weight; m_adjVertex = adj; m_edgeHead = nullptr
//
Graph::Edge::Edge(int weight, int adj) : m_nextEdge(nullptr) {
	if(weight < 0 || adj < 0) {
		Edge();
	} else {
		m_weight = weight;
		m_adjVertex = adj;
	}
}


// Graph default constructor
// create a Graph object with m_size equal to 0
// preconditions:	none
// postconditions:	m_size = 0
//
Graph::Graph() : m_size(0) {}


// copy constructor (deep copy)
// creates a Graph object with m_size equal to graph.m_size, m_vertices equal
// to graph.m_vertices, and m_table equal to graph.m_table. Creates new data.
// preconditions:	graph must be a valid Graph object (must not reference
//					a dereferenced nullptr)
// postconditions:	m_size = graph.m_size; m_vertices = graph.m_vertices;
//					m_table = graph.m_table.
//
Graph::Graph(const Graph &graph) {
	empty();
	resetTable();
	if(graph.m_size > 0) {
		m_size = graph.m_size;
		copyVertices(graph);
		copyTable(graph);
	}
}


// copyVertices: copy constructor helper
// copies all Vertex data in graph.m_vertices into m_vertices. creates new data
// preconditions:	graph must be a valid Graph object (must not reference a
//					dereferenced nullptr)
// postconditions:	m_vertices is equal to the contents of graph.m_vertices
//
void Graph::copyVertices(const Graph &graph) {
	for(int i = 0; i < m_size; i++) {
		m_vertices[i] = Vertex(new GraphData(*graph.m_vertices[i].m_data));
		copyEdge(m_vertices[i].m_edgeHead, graph.m_vertices[i].m_edgeHead);
	}
}


// copyEdge: copyVertives helper
// to becomes a new Edge with m_weight, m_adjVertex, and m_nextEdge equal
// to the corresponding values in from.
// preconditions:	none
// postconditions:	to becomes an identical copy of from
//
void Graph::copyEdge(Edge *&to, Edge *from) {
	if(from == nullptr) {
		to = nullptr;
	} else {
		to = new Edge(from->m_weight, from->m_adjVertex);
		copyEdge(to->m_nextEdge, from->m_nextEdge);
	}
}


// copyTable: copy contructor helper
// copies all data in graph.m_table to m_table
// preconditions:	graph must be a valid Graph object (must not reference a
//					dereferenced nullptr)
// postconditions:	m_table = graph.m_table
//
void Graph::copyTable(const Graph &graph) {
	for(int i = 0; i < m_size; i++) {
		for(int j = 0; j < m_size; j++) {
			m_table[i][j].m_visited = graph.m_table[i][j].m_visited;
			m_table[i][j].m_path = graph.m_table[i][j].m_path;
			m_table[i][j].m_dist = graph.m_table[i][j].m_dist;
		}
	}
}


// destructor
// deletes the contents of m_vertices and sets m_size equal to 0
// preconditions:	none
// postconditions:	all vertices removed and m_size = 0
//
Graph::~Graph() {
	empty();
}


// empty
// removes all data from m_vertices and sets all pointers to nullptr
// preconditions:	none
// postconditions:	all data from m_vertices removed and pointers set to nullptr
//
void Graph::empty() {
	for(int i = 0; i < m_size; i++) {
		while(m_vertices[i].m_edgeHead != nullptr) {
			Edge *del = m_vertices[i].m_edgeHead;
			m_vertices[i].m_edgeHead = m_vertices[i].m_edgeHead->m_nextEdge;
			delete del;
			del = nullptr;
		}
		delete m_vertices[i].m_data;
		m_vertices[i].m_data = nullptr;
	}
	m_size = 0;
}


// buildGraph
// reads graph information from inFile and sets this to the corresponding values.
// precondition:	inFile must be properly formated to the specifications
//					in HW3.pdf. inFile must be a valid ifsteam object.
// postconditions:	m_size set to the size read in from inFile. m_vertices
//					set with the data and edges read in from inFile.
//
void Graph::buildGraph(ifstream &infile) {
	infile >> m_size; // data member stores array size
	if (infile.eof() || m_size > MAX_VERTICES) {
		return;
	}
	infile.ignore(); // throw away '\n' go to next line
	
	// get descriptions of vertices
	for (int i = 0; i < m_size; i++) {
		string name = "";	
		getline(infile, name, '\n'); 
		m_vertices[i] = Vertex(new GraphData(name));
	}

	// fill cost edge array
	int src = 0, dest = 0, cost = 0;
	for (;;) {
		infile >> src >> dest >> cost;
		if (src == 0 || infile.eof()) {
			break;
		}
		insertEdge(src, dest, cost);
	}
}


// insertEdge
// inserts an edge into m_vertices[source]'s edge linked list with m_weight
// equal to cost and m_adjVertex equal to dest. If an edge from source to 
// dest already exists, than that edge's m_weight is set to cost.
// preconditions:	source and dest must be the numerical-order value of the
//					edge's they represent (not the index value)
// postconditions:	a new Edge with m_weight = cost and m_adjVertex = dest is
//					inserted into m_vertices[source]'s edge linked list
//
void Graph::insertEdge(int source, int dest, int cost) {
	if(source < 1 || source > m_size ||
		dest < 1 || dest > m_size ||
		cost < 0 || source == dest) {
		return;
	}
	insertEdge(dest, cost, m_vertices[source - 1].m_edgeHead);
}


// insertEdge helper
// inserts an edge into m_vertices[]'s edge linked list with m_weight
// equal to cost and m_adjVertex equal to dest. If an edge from source to 
// dest already exists, than that edge's m_weight is set to cost.
// preconditions:	source and dest must be the numerical-order value of the
//					edge's they represent (not the index value)
// postconditions:	a new Edge with m_weight = cost and m_adjVertex = dest is
//					inserted into m_vertices[]'s edge linked list
//
void Graph::insertEdge(int dest, int cost, Edge *&edge) { 
	if(dest < 0 || dest > m_size || cost < 0) {
		return;
	}

	if(edge == nullptr) {
		edge = new Edge(cost, dest - 1);
		return;
	}

	if(edge->m_adjVertex == dest - 1) {
		edge->m_weight = cost;
		return;
	}

	insertEdge(dest, cost, edge->m_nextEdge);
}


// removeEdge
// removes the Edge between m_vertices[source] and m_vertices[dest], if it
// exists.
// preconditions:	this not equal to nullptr
// postconditions:	the Edge between m_vertices[source] and m_vertices[dest]
//					is removed, if it exists
//
void Graph::removeEdge(int source, int dest) {
	if(source < 1 || source > m_size ||
		dest < 1 || dest > m_size ||
		m_vertices[source - 1].m_edgeHead == nullptr) {
		return;
	}
	
	if(m_vertices[source - 1].m_edgeHead->m_adjVertex == dest - 1) {
		Edge *del = m_vertices[source - 1].m_edgeHead;
		m_vertices[source - 1].m_edgeHead = m_vertices[source - 1].m_edgeHead->m_nextEdge;
		delete del;
		del = nullptr;
		return;
	}

	Edge *temp = m_vertices[source - 1].m_edgeHead;
	while(temp->m_nextEdge != nullptr) {
		if(temp->m_nextEdge->m_adjVertex == dest - 1) {
			Edge *del = temp->m_nextEdge;
			temp->m_nextEdge = temp->m_nextEdge->m_nextEdge;
			delete del;
			del = nullptr;
			return;
		}
		temp = temp->m_nextEdge;
	}
}


// findShortestPath
// set m_table with the appropriate values of the shortest paths between
// each vertex, corresponding to the contents of m_vertices.
// preconditions:	buildGraph has been called or m_size and m_vertices are
//					all set with valid information
// postconditions:	m_table's fields are set to the values corresponding to
//					the shortest path's between vertices
//
void Graph::findShortestPath() {
	resetTable();
	for(int i = 0; i < m_size; i++) {
		findShortestPath(i);
	}
}


// findShortestPath helper
// set m_table with the appropriate values of the shortest paths between
// each vertex, corresponding to the contents of m_vertices.
// preconditions:	buildGraph has been called or m_size and m_vertices are
//					all set with valid information
// postconditions:	m_table's fields are set to the values corresponding to
//					the shortest path's between vertices
//
void Graph::findShortestPath(int source) {
	if(source < 0 || source > m_size) {
		return;
	}
	setSource(source);
	
	// find shortest path for all vertices
	for(int i = 0; i < m_size; i++) {
		int lowestMove = findLowestMove(source);
		if(lowestMove != INFINITY) {
			visitVertex(source, lowestMove);
		}
	}
}


// findLowestMove
// finds the next shortest path in m_table
// preconditions:	source must be the index value of the desired source vertex
// postconditions:	returns an in representing the shortest path in m_table
//
int Graph::findLowestMove(int source) const {
	int indexOfLowest = INFINITY;
	int lowestWeight = INFINITY;
	for(int i = 0; i < m_size - 1; i++) {
		if(!m_table[source][i].m_visited && m_table[source][i].m_dist < lowestWeight) {
			lowestWeight = m_table[source][i].m_dist;
			indexOfLowest = i;
		}
	}
	return(indexOfLowest);
}


// setSource
// sets the source vetex's values and nest shortest paths in m_table.
// preconditions:	source must be the index value of the desired source vertex
// postconditions:	m_table[source][source].m_visited = true, 
//					m_table[source][source].m_path = 0,
//					m_table[source][source].m_dist = 0. 
//
void Graph::setSource(int source) {
	m_table[source][source].m_path = 0;
	m_table[source][source].m_dist = 0;
	visitVertex(source, source);
}


// visitVertex
// marks m_table[source][dest].m_visited as true and sets any new shortest
// paths in m_table
// preconditions:	source and dest must be the index value of the desired 
//					vertices
// postconditions:	m_table[source][dest].m_visited = true; any new shortest
//					paths set in m_table
//
void Graph::visitVertex(int source, int dest) {
	m_table[source][dest].m_visited = true;

	Edge* edge_ptr = m_vertices[dest].m_edgeHead;
	while(edge_ptr != nullptr) {
		if(!m_table[source][edge_ptr->m_adjVertex].m_visited) {
			if(m_table[source][edge_ptr->m_adjVertex].m_path == INFINITY ||
				m_table[source][edge_ptr->m_adjVertex].m_dist > m_table[source][dest].m_dist + edge_ptr->m_weight) {
				m_table[source][edge_ptr->m_adjVertex].m_path = dest + 1;
				m_table[source][edge_ptr->m_adjVertex].m_dist = m_table[source][dest].m_dist + edge_ptr->m_weight;
			}
		}
		edge_ptr = edge_ptr->m_nextEdge;
	}
}


// resetTable
// for all cells in m_table, sets m_visited to false, and m_path and m_dist
// to INFINITY
// preconditions:	none
// postconditions:	for all cells in m_table, m_visited = false, m_path = 
//					INFINITY, m_dist = INFINITY
//
void Graph::resetTable() {
	for(int i = 0; i < MAX_VERTICES; i++) {
		for(int j = 0; j < MAX_VERTICES; j++) {
			m_table[i][j].m_visited = false;
			m_table[i][j].m_path = INFINITY;
			m_table[i][j].m_dist = INFINITY;
		}
	}
}


// displayAll
// displays all shortest paths for all vertices in m_vertices
// preconditions:	none
// postconditions:	all shortest paths for all vertices in m_vertices are
//					displayed to the console
//
void Graph::displayAll() const {
	if(m_size > 0) {
		displayHeader();
		for(int i = 0; i < m_size; i++) {
			cout << *m_vertices[i].m_data << endl;
			for(int j = 0; j < m_size; j++) {
				if(m_table[i][j].m_path != 0 && m_table[i][j].m_path != INFINITY) {
					cout.width(27); cout << "";
					cout.width(7); cout << std::left << i + 1;
					cout.width(7); cout << std::left << j + 1;
					cout.width(11); cout << std::left << m_table[i][j].m_dist;
					displayPath(i, j);
					cout << endl;
				} else if(m_table[i][j].m_path == INFINITY) {
					cout.width(27); cout << "";
					cout.width(7); cout << std::left << i + 1;
					cout.width(7); cout << std::left << j + 1;
					cout.width(11); cout << std::left << "--" << endl;
				}
			}
		}
	}
}


// displayHeader: DisplayAll Helper
// Displays a header containing the field names for the fields displayed in the
// displayAll() method
// preconditions:	none
// postconditions:	field names sent to console
//
void Graph::displayHeader() const {
	cout.width(27);
	cout << std::left << "Description";
	cout.width(7);
	cout << std::left << "From";
	cout.width(7);
	cout << std::left << "To";
	cout.width(11);
	cout << std::left << "Distance";
	cout.width(7);
	cout << std::left << "Path";
	cout << endl;
}


// display
// displays the path, including Vertex title's, between source and dest
// preconditions:	none
// postconditions:	the path, including Vertex title's, between source and 
//					dest is displayed to the console
//
void Graph::display(int source, int dest) const {
	if(source < 1 || source > m_size) {
		cout << "invalid source" << endl;
		return;
	}

	if(dest < 1 || dest > m_size) {
		cout << "invalid destination" << endl;
		return;
	}

	if(!m_table[source - 1][dest - 1].m_visited) {
		cout << "no such path" << endl;
		return;
	}

	cout << source << '\t' << dest << '\t' << m_table[source - 1][dest - 1].m_dist << '\t';
	displayPath(source - 1, dest - 1);
	cout << endl;
	displayLocations(source - 1, dest - 1);
}


// displayPath
// displays the shortest path from source to dest.
// preconditions:	source must be the index value of the desired source vertex
// postconditions:	shortest path from source to dest sent to console
//
void Graph::displayPath(int source, int dest) const {
	displayPathHelper(source, dest);
	cout << dest + 1;
}


// displayPathHelper
// displays the shortest path from source to dest.
// preconditions:	source must be the index value of the desired source vertex
// postconditions:	shortest path from source to dest sent to console
//
void Graph::displayPathHelper(int source, int dest) const {
	if(m_table[source][dest].m_path > 0) {
		displayPathHelper(source, m_table[source][dest].m_path - 1);
		cout << m_table[source][dest].m_path << " ";
	} 
}


// displayLocations
// displays the data of vertices visited in the shortest path between source
// and dest
// preconditions:	source must be the index value of the desired source vertex
// postconditions:	locations visited in shortest path between source and dest sent
//					to console
//
void Graph::displayLocations(int source, int dest) const {
	if(m_table[source][dest].m_path > 0) {
		displayLocations(source, m_table[source][dest].m_path - 1);
		cout << *m_vertices[dest].m_data << endl;
	} else if(m_table[source][dest].m_path == 0) {
		cout << *m_vertices[dest].m_data << endl;
	}
}


#endif