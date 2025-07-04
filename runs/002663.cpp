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
#include <map>

using namespace std;
// Global variables
const string keyboard[]={"0",".,?","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
unsigned int current_key = 0;
unsigned int shift = 0;
// Classes
class word {
public:
	word(string _name, unsigned int _freq);
	unsigned int GenerateKey();
	unsigned int GetFreq(){return this->freq;}
	string GetName(){return this->name;}
	void IncFreq(){this->freq++;}
private:
	string name;
	unsigned int freq;
};
word::word(string _name, unsigned int _freq)
{
	this->name = _name;
	this->freq = _freq;
}
unsigned int word::GenerateKey()
{
	unsigned int key = 0;

	for (unsigned  int i=0; i < this->name.length(); i++){
		for (unsigned int j = 0; j < 10; j++) {
			if (keyboard[j].find_first_of(this->name[i],0) != string::npos)
			{
				key *= 10; //Appending value to key
				key += j;
			}
		}
	}
	return key;
}
map < unsigned int, vector <word> > dict;

// Functions
bool FreqComp(word w1, word w2)	// Word frequency comaprator
{
	return w1.GetFreq() > w2.GetFreq();
}
string translate(unsigned int key, unsigned int shift) // Translating key to word
{
	string out;

	if (key == 1)
		return keyboard[1].substr(shift%3,1);
	shift %= dict[key].size(); //For cycling
	out = dict[key][shift].GetName();
	dict[key][shift].IncFreq(); // Frequency increasing
	vector <word>::iterator p;
	for (p = dict[key].begin(); p != dict[key].end(); p++) // Reposition
	{
		if (dict[key][shift].GetFreq() >= p->GetFreq())
		{
			dict[key].insert(p,dict[key][shift]);
			dict[key].erase(dict[key].begin()+shift+1); // TODO: Correct >____<
			return out;
		}
	}
}
string parse(char data) // Parsing input string
{
	string out;



//
//	for (unsigned  int i = 0; i <= data.length(); i++)
//	{
		switch (data)
		{
		case '*':
			shift++;
			break;
		case '\0':
			if (current_key != 0){
				out += translate(current_key,shift);
				shift = 0;
				current_key = 0;
			}
			return out;
			break;
		case ' ':
			if (current_key != 0){
				out += translate(current_key,shift);
				shift = 0;
				current_key = 0;
			}
			out += ' ';
			break;
		case '1':
			if (current_key != 0){
			out += translate(current_key,shift);
				shift = 0;
				current_key = 0;
			}
			current_key = 1;
			break;
		default:
			current_key *= 10;
			current_key += data - '0';
			break;
		}
//	}
}
void Sort() // Preliminary sorting of data
{
	map < unsigned int, vector <word> >::iterator p;
	for(p = dict.begin(); p!=dict.end(); ++p)
	{

		sort(p->second.begin(),p->second.end(),FreqComp);
	}
}

int main(int argc, char **argv) {
	unsigned int n;
	cin >> n;
	for (unsigned int i = 0; i < n; i++)
	{

		string buf;
		unsigned int freqbuf;
		cin >> buf >> freqbuf;
		word my_word(buf,freqbuf);
		dict[my_word.GenerateKey()].push_back(my_word);
	}

	Sort();

	string text;

	cin.ignore();

	getline(cin,text,'\n');

	for (int i=0;i<text.length()+1;i++)
		cout << parse(text[i]);


	return 0;
}



