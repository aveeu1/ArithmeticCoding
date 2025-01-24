#ifndef _IDDMODEL_H//if there isn't a header
#define _IDDMODEL_H
#define MinLen 5
#define Probabilty 0.5
#include <random>
#include <vector>
#include <algorithm>
#include "ModelStrategy.h"


using namespace std;
class IidModel {
	int seqLen;
	char *randomSeq;
	double propability;
public:
	IidModel(int seqLen, double propability);//constructor
	~IidModel();//destructor
	//setters
	void SetSeqLen(int seqLen);
	void SetPropability(double propability);
	//getters
	char* GetSequence() const;
	//helpers
	void CreateRandomSeq();
	vector<bool>generateRandomSequence(double propability, int sqLen);
};

// IID Model Strategy
class IidModelStrategy : public ModelStrategy {
public:
	IidModelStrategy(int data_size, double probability) : data_size_(data_size), probability_(probability) {}

	void generateSequence(string& input_data) const override {
		IidModel iid_model(data_size_, probability_);
		iid_model.CreateRandomSeq();
		input_data = iid_model.GetSequence();
	}

private:
	int data_size_;
	double probability_;
};


#endif

