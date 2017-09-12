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
	// The graph of interest
	Graph<T> graph_;

	// The vertices in the graph
	std::vector<T> vertices_;

	// The start vertex that this shortest path object is based on
	T start_vertex_;

	// The map storing the closed node:
	// Key:		node name
	// Value:	a pair containing the parent node and the g-value
	std::map<T, std::pair<T, int>> closed_;

	// The priority queue
	// Make it a data member to keep the priority queue,
	// so we can continue searching after dropping it halfway if needed.
	PriorityQueue<T> pq_;

	// Dijkstra's algorithm to find the shortest path from the start vertex.
	// to the target vertex
	// Inputs:
	//	target_vertex:		The target vertex to search
	// Output:
	//	Ture if path can be found
	bool Dijkstra(T target_vertex);
public:
	// Default constructor.
	// Initializes the closed list as empty
	// Inputs:
	//	start_vertex:		The vertex to begin searching
	PathFinder(const Graph<T>& g, T start_vertex);

	// Finds the shortest path from start to target.
	// If the specified target vertex has been closed, do nothing.
	// If the specified target vertex hasn't been closed, do Dijkstra's algorithm.
	// Inputs:
	//	target_vertex:		The target vertex to search
	// Output:
	//	Ture if path can be found
	bool FindPath(T target_vertex)
	{
		// Find the target vertex in the graph to check its existence
		const auto ite_target = find(vertices_.begin(), vertices_.end(), target_vertex);

		// The target must exist
		assert(ite_target != vertices_.end());

		// If the target vertex is not closed, do Dijkstra's algorthim towards the target
		const auto ite_target_in_closed = closed_.find(target_vertex);
		if (ite_target_in_closed == closed_.end())
			if (!Dijkstra(target_vertex))
				// If path cannot be found, return false
				return false;
		// If path found, return true
		return true;
	}
};


template<class T>
bool PathFinder<T>::Dijkstra(T target_vertex)
{
	// Used to store the newly calculated cost (g-value)
	int cost{ 0 };
	// The current vertex name and the parent's name
	T curr_name, curr_parent_name;
	// The g-value of the current vertex
	int curr_g_value{ 0 };

	// Keep doing until the priority queue is empty
	while (pq_.Size())
	{
		// Pop the next node from the priority queue and get the names and the g-value
		auto curr_node = pq_.PopPriorityNode();
		curr_name = std::get<0>(curr_node);
		curr_parent_name = std::get<1>(curr_node);
		curr_g_value = std::get<2>(curr_node);

		// Put the vertex into closed_
		closed_[curr_name] = std::make_pair(curr_parent_name, curr_g_value);

		// Todo: Separate getting and removing the first node in pq_
		// If the current node is the desired one, return true and exit
		if (curr_name == target_vertex)
			return true;

		// If not found yet, get the neighbors of the current node
		std::vector<T> neighbors = graph_.NeighborsOf(curr_name);
		
		// Expand the neighbors
		for (auto&& next_name : neighbors)
		{
			// Check if this neighbor is already closed
			const auto ite = closed_.find(next_name);
			if (ite != closed_.end())
				continue;

			// If not closed, calculate the its cost from the current node
			cost = curr_g_value + graph_.GetEdgeValue(curr_name, next_name);

			// Try to insert the node into the priority queue
			if(!pq_.TryInsert(next_name, curr_name, cost))
				// If the node in already in the priority queue, try to update it
				pq_.TryUpdateNode(next_name, curr_name, cost);
		}
	}
	return false;
}

template<class T>
PathFinder<T>::PathFinder(const Graph<T>& g, T start_vertex)
	: graph_(g)
	, vertices_(g.GetVertices())
	, start_vertex_(start_vertex)
	, pq_()
	, closed_(std::map<T, std::pair<T, int>>())
{
	// Add the start vertex to the priority queue when constructing
	pq_.TryInsert(start_vertex_, start_vertex_, 0);
}
