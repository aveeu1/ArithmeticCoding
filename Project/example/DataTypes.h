#ifndef _DATATYPES_H//if there isn't a header
#define _DATATYPES_H
//#include <boost/math/constants/constants.hpp>
//#include <iomanip>
//#include <boost/multiprecision/cpp_dec_float.hpp>
////using boost::multiprecision::cpp_dec;
using namespace std;
struct DataNode
{
	char info;
	double Prob_w;
	double P_ab;
	int ab_arr[2];
	DataNode* right;
	DataNode* left;
	bool calc_leave;
};
struct past_data {
	int data_ind;
	int ab_arr[2];
	char* past;
};
struct past_unique {
	char* past;
	int ab_arr[2];
};
struct SymTable {
	char* sym_arr;
	double sym_pr;
};

#endif