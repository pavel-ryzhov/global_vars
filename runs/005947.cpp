#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

template <class type1, class type2, class type3>
class trio
{
public:
	trio()
	{}
	trio(type1 f, type2 s, type3 t) : first(f), second(s), third(t)
	{}
	type1 first;
	type2 second;
	type3 third;
};
void Parse(const string &input, vector <string> &result);
int StrToInt(const string &str);
void Find(const string &search, int char_pos, int leftb, int rightb);
void Comb(char c, int char_pos);
bool MySortASC(int i,int j);
bool MySortRating(int i,int j);

const string BUTTONS[9] = {".,?", "abc", "def",
						   "ghi", "jkl", "mno",
						   "pqrs","tuv", "wxyz"};
vector < trio < string, int, int > > dict;
int updated = 0;
string shortcuts, output;
vector <int> search_result;

int main ()
{
	string input;
	getline(cin, input);
	int n = StrToInt(input);
	vector <string> result(2, "");
	dict.resize(n);
	for(int i = 0; i < n; i++)
	{
		getline(cin, input);
		Parse(input, result);
		dict[i].first  = result[0];
		dict[i].second = StrToInt(result[1]);
		dict[i].third  = 0;
	}
	getline(cin, input);
	int char_pos = -1;
	for(size_t i = 0; i < input.size(); i++)
	{
		if(input[i] != '*' && input[i] != ' ' && input[i] != '1')
		{
			if(search_result.size() != 0 && search_result[0] < 0 )
			{
				output.push_back(BUTTONS[0][ -search_result[0] - 1 ]);
				search_result.clear();
			}
			char_pos++;
			Comb(input[i], char_pos);
		}
		if(input[i] == '*' && search_result.size() != 0)
		{
			if(search_result.size() != 0 && search_result[0] < 0 )
			{
				search_result.erase(search_result.begin());
			}
			else
			{
				while(dict[ search_result[0] ].first.size() != (size_t)(char_pos + 1) )
				{
					search_result.erase(search_result.begin());
				}
				search_result.erase(search_result.begin());
			}
		}
		if(input[i] == ' ')
		{
			if(search_result.size() != 0 && search_result[0] < 0 )
			{
				output.push_back(BUTTONS[0][ -search_result[0] - 1 ]);
				search_result.clear();
			}
			if(search_result.size() != 0)
			{

				while(dict[ search_result[0] ].first.size() != (size_t)(char_pos + 1) )
				{
					search_result.erase(search_result.begin());
				}
				dict[ search_result[0] ].second += 1;
				dict[ search_result[0] ].third = ++updated;
				output.append(dict[ search_result[0] ].first);
				search_result.clear();
			}
			output.push_back(' ');
			char_pos = -1;
		}
		if(input[i] == '1')
		{
			if(search_result.size() != 0 && search_result[0] < 0 )
			{
				output.push_back(BUTTONS[0][ -search_result[0] - 1 ]);
				search_result.clear();
			}
			if(search_result.size() != 0)
			{
				while(dict[ search_result[0] ].first.size() != (size_t)(char_pos + 1) )
				{
					search_result.erase(search_result.begin());
				}
				dict[ search_result[0] ].second += 1;
				dict[ search_result[0] ].third = ++updated;
				output.append(dict[ search_result[0] ].first);
				search_result.clear();
			}
			char_pos = -1;
			search_result.push_back(-1);
			search_result.push_back(-2);
			search_result.push_back(-3);
		}
	}
	if(search_result.size() != 0 && search_result[0] < 0 )
	{
		output.push_back(BUTTONS[0][ -search_result[0] - 1 ]);
		search_result.clear();
	}
	if(search_result.size() != 0)
	{
		while(dict[ search_result[0] ].first.size() != (size_t)(char_pos + 1) )
		{
			search_result.erase(search_result.begin());
		}
		output.append(dict[ search_result[0] ].first);
	}
	cout<<output;
}

void Parse(const string &input, vector <string> &result)
{
	int pos = input.find(" ");
	string substr1, substr2;
	substr1 = input.substr(0, pos);
	substr2 = input.substr(pos+1, input.size()-pos);
	result[0] = substr1;
	result[1] = substr2;
}
int StrToInt(const string &str)
{
	istringstream iss (str, istringstream::in);
	int n;
	iss>>n;
	return n;
}
void Find(const string &search, int char_pos, int leftb, int rightb)
{
	int mid, last, length = search.length();
	last = rightb;
	if(char_pos == 0)
	{
		while(leftb < rightb)
		{
			 mid = leftb + (rightb - leftb) / 2;
			if(search.compare(0, length, dict[ search_result[mid] ].first, char_pos, length) <= 0)
			{
				rightb = mid;
			}
			else if(search.compare(0, length, dict[ search_result[mid] ].first, char_pos, length) > 0)
			{
				leftb = mid+1;
			}
		}
		if(search.compare(0, length, dict[ search_result[rightb] ].first, char_pos, length) == 0)
		{
			for(int i = rightb; i <= last; i++)
			{
				if(search.compare(0, length, dict[ search_result[i] ].first, char_pos, length) == 0) search_result.push_back(search_result[i]);
			}
		}
	}
	else
	{
		for(int i = leftb; i <= last; i++)
		{
			if(search.compare(0, length, dict[ search_result[i] ].first, char_pos, length) == 0) search_result.push_back(search_result[i]);
		}
	}
}

void Comb(char c, int char_pos)
{
	string word;
	if(search_result.size() == 0)
	{
		for(size_t i = 0; i<dict.size(); i++) search_result.push_back(i);
	}
	int number_of_chars = static_cast<int>( BUTTONS[ c - '0' - 1].size() );
	int size = static_cast<int>( search_result.size() ) - 1;
	for(int i = 0; i < number_of_chars; i++)
	{
		word = BUTTONS[ c - '0' - 1][i];
		Find(word, char_pos, 0, size);
	}
	search_result.erase(search_result.begin(), search_result.begin() + size + 1);
	sort(search_result.begin(), search_result.end(), MySortASC);
	sort(search_result.begin(), search_result.end(), MySortRating);
}

bool MySortASC(int i,int j)
{
	return (dict[i].first < dict[j].first);
}

bool MySortRating(int i,int j)
{
	if(dict[i].second == dict[j].second)
	{
		if(dict[i].third == dict[j].third) return (dict[i].first < dict[j].first);
		return (dict[i].third > dict[j].third);
	}
	else return  (dict[i].second > dict[j].second);
}

