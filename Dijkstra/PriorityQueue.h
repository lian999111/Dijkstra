#pragma once
#include <vector>
#include <tuple>
#include <algorithm>
#include <cassert>
#include "Graph.h"

// Priority Queue with custom type T of node names
// Definition:
//	Vertex: The vertices in the graph
//	Node: The picked out vertex in the priority queue
template <class T>
class PriorityQueue
{
private:
	// The priority queue. Every node is stored as a tuple in the following form:
	// (self name, parent name, g-value)
	std::vector<std::tuple<T, T, int>> pri_queue_;	// TODO: try to use priority_queue<>

	static std::vector<std::tuple<T, T, int>> MakePriQueueFromVertices(const std::vector<T>& vertices)
	{
		int queue_size = vertices.size();
		std::vector<std::tuple<T, T, int>> temp_queue;
		temp_queue.reserve(queue_size);

		for (const auto& vertex : vertices)
		{
			// Set the initial parent to self
			// Set the initial g-value to the max of int
			temp_queue.push_back(std::make_tuple(vertex, vertex, std::numeric_limits<int>::max()));
		}
		return temp_queue;
	}

	static std::vector<std::tuple<T, T, int>> MakePriQueueFromGraph(const Graph<T>& g)
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
	explicit PriorityQueue(const Graph<T>& g);

	// Constructs with a vector of vertices
	// Inputs:
	//	vertices:		A vector of vertex names of type T
	explicit PriorityQueue(const std::vector<T>& vertices);

	// Empty destructor
	~PriorityQueue() {}

	// Change the g-value of the given node name and sort the order accordingly, if
	// the existing g-value is greater than the given one
	// Inputs:
	//	node:			A node name
	//	parent:			The name of the parent node
	//	gValue:			The corresponding g-value to be updated
	// Output:
	//	Ture if g-value is changed successfully
	bool TryUpdateNode(const T& node, const T& parent, int gValue);

	// Gets the first priority node in the queue
	// Output:
	//	The tuple: (self name, parent name, g-value)
	std::tuple<T, T, int> GetFirstPriorityNode();

	// Pops the first priority node in the queue
	void PopFirstPriorityNode();

	// Insert the given node with its given gValue, if the node is not yet contained
	// Inputs:
	//	node:			A node name
	//	parent:			The name of the parent node
	//	gValue:			The corresponding g-value to be updated
	// Output:
	//	Ture if insertion is successful
	bool TryInsert(const T& node, const T& parent, int gValue);

	// Returns the size of the priority queue
	unsigned int Size();

};

template <class T>
PriorityQueue<T>::PriorityQueue()
	: pri_queue_(std::vector<std::tuple<T, T, int>>())
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
bool PriorityQueue<T>::TryUpdateNode(const T& node, const T& parent, int gValue)
{
	// Use find_if() to find the pair whose node name is as given
	auto ite = std::find_if(pri_queue_.begin(), pri_queue_.end(),
		[&node](const std::tuple<T, T, int>& element) { return std::get<0>(element) == node; });	// Delegation

	// The given vertex name must exist
	assert(ite != pri_queue_.end());

	// If the current g-value is smaller than the given one, do nothing
	if (std::get<2>(*ite) <= gValue)
		return false;

	// Change the parent node and the g-value
	std::get<1>(*ite) = parent;
	std::get<2>(*ite) = gValue;

	// Sort the priority queue by the g-value (the second of the node pair)
	std::sort(pri_queue_.begin(), pri_queue_.end(), 
		[](const auto& elem1, const auto& elem2)	// Delegation
	{ 
		return std::get<2>(elem1) < std::get<2>(elem2);
	});

	return true;
}

template<class T>
std::tuple<T, T, int> PriorityQueue<T>::GetFirstPriorityNode()
{
	//  Return the first element in the pair which is the node name
	return pri_queue_.front();
}

template<class T>
void PriorityQueue<T>::PopFirstPriorityNode()
{
	// Reverse the vector so we can put the needed node in the queue at the back then pop it
	// The reason to sort the node from small to big is just to make it more reasonable
	std::reverse(pri_queue_.begin(), pri_queue_.end());

	//Pop the first priority from the vector
	pri_queue_.pop_back();

	// Reverse the vector again
	std::reverse(pri_queue_.begin(), pri_queue_.end());
}

template<class T>
bool PriorityQueue<T>::TryInsert(const T& node, const T& parent, int gValue)
{
	// Use find_if() to find the pair whose node name is as given
	// TODO: This will cause superfluous find_if() if this method is used after TryChangeGValue()
	const auto ite = std::find_if(pri_queue_.begin(), pri_queue_.end(),
		[&node](const std::tuple<T, T, int>& element) { return std::get<0>(element) == node; });	// Delegation
																				
	if (ite != pri_queue_.end())
	{
		return false;
	}

	auto new_node = std::make_tuple(node, parent, gValue);
	pri_queue_.push_back(new_node);

	// Sort the priority queue by the g-value (the second of the node pair)
	std::sort(pri_queue_.begin(), pri_queue_.end(),
		[](const auto& elem1, const auto& elem2)	// Delegation
	{
		return std::get<2>(elem1) < std::get<2>(elem2);
	});

	return true;
}

template<class T>
inline unsigned int PriorityQueue<T>::Size()
{
	return pri_queue_.size();
}


