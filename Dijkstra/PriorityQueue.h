#pragma once
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>
#include "Graph.h"

// Priority Queue with custom type T of node names
// Definition:
//	Vertex: The vertices in the graph
//	Node: The picked out vertex in the priority queue
template <class T>
class PriorityQueue
{
private:
	// The priority queue. Every node is stored as a pair with its name as the first
	// element and its g-value as the second.
	std::vector<std::pair<T, int>> pri_queue_;

	static std::vector<std::pair<T, int>> MakePriQueueFromVertices(const std::vector<T>& vertices)
	{
		int queue_size = vertices.size();
		std::vector<std::pair<T, int>> temp_queue;
		temp_queue.reserve(queue_size);

		for (const auto& vertex : vertices)
		{
			// Set the initial g-value to the max of int
			temp_queue.push_back(std::make_pair(vertex, std::numeric_limits<int>::max()));
		}
		return temp_queue;
	}

	static std::vector<std::pair<T, int>> MakePriQueueFromGraph(const Graph<T>& g)
	{
		auto vertices = g.GetVertices();

		return MakePriQueueFromVertices(vertices);
	}
public:
	// Default constructor
	PriorityQueue();
	// Constructs with a graph object with vertex names of type T
	// Inputs:
	//	g:				A graph object with vertex names of type T
	PriorityQueue(const Graph<T>& g);
	// Constructs with a vector of vertices
	// Inputs:
	//	vertices:		A vector of vertex names of type T
	PriorityQueue(const std::vector<T>& vertices);
	// Change the g-value of the given node name and sort the order accordingly, if
	// the existing g-value is greater than the given one
	// Inputs:
	//	node:			A node name
	//	gValue:			The corresponding g-value to be updated
	// Output:
	//	Ture if g-value is changed successfully
	bool TryChangeGValue(T node, int gValue);


	~PriorityQueue() {}
};

template <class T>
PriorityQueue<T>::PriorityQueue()
	: pri_queue_(std::vector<std::pair<T, int>>())
{}

template <class T>
PriorityQueue<T>::PriorityQueue(const Graph<T>& g)
	: pri_queue_(MakePriQueueFromGraph(g))
{}

template <class T>
PriorityQueue<T>::PriorityQueue(const std::vector<T>& vertices)
	: pri_queue_(MakePriQueueFromVertices(vertices))
{}

template<class T>
bool PriorityQueue<T>::TryChangeGValue(T node, int gValue)
{
	// Use find_if() to find the pair whose node name is as given
	auto ite = std::find_if(pri_queue_.begin(), pri_queue_.end(),
		[this, &node](const std::pair<T, int>& element) { return element.first == node; });	// Delegation

	// The given vertex name must exist
	assert(ite != pri_queue_.end());

	// If the current g-value is smaller than the given one, do nothing
	if (ite->second <= gValue)
		return;

	ite->second = gValue;

	// Use sort() to find the pair whose node name is as given
	std::sort(pri_queue_.begin(), pri_queue_.end(), 
		[this, &node](const std::pair<T, int>& elem1, const std::pair<T, int>& elem2)	// Delegation
	{ 
		return elem1.second < elem2.second;
	});
}


