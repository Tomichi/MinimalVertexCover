#pragma once

#include <random>
#include <iostream>
#include "Graph.h"
#include <vector>
#include <set>

class Individual {
	private:
		int size;
		bool * solution = nullptr;
		int fitness = {0};
		bool setFitness{false};

		double getRandomProbability() {
			std::random_device seed;
			std::mt19937 generator(seed());
			std::uniform_real_distribution<> distribution(0.0, 1.0);
			return distribution(generator);
		}

		int getRandomNumber() {
			std::random_device seed;
			std::mt19937 generator(seed());
			std::uniform_int_distribution<> distribution(0, size - 1);
			return distribution(generator);
		}

		int computeFitness() const {
			int sum = 0;
			for (int i = 0; i < this->size; i++) {
				if (this->solution[i]) {
					++sum;
				}
			}

			return sum;
		}

	public:
		explicit Individual(int n) {

			this->size = n;
			if (n <= 0) {
				throw "Invalid size of Individual\n";
			}
			this->solution = new bool[this->size];
			for (int i = 0; i < n; i++) {
				this->solution[i] = this->getRandomProbability() >= 0.5;
			}
		};

		Individual(const Individual & a, const Individual & b) {
			this->size = a.size;
			this->solution = new bool[this->size];
			// operator crossover
			for (int i = 0; i < this->size; i++) {
				this->solution[i] = (i >= a.size / 2) ? a.solution[i] : b.solution[i];
			}
		}

		Individual(const Individual * a, const Individual * b) {
			std::random_device seed;
			std::mt19937 generator(seed());
			std::uniform_real_distribution<> distribution(0.0, 1.0);

			this->size = a->size;
			this->solution = new bool[this->size];
			// operator crossover
			for (int i = 0; i < this->size; i++) {
				this->solution[i] = (distribution(generator) > 0.5) ? a->solution[i] : b->solution[i];
			}


		}

		int getFitness() {
			if (!setFitness) {
				fitness = computeFitness();
				setFitness = true;
			}

			return fitness;
		}

		void Repair(Graph * graph) {
			for (int i = 0; i < size; i++) {
				if (this->solution[i]) continue;
				std::vector<int> neighbour = graph->vertexNeighbour(i);
				for (int j = 0; j < (int) neighbour.size(); j++) {
					if (!solution[neighbour[j]]) {
						this->solution[neighbour[j]] = true;
					}
				}
			}
		};

		int checkSolution(Graph * graph) {
			std::set<int> check;
			for (int i = 0; i < size; i++) {
				if (this->solution[i]) continue;
				auto neighbour = graph->vertexNeighbour(i);
				for (int j = 0; j < (int) neighbour.size(); j++) {
					check.insert(neighbour[j]);
				}
			}
			return (int) check.size();
		}

		void Mutation() {
			auto num = this->getRandomNumber();
			solution[num] = !solution[num];
		}

		~Individual() {
			if (this->size > 0) {
				delete[] this->solution;
				this->solution = nullptr;
			}
		}

		void copy(const Individual * individual) {
			for (int i = 0; i < size; i++) {
				this->solution[i] = individual->solution[i];
			}
			setFitness = true;
			fitness = individual->fitness;
		}

		void Print() const {
			for (int i = 0; i < this->size; i++) {
				if (!this->solution[i]) continue;
				std::cout << i << " ";
			}
			std::cout << '\n';
		}

};
