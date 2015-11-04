// GraphData.cpp		Author: Sam Hoover
// contains the definitions for the GraphData class.
//
// GraphData
// a class containing a standard string representing the title of a location
// in a weighted graph.
// Contains the following overloaded operators:
// operator==, operator!=, operator<, operator>, operator<=, operator>=,
// and operator<<
//
#ifndef GRAPHDATA_CPP
#define GRAPHDATA_CPP
#include "GraphData.h"

// default constructor
// creates a GraphData object with m_title equal to ""
// preconditions:	none
// postconditions:	creates a GraphData object with m_title equal to ""
//
GraphData::GraphData() : m_title("") {}


// constructor(string)
// creates a GraphData object with m_title equal to title
// preconditions:	title must be a valid std::string object
// postconditions:	creates a GraphData object with m_title equal to title
//
GraphData::GraphData(string title) : m_title(title) {}


// getTitle
// returns a string equal to m_title
// preconditions:	none
// postconditions:	returns a string equal to m_title
//
string GraphData::getTitle() const {
	return(m_title);
}


// equality
// Compares two GraphData objects. Uses standard string equality operator.
// Returns true if m_title and data.m_title are equal, else false.
// preconditions:	data must be a valid GraphData object (must not reference
//					a dereferenced nullptr)
// postconditions:	Returns true if m_title = data.m_title, else false
//
bool GraphData::operator==(const GraphData &data) const {
	return(m_title == data.m_title);
}


// inequality
// Compares two GraphData objects. Uses standard string inequality operator.
// Returns true if m_title and data.m_title are not equal, else false.
// preconditions:	data must be a valid GraphData object (must not reference
//					a dereferenced nullptr)
// postconditions:	Returns true if m_title != data.m_title, else false
//
bool GraphData::operator!=(const GraphData &data) const {
	return(m_title != data.m_title);
}


// less-than
// Compares two GraphData objects. Uses standard string less-than operator.
// Returns true if m_title is less than data.m_title, else false.
// preconditions:	data must be a valid GraphData object (must not reference
//					a dereferenced nullptr)
// postconditions:	Returns true if m_title < data.m_title, else false
//
bool GraphData::operator<(const GraphData &data) const {
	return(m_title < data.m_title);
}


// greater-than
// Compares two GraphData objects. Uses standard string greater-than operator.
// Returns true if m_title is greater than data.m_title, else false.
// preconditions:	data must be a valid GraphData object (must not reference
//					a dereferenced nullptr)
// postconditions:	Returns true if m_title > data.m_title, else false
//
bool GraphData::operator>(const GraphData &data) const {
	return(m_title > data.m_title);
}


// less-than-equal
// Compares two GraphData objects. Uses standard string less-than-equal operator.
// Returns true if m_title is less than or equal to data.m_title, else false.
// preconditions:	data must be a valid GraphData object (must not reference
//					a dereferenced nullptr)
// postconditions:	Returns true if m_title <= data.m_title, else false
//
bool GraphData::operator<=(const GraphData &data) const {
	return(m_title <= data.m_title);
}


// greater-than-equal
// Compares two GraphData objects. Uses standard string greater-than-equal operator.
// Returns true if m_title is greater than or equal to data.m_title, else false.
// preconditions:	data must be a valid GraphData object (must not reference
//					a dereferenced nullptr)
// postconditions:	Returns true if m_title >= data.m_title, else false
//
bool GraphData::operator>=(const GraphData &data) const {
	return(m_title >= data.m_title);
}


// output
// prints m_title to the output stream
// preconditions:	data must be a valid GraphData object (must not reference
//					a dereferenced nullptr)
// postconditions:	m_title sent to the ostream
//
ostream& operator<<(ostream &sout, const GraphData &data) {
	sout << data.getTitle();
	return(sout);
}

#endif