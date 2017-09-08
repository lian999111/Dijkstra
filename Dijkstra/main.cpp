#include <string>
#include "Graph.h"
#include "PriorityQueue.h"


int main()
{
	std::vector<std::string> vertices{ "B", "A", "C", "D", "E" };
	Graph<std::string> g(vertices, 0.7, 10);

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

	return 0;
}