#include <iostream>
#include <string>
#include <map>

using namespace std;

struct word
{
	string str;
	int freq;
};

typedef multimap<string, word> dic;
typedef multimap<string, word>::iterator itrDict;

class T9 {
public:
	dic dictionary;
	void readDictionary();
	void printWord(string code, int n);
	void makeCode(string str, string &code);
	void readSMS();
};

int main()
{
	T9 t9;
	t9.readDictionary();
	t9.readSMS();
	return 0;
}
void T9::makeCode(string str, string &code)
{
	for (int i=0; str[i]; i++)
	{
		if (str[i] == 'a' || str[i] == 'b' || str[i] == 'c') code += '2';
		if (str[i] == 'd' || str[i] == 'e' || str[i] == 'f') code += '3';
		if (str[i] == 'g' || str[i] == 'h' || str[i] == 'i') code += '4';
		if (str[i] == 'j' || str[i] == 'k' || str[i] == 'l') code += '5';
		if (str[i] == 'm' || str[i] == 'n' || str[i] == 'o') code += '6';
		if (str[i] == 'p' || str[i] == 'q' || str[i] == 'r' || str[i] == 's') code += '7';
		if (str[i] == 't' || str[i] == 'u' || str[i] == 'v') code += '8';
		if (str[i] == 'w' || str[i] == 'x' || str[i] == 'y' || str[i] == 'z') code += '9';
	}
}
void T9::readDictionary(){
	int numWords;
	string code;
	word temp;
	cin >> numWords;
	for (int i = 0; i < numWords; i++)
	{
		cin >> temp.str >> temp.freq;
		makeCode(temp.str, code);
		dictionary.insert(pair<string, word> (code,temp));
		code.clear();
	}
	cin.ignore();
}
void T9::printWord(string code, int n){
	itrDict itr, itr1;
	int i,k;
	word temp;
	itr = dictionary.find(code);
	k = dictionary.count(code);
	if ((k-1) <= n) n=n%k;
	for (i = 0; i < n; i++)
		itr++;
	cout << itr->second.str;
	itr->second.freq++;
	for (; i>0; i--)
	{
		itr1 = itr;
		itr--;
		if (itr1->second.freq >= itr->second.freq)
		{
			temp = itr1->second;
			itr1->second = itr->second;
			itr->second = temp;
		}
	}
}
void T9::readSMS() {
	string s;
	int n=0;
	int j=0;
	char str[100000];
	cin.getline(str, 100000);
	while (str[j])
	{
		if (str[j] == '1')
		{
			if (!s.empty())
			{
				printWord(s, 0);
				s.clear();
			}
			while (str[j+1] == '*')
			{
				j++;
				n++;
			}
			switch (n)
			{
			case 0:
				cout << ".";
				break;
			case 1:
				cout << ",";
				break;
			case 2:
				cout << "?";
			}
				n = 0;
		}
		else if (str[j] == '*')
			{
				n = 1;
				while (str[j+1] == '*')
				{
					j++;
					n++;
				};
				if (!s.empty())
				{
					printWord(s, n);
					s.clear();
				}
				n = 0;
			}
		else if (str[j] == ' ')
			{
				if (!s.empty())
				{
					printWord(s, 0);
					s.clear();
				}
				cout << " ";
			}
		else
			{
				s+=str[j];
				if (!str[j+1] && !s.empty())
					printWord(s, 0);
			}
		j++;
	}
}