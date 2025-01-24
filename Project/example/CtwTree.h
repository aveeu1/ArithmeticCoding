#ifndef _CTWTREE_H//if there isn't a header
#define _CTWTREE_H
#include<iostream>
#include <string>
#include"DataTypes.h"
#define MinLen 5
#define Probabilty 0.5
using namespace std;

class CtwTree {
	//vars
	DataNode* root;
	char* input_data;
	int depth;
	int sym_num;
	int input_length;
	past_unique* past_rec;
	int past_rec_len;
	SymTable* sym_table;
public:
	//methods
	//utility functions
	char* reverse_str(char word[], int len);
	double Factorial(const int num);
	char *decimal_to_binary(int n, const int depth);
	double Prob_est(const int a_node, const int b_node);
	void LoadProb(DataNode* node);
	//tree functions
	DataNode**CollectPath(DataNode**old_ptr, const int new_size, DataNode* new_node);
	void PabUpdate(DataNode* root,int select_bit);
	void PwUpdate(DataNode* root);
	void UpdatePast(char* start_str, int size);
	void UpdateTree(char* start_past,char added_bit);
	void CleanTree(DataNode* node);
	void destroy_tree(DataNode *leaf);
	void destroy_tree();
	void printArray(char chars[], int len);
	void printPaths(DataNode* node);
	void printPathsRecur(DataNode* node, char path[], int pathLen);
	void LoadLeaves();
	void LoadLeafsRecur(DataNode* node, char path[], int pathLen);
	past_unique* reallocNode(past_unique*old_ptr, const int new_size, past_unique new_node);
	past_unique* SearchInlist(past_unique*str_list, int list_size, const char* c_str);
	bool NotInlist(past_unique*str_list, const int size, const char* c_str);
	//void ExPast();
	//table functions
	void UpdateTable(char path[], double PrPath);
	void CalcProbTableRecur(DataNode* node, char path[], double PrPath, int pathLen);
	void CreateSymTable();
	void CalcProbTable();
	void PrintSymTable() const;
	void BuildTree(int depth, string const & prefix);
	//setters
	void SetInputLen(int len);
	void SetInputData(char*input_data);
	void SetPastLen(int len);
	void SetProbVal(DataNode* node, double prob_weight);
	double SetProbWeight(DataNode* data_node);
	void SetDepth(int depth);
	void SetNode(DataNode* node, char info);
	void SetPast(past_unique* past);
	void SetSymNum(int sym_num);
	//getters
	int GetSymNum()const;
	DataNode* GetRoot()const;
	int GetPastLen()const;
	int GetDepth()const;
	past_unique* GetPastRec()const;
	int GetInputLen()const;
	SymTable* GetSymTable()const;
	CtwTree(int depth);
	~CtwTree();
};


#endif