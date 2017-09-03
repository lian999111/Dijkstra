#pragma once
#include <vector>
#include <utility>
#include "Graph.h"

using namespace std;

// Priority Queue with custom type of node name
template <class T>
class PriorityQueue
{
private:
	// The priority queue. Every node is stored as a pair with its name as the first
	// element and its cost to reach as the second.
	vector<pair<T, int>> pri_queue_;
public:
	// Default constructor
	PriorityQueue();
	// Constructor with a graph object
	PriorityQueue(Graph g);
	// Constructor with a vector of vertices
	PriorityQueue(vector<T> vertices);

	~PriorityQueue();
};

template <class T>
PriorityQueue::PriorityQueue()

