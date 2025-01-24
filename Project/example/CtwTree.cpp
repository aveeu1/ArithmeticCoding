#include "CtwTree.h"
CtwTree::CtwTree(int depth = 3) {
	this->SetDepth(depth);
	this->SetSymNum(pow(2, depth));
	this->root = new DataNode;
	this->GetRoot()->info = NULL;
	this->GetRoot()->right = NULL;
	this->GetRoot()->left = NULL;
	this->GetRoot()->ab_arr[0] = 0;
	this->GetRoot()->ab_arr[1] = 0;
	this->SetPastLen(0);
	this->past_rec = NULL;
};
CtwTree::~CtwTree() {
	destroy_tree();
	if (this->input_data != NULL) {
		delete[] input_data;
	}
	past_unique*past_rec = this->GetPastRec();
	int past_size = this->GetPastLen();
	if (past_rec != NULL)
	{
		for (int jj = 0; jj < past_size; jj++)
		{
			if (past_rec[jj].past != NULL)
				delete[] past_rec[jj].past;
		}
		delete[] past_rec;
	}
	if (sym_table != NULL)
	{
		for (int jj = 0; jj < sym_num; jj++)
		{
			if (sym_table[jj].sym_arr != NULL)
				delete[] sym_table[jj].sym_arr;
		}
		delete[] sym_table;
	}
};
void CtwTree::destroy_tree(DataNode *leaf)
{
	if (leaf != NULL)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}
void CtwTree::destroy_tree()
{
	destroy_tree(this->GetRoot());
}
//setters
void CtwTree::SetSymNum(int sym_num) {
	this->sym_num = sym_num;

}
void CtwTree::SetDepth(const int depth) {
	this->depth = depth;
}
void CtwTree::SetNode(DataNode* node, char info) {
	node->info = info;
}
void CtwTree::SetInputLen(int len) {
	this->input_length = len;
}
void CtwTree::SetInputData(char*input_data)
{
	this->SetInputLen(strlen(input_data)- this->GetDepth());
	this->input_data = new char[strlen(input_data) + 1];
	this->input_data[strlen(input_data)]=NULL;
	strcpy_s(this->input_data,strlen(input_data) + 1, input_data);
}
void CtwTree::SetPastLen(int len)
{
	this->past_rec_len = len;
}
void CtwTree::SetPast(past_unique* past_in) {
	int past_len = this->GetPastLen();
	int depth = this->GetDepth();
	this->past_rec = new past_unique[past_len];
	for (int j = 0; j < past_len; j++)
	{
		this->past_rec[j].ab_arr[0] = past_in[j].ab_arr[0];
		this->past_rec[j].ab_arr[1] = past_in[j].ab_arr[1];
		this->past_rec[j].past = new char[depth + 1];
		strcpy_s(this->past_rec[j].past, depth + 1, past_in[j].past);
	}
}
//getters 
int CtwTree::GetSymNum()const {
	return this->sym_num;

}
int CtwTree::GetDepth()const {
	return this->depth;
}
int CtwTree::GetPastLen()const
{
	return this->past_rec_len;
}
DataNode* CtwTree::GetRoot() const {
	return this->root;
}
past_unique* CtwTree::GetPastRec()const {
	return this->past_rec;
}
int CtwTree::GetInputLen()const {
	return this->input_length;
}
SymTable* CtwTree::GetSymTable()const
{
	return this->sym_table;
}
//helpers
double CtwTree::Factorial(const int num)
{
	double fact = 1;
	for (int i = num; i>1; --i)
	{
		fact *= i;
	}
	return fact;
}
void CtwTree::BuildTree(int depth, string const & prefix = "") {
	if (!depth) {
		int str_len = prefix.length();
		const char* bits_arr = new char[str_len + 1];
		DataNode* current = this->GetRoot();
		current->calc_leave = false;
		this->SetProbVal(current, 1);
		current->Prob_w = 0;
		bits_arr = prefix.c_str();//get c_string
		for (int i = 0; i < str_len; i++)
		{
			if (bits_arr[i] == '0')//create 0 node
			{
				if (current->right == NULL)
				{
					current->right = new DataNode;
					current->right->right = NULL;
					current->right->left = NULL;
					current->right->ab_arr[0] = 0;
					current->right->ab_arr[1] = 0;
					current->right->calc_leave = false;
					this->SetNode(current->right, '0');
					this->SetProbVal(current->right,1);
					current->right->Prob_w = 0;
					current = current->right;
				}
				else
				{
					current = current->right;
				}
			}
			if (bits_arr[i] == '1')//create 1 node
			{
				if (current->left == NULL)
				{
					current->left = new DataNode;
					current->left->right = NULL;
					current->left->left = NULL;
					this->SetNode(current->left, '1');
					current->left->ab_arr[0] = 0;
					current->left->ab_arr[1] = 0;
					current->left->calc_leave = false;
					this->SetProbVal(current->left,1);
					current->left->Prob_w = 0;
					current = current->left;
				}
				else
				{
					current = current->left;
				}
			}

		}
		return;
	}
	BuildTree(depth - 1, prefix + '0');
	BuildTree(depth - 1, prefix + '1');
}
//calcs the estimator of KT estimator by DataNode data
double CtwTree::Prob_est(const int a_node, const int b_node)
{
	double a_product = 1, b_product = 1, ProbEst = 1;//default value in case a_node=b_node=0
	double a_limit, b_limit;
	if ((a_node == 0) && (b_node == 0))
	{
		return 1;
	}
	if (a_node != 0)
	{
		a_limit = (a_node - 0.5);
		for (int ii = 0; ii <= a_limit; ii++)
		{
			a_product = a_product*(0.5 + ii);
		}
	}
	if (b_node != 0)
	{
		b_limit = (b_node - 0.5);
		for (int ii = 0; ii <= b_limit; ii++)
		{
			b_product = b_product*(0.5 + ii);
		}
	}
	//calc Probability_estimation(a_node,const int b_node)
	ProbEst =  ((b_product*a_product) / this->Factorial(a_node + b_node));
	return ProbEst;
	//case 1
	//if ((b_node != 0) && (a_node == 0))
	//{
	//	for (int ii = 1; ii <= b_node; ii++)
	//	{
	//		b_product = b_product/ii;
	//	}
	//	Prob_est = b_product;
	//	return Prob_est;
	//}
	////case2
	//if ((a_node != 0) && (b_node == 0))
	//{
	//	for (int ii = 1; ii <= a_node; ii++)
	//	{
	//		a_product = a_product / ii;
	//	}
	//	Prob_est = a_product;
	//	return Prob_est;
	//}
	////case 3
	//if ((a_node != 0) && (b_node != 0))
	//{
	//	for (int ii = 1; ii <= a_node+b_node; ii++)
	//	{
	//		a_product = a_product / ii;
	//	}
	//	Prob_est = a_product*b_product;
	//	Prob_est = Prob_est;
	//	return Prob_est;
	//}
}
void CtwTree::UpdateTree(char* start_past,char added_bit)
{
	DataNode* root = this->GetRoot();
	int depth = this->GetDepth();
	int select_bit = atoi(&added_bit);
	DataNode**nodeBuff =new DataNode*;
	char* past = NULL;
	past = this->reverse_str(start_past, depth);//get past string in correct order
	int list_size = 1;
	if (past != NULL)
	{
		root->calc_leave = true;//handle root of tree
		root->ab_arr[select_bit] += 1;
		nodeBuff[0] = root;
		for (int i = 0; i <depth; i++)//updating the relevant nodes for tree
		{
			if (past[i] == '0')
			{
				root = root->right;
				root->ab_arr[select_bit] += 1;
				list_size++;
				nodeBuff = this->CollectPath(nodeBuff, list_size, root);
				root->calc_leave = true;
			}
				
			if (past[i] == '1')
			{ 
				root = root->left;
				root->ab_arr[select_bit] += 1;
				list_size++;
				nodeBuff = this->CollectPath(nodeBuff, list_size, root);
				root->calc_leave = true;
			}	
		}
		for (int j = list_size - 1; j >= 0; j--)
		{
			this->PabUpdate(nodeBuff[j], select_bit);
		}
		for (int j = list_size - 1; j >= 0; j--)
		{
			this->PwUpdate(nodeBuff[j]);
		}
		delete[] past;
		delete[] nodeBuff;
	}
}
void CtwTree::PabUpdate(DataNode* root,int select_bit)
{
	double P_ab_new, P_ab_old, trans_factor;
	P_ab_old = root->P_ab;
	trans_factor = (root->ab_arr[select_bit] - 0.5) / (root->ab_arr[0] + root->ab_arr[1]);
	P_ab_new = trans_factor*P_ab_old;//using recursive property
	root->P_ab = P_ab_new;
}
void CtwTree::PwUpdate(DataNode* root)
{
	//case node leaf
	if ((root->left == NULL) && (root->right == NULL))
	{
		root->Prob_w = root->P_ab;
	}
	else
	{
		if (root->right->Prob_w == 0|| root->left->Prob_w == 0)
			root->Prob_w = root->P_ab;
		else
			root->Prob_w = 0.5*(root->P_ab + (root->right->Prob_w)*(root->left->Prob_w));
	}
}
double CtwTree::SetProbWeight(DataNode* data_node)
{
	//p(a,b) case of no sons
	if (data_node->left == NULL && data_node->right == NULL)
		return Prob_est(data_node->ab_arr[0], data_node->ab_arr[1]);
	//cases of a least one son
	//case of one son
	data_node->ab_arr[0] += data_node->left->ab_arr[0] + data_node->right->ab_arr[0];//add the a,b of left son and right son
	data_node->ab_arr[1] += data_node->left->ab_arr[1] + data_node->right->ab_arr[1];
	if ((data_node->left == NULL && data_node->right != NULL) || (data_node->left != NULL && data_node->right == NULL))
		return Prob_est(data_node->ab_arr[0], data_node->ab_arr[1]);
	//case of 2 sons and one has zero prob.
	if ((data_node->left->Prob_w == 0) || (data_node->right->Prob_w == 0))
		return Prob_est(data_node->ab_arr[0], data_node->ab_arr[1]);
	//case each son has nonzero prob. 
	return 0.5*(Prob_est(data_node->ab_arr[0], data_node->ab_arr[1]) + (data_node->left->Prob_w*data_node->right->Prob_w));
}
void CtwTree::SetProbVal(DataNode* node, double prob_weight) {

	node->P_ab = prob_weight;
}
void CtwTree::LoadProb(DataNode* node)
{
	double pr_weight;
	if (node == NULL)
		return;
	LoadProb(node->left);
	LoadProb(node->right);
	if ((node->left == NULL) && (node->right == NULL) && (node->info != NULL))//if the node is a leaf
	{
		if (node->calc_leave == true)
		{
			pr_weight = this->SetProbWeight(node);//calc the probability for the leaf
			this->SetProbVal(node, pr_weight);
		}
		else//dummy leaf for prob. 0.0
		{
			this->SetProbVal(node, 0.0);
		}
	}
	else
	{
		pr_weight = this->SetProbWeight(node);//calc the probability for the sons
		this->SetProbVal(node, pr_weight);
	}
}
//printing path functions
/* Utility that prints out an array on a line */
void CtwTree::printArray(char chars[], int len)
{
	int i;
	for (i = 0; i<len; i++) {
		printf("%c ", chars[i]);
	}
	printf("\n");
}
/* Given a binary tree, print out all of its root-to-leaf
paths, one per line. Uses a recursive helper to do the work.*/
void CtwTree::printPaths(DataNode* node)
{
	int depth = this->GetDepth();
	char*path = new char[depth + 1];
	path[depth] = NULL;
	if (path != NULL)
	{
		cout << "////Past String Table////" << endl;
		printPathsRecur(node, path, 0);
		delete[] path;
	}
}

/* Recursive helper function -- given a node, and an array containing
the path from the root node up to but not including this node,
print out all the root-leaf paths. */
void CtwTree::printPathsRecur(DataNode* node, char path[], int pathLen)
{
	if (node == NULL) return;
	char* rev_path;
	/* append this node to the path array */
	if (node->info != NULL) {
		path[pathLen] = node->info;
		pathLen++;
	}
	/* it's a leaf, so print the path that led to here */
	if (node->left == NULL && node->right == NULL)
	{
		cout << "string:" << endl;
		rev_path = this->reverse_str(path, pathLen);
		if (rev_path != NULL)
		{
			printArray(rev_path, pathLen);
			rev_path = this->reverse_str(path, pathLen);
			cout << "probability: " << node->Prob_w << endl;
			//dispose of path string
			delete[] rev_path;
		}
	}
	else
	{
		/* otherwise try both subtrees */
		printPathsRecur(node->left, path, pathLen);
		printPathsRecur(node->right, path, pathLen);
	}
}

//store data functions
/* Given a binary tree, Load all of its leaves
Uses a recursive helper to do the work.*/
void CtwTree::LoadLeaves()
{
	char*path = new char[std::pow(2, this->GetDepth() + 1)];
	DataNode* root = this->GetRoot();
	LoadLeafsRecur(root, path, 0);
	delete[] path;
}

/* Recursive helper function -- given a node, and an array containing
the path from the root node up to but not including this node,
print out all the root-leaf paths. */
void CtwTree::LoadLeafsRecur(DataNode* node, char path[], int pathLen)
{
	if (node == NULL) return;
	/* append this node to the path array */
	if (node->info != NULL) {
		path[pathLen] = node->info;
		pathLen++;
	}
	past_unique*past;
	double leaf_Pr;
	char* rev_path = NULL;
	/* it's a leaf, so check the path that led to here */
	if (node->left == NULL && node->right == NULL)
	{
		rev_path = this->reverse_str(path, pathLen);
		if (rev_path != NULL)//dispose of path string
		{
			if (this->NotInlist(this->GetPastRec(), this->GetPastLen(), rev_path) == true)//if path not in past list
			{
				node->calc_leave = false;
			}
			else//if path in past list
			{
				past = this->SearchInlist(this->GetPastRec(), this->GetPastLen(), rev_path);
				node->ab_arr[0] = past->ab_arr[0];//load a,b values
				node->ab_arr[1] = past->ab_arr[1];
				node->calc_leave = true;
				//leaf_Pr=this->Prob_est(node->ab_arr[0], node->ab_arr[1]);//calc P(a,b) estimation
				//this->SetProbVal(node, leaf_Pr);//load prob. est to leaf(P(a,b))
				/*cout << rev_path << endl;
				cout << node->Prob_w << endl;*/
			}
			delete[] rev_path;
		}
	}
	else
	{
		/* otherwise try both subtrees */
		LoadLeafsRecur(node->left, path, pathLen);
		LoadLeafsRecur(node->right, path, pathLen);
	}
}

//calc past string table

/* Given a binary tree, calculate out all of its root-to-leaf
paths probability of paths, one per line. Uses a recursive helper to do the work.*/
void CtwTree::UpdateTable(char path[], double PrPath)
{
	int depth = this->GetDepth();
	int sym_num = this->GetSymNum();
	for (int i = 0; i <= sym_num - 1; i++)
	{
		if (strcmp(path, this->sym_table[i].sym_arr) == 0)
			this->sym_table[i].sym_pr = PrPath;
	}
}
void CtwTree::CalcProbTable()
{
	DataNode* root = this->GetRoot();
	int depth = this->GetDepth();
	char*path = new char[depth + 1];
	int sym_num = this->GetSymNum();
	path[depth] = NULL;
	if (path != NULL)
	{
		CalcProbTableRecur(root, path, root->Prob_w, 0);
		delete[] path;
	}
}

/* Recursive helper function -- given a node, and an array containing
the path from the root node up to but not including this node,
print out all the root-leaf paths. */
void CtwTree::CalcProbTableRecur(DataNode* node, char path[], double PrPath, int pathLen)
{
	if (node == NULL) return;
	char* rev_path;
	/* append this node to the path array */
	if (node->info != NULL)
	{
		PrPath *= node->Prob_w;
		path[pathLen] = node->info;
		pathLen++;
	}
	/* it's a leaf, so print the path that led to here */
	if (node->left == NULL && node->right == NULL)
	{
		rev_path = this->reverse_str(path, pathLen);
		if (rev_path != NULL)
		{
			this->UpdateTable(rev_path, PrPath);
			PrPath = this->GetRoot()->Prob_w;
			//dispose of path string
			delete[] rev_path;
		}
	}
	else
	{
		/* otherwise try both subtrees */
		CalcProbTableRecur(node->left, path, PrPath, pathLen);
		CalcProbTableRecur(node->right, path, PrPath, pathLen);
	}
}
void CtwTree::PrintSymTable() const
{
	cout << "\n///sym table///" << endl;
	cout << "//////////////////////////////////////////////////////" << endl;
	cout << "symbol    symbol probability    " << endl;
	cout << "//////////////////////////////////////////////////////" << endl;
	cout << std::scientific;
	SymTable* sym_table = this->GetSymTable();
	int len = this->GetSymNum();
	for (int i = 0; i < len; i++)
	{
		cout << sym_table[i].sym_arr << "       " << sym_table[i].sym_pr <<endl;
	}
}
past_unique* CtwTree::SearchInlist(past_unique*str_list, int list_size, const char* c_str)
{
	for (int jj = 0; jj<list_size; jj++)
	{
		if (strcmp(str_list[jj].past, c_str) == 0)
		{
			return &str_list[jj];
		}
	}
	return NULL;
}
past_unique*CtwTree::reallocNode(past_unique*old_ptr, const int new_size, past_unique new_node)
{
	past_unique*new_arr = new past_unique[new_size];//allocate new DataNode pointer array
	for (int i = 0; i < new_size; i++)
	{
		new_arr[i].past = new char[this->GetDepth() + 1];
	}
	::strcpy_s(new_arr[new_size - 1].past, this->GetDepth() + 1, new_node.past);//set new data to  new node
	new_arr[new_size - 1].ab_arr[0] = new_node.ab_arr[0];
	new_arr[new_size - 1].ab_arr[1] = new_node.ab_arr[1];
	for (int i = 0; i <new_size - 1; i++)//copy old data to new node list
	{
		new_arr[i].ab_arr[0] = old_ptr[i].ab_arr[0];
		new_arr[i].ab_arr[1] = old_ptr[i].ab_arr[1];
		::strcpy_s(new_arr[i].past, this->GetDepth() + 1, old_ptr[i].past);
	}
	for (int i = 0; i <new_size - 1; i++)//delete old node list
	{
		delete[] old_ptr[i].past;
	}
	delete[] old_ptr;
	return new_arr;
}
DataNode**CtwTree::CollectPath(DataNode**old_ptr, const int new_size,DataNode* new_node)
{
	DataNode**new_arr = new DataNode*[new_size];//allocate new DataNode pointer array
	new_arr[new_size - 1] = new_node;
	for (int i = 0; i <new_size - 1; i++)//copy old data to new node list
		new_arr[i] = old_ptr[i];
	delete[] old_ptr;
	return new_arr;
}
//getting the past string list and its length
//void CtwTree::ExPast() {
//	//past_data* intial_ab = new past_data[this->GetInputLen()];
//	//string temp;
//	//past_unique*past_rec;
//	//past_rec = new past_unique;
//	//int data_len = this->GetInputLen();
//	//int depth = this->GetDepth();
//	////strcpy_s(this->input_data, data_len + depth + 1, "1100100110");
//	//for (int ii = 0; ii < data_len; ii++)
//	//{
//	//	intial_ab[ii].past = new char[depth + 1];
//	//	//strcpy_s(intial_ab[ii].past,4,"999");	
//	//}
//	////storing data of each past symbol(past,number of zeros and ones in present)
//	//for (int ii = depth, jj = 0; ii < (depth + data_len); ii++, jj++)
//	//{
//	//	intial_ab[jj].data_ind = jj + 1;//set index for intial values
//	//	temp.assign(&input_data[jj], depth);
//	//	strcpy_s(intial_ab[jj].past, depth + 1, temp.c_str());//put as bits in past buffer for each inf. bit
//	//														  //intial_ab[jj].past_num = std::stoi(temp, 0, 2);//put as bits in past buffer for each inf. bit
//	//	if (input_data[ii] == '0')
//	//	{
//	//		intial_ab[jj].ab_arr[0] = 1;
//	//		intial_ab[jj].ab_arr[1] = 0;
//	//	}
//	//	if (input_data[ii] == '1')
//	//	{
//	//		intial_ab[jj].ab_arr[0] = 0;
//	//		intial_ab[jj].ab_arr[1] = 1;
//	//	}
//	//	temp.erase(temp.begin(), temp.end());//discard past
//	//}
//	////creating a list of unique past symbols
//	//past_rec->past = new char[depth + 1];
//	//strcpy_s(past_rec->past, depth + 1, intial_ab[0].past);
//	//past_rec->ab_arr[0] = intial_ab[0].ab_arr[0];
//	//past_rec->ab_arr[1] = intial_ab[0].ab_arr[1];
//	//int list_size = 1;
//	//past_unique* found;
//	//for (int jj = 1; jj < data_len; jj++)
//	//{
//	//	if (this->NotInlist(past_rec, list_size, intial_ab[jj].past) == true)//if the string past not in list
//	//	{
//	//		list_size++;
//	//		past_rec = this->reallocNode(past_rec, list_size, intial_ab[jj]);
//	//	}
//	//	else//if in list
//	//	{
//	//		found = this->SearchInlist(past_rec, list_size, intial_ab[jj].past);//extract the data set of past from list
//	//		found->ab_arr[0] += intial_ab[jj].ab_arr[0];//union of pasts
//	//		found->ab_arr[1] += intial_ab[jj].ab_arr[1];
//	//	}
//	//}
//	//////set intial values before update for a,b counters
//	////for (int jj = 0; jj < list_size; jj++)
//	////{
//	////	temp.assign(past_rec[jj].past);
//	////	past_rec[jj].ab_arr[0] = std::count(temp.begin(), temp.end(), '0');//set zero count.
//	////	past_rec[jj].ab_arr[1] = std::count(temp.begin(), temp.end(), '1');//set ones count.
//	////	temp.erase(temp.begin(), temp.end());//discard past
//	////}
//	//this->SetPastLen(list_size);//set the length of past string list 
//	//this->SetPast(past_rec);//transfer to bin_tree data
//}
void CtwTree::CreateSymTable() {
	char* bin_str;
	int depth = this->GetDepth();
	int sym_num = this->GetSymNum();
	this->sym_table = new SymTable[sym_num];
	for (int i = 0; i <= sym_num - 1; i++)
	{
		this->sym_table[i].sym_pr = 0.0;
		this->sym_table[i].sym_arr = new char[depth + 1];
		this->sym_table[i].sym_arr[depth] = NULL;
		bin_str = this->decimal_to_binary(i, depth);
		if (bin_str != NULL)
		{
			strcpy_s(this->sym_table[i].sym_arr, depth + 1, bin_str);
			delete[] bin_str;
		}

	}
}
bool CtwTree::NotInlist(past_unique*str_list, const int size, const char* c_str)
{
	for (int jj = 0; jj<size; jj++)
	{
		if (strcmp(str_list[jj].past, c_str) == 0)
			return false;
	}
	return true;
}
char* CtwTree::reverse_str(char word[], int len)
{
	char* rev_word = new char[len + 1];
	rev_word[len] = NULL;
	for (int i = 0; i <= len / 2; i++)
	{
		rev_word[i] = word[len - i - 1];
		rev_word[len - i - 1] = word[i];
	}
	return rev_word;
}
char * CtwTree::decimal_to_binary(int n = 0, const int depth = 8 * sizeof(int))
{
	int c, d, count;
	char *pointer;
	count = 0;
	pointer = new char[depth + 1];
	if (pointer == NULL)//handle no allocation 
		exit(EXIT_FAILURE);
	for (c = depth - 1; c >= 0; c--)
	{
		d = n >> c;

		if (d & 1)
			pointer[count] = 1 + '0';
		else
			pointer[count] = 0 + '0';

		count++;
	}
	pointer[count] = '\0';
	return  pointer;
}
void CtwTree::CleanTree(DataNode* node)
{
	if (node == NULL) return;
	node->ab_arr[0] = 0;//clear old values from each node
	node->ab_arr[1] = 0;
	node->Prob_w = 0.0;
	//otherwise try both subtrees 
	CleanTree(node->left);
	CleanTree(node->right);
}
void CtwTree::UpdatePast(char* start_str,int size)//size=depth+1
{
	past_unique*past_un;
	past_un = new past_unique;
	past_un->past = new char[size];
	past_un->past[size - 1] = NULL;
	for (int i = 0; i < size-1; i++)//get the bit past
		past_un->past[i] = start_str[i];
	//storing data of each past symbol(past,number of zeros and ones in present)
	if (start_str[size-1] == '0')
	{
		past_un->ab_arr[0] = 1;
		past_un->ab_arr[1] = 0;
	}
	if (start_str[size-1] == '1')
	{
		past_un->ab_arr[0] = 0;
		past_un->ab_arr[1] = 1;
	}
	//update list of unique past symbols
	int list_size = this->GetPastLen();
	past_unique* found;
	if (this->NotInlist(this->past_rec, list_size, past_un->past) == true)//if the string past not in list
	{
		list_size++;		
		this->past_rec = this->reallocNode(this->past_rec, list_size,*past_un);
	}
	else//if in list
	{
		found = this->SearchInlist(this->past_rec, list_size,past_un->past);//extract the data set of past from list
		found->ab_arr[0] += past_un->ab_arr[0];//union of pasts
		found->ab_arr[1] += past_un->ab_arr[1];
	}
	this->SetPastLen(list_size);//set list size
	if (past_un != NULL)
	{
		delete[] past_un->past;
		delete past_un;
	}
}
