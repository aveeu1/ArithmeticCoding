#ifndef _MARKOVIANMODEL_H//if there isn't a header
#define _MARKOVIANMODEL_H
#define MinLen 5
#define Pr1 0.1
#define Pr10 0.3
#define Pr00 0.5
#define depth_def 2
#include <random>
#include <vector>
#include <algorithm>

#include "ModelStrategy.h"

using namespace std;
class MarkovianModel {
	int seqLen;
	int depth;
	char *randomSeq;
	double Pr_1;
	double Pr_10; 
	double Pr_00;
public:
	MarkovianModel(int seqLen,int depth, double Pr_1, double Pr_10, double Pr_00);//constructor
	~MarkovianModel();//destructor
	//setters
	void SetSeqLen(int seqLen);
	void SetPropability(double Pr_1, double Pr_10, double Pr_00);
	void SetDepth(int depth);
	//getters
	char*MarkovianModel::GetSequence()const;
	//helpers
	void CreateRandomSeq();
	vector<bool>MarkovianModel::generateRandomBit(double propability);
};

// Markovian Model Strategy
class MarkovianModelStrategy : public ModelStrategy {
public:
	MarkovianModelStrategy(int data_size, int order, double p0, double p1, double p2)
		: data_size_(data_size), order_(order), p0_(p0), p1_(p1), p2_(p2) {}

	void generateSequence(string& input_data) const override {
		MarkovianModel mark_model(data_size_, order_, p0_, p1_, p2_);
		mark_model.CreateRandomSeq();
		input_data = mark_model.GetSequence();
	}

private:
	int data_size_;
	int order_;
	double p0_, p1_, p2_;
};



#endif