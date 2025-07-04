#include <iostream>
#include <stdio.h>
#include "string"
#include "vector"
#include "queue"
using namespace std;

struct Word
{
	string word;
	int freq;
	int last;
};

int N;
struct Word *Dictionary;

void read()
{
	cin >> N;
	Dictionary = new struct Word[N];
	for (int i = 0; i < N; i++)
	{
		cin >> Dictionary[i].word;
		cin >> Dictionary[i].freq;
		Dictionary[i].last = 0;
	}
}

string getWord(string current_word, int star)
{
	int i = 0;
	char c;
	vector<int> temp;
	int max_last = 0;
	c = current_word[i++];
	for (int j = 0; j < N; j++)
	{
		if ((c == '2') && (Dictionary[j].word[0] == 'a' || Dictionary[j].word[0] == 'b' || Dictionary[j].word[0] == 'c'))
			temp.push_back(j);
		if ((c == '3') && (Dictionary[j].word[0] == 'd' || Dictionary[j].word[0] == 'e' || Dictionary[j].word[0] == 'f'))
			temp.push_back(j);
		if ((c == '4') && (Dictionary[j].word[0] == 'g' || Dictionary[j].word[0] == 'h' || Dictionary[j].word[0] == 'i'))
			temp.push_back(j);
		if ((c == '5') && (Dictionary[j].word[0] == 'j' || Dictionary[j].word[0] == 'k' || Dictionary[j].word[0] == 'l'))
			temp.push_back(j);
		if ((c == '6') && (Dictionary[j].word[0] == 'm' || Dictionary[j].word[0] == 'n' || Dictionary[j].word[0] == 'o'))
			temp.push_back(j);
		if ((c == '7') && (Dictionary[j].word[0] == 'q' || Dictionary[j].word[0] == 'r' || Dictionary[j].word[0] == 's'))
			temp.push_back(j);
		if ((c == '8') && (Dictionary[j].word[0] == 't' || Dictionary[j].word[0] == 'u' || Dictionary[j].word[0] == 'v'))
			temp.push_back(j);
		if ((c == '9') && (Dictionary[j].word[0] == 'w' || Dictionary[j].word[0] == 'x' || Dictionary[j].word[0] == 'y' || Dictionary[j].word[0] == 'z'))
			temp.push_back(j);
	}
	for (int j = 0; j < temp.size(); j++)
		if (Dictionary[temp[j]].word.size() != (current_word.size() - 1))
			temp.erase(temp.begin() + j);
	if (temp.size() == 1)
	{
		Dictionary[temp[0]].freq++;
		max_last = 0;
		for (int j = 0; j < N; j++)
		{
			if (Dictionary[j].last > max_last)
				max_last = Dictionary[i].last;
		}
		Dictionary[temp[0]].last = max_last + 1;
		return Dictionary[temp[0]].word;
	}
	else while (c = current_word[i] != '#')
	{
		for (int j = 0; j < temp.size(); j++)
		{
			if ((c == '2') && !(Dictionary[temp[j]].word[i] == 'a' || Dictionary[j].word[i] == 'b' || Dictionary[j].word[i] == 'c'))
				temp.erase(temp.begin() + j);
			if ((c == '3') && !(Dictionary[temp[j]].word[i] == 'd' || Dictionary[j].word[i] == 'e' || Dictionary[j].word[i] == 'f'))
				temp.erase(temp.begin() + j);
			if ((c == '4') && !(Dictionary[temp[j]].word[i] == 'g' || Dictionary[j].word[i] == 'h' || Dictionary[j].word[i] == 'i'))
				temp.erase(temp.begin() + j);
			if ((c == '5') && !(Dictionary[temp[j]].word[i] == 'j' || Dictionary[j].word[i] == 'k' || Dictionary[j].word[i] == 'l'))
				temp.erase(temp.begin() + j);
			if ((c == '6') && !(Dictionary[temp[j]].word[i] == 'm' || Dictionary[j].word[i] == 'n' || Dictionary[j].word[i] == 'o'))
				temp.erase(temp.begin() + j);
			if ((c == '7') && !(Dictionary[temp[j]].word[i] == 'q' || Dictionary[j].word[i] == 'r' || Dictionary[j].word[i] == 's'))
				temp.erase(temp.begin() + j);
			if ((c == '8') && !(Dictionary[temp[j]].word[i] == 't' || Dictionary[j].word[i] == 'u' || Dictionary[j].word[i] == 'v'))
				temp.erase(temp.begin() + j);
			if ((c == '9') && !(Dictionary[temp[j]].word[i] == 'w' || Dictionary[j].word[i] == 'x' || Dictionary[j].word[i] == 'y' || Dictionary[j].word[i] == 'z'))
				temp.erase(temp.begin() + j);
		}
		i++;
	}
	if (temp.size() == 1)
	{
		Dictionary[temp[0]].freq++;
		max_last = 0;
		for (int j = 0; j < N; j++)
		{
			if (Dictionary[j].last > max_last)
				max_last = Dictionary[i].last;
		}
		Dictionary[temp[0]].last = max_last + 1;
		return Dictionary[temp[0]].word;
	}
	else 
	{
		bool t = true;
		while(t)
		{
			t = false;
			for (int j = 0; j < temp.size() - 1; j++)
			{
				if (Dictionary[temp[j+1]].freq > Dictionary[temp[j]].freq)
				{
					int k = temp[j];
					temp[j] = temp[j+1];
					temp[j+1] = k;
					t = true;
				}
				else if (Dictionary[temp[j+1]].freq == Dictionary[temp[j]].freq)
				{
					if (Dictionary[temp[j+1]].last > Dictionary[temp[j]].last)
					{
						int k = temp[j];
						temp[j] = temp[j+1];
						temp[j+1] = k;
						t = true;
					}
				}
			}
		}
		Dictionary[temp[star]].freq++;
		max_last = 0;
		for (int j = 0; j < N; j++)
		{
			if (Dictionary[j].last > max_last)
				max_last = Dictionary[j].last;
		}
		Dictionary[temp[star]].last = max_last + 1;
		return Dictionary[temp[star]].word;
	}
	return "word";
}

int main()
{
	read();
	getchar();
	char c = getchar();
	string result = "";
	string current_word = "";
	int star = 0;
	while(c != '\n')
	{
		if(c == '1')
		{ 
			if(!current_word.empty())
			{
				current_word += '#';
				result += getWord(current_word, star);
				star = 0;
				current_word = "";
			}
			c = getchar();
			while(c == '*')
			{
				star++;
				c = getchar();
			}
			switch(star)
			{
				case 0: 
					result += ".";
					star = 0;
					break;
				case 1:
					result += ",";
					star = 0;
					break;
				case 2:
					result += "?";
					star = 0;
					break;
			}
		}
		else if((c >= '2') && (c <= '9'))
		{
			current_word += c;
			c = getchar();
		}
		else if(c == '*')
		{
			star++;
			c = getchar();
		}
		else if(c == ' ')
		{
			if(!current_word.empty())
			{
				current_word += '#';
				result += getWord(current_word, star);
				star = 0;
				current_word = "";
			}
			result += c;
			c = getchar();
		}
	}
	if(!current_word.empty())
	{
		current_word += '#';
		result += getWord(current_word, star);
		star = 0;
		current_word = "";
	}
	result += '\n';
	cout << result;
}
