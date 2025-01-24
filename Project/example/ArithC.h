#ifndef _ARITHC_H//if there isn't a header
#define _ARITHC_H
#include<iostream>
#include <string>
#include"DataTypes.h"
using namespace std;
struct RangeTable {
	double high;
	double low;
	char sym[2];
};
using namespace std;
class ArithC {
	int SymNum;
	double high_init;
	double low_init;
	double c_prob;
	RangeTable* Range_table;
	double EncData;
	double EncData_rec;
	char* DecData;
public:
	ArithC();//constructor
	~ArithC();//destructor
	//helper
	RangeTable* AddTableElement(RangeTable*old_ptr, const int new_size, RangeTable new_node);
	//void CalcTable(SymTable* sym_table);
	//int SearchInTable(char* sym_arr);
	int CheckNumRange(double input);
	void Encode_fp(char* sym, double prob);
	void Decode_fp();
    //setters
	//void SetInputData(char* input);
	void PrintRangeTable()const;
	void PrintResults()const;
};
#endif