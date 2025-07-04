#include <stdio.h>

#include <fstream>
using std::ifstream;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <cctype>
using std::isalpha;
using std::isdigit;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <queue>
using std::queue;

#include <algorithm>

#include <utility>
using std::pair;
using std::make_pair;

#define PLACE_SHIFT 2; //для кнопки '2' информация в векторе хранится в позиции 0 и т.д.

enum CHOICE_SET {WORD = 0, PUNCT};


//ifstream infile( "dict.txt" );/////////////////////////////////////////////

struct Node {
  string word;
  int frequency;

  Node(string word = string(), int frequency = 0): word(word), frequency(frequency) {}
};

class Compare {
public:
	bool operator()(const Node& left, const Node& right) 
	{
		return left.frequency > right.frequency;
	}
};

struct Button 
{
  int nextButton[8];//8 кнопок. 1 не в счет, так как ее символы не будут учитываться при хранении слова.
  vector<Node> words;

  Button() 
  {
	for (int i = 0; i < 8; ++i) 
	{
        nextButton[i] = 0;
    }
  }
};

class Dictionary 
{
public:
	Dictionary() {size = 0; strikesTree.push_back(Button());}
	void fill();
	string getText();
private:
	int symbolToDigit(char symobl);
    vector<Button> strikesTree;
	int size;
};

int Dictionary::symbolToDigit(char symbol)
{
	switch(symbol)
	{
	case 'a': case 'b': case 'c':
		return 2;
	case 'd': case 'e': case 'f':
		return 3;
	case 'g': case 'h': case 'i':
		return 4;
	case 'j': case 'k': case 'l':
		return 5;
	case 'm': case 'n': case 'o':
		return 6;
	case 'p': case 'q': case 'r': case 's':
		return 7;
	case 't': case 'u': case 'v':
		return 8;
	case 'w': case 'x': case 'y': case 'z':
		return 9;
	default:
		return 0;
		break;
	}
}

void Dictionary::fill() 
{
	//infile >> this->size;/////////////////////////////
	cin >> this->size;
	
	vector<Node> All;
	All.resize(size);

	for (int wordsCounter = 0; wordsCounter < size; wordsCounter++)
	{
		string wholeWord;
		int frequency;
		
		//infile >> wholeWord >> frequency;//////////////////////
		cin >> wholeWord >> frequency;

		All.push_back ( Node(wholeWord, frequency) );
	}
		
	std::stable_sort(All.begin(), All.end(), Compare());

	for (int wordsCounter = 0; wordsCounter < size; wordsCounter++)
	{
		Button* current = & this->strikesTree.at(0);

		for (string::const_iterator it = All.at(wordsCounter).word.begin(); it != All.at(wordsCounter).word.end(); ++it)
		{
			char symbol;
			int digit, position;
			
			symbol = *it;
			digit = symbolToDigit(symbol);
			position = digit - PLACE_SHIFT;
			
			if (current->nextButton[position] == 0)
			{
				int newButtonNumber = strikesTree.size();
				current->nextButton[position] = newButtonNumber;
				strikesTree.push_back(Button());
				current = & strikesTree.at(newButtonNumber);
			}
			else
			{
				int nextButtonNumber = current->nextButton[position];
				current = & strikesTree.at(nextButtonNumber); 
			}
		}
		current->words.push_back( All.at(wordsCounter) );
	}
}

string Dictionary::getText()
{
	string output;
	int starsQuantity = 0;
	char symbol, lastSymbol = ' ';
	string currentWord;
	CHOICE_SET starServe = WORD;
	
	Button* current = & this->strikesTree.at(0);

	//infile.get(symbol); //////////////////////////пропускаем перенос строки
	cin.get(symbol); //пропускаем перенос строки

	//while ( infile.get(symbol) )//////////////////////////////////
	while ( cin.get(symbol) ) 
	{
		if (isdigit(symbol) && symbol != '1') // 2-9
		{
			if ( !(isdigit(lastSymbol) && lastSymbol != '1') ) //либо 1, либо *, либо ' '
			{
				output += currentWord;
				starServe = WORD;
				current = & this->strikesTree.at(0);
				starsQuantity = 0;
			}

			int number = atoi(&symbol);
			int position = number - PLACE_SHIFT;
			int nextButtonNumber = current->nextButton[position];
			current = & strikesTree.at(nextButtonNumber);
			lastSymbol = symbol;

			if (!current->words.empty())
				currentWord = current->words.at(0).word;
		}
		else if (symbol == '*' && starServe == WORD)
		{
			++starsQuantity;
			currentWord = current->words.at(starsQuantity).word;
			lastSymbol = symbol;
		}
		else if (symbol == '*' && starServe == PUNCT)
		{
			if (lastSymbol == '*')
				currentWord = '?';

			if (lastSymbol == '1')
				currentWord = ',';

			lastSymbol = symbol;
		}
		else if (symbol == '1' || symbol == ' ')
		{//если до этого звездочкой крутили знак препинания или был пробел, то ничего особенного не делаем
			if ( isdigit(lastSymbol) && lastSymbol != '1') // определяет предыдущую цифру 2-9
			{
				current->words.at(starsQuantity).frequency += 1;
				currentWord = current->words.at(starsQuantity).word;
			}

			if ( lastSymbol == '*' && starServe == WORD ) //звездочкой крутили слово
			{
				int currentFrequency = ++current->words.at(starsQuantity).frequency;
				currentWord = current->words.at(starsQuantity).word;
				int pointer = starsQuantity;

				for(; pointer > 0 && currentFrequency >= current->words.at(pointer-1).frequency; --pointer)
				{
					current->words.at(pointer).word = current->words.at(pointer-1).word;
					current->words.at(pointer).frequency = current->words.at(pointer-1).frequency;
				}

				current->words.at(pointer).word = currentWord;
				current->words.at(pointer).frequency = currentFrequency;
			}
			
			output += currentWord;
			lastSymbol = symbol;
			currentWord = symbol;

			if (symbol == '1')
			{
				starServe = PUNCT;
				currentWord = '.';
			}
		}
		else
		{//на всякий случай, если последний символ непонятно что
			output += currentWord;
			currentWord = ""; 
			break;
		}
	}
	output += currentWord;//или вот такой конец всему, если выходим из цикла
	return output;
}


int main()
{
	Dictionary Dict;
	Dict.fill();
	cout << Dict.getText();
	
	return 0;
}