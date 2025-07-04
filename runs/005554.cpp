#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

struct Entry
{
	string word;
	int freq;

	bool usedLast;
};

class Vocabulary
{	
public:
	Vocabulary *Child[8];
	list<Entry> Entries;

	Vocabulary()
	{
		for (int i = 0; i < 8; i++)
			Child[i] = NULL;

		Entries.empty();
	}
};

void LoadVocabulary(Vocabulary*);
bool EntriesCompare(Entry, Entry);
vector<int> FindPath(string);
int PrintVocabulary(Vocabulary*);
void ReadMessage(Vocabulary*);
void SortEntries(list<Entry>*,list<Entry>::iterator);

int main()
{
	Vocabulary Voc;

	LoadVocabulary(&Voc);

	ReadMessage(&Voc);
	return 0;
}

void LoadVocabulary(Vocabulary *Voc)
{
	Entry Temp;
	Vocabulary* Childs = new Vocabulary();
	vector<int> path;
	vector<int>::iterator it;

	int size;
	scanf("%d", &size);

	for (int i = 0; i < size; i++)
	{
		cin >> Temp.word >> Temp.freq;
		Temp.usedLast = 0;
		path = FindPath(Temp.word);

		Childs = Voc;

		for (it = path.begin(); it != path.end(); it++)
		{
			if ( Childs->Child[*it-2] )
				Childs = Childs->Child[*it-2];

			else
			{
				Childs->Child[*it-2] = new Vocabulary();
				Childs = Childs->Child[*it-2];
			}
				
		}

		Childs->Entries.push_back(Temp);
		Childs->Entries.sort(EntriesCompare);
	}
}

int PrintVocabulary(Vocabulary *Voc)
{
	list<Entry>::iterator it;

	if ( Voc->Entries.size() != 0 )
		for (it = Voc->Entries.begin(); it != Voc->Entries.end(); it++)
			cout << it->word << " " << it->freq << endl;

	for (int i = 0; i < 8; i++)
		if ( Voc->Child[i] )
			PrintVocabulary(Voc->Child[i]);

	return 0;
}

bool EntriesCompare(Entry first, Entry second)
{
	if ( first.freq == second.freq )
	{
		if ( first.usedLast )
			return true;

		if ( second.usedLast )
			return false;
	}

	return ( first.freq > second.freq ? true : false );
}

vector<int> FindPath(string word)
{
	vector<int> path;
	string::iterator it;

	for (it = word.begin(); it != word.end(); it++)
	{
		if ( ((int)'a' <= (int)*it) && ((int)*it <= (int)'c') )
			path.push_back(2);

		else if ( ((int)'d' <= (int)*it) && ((int)*it <= (int)'f') )
			path.push_back(3);

		else if ( ((int)'g' <= (int)*it) && ((int)*it <= (int)'i') )
			path.push_back(4);

		else if ( ((int)'j' <= (int)*it) && ((int)*it <= (int)'l') )
			path.push_back(5);

		else if ( ((int)'m' <= (int)*it) && ((int)*it <= (int)'o') )
			path.push_back(6);

		else if ( ((int)'p' <= (int)*it) && ((int)*it <= (int)'s') )
			path.push_back(7);

		else if ( ((int)'t' <= (int)*it) && ((int)*it <= (int)'v') )
			path.push_back(8);

		else if ( ((int)'w' <= (int)*it) && ((int)*it <= (int)'z') )
			path.push_back(9);

		else path.push_back(-1);
	}

	return path;
}

void ReadMessage(Vocabulary *Voc)
{
	int chs = 0;
	int flag = 1;
	char temp;
	char signs[3] = {'.', ',', '?'};
	int sit = 0;

	scanf("%c", &temp);

	int chRead;
	string currWord = "";
	Vocabulary *Temp = Voc;
	list<Entry>::iterator it;

	while ( chs < 100000 && flag )
	{
		scanf("%c", &temp);

		if ( temp == 10 )
		{
			if ( currWord.length() )
				cout << currWord;

			flag = 0;
			break;
		}

		chRead = temp - 50;

		if ( chRead > -1 && temp != '1' )
		{
			if ( flag == 2 )
			{
				cout << currWord;
				currWord = "";
				flag = 1;
			}

			Temp = Temp->Child[chRead];
			it = Temp->Entries.begin();
			
			if ( Temp->Entries.size() )
				currWord = it->word;
		}

		else if ( temp == ' ' )
		{
			if ( currWord.length() )
				cout << currWord;
			
			if ( flag == 1 )
			{
				if ( it->freq < 1000 )
				{
					it->freq++;
					
//					for (list<Entry>::iterator i = Temp->Entries.begin(); i != Temp->Entries.end(); i->usedLast = 0, i++);

//					it->usedLast = 1;
//					Temp->Entries.sort(EntriesCompare);

					SortEntries(&Temp->Entries, it);
				}
			
				Temp = Voc;
			}

			else
			{
				sit = 0;
				flag = 1;
			}

			currWord = "";
			cout << " ";
		}

		else if ( temp == '*' )
		{
			if ( flag == 1 )
			{
				if ( ++it == Temp->Entries.end() )
					it = Temp->Entries.begin();
				
				currWord = it->word;
			}

			if ( flag == 2)
			{
				if ( ++sit == 3 )
					sit = 0;

				currWord = signs[sit];
			}
		}

		else if ( temp = '1' )
		{
			if ( currWord.length() )
				cout << currWord;

			currWord = "";

			if ( flag == 1 )
			{				
				if ( it->freq < 1000 )
				{
					it->freq++;

//					for (list<Entry>::iterator i = Temp->Entries.begin(); i != Temp->Entries.end(); i->usedLast = 0, i++);

//					it->usedLast = 1;
//					Temp->Entries.sort(EntriesCompare);
					SortEntries(&Temp->Entries, it);
				}
			
				Temp = Voc;
			}

			sit = 0;
			flag = 2;

			currWord = signs[sit];
		}
	}
}

void SortEntries(list<Entry> *Entries, list<Entry>::iterator it)
{
	Entry Temp;
	list<Entry>::iterator temp;

	while ( it != Entries->begin() )
	{
		temp = it;
		temp--;

		if ( it->freq >= temp->freq )
		{
			Temp = *temp;
			*temp = *it;
			*it = Temp;

			it--;
		}

		else it = Entries->begin();
	}
}