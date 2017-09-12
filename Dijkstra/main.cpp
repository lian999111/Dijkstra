#include <string>
#include <iostream>
#include "Graph.h"
#include "PriorityQueue.h"
#include "PathFinder.h"


int main()
{
	std::vector<std::string> vertices{ "A", "B", "C", "D", "E" };
	Graph<std::string> g(vertices, 0.7, 10);
	Graph<int> g1(50, 0.01, 10);

	PriorityQueue<std::string> pq1(vertices);
	PriorityQueue<std::string> pq2(g);
	PriorityQueue<std::string> pq3;

	pq1.TryUpdateNode("A", "B", 5);
	pq1.TryUpdateNode("D", "A", 10);
	pq1.TryUpdateNode("D", "A", 5);
	pq1.TryUpdateNode("D", "A",10);

	pq3.TryInsert("BB", "BB", 2);
	pq3.TryInsert("AA", "AA", 1);
	pq3.TryInsert("CC", "CC", 3);
	pq3.TryInsert("AA", "AA", 3);

	auto name = pq1.PopPriorityNode();
	
	auto size = pq1.Size();

	PathFinder<std::string> pf_for_g(g, "A");
	pf_for_g.FindPath("E");
	pf_for_g.FindPath("E");

	PathFinder<int> pf_for_g1(g1, 0);
	pf_for_g1.FindPath(49);
	auto path = pf_for_g1.PathTo(2);

	for (const auto& vertex : path)
	{
		std::cout << vertex << "->";
	}

	// This will cause an error 
	// because of attempting to implicit convert vertices into a prioirty queue
	// PriorityQueue<std::string> pqpq = vertices;

	return 0;
}