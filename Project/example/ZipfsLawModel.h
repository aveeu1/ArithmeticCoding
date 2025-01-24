#pragma once

#include "ModelStrategy.h"
#include <vector>
#include <random>
#include <string>
#include <cmath>
#include <sstream>


class ZipfLawModelStrategy : public ModelStrategy {
public:
	ZipfLawModelStrategy(int numItems, double exponent, int length)
		: numItems_(numItems), exponent_(exponent), length_(length) {}

	void generateSequence(std::string& input_data) const override;

private:
	int numItems_;
	double exponent_;
	int length_;

	std::vector<double> generateZipfProbabilities() const;
};