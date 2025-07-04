#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <stdio.h>

#define MAX_WORD 21
#define MAX_STR 100001

using namespace std;

struct Word
{
	char * word;
	char * code;
	int frequency;
};

struct Word1
{
	string word;
	int frequency;
};

struct Keyboard
{
	string code;
	int number;
};

//globals
int N;
map <string ,vector <Word1> > dictionary;

 
//get code from string 
string getCode(string str1)
{
	string str;
	str.assign(str1);
	int i = 0;
	while (i < str.length())
	{
		switch(str[i])
		{
			case 'a': 
			case 'b': 
			case 'c': str[i] = '2'; break;
			case 'd': 
			case 'e': 
			case 'f': str[i] = '3'; break;
			case 'g': 
			case 'h': 
			case 'i': str[i] = '4'; break;
			case 'j': 
			case 'k': 
			case 'l': str[i] = '5'; break;
			case 'm': 
			case 'n': 
			case 'o': str[i] = '6'; break;
			case 'p': 
			case 'q': 
			case 'r': 
			case 's': str[i] = '7'; break;
			case 't': 
			case 'u': 
			case 'v': str[i] = '8'; break;
			case 'w': 
			case 'x': 
			case 'y': 
			case 'z': str[i] = '9'; break;
		}
		i++;
	}
	return str;
}

//sign handler
void findSign (int number)
{
	switch(number % 3)
	{
	case 0:
		cout << '.';
		break;
	case 1:
		cout << ',';
		break;
	case 2:
		cout << '?';
		break;
	};
}

//quick previous sort
bool prevSort(Word1 a, Word1 b)
{
	if (a.frequency == b.frequency)
		return a.word.compare(b.word) < 0;
	else 
		return a.frequency > b.frequency;
}

//sort dictionary depends on user
void specialSort(string str, int num, int freq)
{
	while (num != 0)
	{
		if(freq >= dictionary[str][num - 1].frequency)
		{
			swap(dictionary[str][num], dictionary[str][num - 1]);
			num --;
		}
		else
		{
			break;
		}
	}
}

//word handler
void findWord (Keyboard keyboard)
{
	string str = keyboard.code;
	int num = keyboard.number;
	cout << dictionary[str][num].word;
	dictionary[str][num].frequency += 1;
	int freq = dictionary[str][num].frequency;
	specialSort(str, num, freq);
}


int main(int argc, char * argv[])
{
	//input
	cin >> N;
	
	for(int i = 0; i < N; i++)
	{
		string inpStr;
		string local;
		string code;
		Word1 wrd;

		cin >> inpStr;
		wrd.word = inpStr;
	
		local = getCode(inpStr);
		code = local;

		cin >> wrd.frequency;	
		
		dictionary[code].push_back(wrd);
	}

	//sort our dictionary
	for(map <string,vector <Word1> >::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		sort(it->second.begin(),it->second.end(),prevSort);
	}

        for (map <string,vector <Word1> >::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			cout << it->second[i].word << endl;
		}
        }
	
	//text parse
	int cnt = 0;
	string tempStr;

	//mode: 0 - space ; 1 - word ; 2 - sign ; 4 - eoln ;
	//flag: true - star false none
	bool flag = false;
	int mode = 0;
	int star = 0;
	char ch;

        ch = getc(stdin);
        ch = getc(stdin);
	while(1)
	{
                ch = getc(stdin);
		//get string
		switch(ch)
		{
		case '1':
			if(mode == 1)
			{
				Keyboard a;
				a.code = tempStr;
				a.number = star;
				findWord(a);
				star = 0;
				tempStr.clear();
			}
			if(mode == 2)
			{
				findSign(star);
				star = 0;
			}
			mode = 2;
			break;
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if(mode == 0)
			{
				tempStr.append(&ch);
				star = 0;
			}
			if(mode == 1)
			{
				tempStr.append(&ch);
				star = 0;
			}
			if(mode == 2)
			{
				findSign(star);
				star = 0;
				tempStr.append(&ch);
			}
			mode = 1;
			break;
		case '*':
			if(mode == 1)
			{
				star ++;
			}
			if(mode == 2)
			{
				star ++;
			}
			break;
		case ' ':
			if(mode == 1)
			{
				Keyboard a;
				a.code = tempStr;
				a.number = star;
				findWord(a);
				star = 0;
				tempStr.clear();
			}
			if(mode == 2)
			{
				findSign(star);
				star = 0;
			}
			cout << ' ';
			mode = 0;
			break;
		case '\n':
		case '\0':
		case '\r':
		case EOF:
			if(mode == 1)
			{
				Keyboard a;
				a.code = tempStr;
				a.number = star;
				findWord(a);
				star = 0;
				tempStr.clear();
			}
			if(mode == 2)
			{
				findSign(star);
				star = 0;
			}
			mode = 4;
			break;
		};
		cnt ++;
		if (mode == 4)
			break;
	}
	
	cout << endl;
	
	dictionary.clear();

	return 0;
}
