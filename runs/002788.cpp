//============================================================================
// Name        : problem3.cpp
// Author      : Toporkov P.
// Version     :
// Copyright   :
// Description : Problem3 Solution
//============================================================================

#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <map>

using namespace std;
// Global variables
const string keyboard[]={"0",".,?","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

// Classes
class word {
public:
	word(string _name, unsigned int _freq);
	string GenerateKey();
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
string word::GenerateKey()
{
	string key;

	for (unsigned  int i=0; i < this->name.length(); i++){
		for (unsigned int j = 0; j < 10; j++) {
			if (keyboard[j].find_first_of(this->name[i],0) != string::npos)
			{
				//key *= 10; //Appending value to key
				key += (j+'0');
			}
		}
	}
	return key;
}
map < string, list <word> > dict;

// Functions
bool FreqComp(word w1, word w2)	// Word frequency comaprator
{
	return w1.GetFreq() > w2.GetFreq();
}
string translate(string key, unsigned int shift) // Translating key to word
{
	string out;

	if (key == "1")
		return keyboard[1].substr(shift%3,1);
	//shift %= dict[key].size(); //For cycling
	list <word>::iterator it;
	it=dict[key].begin();
	for(unsigned int i=0;i<shift;i++)
		it++;

	out=it->GetName();

	it->IncFreq();
	//dict[key][shift].IncFreq(); // Frequency increasing
	list <word>::iterator p1;
	for (p1 = dict[key].begin(); p1 != dict[key].end(); p1++) // Reposition
	{
		if (it->GetFreq() >= p1->GetFreq())
		{

			dict[key].insert(p1,*it);

			dict[key].erase(it);

			return out;
		}
	}
}
string parse(string data) // Parsing input string
{
	string out;
	string current_key;
	unsigned int shift = 0;
	for (unsigned long int i=0;i<data.length()+1;i++)
	{
		switch (data[i])
		{
		case '*':
			shift++;
			break;
		case '\0':
			if (!current_key.empty()){
				out += translate(current_key,shift);
				shift = 0;
				current_key.clear();
			}
			return out;
			break;
		case ' ':
			if (!current_key.empty()){
				out += translate(current_key,shift);
				shift = 0;
				current_key.clear();
			}
			out += ' ';
			break;
		case '1':
			if (!current_key.empty()){
				out += translate(current_key,shift);
				shift = 0;
				current_key.clear();
			}
			current_key = "1";
			break;
		default:
			if (current_key=="1"){
				out += translate(current_key,shift);
				shift = 0;
				current_key.clear();
			}

			current_key += data[i];
			break;
		}
	}
}

void Sort() // Preliminary sorting of data
{
	map < string, list <word> >::iterator p;
	for(p = dict.begin(); p!=dict.end(); ++p)
	{
		p->second.sort(FreqComp);
		//stable_sort(p->second.begin(),p->second.end(),FreqComp);
	}
}

void Print()
{
	int n=0;
	map < string, list <word> >::iterator p;
	list <word>::iterator p1;
	for(p = dict.begin(); p!=dict.end(); ++p)
		for(p1 = p->second.begin(); p1!=p->second.end(); ++p1)
		{
			cout << n << ". " <<p1->GetName() << " " << p1->GenerateKey()<< " " <<p1->GetFreq() <<endl;
			n++;
		}
}
int main(int argc, char **argv) {
	unsigned int n;
	cin >> n;
	if (n>50000)
	{
		cerr << "Error. Too large file";
		return -1;
	}
	for (unsigned int i = 0; i < n; i++)
	{

		string buf;
		unsigned int freqbuf;
		cin >> buf >> freqbuf;
		word my_word(buf,freqbuf);
		dict[my_word.GenerateKey()].push_back(my_word);
	}

	Sort();
	//Print();
	string text;

	cin.ignore();

	getline(cin,text,'\n');


	cout << parse(text);


	return 0;
}


