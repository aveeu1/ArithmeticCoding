#pragma once
#include "ModelStrategy.h"
#include "IidModel.h"
#include "MarkovianModel.h"
#include "GaussianModel.h"
#include "ZipfsLawModel.h"

// Context class to use Strategy
class ModelContext {
public:
	ModelContext(ModelType type, int data_size) : model_type_(type), data_size_(data_size) {
		if (model_type_ == IID) {
			strategy_ = make_unique<IidModelStrategy>(data_size_, 0.5);
		}
		else if (model_type_ == MARKOVIAN) {
			strategy_ = make_unique<MarkovianModelStrategy>(data_size_, 2, 0.1, 0.3, 0.5);
		}
		else if (model_type_ == GAUSSIAN)
		{
			strategy_ = make_unique<GaussianModelStrategy>(0.0, 1.0, 100);
		}
		else if (model_type_ == ZIPFSLAW)
		{
			int num_items = 10;  // Number of items for Zipf's law
			double exponent = 1.0;  // Exponent for Zipf's law
			strategy_ = make_unique<ZipfLawModelStrategy>(num_items, exponent, data_size_);
		}

		else {
			throw std::invalid_argument("Invalid model type!");
		}
	}

	void generateSequence(string& input_data) const {
		strategy_->generateSequence(input_data);
	}

private:
	ModelType model_type_;
	int data_size_;
	unique_ptr<ModelStrategy> strategy_;
};