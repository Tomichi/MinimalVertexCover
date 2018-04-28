#pragma once

#include <random>
#include <iostream>
#include "Graph.h"
#include <vector>
#include <memory>
#include <omp.h>
const double CROSS_OVER = 0.5;

class Individual {
	private:
		int size;
		bool * solution = nullptr;
		int fitness = {0};
		bool setFitness{false};

		double getRandomProbability() {
			std::uniform_real_distribution<> distribution(0.0, 1.0);
			return distribution(generator);
		}

		int getRandomNumber(int max) {
			std::uniform_int_distribution<> distribution(0, max - 1);
			return distribution(generator);
		}

		int computeFitness() const {
			int sum = 0;
			for (int i = 0; i < this->size; i++) {
				sum += this->solution[i] ? 1 :0;
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
				this->solution[i] = this->getRandomProbability() >= CROSS_OVER;
			}
		};

		Individual(const std::shared_ptr<Individual> & a, const std::shared_ptr<Individual> & b) {
			std::random_device seed;
			std::mt19937 generator(seed());
			std::uniform_real_distribution<> distribution(0.0, 1.0);
			this->size = a->size;
			this->solution = new bool[this->size];
			// operator crossover
			for (int i = 0; i < this->size; i++) {
				this->solution[i] = (distribution(generator) > CROSS_OVER) ? a->solution[i] : b->solution[i];
			}
		}

		int getFitness() {
			if (!setFitness) {
				fitness = computeFitness();
				setFitness = true;
			}

			return fitness;
		}

		void Repair(std::shared_ptr<Graph> & graph) {
			for (int i = 0; i < size; i++) {
				if (this->solution[i]) continue;
				std::vector<int> neighbour = graph->vertexNeighbour(i);
				int size = (int) neighbour.size();
				for (int j = 0; j < size; j++) {
					if (!solution[neighbour[j]]) {
						this->solution[neighbour[j]] = true;
					}
				}
			}
			this->setFitness = false;
		};

		void mutate() {
				auto num = this->getRandomNumber(size);
				solution[num] = !solution[num];
		}

		~Individual() {
			if (this->size > 0) {
				delete[] this->solution;
				this->solution = nullptr;
			}
		}

		void copy(const std::shared_ptr<Individual> & individual) {
			#pragma omp parallel for shared(solution,individual)
			for (int i = 0; i < size; i++) {
				this->solution[i] = individual->solution[i];
			}
			setFitness = individual->setFitness;
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
