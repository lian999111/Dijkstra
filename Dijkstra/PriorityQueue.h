#pragma once
#include <vector>
#include <utility>
#include <limits>
#include "Graph.h"

// Priority Queue with custom type of node names
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
	// Constructor with a graph object with node names of type T
	PriorityQueue(const Graph<T>& g);
	// Constructor with a vector of vertices
	PriorityQueue(const std::vector<T>& vertices);

	//~PriorityQueue();
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


