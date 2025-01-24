#include"ArithC.h"
ArithC::ArithC() {
	this->high_init = 1;
	this->low_init = 0;
	this->DecData=NULL;
	this->SymNum = 1;
	this->c_prob = 0;
	RangeTable rng_t;
	rng_t.high = this->high_init;
	rng_t.low = this->low_init;
	strcpy_s(rng_t.sym, 2, "e");
	this->Range_table = this->AddTableElement(this->Range_table, this->SymNum,rng_t);
}
ArithC::~ArithC() {
	if (this->Range_table != NULL)
		delete [] Range_table;
	if (this->DecData != NULL)
		delete [] this->DecData;
}

int ArithC::CheckNumRange(double input)
{
	int symNum = this->SymNum;
	for (int j = 0; j<symNum; j++)
	{
		if ((input>=this->Range_table[j].low)&&(input<=this->Range_table[j].high))
		{
			cout << "index: " << j << endl;
			return j;
		}
	}
	return -1;
}
void ArithC::Encode_fp(char* sym, double prob)
{
	RangeTable rng_t;
	double code_range;
	int old = this->SymNum;
	code_range = this->Range_table[old].high - this->Range_table[old].low;
	rng_t.low = this->Range_table[old].low + code_range*(this->c_prob);
	this->c_prob += prob;
	rng_t.high = this->Range_table[old].low + code_range*(this->c_prob);
	this->SymNum++;
	this->Range_table = AddTableElement(Range_table, this->SymNum, rng_t);
	//cout << "enc_index: " << sym_ind << endl;
	//cout << "enc_str: " << sym_arr << endl;
}
void ArithC::Decode_fp()
{
	
}
RangeTable* ArithC::AddTableElement(RangeTable*old_ptr, const int new_size, RangeTable new_node)
{
	RangeTable*new_arr = new RangeTable[new_size];//allocate new DataNode pointer array
	new_arr[new_size - 1].high = new_node.high;
	new_arr[new_size - 1].low = new_node.low;
	strcpy_s(new_arr[new_size - 1].sym,2,new_node.sym);
	for (int i = 0; i < new_size - 1; i++)//copy old data to new node list
	{
		new_arr[i].high = old_ptr[i].high;
		new_arr[i].low = old_ptr[i].low;
		strcpy_s(new_arr[new_size - 1].sym,2, old_ptr[i].sym);
	}
	delete[] old_ptr;
	return new_arr;
}
void ArithC::PrintRangeTable() const
{
	cout << "\n///Range table///" << endl;
	cout << "//////////////////////////////////////////////////////" << endl;
	cout << "Symbol    Symbol Range    " << endl;
	cout << "//////////////////////////////////////////////////////" << endl;
	cout << std::scientific;
	int len = this->SymNum;
	for (int i = 0; i < len; i++)
	{
		cout << this->Range_table[i].sym << "       " <<"["<<this->Range_table[i].low<<" - "<< this->Range_table[i].high<<"]" << endl;
	}
}
void ArithC::PrintResults()const
{
	cout <<"Encoded Data: "<< this->EncData_rec << endl;
	cout << "Decoded Data: "<<this->DecData << endl;
}
