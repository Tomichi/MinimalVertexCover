#include <iostream>
#include "Individual.h"
#include "Population.h"

int main() {
	std::cout.sync_with_stdio(false);
	std::cout.tie();
	int vertices, edges, count, v1, v2;
	std::cin >> vertices >> edges;
	auto graph = std::make_shared<Graph> (vertices, edges);
	for (int i = 0; i < vertices; i++) {
		// load vertex
		std::cin >> v1 >> count;
		// load edges
		for (int j = 0; j < count; ++j) {
			std::cin >> v2;
			graph->addEdge(v1, v2);
		}
	}

	int numberOfGeneration;
	std::cin >> numberOfGeneration;
	auto population = std::make_unique<Population>(graph, numberOfGeneration);
	population->improve();


	std::cout << "END";
	return 0;
}

