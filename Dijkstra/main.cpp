#include <string>
#include <iostream>
#include "Graph.h"
#include "PriorityQueue.h"
#include "PathFinder.h"


int main()
{
	std::vector<std::string> vertices{ "A", "B", "C", "D", "E", "F", "G", "H" };
	Graph<std::string> g(vertices, 0.5, 10);
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

	PathFinder<std::string> pf_for_g(g, "A");
	pf_for_g.FindPath("E");
	pf_for_g.FindPath("E");

	PathFinder<int> pf_for_g1(g1, 0);
	pf_for_g1.FindPath(49);

	auto path = pf_for_g.PathTo("B");
	int cost = pf_for_g.CostTo("B");

	std::string sep = "";
	for (const auto& item : path)
	{
		std::cout << sep << item;
		sep = "->";
	}

	std::cout << std::endl;


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
	path = pf_for_g2.PathTo("D");
	cost = pf_for_g2.CostTo("D");

	sep = "";
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

	pf_for_g2.SetStartVertex("H");
		
	return 0;
}