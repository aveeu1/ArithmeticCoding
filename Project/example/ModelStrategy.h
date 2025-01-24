#pragma once
#include <string>

using namespace std;

// Enum for model types
enum ModelType {
	IID = 0,    // IID Model
	MARKOVIAN = 1, // Markovian Model
	GAUSSIAN = 2, // Gaussian Model
	ZIPFSLAW = 3,// ZipfsLaw Model
};

// Strategy Interface
class ModelStrategy {
public:
	virtual ~ModelStrategy() = default;
	virtual void generateSequence(string& input_data) const = 0;
};
