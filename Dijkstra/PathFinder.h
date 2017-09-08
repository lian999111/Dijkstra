#pragma once
#include <vector>
#include <map>
#include <utility>
#include "Graph.h"
#include "PriorityQueue.h"

// Shortest path alogorthm with node names of type T
template <class T>
class PathFinder
{
private:
	// The start node that this shortest path object is based on
	T start_node_;

	// The map storing the finished node:
	// Key:		node name
	// Value:	a pair containing the parent node and the g-value
	std::map<T, std::pair<T, int>> closed_;

public:
	// Default constructor.
	// Initializes closed as empty
	PathFinder(T start_node);

};


template<class T>
PathFinder<T>::PathFinder(T start_node)
	: start_node_(start_node)
	, closed_(std::map<T, std::pair<T, int>>())
{}
