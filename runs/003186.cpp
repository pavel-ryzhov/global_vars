#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>

using std::vector;
using std::string;
using std::map;
using std::set;
using std::pair;
using std::cin;
using std::cout;
using std::endl;

typedef pair<string, int> dictionaryWord;


enum { initState, wordState, starsState, spaceState, punctuationState };

int numberFromWord(const string& word) {
	int number = 0;
	int wordLength = word.length();
	for (int index = 0; index < wordLength; ++index) {
		int keyNumber;
		if (word[index] < 'm') {
			if (word[index] < 'g') {
				if (word[index] < 'd') {
					keyNumber = 2;
				}
				else {
					keyNumber = 3;
				}
			}
			else {
				if (word[index] < 'j') {
					keyNumber = 4;
				}
				else {
					keyNumber = 5;
				}
			}
		}
		else {
			if (word[index] < 't') {
				if (word[index] < 'p') {
					keyNumber = 6;
				}
				else {
					keyNumber = 7;
				}
			}
			else {
				if (word[index] < 'w') {
					keyNumber = 8;
				}
				else {
					keyNumber = 9;
				}
			}
		}
		number = keyNumber + number*10;
	}
	return number;
}

bool ascMoreFrequencyComp (dictionaryWord leftWord, dictionaryWord rightWord) 
{
	if(leftWord.second == rightWord.second) {
		return leftWord.first < rightWord.first;
	}
	return leftWord.second > rightWord.second;
}

bool moreFrequencyComp (dictionaryWord leftWord, dictionaryWord rightWord) 
{
	return leftWord.second >= rightWord.second;
}


void input(map<int,set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)>* >& dictionary, string& inputString)
{
	int n;
	cin >> n;

	bool(*cmp_fn_pt)(dictionaryWord,dictionaryWord) = ascMoreFrequencyComp;
	for (int index = 0; index < n; ++index) {
		string word;
		int wordNumber;
		int frequency;

		cin >> word;
		cin >> frequency;
		
		wordNumber = numberFromWord(word);
		if (dictionary.find(wordNumber) == dictionary.end()) {
			dictionary[wordNumber] = new set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)>(cmp_fn_pt);
		}
		dictionary[wordNumber]->insert(dictionaryWord(word,frequency));
		
		//(dictionary[wordNumber]).comp = ascMoreFrequencyComp;
	}

	map<int,set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)> >::iterator dictionaryIterator;

	cmp_fn_pt = moreFrequencyComp;
	
	getline(cin,inputString);
	getline(cin,inputString);
	inputString += '\n';
}

string getWordByFrequency(set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)>* wordsList, int starsCount)
{
	starsCount = (starsCount < wordsList->size()) ? starsCount : starsCount % wordsList->size();
	set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)>::iterator wordsListIterator = wordsList->begin();
	for (int index = 0; index < starsCount; ++index) {
		++wordsListIterator;
	}
	dictionaryWord word = *wordsListIterator;
	++word.second;
	wordsList->erase(wordsListIterator);
	wordsList->insert(word);

	return word.first;
}

void automateT9(const string& inputSequence, map<int,set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)>* >& dictionary)
{
	int sequenceLength = inputSequence.length();
	int currentState = initState;
	int wordCode;
	int starsPressed;
	int currentSignIndex;
	string word;
	string punctualSigns(".,?");
	
	for (int index = 0; index < sequenceLength; ++index) {
		switch (currentState) {
		case initState:
			{
				wordCode = 0;
				starsPressed = 0;
				currentSignIndex = 0;
				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						currentState = wordState;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentState = starsState;
						++starsPressed;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
					}
					break;
				case '1':
					{
						currentState = punctuationState;
					}
					break;
				case '\n':
					{

					}
					break;
				}
			}
			break;
		case wordState:
			{
				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						currentState = wordState;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentState = starsState;
						++starsPressed;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
						cout << getWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				case '1':
					{
						currentState = punctuationState;
						cout << getWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				case '\n':
					{
						cout << getWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				}
			}
			break;
		case starsState:
			{
				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						cout << getWordByFrequency(dictionary[wordCode],starsPressed);
						currentState = wordState;
						wordCode = 0;
						starsPressed = 0;
						currentSignIndex = 0;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentState = starsState;
						++starsPressed;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
						cout << getWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				case '1':
					{
						currentState = punctuationState;
						cout << getWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				case '\n':
					{
						cout << getWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				}
			}
			break;
		case punctuationState:
			{
				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						cout << punctualSigns[currentSignIndex];
						currentState = wordState;
						wordCode = 0;
						starsPressed = 0;
						currentSignIndex = 0;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentSignIndex = (++currentSignIndex < 3) ? currentSignIndex : currentSignIndex % 3;
						currentState = punctuationState;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
						cout << punctualSigns[currentSignIndex];
						currentSignIndex = 0;
					}
					break;
				case '1':
					{
						currentState = punctuationState;
						cout << punctualSigns[currentSignIndex];
						currentSignIndex = 0;
					}
					break;
				case '\n':
					{
						cout << punctualSigns[currentSignIndex];
						currentSignIndex = 0;
					}
					break;
				}
			}
			break;
		case spaceState:
			{
				cout << " ";

				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						currentState = wordState;
						wordCode = 0;
						starsPressed = 0;
						currentSignIndex = 0;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentState = starsState;
						++starsPressed;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
					}
					break;
				case '1':
					{
						currentState = punctuationState;
					}
					break;
				case '\n':
					{

					}
					break;
				}
			}
			break;
		default:
			break;
		}
	}
}

int main(int argc, char **argv)
{
	map<int,set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)>* > dictionary;
	string inputString;

	input(dictionary, inputString);

	automateT9(inputString,dictionary);
}