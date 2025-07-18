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

#define PLACE_SHIFT 2; //��� ������ '2' ���������� � ������� �������� � ������� 0 � �.�.

enum CHOICE_SET {WORD = 0, PUNCT};


//ifstream infile( "dict.txt" );

struct Button 
{
  vector<int> nextButton;
  vector<string> words; //����� ������� ������������� �������� ���� ������ � ������
  vector<int> frequencies; //��������������� �� �������

  Button() 
  {
	  nextButton.resize(8); //8 ������. 1 �� � ����, ��� ��� �� ������� �� ����� ����������� ��� �������� �����.
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

	for (int wordsCounter = 0; wordsCounter < size; wordsCounter++)
	{
		string wholeWord;
		int frequency;
		
		//infile >> wholeWord >> frequency;//////////////////////
		cin >> wholeWord >> frequency;

		Button* current = & this->strikesTree.at(0);

		for (string::const_iterator it = wholeWord.begin(); it != wholeWord.end(); ++it)
		{
			char symbol;
			int digit, position;
			
			symbol = *it;
			digit = symbolToDigit(symbol);
			position = digit - PLACE_SHIFT;
			
			if (current->nextButton.at(position) == 0)
			{
				int newButtonNumber = strikesTree.size();
				current->nextButton.at(position) = newButtonNumber;
				strikesTree.push_back(Button());
				current = & strikesTree.at(newButtonNumber);
			}
			else
			{
				int nextButtonNumber = current->nextButton.at(position);
				current = & strikesTree.at(nextButtonNumber); 
			}
		}		
		current->words.push_back(wholeWord);
		current->frequencies.push_back(frequency);
	}
}

string Dictionary::getText()
{
	string output;
	int starsQuantity = 0;
	int frequencyWorkLevelPointer = -1;
	int frequencyWorkLevel = -1;
	int frequencyStorageLevelPointer = -1;
	int frequencyStorageLevel = -1;
	char symbol, lastSymbol = ' ';
	string currentWord;
	CHOICE_SET starServe = WORD;
	
	Button* current = & this->strikesTree.at(0);

	//infile.get(symbol); //////////////////////////���������� ������� ������
	cin.get(symbol); //���������� ������� ������

	//while ( infile.get(symbol) )//////////////////////////////////
	while ( cin.get(symbol) ) 
	{
		if (isdigit(symbol) && symbol != '1') // 2-9
		{
			if ( !(isdigit(lastSymbol) && lastSymbol != '1') ) //���� 1, ���� *, ���� ' '
			{
				output += currentWord;
				starServe = WORD;
				current = & this->strikesTree.at(0);
				starsQuantity = 0;
				frequencyWorkLevelPointer = -1;
				frequencyWorkLevel = -1;
				frequencyStorageLevelPointer = -1;
				frequencyStorageLevel = -1;
			}

			int number = atoi(&symbol);
			int position = number - PLACE_SHIFT;
			int nextButtonNumber = current->nextButton.at(position);
			current = & strikesTree.at(nextButtonNumber);
			lastSymbol = symbol;
		}
		else if (symbol == '*' && starServe == WORD)
		{
			if (frequencyWorkLevel == -1)
			{
				frequencyWorkLevel = current->frequencies.at(starsQuantity);
				frequencyWorkLevelPointer = starsQuantity;
				frequencyStorageLevel = current->frequencies.at(starsQuantity + 1);
				frequencyStorageLevelPointer = starsQuantity + 1;
			}
			
			if (frequencyWorkLevel - current->frequencies.at(starsQuantity + 1) >= 1)
			{
				if (frequencyWorkLevel - current->frequencies.at(starsQuantity + 1) >= 2)
				{
					frequencyWorkLevel = frequencyStorageLevel;
					frequencyWorkLevelPointer = frequencyStorageLevelPointer;
				}

				if (frequencyStorageLevel != current->frequencies.at(starsQuantity + 1))
				{
					frequencyStorageLevel = current->frequencies.at(starsQuantity + 1);
					frequencyStorageLevelPointer = starsQuantity + 1;
				}
			}
			//else frequencyLevel stays the same and sameFrequencyFirstUnitPointer stays the same

			++starsQuantity;
			currentWord = current->words.at(starsQuantity);
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
		{
			if ( lastSymbol == ' ' ){} //���������� ������

			if ( isdigit(lastSymbol) && lastSymbol != '1') //���������� ���������� ���������� ����� 2-9
			{
				current->frequencies.at(starsQuantity) += 1;
				currentWord = current->words.at(starsQuantity);
			}

			if ( lastSymbol == '*' && starServe == PUNCT ){} //���������� ������� ���� ����������

			if ( lastSymbol == '*' && starServe == WORD ) //���������� ������ �����
			{//���� ������� ��� ���������� �� 1 �� ������ �������
				if (starsQuantity == frequencyWorkLevelPointer)
				{
					current->frequencies.at(starsQuantity) += 1;
					currentWord = current->words.at(starsQuantity);
				}
				else
				{//����� �������� / ���������
				currentWord = current->words.at(starsQuantity);
				int currentFrequency = current->frequencies.at(starsQuantity);
				current->words.erase(current->words.begin() + starsQuantity);
				current->frequencies.erase(current->frequencies.begin() + starsQuantity);
				current->words.insert(current->words.begin() + frequencyWorkLevelPointer, currentWord);
				current->frequencies.insert(current->frequencies.begin() + frequencyWorkLevelPointer, currentFrequency + 1);
				} //����� ���, ������ ����� �������� ���
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
		{//�� ������ ������, ���� ��������� ������ ��������� ���
			output += currentWord;
			currentWord = ""; 
			break;
		}
	}
	//��� ��� ����� ����� �����, ���� ������� �� �����
	output += currentWord;

	return output;
}


int main()
{
	Dictionary* Dict = new Dictionary();
	Dict->fill();
	cout << Dict->getText();
//	infile.close();
	return 0;
}