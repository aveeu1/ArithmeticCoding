#include "GaussianModel.h"

GaussianModelStrategy::GaussianModelStrategy(int data_size, double mean, double stddev)
	: data_size_(data_size), mean_(mean), stddev_(stddev) {}

void GaussianModelStrategy::generateSequence(string& input_data) const{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> dist(mean_, stddev_);

	input_data.clear();
	for (int i = 0; i < data_size_; ++i) {
		double value = dist(gen);
		input_data += std::to_string(value) + " ";  // Store each generated number as a string
	}
}