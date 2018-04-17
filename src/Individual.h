#pragma once

#include <random>
#include <iostream>

class Individual {
	private:
		int size;
		bool * solution = nullptr;
		int fitness = {0};
		bool setFitness{false};

		double getRandom() {
			std::random_device seed;
			std::mt19937 generator(seed());
			std::uniform_real_distribution<> distribution(0.0, 1.0);
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
				this->solution[i] = this->getRandom() >= 0.5;
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

		int getFitness() {
			if (!setFitness) {
				fitness = computeFitness();
				setFitness = true;
			}

			return fitness;
		}

		void Repair() {
			//@todo make some operation repair
		}

		void Mutation() {
			setFitness = false;
			//@todo random change some bit...
		}

		~Individual() {
			if (this->size > 0) {
				delete[] this->solution;
				this->solution = nullptr;
			}
		}

		void Print() const {
			for (int i = 0; i < this->size; i++) {
				std::cout << (int) this->solution[i] << " ";
			}
			std::cout << '\n';
		}
};
