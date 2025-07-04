#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::for_each;
using std::pair;
using std::make_pair;
using std::stable_sort;
using std::swap;
using std::getline;
using std::unary_function;
using std::greater;

struct TreeNode{
	int child[8];
	int bounded_words;
};

const TreeNode void_node = {{-1, -1, -1, -1, -1, -1, -1, -1}, -1};

inline bool IndexValid(int index) {return index >= 0;}

class AddCharToTree: public unary_function<void, const string::value_type> 
{
	vector<TreeNode> *tree;
	int &position_in_tree;
public:
	AddCharToTree(vector<TreeNode> *real_tree, int *real_position): 
	  tree(real_tree), position_in_tree(*real_position){}
	void operator()(const string::value_type current_char)
	{
		int key;
		if(current_char < 's')
		{
			key = (current_char - 'a') / 3;
		}
		else if(current_char < 'z')
		{
			key = (current_char - 'a' - 1) / 3;
		}
		else
		{
			key = 7;
		}
		if(IndexValid(tree->at(position_in_tree).child[key]))
		{
			position_in_tree = tree->at(position_in_tree).child[key];
		}
		else
		{
			tree->push_back(void_node);
			tree->at(position_in_tree).child[key] = tree->size() - 1;
			position_in_tree = tree->size() - 1;
		}
	}
};

class AddStringToTree:
	public unary_function<void, const pair<string, int>&>{
	vector<TreeNode> *tree;
	vector< vector< pair<int, const string*> > > *same_t9_words_container;
public:
	AddStringToTree(
		vector<TreeNode> *real_tree, 
		vector< vector< pair<int, const string*> > > *real_same_t9_words_container):
	tree(real_tree), same_t9_words_container(real_same_t9_words_container){}
	void operator()(const pair<string, int> &current);
};

void AddStringToTree::operator ()(const pair<string, int> &current)
{
	int position_in_tree = 0;
	for_each(
		current.first.begin(),
		current.first.end(),
		AddCharToTree(tree, &position_in_tree));
	if(!IndexValid(tree->at(position_in_tree).bounded_words))
	{
		same_t9_words_container->push_back(vector< pair<int, const string*> >());
		tree->at(position_in_tree).bounded_words = same_t9_words_container->size() - 1;

	}
	same_t9_words_container->at(
		tree->at(position_in_tree).bounded_words
		).push_back(make_pair(current.second, &current.first));
}

inline bool FirstArgumentGreater(
				const pair<int, const string*> &first, 
				const pair<int, const string*> &second)
{
	return first.first > second.first;
}

void SortT9WordsVector(vector< pair<int, const string*> > &vector_to_sort)
{
	stable_sort(vector_to_sort.begin(), vector_to_sort.end(), FirstArgumentGreater);
}

void T9Prepare(
		const vector< pair<string, int> > &words_array,
		vector<TreeNode> *tree,
		vector< vector< pair<int, const string*> > > *same_t9_words_container)
{
	tree->push_back(void_node);
	same_t9_words_container->reserve(words_array.size());
	for_each(
		words_array.begin(),
		words_array.end(),
		AddStringToTree(tree, same_t9_words_container));
	for_each(
		same_t9_words_container->begin(),
		same_t9_words_container->end(),
		SortT9WordsVector);
}

class PerformCharAction: public unary_function<void, string::value_type>
{
	void WordComplete();
	const vector<TreeNode> &tree;
	int position_in_tree;
	vector< vector< pair<int, const string*> > > &same_t9_words_container;
	int position_in_same_t9_words_array;
	enum{VOID_MODE, WORD_MODE, POINT_MODE} current_state;
	int current_point;
	char points[3];
	string &output_vector;
public:
	PerformCharAction(
		const vector<TreeNode> &real_tree,
		vector< vector< pair<int, const string*> > > &real_same_t9_words_container,
		string *real_output_vector):
	tree(real_tree), same_t9_words_container(real_same_t9_words_container), 
	output_vector(*real_output_vector)
	{
		position_in_tree = 0;
		position_in_same_t9_words_array = 0;
		current_state = VOID_MODE;
		current_point = 0;
		points[0] = '.';
		points[1] = ',';
		points[2] = '?';
	}
	void operator()(string::value_type action_to_perform);
};

void PerformCharAction::WordComplete()
{
	vector< pair<int, const string*> >::iterator cur_it_in_w_a =
		same_t9_words_container[tree[position_in_tree].bounded_words].begin() + 
		position_in_same_t9_words_array;
	output_vector += *cur_it_in_w_a->second;
	++cur_it_in_w_a->first;
	while(
		position_in_same_t9_words_array > 0 &&
		cur_it_in_w_a->first >= (cur_it_in_w_a - 1)->first)
	{
		swap(*cur_it_in_w_a, *(cur_it_in_w_a - 1));
		--position_in_same_t9_words_array;
		--cur_it_in_w_a;
	}
	position_in_tree = 0;
	position_in_same_t9_words_array = 0;
	
}

void PerformCharAction::operator ()(string::value_type action_to_perform)
{
	if (action_to_perform <= '9' && action_to_perform >= '2')
	{
		if(current_state == POINT_MODE)
		{
			output_vector += points[current_point];
			current_point = 0;
		}
		current_state = WORD_MODE;
		position_in_tree = tree[position_in_tree].child[action_to_perform - '2'];
	}
	else if(action_to_perform == '1')
	{
		switch(current_state)
		{
		case POINT_MODE:
			output_vector += points[current_point];
			current_point = 0;
			break;
		case WORD_MODE:
			WordComplete();
			break;
		}
		current_state = POINT_MODE;
	}
	else if(action_to_perform == '*')
	{
		switch(current_state)
		{
		case POINT_MODE:
			++current_point;
			break;
		case WORD_MODE:
			++position_in_same_t9_words_array;
			break;
		}
	}
	else
	{
		switch(current_state)
		{
		case POINT_MODE:
			output_vector += points[current_point];
			current_point = 0;
			break;
		case WORD_MODE:
			WordComplete();
			break;
		}
		if(current_state)
			output_vector += ' ';
		current_state = VOID_MODE;
	}
}

string T9Perform(
		const string &requests,
		const vector<TreeNode> &tree,
		vector< vector< pair<int, const string*> > > &same_t9_words_container)
{
	string output_string;
	for_each(
		requests.begin(),
		requests.end(),
		PerformCharAction(tree, same_t9_words_container, &output_string));
	return output_string;
}

string T9(const vector< pair<string, int> > &words_array, const string &requests)
{
	vector<TreeNode> tree;
	vector< vector< pair<int, const string*> > > same_t9_words_container;
	T9Prepare(words_array, &tree, &same_t9_words_container);

	return T9Perform(requests, tree, same_t9_words_container);
}

void ReadString(pair<string, int> &string_for_read)
{
	cin >> string_for_read.first >> string_for_read.second;
}

void Input(vector< pair<string, int> > *words_array, string *requests)
{
	int words_number;
	cin >> words_number;
	words_array->resize(words_number);
	for_each(
		words_array->begin(),
		words_array->end(),
		ReadString);
	while(requests->empty())
		getline(cin, *requests);
	*requests += '\n';
}

int main()
{
	vector< pair<string, int> > words_array;
	string requests;
	Input(&words_array, &requests);

	cout << T9(words_array, requests) << endl;
	return 0;
}
