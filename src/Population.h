#pragma once

#include <vector>
#include <climits>
#include "Individual.h"

const int SIZE_POPULATION = 40;

class Population{
	private:
		std::vector<Individual*> currentPopulation;
		std::vector<Individual*> nextPopulation;
		Individual * best{};
		int bestFitness;
		Graph * graph;
		int numberOfGeneration;

		void updateBestIndividual() {
			for (int i = 0; i < (int) currentPopulation.size(); ++i) {
				if (bestFitness > currentPopulation[i]->getFitness()) {
					bestFitness = currentPopulation[i]->getFitness();
					best->copy(currentPopulation[i]);
				}
			}
		}

		int getRandomNumber(int maxsize) {
			std::random_device seed;
			std::mt19937 generator(seed());
			std::uniform_int_distribution<> distribution(0, maxsize-1);
			return distribution(generator);
		}

	public:
		Population(Graph * graph, const int n) {
			this->graph = graph;
			this->numberOfGeneration = n;
			bestFitness = INT_MAX;
			best = new Individual(graph->getVertices());
			// init Population
			for (int i = 0; i < SIZE_POPULATION; i++) {
				currentPopulation.emplace_back(new Individual(graph->getVertices()));
				currentPopulation[i]->Repair(graph);
			}
			updateBestIndividual();
		}


		int select() {
			int index1 = getRandomNumber((int) currentPopulation.size());
			int index2 = getRandomNumber((int) currentPopulation.size());

			return (currentPopulation[index1]->getFitness() > currentPopulation[index2]->getFitness()) ? index2 : index1;
		}

		void improve() {
			// print current results
			for (int i = 0; i < this->numberOfGeneration; i++) {
				if (this->nextPopulation.size() != 0) {
					this->nextPopulation.clear();
				}

				for (int j = 0; j < SIZE_POPULATION; j++) {
					this->nextPopulation.emplace_back(new Individual(
							this->currentPopulation[select()],
							this->currentPopulation[select()])
					);
				}

				this->currentPopulation.clear();
				this->currentPopulation = this->nextPopulation;
				for (int j = 0; j < SIZE_POPULATION /2; j++) {
					int randNumber = this->getRandomNumber((int) this->currentPopulation.size());
					this->currentPopulation[randNumber]->Mutation();
				}
				this->nextPopulation.emplace_back(this->best);

				for (int j = 0; j < (int) this->currentPopulation.size(); j++) {
					this->currentPopulation[j]->Repair(this->graph);
				}

				this->updateBestIndividual();
				// clearing screen
				//std::cout << "\033[2J\033[1;1H";
				std::cout << "Generation " << i << ". fitness " << bestFitness <<"\n";
			}
			this->printBest();
		}

		void printBest() {
			this->best->Print();
		}

		~Population() {
			if (this->nextPopulation.size() == 0) {
				this->nextPopulation.clear();
			}

			if (this->currentPopulation.size() == 0) {
				this->currentPopulation.clear();
			}

			delete best;
		}





};
