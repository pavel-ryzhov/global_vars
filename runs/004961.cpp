#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

struct Word //структура "Слово"
{
	string str;
	int input_fmt;
	int hits;
};

list<Word> dictionary; //словарь
int words_num; //число слов в словаре
int text_n; //число слов в строке
void setStr(Word, string, int); //задание слова
void makeDict(); //создание словаря
string analizeText(string); //анализ входного текста
string* split(string); //разбиение строки на подстроки
string analizeWord(string);
void hitAdd(list<Word>::iterator);
int strtoi(string);


//перегрузка операторов сравнения
bool operator<(const Word&, const Word&);
bool operator>(const Word&, const Word&);
bool operator==(const Word&, const Word&);

bool operator<(const Word& A, const Word& B)
{
	if(A.hits < B.hits) return true;
	return false;
}

bool operator>(const Word& A, const Word& B)
{
	if(A.hits > B.hits) return true;
	return false;
}

bool operator==(const Word& A, const Word& B)
{
	if(A.hits == B.hits) return true;
	return false;
}

void setStr(Word* wd, string s, int ht)
{
	(*wd).str = s;
	int k = 0, button = 0;
	(*wd).input_fmt = 0;
	(*wd).hits = ht;
	for(int i = (*wd).str.length() - 1; i >=0; i--)
	{
		switch((*wd).str[i])
		{
			case 'a':
			case 'b':
			case 'c': button = 2;
				break;
			case 'd':
			case 'e':
			case 'f': button = 3;
				break;
			case 'g':
			case 'h':
			case 'i': button = 4;
				break;
			case 'j':
			case 'k':
			case 'l': button = 5;
				break;
			case 'm':
			case 'n':
			case 'o': button = 6;
				break;
			case 'p':
			case 'q':
			case 'r': 
			case 's': button = 7;
				break;
			case 't':
			case 'u':
			case 'v': button = 8;
				break;
			case 'w':
			case 'x':
			case 'y': 
			case 'z': button = 9;
				break;
			default: button = 0;
				break;
		}
		(*wd).input_fmt += button * (int)pow(10.0, k);
		k++;
	}
}

void makeDict()
{
	Word wd;
	string str;
	int ht;

	for(int i = 0; i < words_num; i++)
	{
		cin >> str >> ht;
		setStr(&wd, str, ht);
		dictionary.push_back(wd);
	}
	dictionary.sort(greater<Word>());
}

string analizeText(string istr)
{
	string res = "";
	string* text = split(istr);
	for(int i = 0; i < text_n; i++)
	{
		text[i] = analizeWord(text[i]);
		res += text[i] + " ";
	}

	return res;
}

string analizeWord(string wrd)
{
	int main_part, pos, npos = -1;
	string other = "", res = "", tmp;
	
	int pos_ind = wrd.find_first_of('*');
	int oth_ind = wrd.find_first_of('1');
	if((oth_ind < pos_ind) && (oth_ind != npos)) 
		pos_ind = npos;

	//определение позиции в словаре
	if(pos_ind == npos)
		pos = 1;
	else if(oth_ind != npos) pos = oth_ind - pos_ind + 1;
	else pos = (int)wrd.size() - pos_ind + 1;
	
	//определение цифровой главной части
	if(pos_ind == npos && oth_ind == npos) main_part = strtoi(wrd);
	else if(pos_ind != npos) main_part = strtoi(wrd.substr(0, pos_ind));
	else main_part = strtoi(wrd.substr(0, oth_ind));
	
	//расшифровка основной части
	list<Word>::iterator it = dictionary.begin();
	while(pos > 0)
	{
		if((*it).input_fmt == main_part)
		{
			pos--;
			res = (*it).str;
			if(!pos) 
			{
				hitAdd(it);
				break;
			}
		}
		it++;
		if(it == dictionary.end()) 
			it = dictionary.begin();
	}
	
	//знак препинания
	if(oth_ind != npos) 
	{
		other = wrd.substr(oth_ind, wrd.size());
		int oth_pos = (other.length() - 1) % 3;
		switch(oth_pos)
		{
		case 0: other = ".";
			break;
		case 1: other = ",";
			break;
		case 2: other = "?";
			break;
		default: break;
		}
	}

	return res + other;
}

void hitAdd(list<Word>::iterator p)
{
	(*p).hits++;
	
	for(list<Word>::iterator i = dictionary.begin(); i != dictionary.end(); ++i)
	{
		if(i != p)
			if((*i).input_fmt == (*p).input_fmt && (*i).hits == (*p).hits) 
			{
				dictionary.insert(i, (*p));
				dictionary.erase(p);
				dictionary.sort(greater<Word>());
				break;
			}
	}
}

string* split(string str)
{
	string* res;
	vector<string> res_v;
	string temp = "";
	text_n = 0;

	for(size_t i = 0; i < str.length(); i++)
	{
		if(str[i] == ' ')
		{
			res_v.push_back(temp);
			temp = "";
			text_n++;
			continue;
		}
		temp.append(1, str[i]);
	}
	text_n++;
	res_v.push_back(temp);

	res = new string[text_n];
	for(int i = 0; i < text_n; i++)
		res[i] = res_v[i];

	return res;
}

int strtoi(string s)
{
	int k;
	int res = 0;
	for(size_t i = 0; i < s.size(); i++)
	{
		switch(s[i])
		{
		case '0': k = 0;
			break;
		case '1': k = 1;
			break;
		case '2': k = 2;
			break;
		case '3': k = 3;
			break;
		case '4': k = 4;
			break;
		case '5': k = 5;
			break;
		case '6': k = 6;
			break;
		case '7': k = 7;
			break;
		case '8': k = 8;
			break;
		case '9': k = 9;
			break;
		default: break;
		}
		int y = s.size() - i - 1;
		res += k * pow(10.0, y);
	}
	return res;
}

int main()
{
	string txt = "";
	cin >> words_num;
	makeDict();
	cin.get();
	getline(cin, txt);
	cout << analizeText(txt);
	return 0;
}