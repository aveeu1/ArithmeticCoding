#include "MarkovianModel.h"


MarkovianModel::MarkovianModel(int seqLen = MinLen, int depth = depth_def, double Pr_1 = Pr1, double Pr_10 = Pr10, double Pr_00 = Pr00)
{
	this->randomSeq = NULL;
	this->seqLen = seqLen;
	this->Pr_1 = Pr_1;  
	this->Pr_10 = Pr_10;
	this->Pr_00 = Pr_00;
	this->depth = depth;
}
MarkovianModel::~MarkovianModel()
{
	if (this->randomSeq != NULL)
		delete[] randomSeq;
}
char*MarkovianModel::GetSequence()const
{
	return this->randomSeq;
}
void MarkovianModel::SetSeqLen(int seqLen)
{
	this->seqLen = seqLen;
}
void MarkovianModel::SetPropability(double Pr_1, double Pr_10, double Pr_00)
{
	this->Pr_1 = Pr_1;
	this->Pr_10 = Pr_10;
	this->Pr_00 = Pr_00;
}
void MarkovianModel::SetDepth(int depth)
{
	this->depth = depth;
}
void MarkovianModel::CreateRandomSeq()
{
	vector<bool> rndBit;
	this->randomSeq = new char[this->seqLen + 1];
	this->randomSeq[this->seqLen] = NULL;
	this->randomSeq[0] = '1';
	int depth = this->depth;
	char*past = new char[depth + 1];
	if(past!=NULL)
	{ 
		past[depth] = NULL;
		for (int i = 1; i < seqLen; i++)
		{
			if (randomSeq[i - 1] == '1')
			{
				rndBit = this->generateRandomBit(this->Pr_1);
				randomSeq[i] = rndBit[0] + '0';
			}
			else
			{
				if (i + 1 >= depth)
				{
					for (int j = 0; j < depth; j++)
						past[j] = randomSeq[i - depth + j];
					if (strcmp(past, "10") == 0)
					{
						rndBit = this->generateRandomBit(this->Pr_10);
						randomSeq[i] = rndBit[0] + '0';
					}
					if (strcmp(past, "00") == 0)
					{
						rndBit = this->generateRandomBit(this->Pr_00);
						randomSeq[i] = rndBit[0] + '0';
					}
				}
			}
		}
		delete[] past;
	}
}
vector<bool>MarkovianModel::generateRandomBit(double propability)
{
	std::vector<bool> randomBit;
	randomBit.resize(1);
	std::random_device rd;
	std::mt19937 generator(rd());
	std::bernoulli_distribution distribution(propability); //set probability to 1
	std::generate(randomBit.begin(), randomBit.end(), [&generator, &distribution] { return distribution(generator); });
	return randomBit;
}

