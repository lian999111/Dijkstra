#pragma once
#include <vector>
#include <tuple>
#include "Graph.h"

// Shortest path alogorthm with node names of type T
template <class T>
class ShortestPath
{
private:
	// The vector storing the finished node with the element tuple:
	// (self, parent, g-value)
	std::vector<std::tuple<T, T, int>> closed;
public:
	// Default constructor.
	// Initializes closed as empty
	ShortestPath();

	std::vector<T> Dijkstra(Graph g);


};

template<class T>
ShortestPath<T>::ShortestPath()
	: closed(std::vector<std::tuple<T, T, int>>())
{}
