#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "ZipfsLawModel.h"
using namespace std;

std::vector<double> ZipfLawModelStrategy::generateZipfProbabilities() const {
	std::vector<double> probabilities;
	double sum = 0.0;

	// Calculate Zipf's probabilities
	for (int i = 1; i <= numItems_; ++i) {
		double p = 1.0 / std::pow(i, exponent_);
		probabilities.push_back(p);
		sum += p;
	}

	// Normalize probabilities to sum to 1
	for (double& p : probabilities) {
		p /= sum;
	}

	return probabilities;
}

void ZipfLawModelStrategy::generateSequence(std::string& input_data) const {
	std::vector<double> probabilities = generateZipfProbabilities();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());

	std::ostringstream oss;

	// Generate sequence based on Zipf's law
	for (int i = 0; i < length_; ++i) {
		int item = dist(gen);
		oss << item << " ";
	}

	input_data = oss.str();  // Store the generated sequence as a single string
}






