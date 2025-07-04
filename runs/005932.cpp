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
int Find(const string &search, int leftb, int rightb);
bool MySort(int i,int j);
void Comb();

const string BUTTONS[9] = {".,?", "abc", "def",
						   "ghi", "jkl", "mno",
						   "pqrs","tuv", "wxyz"};
vector < trio < string, int, int > > dict;
int updated, n;
string shortcuts, output;
vector <int> search_result;

int main ()
{
	updated = 0;
	string input;
	getline(cin, input);
	n = StrToInt(input) + 3;
	vector <string> result(2, "");
	dict.resize(n);
	dict[0].first = ",";
	dict[0].second = 1;
	dict[0].third = 0;
	dict[1].first = ".";
	dict[1].second = 2;
	dict[1].third = 0;
	dict[2].first = "?";
	dict[2].second = 0;
	dict[2].third = 0;
	for(int i = 3; i < n; i++)
	{
		getline(cin, input);
		Parse(input, result);
		dict[i].first  = result[0];
		dict[i].second = StrToInt(result[1]);
		dict[i].third  = 0;
	}
	getline(cin, input);
	for(size_t i = 0; i < input.size(); i++)
	{
		if(input[i] != '*' && input[i] != ' ' && input[i] !='1')
		{
			shortcuts.push_back(input[i]);
		}
		if(input[i] == '*' && search_result.size() != 0)
		{
			search_result.erase(search_result.begin());
		}
		if(input[i] == '*' && search_result.size() == 0 && shortcuts.size() != 0)
		{
			Comb();
			search_result.erase(search_result.begin());
		}
		if( ( input[i] == '1' || input[i] == ' ' || ( input.size() - i ) == 1))
		{
			if(search_result.size() == 0 && shortcuts.size() != 0) Comb();
			if(shortcuts[0] != '1')
			{
				(dict[ search_result[0] ].second)++;
				(dict[ search_result[0] ].third) = ++updated;
			}
			if(search_result.size() != 0) output.append(dict[ search_result[0] ].first);
			shortcuts.clear();
			if(input[i] == ' ') output.push_back(' ');
			search_result.clear();
			if(input[i] == '1')
			{
				shortcuts.push_back(input[i]);
				Comb();
			}
		}

	}
	if(search_result.size() != 0)
	{
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
int Find(const string &search, int leftb, int rightb)
{
	int mid;
	while(leftb < rightb)
	{
		 mid = leftb + (rightb - leftb) / 2;
		if(search < dict[mid].first)
		{
			rightb = mid - 1;
		}
		else if(search > dict[mid].first)
		{
			leftb = mid + 1;
		}
		else return mid;
	}
	return (search == dict[leftb].first) ? leftb : -1;
}

bool MySort(int i,int j)
{
	if(dict[i].second == dict[j].second)
	{
		return (dict[i].third > dict[j].third);
	}
	else return  (dict[i].second > dict[j].second);
}
void Comb()
{
	int number_of_shortcuts = static_cast<int>(shortcuts.size());
	vector <int> comb (number_of_shortcuts, 0);
	while(true)
	{
		for(int j = number_of_shortcuts - 1; j > 0; j--)
		{
			int number_of_chars = static_cast<int>( BUTTONS[ shortcuts[j]- '0' - 1].size() );
			if(comb[j] == number_of_chars)
			{
				comb[j-1] += 1;
				comb[j] = 0;
			}
		}
		if(comb[0] == static_cast<int>( BUTTONS[ shortcuts[0] - '0' - 1].size() )) break;
		string word;
		for(int z = 0; z < number_of_shortcuts; z++) word.push_back( ( BUTTONS[ shortcuts[z] - '0' -1 ] )[ comb[z] ]  );
		int f = Find(word, 0, n-1);
		if(f != -1) search_result.push_back(f);
		comb[number_of_shortcuts-1] += 1;
	}
	sort(search_result.begin(), search_result.end(), MySort);
}
