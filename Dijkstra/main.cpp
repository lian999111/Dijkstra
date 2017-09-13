#include <string>
#include <iostream>
#include "Graph.h"
#include "PriorityQueue.h"
#include "PathFinder.h"


int main()
{
	std::vector<std::string> vertices{ "A", "B", "C", "D", "E", "F", "G", "H" };
	Graph<std::string> g1(vertices, 0.5, 10);

	// Test PriorityQueue
	PriorityQueue<std::string> pq1(vertices);
	PriorityQueue<std::string> pq2(g1);
	PriorityQueue<std::string> pq3;

	pq1.TryUpdateNode("A", "B", 5);
	pq1.TryUpdateNode("D", "A", 10);
	pq1.TryUpdateNode("D", "A", 5);
	pq1.TryUpdateNode("D", "A",10);

	pq3.TryInsert("BB", "BB", 2);
	pq3.TryInsert("AA", "AA", 1);
	pq3.TryInsert("CC", "CC", 3);
	pq3.TryInsert("AA", "AA", 3);

	// This will cause an error 
	// because of attempting to implicit convert vertices into a prioirty queue
	// PriorityQueue<std::string> pqpq = vertices;

	Graph<std::string> g2(vertices);

	g2.AddEdge("A", "B", 4);
	g2.AddEdge("A", "C", 3);
	g2.AddEdge("A", "D", 2);
	g2.AddEdge("B", "C", 2);
	g2.AddEdge("B", "E", 1);
	g2.AddEdge("C", "E", 4);
	g2.AddEdge("D", "F", 3);
	g2.AddEdge("E", "G", 1);
	g2.AddEdge("E", "H", 2);
	g2.AddEdge("G", "H", 2);
	g2.AddEdge("F", "H", 1);

	PathFinder<std::string> pf_for_g2(g2, "A");
	auto path = pf_for_g2.PathTo("D");
	int cost = pf_for_g2.CostTo("D");

	std::string sep = "";
	for (const auto& item : path)
	{
		std::cout << sep << item;
		sep = "->";
	}
	std::cout << std::endl;

	path = pf_for_g2.PathTo("H");
	cost = pf_for_g2.CostTo("H");

	sep = "";
	for (const auto& item : path)
	{
		std::cout << sep << item;
		sep = "->";
	}

	std::cout << std::endl;

	// Test setting a new start vertex
	pf_for_g2.SetStartVertex("H");


	// Test graphs with different edge densities
	std::cout << std::endl;
	std::vector<double> densities = { 0.1, 0.4, 0.8 };

	std::cout << "50 vertices and edges ranging from 1 to 10 randomly:" << std::endl;
	for (const auto& density : densities)
	{
		int num_of_vertices{ 50 };
		// The range of edge distance: 10
		Graph<int> graph(num_of_vertices, density, 10);
		// Start vertex: 0
		PathFinder<int> pf_graph(graph, 0);

		int total_cost{ 0 };
		int curr_cost{ 0 };
		int counter{ 0 };

		for (int i = 0; i < num_of_vertices; ++i)
		{
			curr_cost = pf_graph.CostTo(i);
			// Ignore the unreachable cases
			if (curr_cost > 0)
			{
				counter++;
				total_cost += curr_cost;
			}
		}

		std::cout << "When the edge density is: " << density << std::endl;
		std::cout << "The average distance from 0 to other reachable vertices is: " << static_cast<double>(total_cost) / counter << std::endl;
		std::cout << std::endl;
	}
	
	return 0;
}