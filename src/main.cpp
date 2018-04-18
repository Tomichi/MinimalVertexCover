#include <iostream>
#include "Individual.h"
#include "Graph.h"

int main() {
	int vertices, edges, count, v1, v2;
	std::cin >> vertices >> edges;
	Graph graph(vertices, edges);
	for (int i = 0; i < vertices; i++) {
		// load vertex
		std::cin >> v1 >> count;
		// load edges
		for (int j = 0; i < count; ++j) {
			std::cin >> v2;
			graph.addEdge(v1, v2);
		}
	}





	Individual a(5);
	Individual b(5);
	Individual c(a,b);
	a.Print();
	std::cout << '\n';
	b.Print();
	std::cout << '\n';
	c.Print();

	return 0;
}

