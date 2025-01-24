#include "IidModel.h"
#include "ModelStrategy.h"

IidModel::IidModel(int seqLen = MinLen, double propability = Probabilty)
{
	this->randomSeq = NULL;
	this->seqLen = seqLen;
	this->propability = propability;
}
IidModel::~IidModel()
{
	if (this->randomSeq != NULL)
		delete[] randomSeq;
}
void IidModel::SetSeqLen(int seqLen)
{
	this->seqLen = seqLen;
}
void IidModel::SetPropability(double propability)
{
	this->propability = propability;
}
void IidModel::CreateRandomSeq()
{
	vector<bool> rnd_vec = this->generateRandomSequence(this->propability,this->seqLen);
	this->randomSeq = new char[this->seqLen + 1];
	this->randomSeq[this->seqLen] = NULL;
	for (int i = 0; i < seqLen; i++)
		randomSeq [i] = rnd_vec[i]+'0';
}
vector<bool>IidModel::generateRandomSequence(double propability, int sqLen)
{
	std::vector<bool> randomSequence;
	randomSequence.resize(sqLen);
	std::random_device rd;
	std::mt19937 generator(rd());
	std::bernoulli_distribution distribution(propability); //set probability to 1
	std::generate(randomSequence.begin(), randomSequence.end(), [&generator, &distribution] { return distribution(generator); });
	return randomSequence;
}
char*IidModel::GetSequence()const
{
	return this->randomSeq;
}




