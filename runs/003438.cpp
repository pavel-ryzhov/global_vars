#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <queue>
#include <stack>
#include <map>
using namespace std;
map <char, char> numbers;				///<������ ��������. ������ �������, � ����� ��������������� ������� ������.>

///<��������� �������. ���� ��������� �������� ������ � ������� ������� (priority),>
///<��������� ������(last_call) �����(text).>
struct Word{
	int priority; 
	int last_call;
	string text;  
};

///<Declarations>
typedef map <string, priority_queue <Word> > type;
bool operator < (const Word&, const Word&);        ///<���������� ��������� ��������� ��� �������� Word.>

void buttons();									   ///<������� �������� ������� ������� � ������(������� ������).>
void input(string&, type&);						   ///<������ ������� ������>
void find(string&, string&, type&);				   ///<����� ���� � ����������� ��������������� ���������.>
string inv_T9(string&);							   ///<������� ����� � ����� ����, ������� ��������� ������>
												   ///<�� ����������, ��� ����� ������� �����.>


int main()
{
	///<�������(dictionary). ���������: ������� �������� � ������������� �������(map), ��� ������>
	///<�������� �������� ����� �����(��������: 228(��� ������������� ����� act)), ��������,>
	///<��������������� � �������� ������ - ��� ������� � ������������, � ���������� �������>
	///<�������� ��������� ��������� Word, ����������� ������ �����.>
	type dictionary;								
	string result, line_set;						///<���������� ��������� � ������� ������.>

	buttons();
	input(line_set, dictionary);
	find(line_set, result, dictionary);
	
	cout << result << endl;							///<������ ����������.>
	return 0;
}

///<���������� ��������� ���������.>
///<���������� ����� � ������� �� ������� �������������, ���� ��� �����,>
///<�� �� ���������� ������, ���� ����� ��� �� ����������, ��>
///<� ������������������ �������.>
bool operator < (const Word& lh, const Word& rh)
{
	if(lh.priority == rh.priority)
		if(lh.last_call == rh.last_call){
			if(strcmp(lh.text.data(), rh.text.data()) <= 0)
				return false;
			else return true;
		}
		else
			return lh.last_call < rh.last_call;

	return lh.priority < rh.priority;
}

///<������������ ������ ������ �������� � ������� ������ �� ����������.>
void buttons()
{
	char c = '2'; 
	int count = 0;
	string str = "abcdefghijklmnoqrstuvwxy";

	for(int i = 2; i < 10; i++, c++)
		for(int j = 0; j < 3; j++)
			numbers[str[count++]] = c;
	numbers['z'] = '9';
	numbers['p'] = '7'; 
}

///<������� ����� �� ���������� ���� � ��������.>
string inv_T9(string& s_word)
{
	string ret = "";
	for(unsigned int i = 0; i < s_word.length(); ++i)
		ret += numbers[s_word[i]];
	return ret;
}


void input(string& line_set, type& dictionary)
{
	int N;
	cin >> N;

	Word temp;
	for(int i = 0; i < N; ++i) {
		cin >> temp.text >> temp.priority;
		temp.last_call = 0;
		dictionary[inv_T9(temp.text)].push(temp);    ///<���������� �������.>
	}
	cin.get();

	line_set.reserve(100001);
	getline(cin, line_set);
}

void find(string& line_set, string& result, type& dictionary)
{
	stack <Word> st;
	string sq, temp_sq;
	string one[3] = {".", ",", "?"};
	unsigned int count(0), index(0), step(0), i;

	istringstream stream(line_set);							///<���������� ������ �� ������� ������>

	for(; index < line_set.length() && line_set[index] == ' '; index++) ///<������ �������� ����� ������ ������>
		result += ' ';

	bool check = true;
	while(!check || (check && !stream.eof()))
	{
		if(check){
			stream >> sq;				///<������ ������>
			i = 0; 
		}
		step = 0;
		temp_sq = "";
		for(; i < sq.length() && sq[i] != '1' && sq[i] != '*'; i++)  ///<������� � ������ �������� ��� �����>
			temp_sq += sq[i];

		for(; i < sq.length() && sq[i] == '*'; i++)                  ///<������� ���������� ��������� ����� ����>
			step++;

		type::iterator iter = dictionary.find(temp_sq);				 ///<������� ������ ��� � �������>
		if(iter != dictionary.end())
		{
			if(step >= iter->second.size())							 ///<���� ���������� ��������� ������ ��� ���� � ������� ���������������>
				step = step % iter->second.size();					 ///<������� ����, �� ����� ��� ���-�� �� ���������� ���� ����.>

			while(step > 0)
			{
				st.push(iter->second.top());						 ///<������� �� ������� ����� � ������� ��������� ����������.>
				iter->second.pop();									 ///<(���-�� ���� ������������ ���-� ��������� ����� ����)>
				--step;												 ///<� ��������� ��� ����� � ����.>
			}		
			result += iter->second.top().text;						 ///<�������� � �������������� ������ �������� �����>

			st.push(iter->second.top());
			iter->second.pop();
			st.top().priority++;									 ///<����������� ������� ������������� ��������� �����>
			st.top().last_call = ++count;							 ///<� ����������� �������� ���������� ������ (�� �������������)>	

			while(!st.empty())
			{	
				dictionary[temp_sq].push(st.top());					 ///<��������� ����� �� ����� ������� � �������>
				st.pop();
			}
		}	
		while(i < sq.length() && sq[i] == '1')
		{			
			for(i++, step = 0; i < sq.length() && sq[i] == '*'; i++) ///<��������� � ������ ����� ����������(���� ����������)>
				step++;
			result += one[step % 3];
		}
		check = (i < sq.length())? false: true;
		if(check)			
			for(index += sq.length(); index < line_set.length() && line_set[index] == ' '; index++) ///<���������� ������� ����� �����.>
				result += ' ';

		if(index == line_set.length()) break;
	}	
}