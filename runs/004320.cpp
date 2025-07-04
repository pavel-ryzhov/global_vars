#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>

using namespace std;

//2-9 buttons
const unsigned int num_of_buttons=8; 

struct node {
    node* parent;
    //Data contains frequency of words and their numbers
    vector< pair<unsigned int, unsigned int> > data;
    vector<node*> son;
};

struct tree {
    node* root;
};

node *newnode(void);

void go_root(tree &T);

void go_son(tree &T, int dir);

void go_begin(tree &T);

void add_data(tree &T, unsigned int freq, unsigned int num);

unsigned int get_num(tree &T, unsigned int num_of_ast);

void sort_data_of_tree(node *start_node);

bool compare(const pair<unsigned int, unsigned int> &arg1, const pair<unsigned int, unsigned int> &arg2);

int main(int argc, char** argv) {
    unsigned int i;
    tree T9_dict;
	T9_dict.root=newnode();
	T9_dict.root->parent=NULL;

    unsigned int dict_size;
    scanf("%d", &dict_size);

    unsigned int freq;
    vector<string> word;
	word.resize(dict_size);
    //Reading the dictionary from the input file
	unsigned int c_n;
	char temp_s[21];
    for( i = 0; i < dict_size; i++ ) {
        scanf("%s %d", temp_s, &freq);
		word.at(i)=temp_s;

        for( string::iterator it = word.at(i).begin(); it != word.at(i).end(); ++it ) {
			c_n=(int)*it;
			if( c_n < 100 )
				go_son(T9_dict, 0);
			else if( c_n < 103 )
				go_son(T9_dict, 1);
			else if( c_n < 106 )
				go_son(T9_dict, 2);
			else if( c_n < 109 )
				go_son(T9_dict, 3);
			else if( c_n < 112 )
				go_son(T9_dict, 4);
			else if( c_n < 116 )
				go_son(T9_dict, 5);
			else if( c_n < 119 )
				go_son(T9_dict, 6);
			else if( c_n < 123 )
				go_son(T9_dict, 7);
        }
        add_data(T9_dict, freq, i);
        go_begin(T9_dict);
    }

	

	//Reading and converting message
	string result;
	result.clear();
	bool wordtoprint=false;
	bool marktoprint=false;
	unsigned int num_of_ast, word_num;
	char c;
	scanf("%c", &c);
	scanf("%c", &c);
	c_n=(int)c;
	while( c_n != 10 ) {
		if( c_n == 32 ) {
			if( wordtoprint ) {
				word_num=get_num(T9_dict, num_of_ast);
				go_begin(T9_dict);
				result+=word.at(word_num);
				num_of_ast=0;
				wordtoprint=false;
			}
			else if( marktoprint ) {
				num_of_ast=num_of_ast%3;
				switch( num_of_ast ) {
				case 0:
					result+='.';
					break;
				case 1:
					result+=',';
					break;
				case 2:
					result+='?';
					break;
				}
				num_of_ast=0;
				marktoprint=false;
			}
			result+=' ';
		}
		else if( c_n == 42 ) {
			num_of_ast++;
		}
		else if( c_n == 49 ) {
			if( wordtoprint ) {
				word_num=get_num(T9_dict, num_of_ast);
				go_begin(T9_dict);
				result+=word.at(word_num);
				num_of_ast=0;
				wordtoprint=false;
			}
			else if( marktoprint ) {
				num_of_ast=num_of_ast%3;
				switch( num_of_ast ) {
				case 0:
					result+='.';
					break;
				case 1:
					result+=',';
					break;
				case 2:
					result+='?';
					break;
				}
				num_of_ast=0;
				marktoprint=false;
			}
			num_of_ast=0;
			marktoprint=true;
		}
		else {
			if( marktoprint ) {
				num_of_ast=num_of_ast%3;
				switch( num_of_ast ) {
				case 0:
					result+='.';
					break;
				case 1:
					result+=',';
					break;
				case 2:
					result+='?';
					break;
				}
				num_of_ast=0;
				marktoprint=false;
			}
			num_of_ast=0;
			wordtoprint=true;
			go_son(T9_dict, (c_n-50));
		}
		scanf("%c", &c);
		c_n=(int)c;
    }
	if( wordtoprint ) {
		word_num=get_num(T9_dict, num_of_ast);
		go_begin(T9_dict);
		result+=word.at(word_num);
		num_of_ast=0;
		wordtoprint=false;
	}
	else if( marktoprint ) {
		num_of_ast=num_of_ast%3;
		switch( num_of_ast ) {
		case 0:
			result+='.';
			break;
		case 1:
			result+=',';
			break;
		case 2:
			result+='?';
			break;
		}
		num_of_ast=0;
		marktoprint=false;
	}
	printf("%s\n", result.c_str());

	return 0;
}

node *newnode(void) {
    node *result=new node[sizeof(node)];
    result->data.clear();
	result->son.resize(num_of_buttons);
    unsigned int i;
    for( i = 0; i < num_of_buttons; i++ )
        result->son.at(i)=NULL;
    return result;
}

void go_root(tree &T) {
    if( T.root->parent != NULL )
		T.root=T.root->parent;
}

void go_begin(tree &T) {
	while( T.root->parent != NULL )
		go_root(T);
}

void go_son(tree &T, int dir) {
    if( T.root->son.at(dir) == NULL ) {
        T.root->son.at(dir)=newnode();
        T.root->son.at(dir)->parent=T.root;
        T.root=T.root->son.at(dir);
    }
    else
        T.root=T.root->son.at(dir);
}

void add_data(tree &T, unsigned int freq, unsigned int num) {
    pair<unsigned int, unsigned int> temp;
	temp.first=freq;
	temp.second=num;
	T.root->data.push_back(temp);
}

unsigned int get_num(tree &T, unsigned int num_of_ast) {
	unsigned int result;
	int i;
    num_of_ast=num_of_ast % (T.root->data.size());
    result=T.root->data.at(num_of_ast).second;
    unsigned int freq=T.root->data.at(num_of_ast).first;
	pair<unsigned int, unsigned int> temp;
	freq++;
	temp.first=freq;
	temp.second=result;	
	T.root->data.at(num_of_ast)=temp;
	if(num_of_ast != 0)
		for( i = (int)num_of_ast-1; i >= 0; i-- )
			if( temp.first >= T.root->data.at(i).first ) {
				T.root->data.at(i+1)=T.root->data.at(i);
				T.root->data.at(i)=temp;
			}
			else
				break;
    return result;
}

void sort_data_of_tree(node *start_node) {
	node *current_node;
	deque<node*> current;
	vector<node*> visited;
	current.clear();
	visited.clear();
	current.push_back(start_node);
	visited.push_back(start_node);
	while( !current.empty() ) {
		current_node=current.front();
		current.pop_front();
		if( current_node->data.size() != 0 )
			sort(current_node->data.begin(), current_node->data.end(), compare);
		for ( vector<node*>::iterator it=start_node->son.begin(); it!=start_node->son.end(); ++it ) {
			current.push_back(*it);
		}
	}
}

bool compare(const pair<unsigned int, unsigned int> &arg1, const pair<unsigned int, unsigned int> &arg2)
{
	return arg1.first < arg2.second;
}

