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
	// The start vertex that this shortest path object is based on
	T start_vertex_;

	Graph<T> graph_;

	std::vector<T> vertices_;

	// The map storing the finished node:
	// Key:		node name
	// Value:	a pair containing the parent node and the g-value
	std::map<T, std::pair<T, int>> closed_;

	PriorityQueue<T> pq_;

	bool Dijkstra(T target_vertex);
public:
	// Default constructor.
	// Initializes closed as empty
	PathFinder(const Graph<T>& g, T start_vertex);

	// TODO: Return reconstructed path
	void FindPath(T target_vertex)
	{
		// Find the target vertex in the graph to check their existence
		const auto ite_target = find(vertices_.begin(), vertices_.end(), target_vertex);

		// The target must exist
		assert(ite_target != vertices_.end());

		// If the target vertex is not closed, do Dijkstra's algorthim towards the target
		const auto ite_target_in_closed = closed_.find(target_vertex);
		if(ite_target_in_closed == closed_.end())
			bool found = Dijkstra(target_vertex);
	}
};


template<class T>
bool PathFinder<T>::Dijkstra(T target_vertex)
{
	int cost{ 0 };

	T curr_name, curr_parent_name;
	int curr_g_value{ 0 };

	//
	while (pq_.Size())
	{
		auto curr_node = pq_.PopPriorityNode();
		curr_name = std::get<0>(curr_node);
		curr_parent_name = std::get<1>(curr_node);
		curr_g_value = std::get<2>(curr_node);

		closed_[curr_name] = std::make_pair(curr_parent_name, curr_g_value);

		if (curr_name == target_vertex)
			return true;

		std::vector<T> neighbors = graph_.NeighborsOf(curr_name);
		
		for (auto&& next_name : neighbors)
		{
			const auto ite = closed_.find(next_name);
			if (ite != closed_.end())
				continue;

			cost = curr_g_value + graph_.GetEdgeValue(curr_name, next_name);

			if(!pq_.TryInsert(next_name, curr_name, cost))
				pq_.TryUpdateNode(next_name, curr_name, cost);
		}
	}
	return false;
}

template<class T>
PathFinder<T>::PathFinder(const Graph<T>& g, T start_vertex)
	: start_vertex_(start_vertex)
	, graph_(g)
	, vertices_(g.GetVertices())
	, pq_()
	, closed_(std::map<T, std::pair<T, int>>())
{
	// Add the start vertex to the priority queue when constructing
	pq_.TryInsert(start_vertex_, start_vertex_, 0);
}
