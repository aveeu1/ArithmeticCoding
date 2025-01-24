#include "CtwTree.h"
#include "Models.h"
#include <iostream>
#include <limits>
#include <cstring>
#include <string>
#include <memory>  // For std::unique_ptr
#include "ModelStrategy.h"
#include "ModelContext.h"

using namespace std;



int main(int argc, char* argv[]) {
	// Default parameters for default states
	int depth = 10;      // Default depth
	int data_size = 50;  // Default data_size
	string input_data = "1101010010110101010111001010101010100110101101001101";  // Default data sequence

	// Select model type: 0 for IID, 1 for Markovian
	int model_type = 0; // Default to IID model

	// Parse command-line arguments
	if (argc > 1) {
		depth = atoi(argv[1]);  // Convert the first argument to an integer for depth
	}
	if (argc > 2) {
		data_size = atoi(argv[2]);  // Convert the second argument to an integer for data size
	}
	if (argc > 3) {
		model_type = atoi(argv[3]);  // Convert the third argument to select model type (0 or 1)
	}
	if (argc > 4) {
		input_data = argv[4];  // Use the fourth argument as input data string
	}

	// Ensure the data_size matches the length of input_data
	if (data_size != input_data.size()) {
		cout << "Warning: data_size does not match the length of input_data. Adjusting data_size..." << endl;
		data_size = input_data.size();
	}

	try {
		// Use the Strategy Design Pattern to select the model
		ModelContext modelContext(static_cast<ModelType>(model_type), data_size);
		modelContext.generateSequence(input_data);  // Generate the sequence based on selected model

		// Create tree and set input data
		DataNode* root = nullptr;
		CtwTree bin_tree(depth);
		bin_tree.BuildTree(depth, "");
		root = bin_tree.GetRoot();

		// Use c_str() to convert string to const char*
		bin_tree.SetInputData(const_cast<char*>(input_data.c_str()));

		// Set output format for probabilities
		std::cout << std::scientific;

		double sum = 0;
		for (int i = 0; i < bin_tree.GetInputLen(); i++) {
			// Ensure the second argument does not go out of bounds
			if (i + bin_tree.GetDepth() < bin_tree.GetInputLen()) {
				bin_tree.UpdateTree(&input_data[i], input_data[i + bin_tree.GetDepth()]);
				std::cout << "Root probability: " << root->Prob_w << std::endl;
			}
			sum += root->Prob_w;
		}

		std::cout << "SUM OF PROBS: " << sum << std::endl;
	}
	catch (const std::exception& e) {
		cout << "Error: " << e.what() << endl;
		return 1;
	}

	return 0;
}
