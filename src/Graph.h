#pragma once

#include<vector>

class Graph{
	private:
		int vertices = { 0 };
		int edges;
		std::vector<int> * data;
	public:
		Graph(const int v, const int e) : vertices{v}, edges{e} {
			if (vertices <= 0) {
				throw "Vertices must be postive and greater than zero.\n";
			}
			data = new std::vector<int>[vertices];
		}

		~Graph() {
			delete [] data;
		}

		void addEdge(const int vertex1, const int vertex2) {
			if (vertex1 >= vertices || vertex2 >= vertices) {
				return;
			}
			data[vertex1].push_back(vertex2);
			data[vertex2].push_back(vertex1);
		}

		std::vector<int> & vertexNeighbour(int vertex) {
			return data[vertex];
		}
};
