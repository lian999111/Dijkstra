#pragma once
#include <vector>
#include "Graph.h"

// Shortest path alogorthm with node names of type T
template <class T>
class ShortestPath
{
private:
	// The vector storing the trace of the path found
	std::vector<T> path;
public:
	ShortestPath();

	static std::vector<T> FindPath(Graph g);
};