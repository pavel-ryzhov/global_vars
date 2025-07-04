#include <iostream>
#include <stdlib.h>
#include <map>
#include <deque>
#include <string>

using namespace std;

class Element
{
private:
	map< unsigned, deque<string> > freqWords;
public:
	void addFreqWords(unsigned F, string word)
	{
		freqWords[F].push_front(word); 
	}
	string getWordAndIncreaseFreq(unsigned F)
	{
		if (F == 0)
		{
			map< unsigned, deque<string> >::iterator it = freqWords.end();
			--it;
			string word = it->second.back();
			unsigned freq = it->first;
			it->second.pop_back();
			if (it->second.empty())
				freqWords.erase(it);
			freqWords[freq + 1].push_back(word);
			return word;
		}
		else
		{
			map< unsigned, deque<string> >::iterator it = freqWords.end();
			--it;
			unsigned freq = it->first;
			while ( F >= freqWords[freq].size() )
			{
				if ( freqWords.size() == 1)
					F -= freqWords[freq].size();
				else
				{
					F -= freqWords[freq].size();
					if (it == freqWords.begin())
						it = freqWords.end();
					--it;
					freq = it->first;
				}
			}
			unsigned size = freqWords[freq].size() - 1;
			string word = freqWords[freq][size - F];
			freqWords[freq].erase(freqWords[freq].end() - F - 1);
			if (freqWords[freq].empty())
				freqWords.erase(freq);
			freqWords[freq+1].push_back(word);
			return word;
		}
	}
};

unsigned convertN(string N)
{
	return atoi(N.c_str());
}

void convertString(string wordFreq, string* word, unsigned* F)
{
	string tempStr = "";
	unsigned i = 0, length = wordFreq.length();
	while (wordFreq[i] != ' ')
	{
		*word += wordFreq[i];
		++i;
	}
	++i;
	while (i < length)
	{
		tempStr += wordFreq[i];
		++i;
	}

	*F = atoi(tempStr.c_str());
}

int main()
{
	string message, word = "", tempKey = "", tempWord, wordFreq, strN;
	unsigned countFreqWord = 0, countFreqSign = 0;
	bool inputWord = false, inputFreqWord = false, inputFreqSign = false, inputSign = false, lastSymbol = false;
	unsigned N, iLast, F;
	map<string, Element> dictionary;
	map<char, char> letNum;
	char signs[3] = {'.', ',', '?'};
	letNum['a'] = letNum['b'] = letNum['c'] = '2'; 
	letNum['d'] = letNum['e'] = letNum['f'] = '3';  
	letNum['g'] = letNum['h'] = letNum['i'] = '4'; 
	letNum['j'] = letNum['k'] = letNum['l'] = '5';
	letNum['m'] = letNum['n'] = letNum['o'] = '6';
	letNum['p'] = letNum['q'] = letNum['r'] = letNum['s'] = '7';
	letNum['t'] = letNum['u'] = letNum['v'] = '8';
	letNum['w'] = letNum['x'] = letNum['y'] = letNum['z'] = '9';

	
	getline(cin, strN);
	N = convertN(strN);
	for (unsigned i = 0; i < N; i++)
	{
		getline(cin, wordFreq);
		convertString(wordFreq, &word, &F);
		for (unsigned i = 0; i < word.length(); i++)
		{
			tempKey += letNum[word[i]];
		}
		dictionary[tempKey].addFreqWords(F, word);
		tempKey = "";
		word = "";
	}
	
	getline(cin, message);

	iLast = message.length();
	for (unsigned i = 0; i < iLast; i++)
	{
		if ( i == (iLast - 1) )
			lastSymbol = true;
		if ( (message[i] != '1') && (message[i] != ' ') && (message[i] != '*') )
		{
			if (inputWord)
			{
				tempKey += message[i];
				if (lastSymbol)
					cout<<dictionary[tempKey].getWordAndIncreaseFreq(0);
			}
			else
			{
				inputWord = true;
				tempKey += message[i];
				
				if (inputSign)
				{
					cout << signs[0];
					inputSign = false;
					if (lastSymbol)
						cout<<dictionary[tempKey].getWordAndIncreaseFreq(0);
				}
				else if (inputFreqSign)
				{
					cout << signs[countFreqSign % 3];
					inputFreqSign = false;
					countFreqSign = 0;
					if (lastSymbol)
						cout<<dictionary[tempKey].getWordAndIncreaseFreq(0);
				}
			}
		}
		else if ( message[i] == '1' )
		{
			if (inputSign)
			{
				cout << signs[0];
				if (lastSymbol)
					cout << signs[0];
			}
			else
			{
				inputSign = true;
				if (inputWord)
				{
					inputWord = false;
					cout<<dictionary[tempKey].getWordAndIncreaseFreq(0);
					tempKey = "";
					if (lastSymbol)
						cout << signs[0];
				}
				else if (inputFreqWord)
				{
					inputFreqWord = false;
					cout<<dictionary[tempKey].getWordAndIncreaseFreq(countFreqWord);
					countFreqWord = 0;
					tempKey = "";
					if (lastSymbol)
						cout << signs[0];
				}
				else if (inputFreqSign)
				{
					inputFreqSign = false;
					cout<<signs[countFreqSign % 3];
					countFreqSign = 0;
					if (lastSymbol)
						cout << signs[0];
				}
			}
		}
		else if (message[i] == '*')
		{
			if (inputFreqWord)
			{
				++countFreqWord;
				if (lastSymbol)
					cout<<dictionary[tempKey].getWordAndIncreaseFreq(countFreqWord);
			}
			else if (inputFreqSign)
			{
				++countFreqSign;
				if (lastSymbol)
					cout<<signs[countFreqSign % 3];
			}
			else
			{
				if (inputWord)
				{
					inputWord = false;
					inputFreqWord = true;
					++countFreqWord;
					if (lastSymbol)
						cout<<dictionary[tempKey].getWordAndIncreaseFreq(countFreqWord);
				}
				else if (inputSign)
				{
					inputSign = false;
					inputFreqSign = true;
					++countFreqSign;
					if (lastSymbol)
						cout<<signs[countFreqSign % 3];
				}
			}
		}
		else if (message[i] == ' ')
		{
			if (inputWord)
			{
				inputWord = false;
				cout<<dictionary[tempKey].getWordAndIncreaseFreq(0);
				cout<<' ';
				tempKey = "";
			}
			else if (inputSign)
			{
				inputSign = false;
				cout<<signs[0];
				cout<<' ';
			}
			else if (inputFreqWord)
			{
				inputFreqWord = false;
				cout<<dictionary[tempKey].getWordAndIncreaseFreq(countFreqWord);
				countFreqWord = 0;
				cout<<' ';
				tempKey = "";
			}
			else if (inputFreqSign)
			{
				inputFreqSign = false;
				cout<<signs[countFreqSign % 3];
				countFreqSign = 0;
				cout<<' ';
			}
			else
				cout<<' ';
		}
	}
	return 0;
}