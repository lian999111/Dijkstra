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
	std::vector<std::pair<T, int>> pri_queue_;	// TODO: try to use priority_queue<>

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
	// Default constructor.
	// Constructs an empty priority queue (SHOULD BE USED MOST FREQUENTLY).
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

	// Pops and returns the first priority node in the queue
	// Output:
	//	The node name of type T of the node with the smallest g-value in the queue
	T PopPriorityNode();

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
		[&node](const std::pair<T, int>& element) { return element.first == node; });	// Delegation

	// The given vertex name must exist
	assert(ite != pri_queue_.end());

	// If the current g-value is smaller than the given one, do nothing
	if (ite->second <= gValue)
		return false;

	ite->second = gValue;

	// Sort the priority queue by the g-value (the second of the node pair)
	std::sort(pri_queue_.begin(), pri_queue_.end(), 
		[](const auto& elem1, const auto& elem2)	// Delegation
	{ 
		return elem1.second < elem2.second;
	});

	return true;
}

template<class T>
T PriorityQueue<T>::PopPriorityNode()
{
	// Reverse the vector so we can put the needed node in the queue at the back then pop it
	// The reason to sort the node from small to big is just to make it more reasonable
	std::reverse(pri_queue_.begin(), pri_queue_.end());

	// Get the node and pop it from the vector
	std::pair<T, int> pri_node = pri_queue_.back();
	pri_queue_.pop_back();

	// Reverse the vector again
	std::reverse(pri_queue_.begin(), pri_queue_.end());

	//  Return the first element in the pair which is the node name
	return pri_node.first;
}


