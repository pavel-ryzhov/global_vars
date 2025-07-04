#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

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

bool makingDictionary = true;

int NumberFromWord(const string& word) {
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

bool MoreFrequencyComp (const dictionaryWord leftWord, const dictionaryWord rightWord) 
{
	if (makingDictionary) {
		if(leftWord.second == rightWord.second) {
			return leftWord.first < rightWord.first;
		}
		return leftWord.second > rightWord.second;
	} else {
		return leftWord.second >= rightWord.second;
	}
	
}

string GetWordByFrequency(set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)>& wordsList, int starsCount)
{
	starsCount = (starsCount < wordsList.size()) ? starsCount : starsCount % wordsList.size();
	set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)>::iterator wordsListIterator = wordsList.begin();
	for (int index = 0; index < starsCount; ++index) {
		++wordsListIterator;
	}
	dictionaryWord word = *wordsListIterator;
	++word.second;
	wordsList.erase(wordsListIterator);
	wordsList.insert(word);

	return word.first;
}

void Input(map<int,set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)> >& dictionary, string& inputString)
{
	int dictionarySize;
	cin >> dictionarySize;
	for (int index = 0; index < dictionarySize; ++index) {
		string word;
		int wordNumber;
		int frequency;
		cin >> word;
		cin >> frequency;
		wordNumber = NumberFromWord(word);
		if (dictionary.find(wordNumber) == dictionary.end()) {
			dictionary[wordNumber] = set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)>(MoreFrequencyComp);
		}
		dictionary[wordNumber].insert(dictionaryWord(word,frequency));
	}

	// Global variable - very bad practice, but easiest implementation in this case.
	// Used in compare function to distinguish between creating dictionary and using it.
	makingDictionary = false;

	cin.ignore(256,'\n');
	getline(cin,inputString);
	inputString += '\n';
}

void Output(const string& outputString)
{
	cout << outputString;
}

void automateT9(const string& inputSequence, string& outputString, map<int,set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)> >& dictionary)
{
	int sequenceLength = inputSequence.length();
	int currentState = initState;
	int wordCode;
	int starsPressed;
	int currentSignIndex;
	string word;
	string punctuationSigns(".,?");
	
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
						outputString += GetWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				case '1':
					{
						currentState = punctuationState;
						outputString += GetWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				case '\n':
					{
						outputString += GetWordByFrequency(dictionary[wordCode],starsPressed);
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
						outputString += GetWordByFrequency(dictionary[wordCode],starsPressed);
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
						outputString += GetWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				case '1':
					{
						currentState = punctuationState;
						outputString += GetWordByFrequency(dictionary[wordCode],starsPressed);
					}
					break;
				case '\n':
					{
						outputString += GetWordByFrequency(dictionary[wordCode],starsPressed);
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
						outputString += punctuationSigns[currentSignIndex];
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
						outputString += punctuationSigns[currentSignIndex];
						currentSignIndex = 0;
					}
					break;
				case '1':
					{
						currentState = punctuationState;
						outputString += punctuationSigns[currentSignIndex];
						currentSignIndex = 0;
					}
					break;
				case '\n':
					{
						outputString += punctuationSigns[currentSignIndex];
						currentSignIndex = 0;
					}
					break;
				}
			}
			break;
		case spaceState:
			{
				outputString +=  " ";

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
	map<int,set<dictionaryWord,bool(*)(dictionaryWord,dictionaryWord)> > dictionary;
	string inputString;
	string outputString;
	Input(dictionary, inputString);
	automateT9(inputString, outputString, dictionary);
	Output(outputString);
}