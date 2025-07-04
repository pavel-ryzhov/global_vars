//============================================================================
// Name        : problem3.cpp
// Author      : Toporkov P.
// Version     :
// Copyright   :
// Description : Problem3 Solution
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
//Global variables
const string keyboard[]={
		"0",
		".,?",
		"abc",
		"def",
		"ghi",
		"jkl",
		"mno",
		"pqrs",
		"tuv",
		"wxyz",
};



class word {
public:
	word(string _name, int _freq);
	int GenerateKey( string name);
	void print();
	int GetFreq(){return this->frequency;}
	int GetKey(){return this->key;}
	string GetName(){return this->name;}
	void IncFreq(){this->frequency++;}
private:
	string name;
	int frequency;
	int key;
};


word::word(string _name, int _freq)
{
	this->name=_name;
	this->frequency=_freq;
	this->key=GenerateKey(_name);
}

void word::print()
{
	cout << "name=" << this->name <<" freq=" << this->frequency << " key=" << this->key<< endl;
}

int word::GenerateKey(string name)
{
	int key=0;

	for (unsigned int i=0; i<name.length();i++){
		for (int j=0; j<9; j++) {
			if (keyboard[j].find_first_of(name[i],0)!=string::npos)
			{
				key*=10; //Appending value to key
				key+=j;
			}
		}
	}
	return key;
}
vector <word> dict;




// Functions
bool FreqComp(word w1, word w2)
{
	return w1.GetFreq() > w2.GetFreq();
}

string translate(int key, int shift)
{
	string out;

	if (key == 1)
		return keyboard[1].substr(shift,1);
	for (unsigned int i=0; i<dict.size(); i++)
	{
		if (dict[i].GetKey() == key)
		{
			dict[i+shift].IncFreq();
			out = dict[i+shift].GetName();
			if (shift)
				for (unsigned int j=i; j<i+shift;j++)
					if (dict[i+shift].GetFreq() >= dict[j].GetFreq())
					{
						dict.insert(dict.begin()+i+j, dict[i+shift]);
						dict.erase(dict.begin()+i+shift+1);
						return out;
					}
			return out;
		}
	}
}

string parse(string data)
{
	string out;
	int current_key=0;
	int shift=0;

	for (unsigned int i=0; i<=data.length();i++)
	{
		switch (data[i])
		{
		case '*':
			shift++;
			break;
		case '\0':
			if (current_key!=0){
				out += translate(current_key,shift);
				shift=0;
				current_key = 0;
			}
			return out;
			break;
		case ' ':
			if (current_key!=0){
				out += translate(current_key,shift);
				shift=0;
				current_key = 0;
			}
			out +=' ';
			break;
		case '1':
			if (current_key!=0){
			out += translate(current_key,shift);
				shift=0;
				current_key = 0;
			}
			current_key=1;
			break;
		default:
			current_key *= 10;
			current_key += data[i]-'0';
			break;
		}
	}
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	for (unsigned int i=0; i<n; i++)
	{

		string buf;
		int freqbuf;
		cin >> buf >> freqbuf;
		word my_word(buf,freqbuf);

		dict.push_back(my_word);
	}

	//sorting
	int start=0;

	for (unsigned int i=0;i<dict.size();i++)
	{
		if (dict[start].GetKey() != dict[i+1].GetKey())
		{

			sort(dict.begin()+start,dict.begin()+i,FreqComp);
			start=i+1;
		}
	}
	string text;
	cin.ignore();
	getline(cin,text,'\n');
	cout << parse(text) <<endl;

	return 0;
}


