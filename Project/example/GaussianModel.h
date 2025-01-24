#pragma once
#include "ModelStrategy.h"
#include <random>
#include "ModelStrategy.h"
#include <cstring>


// Gaussian Distribution Model
class GaussianModelStrategy : public ModelStrategy {
public:
	GaussianModelStrategy(int data_size, double mean, double stddev);
	
	void generateSequence(string& input_data) const override;

private:
	int data_size_;
	double mean_;
	double stddev_;
};