#include <string>
#include "Graph.h"
#include "PriorityQueue.h"


int main()
{
	std::vector<std::string> vertices{ "A", "B", "C", "D", "E" };
	Graph<std::string> g(vertices, 0.7, 10);

	PriorityQueue<std::string> pq1(vertices);
	PriorityQueue<std::string> pq2(g);
	PriorityQueue<std::string> pq3;

	pq1.TryChangeGValue("A", 5);
	pq1.TryChangeGValue("D", 10);
	pq1.TryChangeGValue("D", 5);
	pq1.TryChangeGValue("D", 10);

	return 0;
}