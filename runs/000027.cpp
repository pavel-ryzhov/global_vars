#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <map>
//#include <fstream>
using namespace std;
map <char, char> numbers;

struct Word{
public:
	int priority; 
	int last_call;
	string text;  
};

bool operator < (const Word& lh, const Word& rh)
{
	if(lh.priority == rh.priority)
		return lh.last_call < rh.last_call;

	return lh.priority < rh.priority;
}

typedef map <string, priority_queue <Word> > type;

void buttons()
{
	string str = "abcdefghijklmnoqrstuvwxy";

	char c = '2'; 
	int count = 0;
	for(int i = 2; i < 10; i++, c++)
		for(int j = 0; j < 3; j++)
			numbers[str[count++]] = c;
	numbers['z'] = --c;
	numbers['p'] = '7'; 
}

string inv_T9(string& s_word)
{
	string ret = "";
	for(unsigned int i = 0; i < s_word.length(); ++i)
		ret += numbers[s_word[i]];
	return ret;
}

void input(string& line_set, type& dictionary)
{
	//ifstream cin("test.txt", ios::in | ios::app);
	int N;
	cin >> N;
	
	Word temp;
	for(int i = 0; i < N; ++i) {
		cin >> temp.text >> temp.priority;
		temp.last_call = 0;
		dictionary[inv_T9(temp.text)].push(temp);
	}
	cin.get();
	getline(cin, line_set);
	//cin.close();
}


int main()
{
	type dictionary;
	stack <Word> st;
	string one[3] = {".", ",", "?"};
	string line_set, sq, temp_sq, result;
	unsigned int count(0), index(0), step(0), i;

	line_set.reserve(100001);

	buttons();
	input(line_set, dictionary);

	istringstream stream(line_set);

	for(; index < line_set.length() && line_set[index] == ' '; index++)
		result += ' ';

	while(!stream.eof())
	{
		stream >> sq;
		i = 0; step = 0;
		temp_sq = "";
		for(; i < sq.length() && sq[i] != '1' && sq[i] != '*'; i++)
			temp_sq += sq[i];

		for(; i < sq.length() && sq[i] == '*'; i++)
			step++;

		type::iterator iter = dictionary.find(temp_sq);
		if(step >= iter->second.size())
			step = step % iter->second.size();

		while(step > 0)
		{
			st.push(iter->second.top());
			iter->second.pop();
			--step;
		}		
		result += iter->second.top().text;
		count += 2;
		st.push(iter->second.top());
		iter->second.pop();
		st.top().priority++;
		st.top().last_call = count;
		index += sq.length();

		while(!st.empty())
		{
			st.top().last_call++;
			dictionary[temp_sq].push(st.top());
			st.pop();
		}

		while(i < sq.length())
		{
			if(i < sq.length() && sq[i++] == '1')
				for(; i < sq.length() && sq[i] == '*'; i++)
					step++;
			
			result += one[step % 3];
		}	
		for(; index < line_set.length() && line_set[index] == ' '; index++)
			result += ' ';
		if(index == line_set.length()) 
		break;
	}
	
	cout << result << endl;
	return 0;
}