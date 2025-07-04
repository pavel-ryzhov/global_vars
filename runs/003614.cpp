#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// code of a. A must be a letter (a >= 'a' && a <= 'z');
char letterCode(char a)
{
	if (a < 'p')
	{
		return '0' + ((int)(a - 'a') / 3 + 2);
	}
	else if (a < 't')
	{
		return '7';
	}
	else if (a < 'w')
	{
		return '8';
	}
	else
	{
		return '9';
	}
}

void wordCoding(string& word, string& code) // transforming word to digit-code
{
	for (int i = 0; i < (int)word.size(); ++i)
	{
		code[i] = letterCode(word[i]);
	}
}

struct node // node of prefix tree
{
	int set_index; //index in array of sets
	vector<int> sons; // array of successors
	string code; // digit-code of current vertex

	node() {}
};

vector<node> tree; // prefix tree
vector<string> words; // dictionary words array
vector<char> marks(3); // '.', ',', '?'

struct setmember
{
	int word_index; //index of word in dictionary
	int freq;	// frequency of word usage
	int time;	// time where this word was last used
	setmember() {};
	setmember(int wi, int f, int t = 0)
	{
		word_index = wi;
		freq = f;
		time = t;
	}
	bool operator<(setmember const & rvalue) const 
	{
		if (freq > rvalue.freq) //first, comparing by frequency
		{
			return true;
		}
		else if (freq < rvalue.freq)
		{
			return false;
		}
		else
		{
			if (time > rvalue.time) //second, comparing by time
			{
				return true;
			}
			else if (time < rvalue.time)
			{
				return false;
			}
			else
			{
				return words[word_index] < words[rvalue.word_index];  //last - lexicographically
			}
		}
	}
};

vector<set<setmember> > sets; // sets of frequences

// just minimal of two integers
inline int min(int a, int b)
{
	return (a < b)? a : b;
}

void tree_add(int word_index, int freq, string& code, int left_index, int right_index, int vertex)
{
	// finding code's prefix in existing sons
	bool found = false; // whether we found it or not
	for (int i = 0; i < (int)tree[vertex].sons.size(); ++i)
	{
		int firstDifference = -1; //index of first different character (comparing code and current node's code)
		for (int j = 0; j < min(right_index - left_index + 1, tree[tree[vertex].sons[i]].code.length()); ++j)
		{
			if (code[left_index + j] != tree[tree[vertex].sons[i]].code[j])
			{
				firstDifference = j;
				break;
			}
		}

		if (firstDifference < 0) //means that current node's code is a prefix of code
		{
			if (right_index - left_index + 1 == (int)tree[tree[vertex].sons[i]].code.length()) // if node's code equal code
			{
				sets[tree[tree[vertex].sons[i]].set_index].insert(setmember(word_index,freq)); // adding new element to this node's set
			}
			else
			{
				// pushing code's suffix further to code's succesors
				tree_add(word_index, freq, code, left_index + tree[tree[vertex].sons[i]].code.length(), right_index, tree[vertex].sons[i]);
			}
			found = true;
			break;
		}
		else if (firstDifference > 0) // means that code and current node's code have common prefix, not equal to current node's code
		{
			int curInd = tree[vertex].sons[i]; // index of current succesor
			tree.push_back(node()); // new element to the tree
			tree[vertex].sons[i] = tree.size() - 1;
			tree.back().code = tree[curInd].code.substr(0, firstDifference); //which is to be this common prefix
			tree.back().sons.resize(0);
			tree.back().sons.push_back(curInd);
			tree[curInd].code = tree[curInd].code.substr(firstDifference, tree[curInd].code.length() - firstDifference);
			tree.push_back(node()); // old current node's code suffix
			tree[tree.size() - 2].sons.push_back(tree.size() - 1);
			tree.back().code = code.substr(firstDifference, right_index - firstDifference + 1);
			sets.push_back(set<setmember>()); //and adding new element to respective set
			sets.back().insert(setmember(word_index,freq));
			tree.back().set_index = sets.size() - 1;
			found = true;
		}
	}

	// if never found
	if (!found)
	{
		// just adding new node to tree and new element to respective set
		tree[0].sons.push_back(tree.size());
		tree.push_back(node());
		tree.back().code = code.substr(left_index, right_index - left_index + 1);
		sets.push_back(set<setmember>());
		sets.back().insert(setmember(word_index,freq));
		tree.back().set_index = sets.size() - 1;
	}
}

int setIndex(string& code, int left_index, int right_index, int vertex)
{
	// finding code's prefix in existing sons
	for (int i = 0; i < (int)tree[vertex].sons.size(); ++i)
	{
		int firstDifference = -1; //index of first different character (comparing code and current node's code)
		for (int j = 0; j < min(right_index - left_index + 1, tree[tree[vertex].sons[i]].code.length()); ++j)
		{
			if (code[left_index + j] != tree[tree[vertex].sons[i]].code[j])
			{
				firstDifference = j;
				break;
			}
		}
		if (firstDifference < 0) //means that current node's code is a prefix of code
		{
			if (right_index - left_index + 1 == (int)tree[tree[vertex].sons[i]].code.length())
			{
				return tree[tree[vertex].sons[i]].set_index; // if we found already
			}
			else
			{
				// have to push code's suffix further to seek there
				return setIndex(code, left_index + tree[tree[vertex].sons[i]].code.length(), right_index, tree[vertex].sons[i]);
			}
		}

		// statements assure that we find needed node anyway
	}
}


// just one string atom (without spaces)
void processString(string& str, int timing)
{
	if (str[0] >= '2' && str[0] <= '9')
	{
		// finding substring with only a word code and determining respective set
		int afterIndex = -1; // index of '1' or '*' character
		for (int i = 0; i < (int)str.length(); ++i)
		{
			if (str[i] == '*' || str[i] == '1')
			{
				afterIndex = i;
				break;
			}
		}
		// if there is '1' or '*'
		if (afterIndex > 0)
		{
			string code = str.substr(0, afterIndex); // actual word code
			int setInd = setIndex(code, 0, code.length() - 1, 0); // searching respective set
			set<setmember>::iterator it = sets[setInd].begin(); 
			int i = afterIndex;
			for (; i < (int)str.length(); ++i)
			{
				if (str[i] == '*')
				{
					++it;
					if (it == sets[setInd].end())
					{
						it = sets[setInd].begin();
					}
				}
				else
				{
					break;
				}
			}
			//modifying frequency and timing
			int wi = it->word_index; 
			int f = it->freq;
			sets[setInd].erase(it);
			sets[setInd].insert(setmember(wi,f + 1, timing));
			cout << words[wi];

			// if there is other characters after digits and '*'-s, then it is '1'
			if (i < (int)str.length())
			{
				cout << marks[(str.length() - i - 1) % 3];
			}
		}
		else
		{
			// means that all 'str' is word code
			int setInd = setIndex(str, 0, str.length() - 1, 0);
			int wi = sets[setInd].begin()->word_index;
			int f = sets[setInd].begin()->freq;
			sets[setInd].erase(sets[setInd].begin());
			sets[setInd].insert(setmember(wi,f + 1, timing));
			cout << words[wi];
		}
	}
	else // means that all 'str' is like '1' and some '*'-s
	{
		cout << marks[(str.length() - 1) % 3];
	}
}

int main()
{
	marks[0] = '.';
	marks[1] = ',';
	marks[2] = '?';
	
	//at start, only root
	tree.resize(1);
	sets.resize(0);
	tree[0].sons.resize(0);

	int N = 0; // dictionary words amount
	cin >> N;
	words.resize(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> words[i];
		int freq;
		cin >> freq;
		string code(words[i]);
		wordCoding(words[i], code);
		tree_add(i, freq, code, 0, code.length() - 1, 0);
	}

	//now prefix tree is build

	string line;

	getline(cin, line); //after previous input, unreaded line remainder
	getline(cin, line);

	int lastSpace = -1; //index of previous ' ' character
	for (int ind = 0; ind < (int)line.length(); ++ind)
	{
		if (line[ind] == ' ')
		{
			string str = line.substr(lastSpace + 1, ind - lastSpace - 1);
			processString(str, lastSpace + 1);
			cout << " ";
			lastSpace = ind;
		}
	}

	string sub1 = line.substr(lastSpace + 1, line.length() - lastSpace - 1);
	processString(sub1, line.length()); // line remainder

	cout << endl;
	return 0;
}