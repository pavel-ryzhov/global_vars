#include <map>
#include <set>
#include <string>
#include <iostream>

char convertToString(char letter)
{
	switch(letter)
	{
	case 'a': return '2';
	case 'b': return '2';
	case 'c': return '2';
	case 'd': return '3';
	case 'e': return '3';
	case 'f': return '3';
	case 'g': return '4';
	case 'h': return '4';
	case 'i': return '4';
	case 'j': return '5';
	case 'k': return '5';
	case 'l': return '5';
	case 'm': return '6';
	case 'n': return '6';
	case 'o': return '6';
	case 'p': return '7';
	case 'q': return '7';
	case 'r': return '7';
	case 's': return '7';
	case 't': return '8';
	case 'u': return '8';
	case 'v': return '8';
	case 'w': return '9';
	case 'x': return '9';
	case 'y': return '9';
	case 'z': return '9';
	}
}

class setComparator
{
public:
	bool operator() (std::pair<int, std::string> pair1, std::pair<int, std::string> pair2) {return pair1.first < pair2.first;}
};

int main()
{
	int numberWords, frequency;
	char symbol;
	std::string word, combinationOfNumbers;
	std::multiset<std::pair<int, std::string>, setComparator > wordPair;
	std::map<std::string, std::multiset<std::pair<int, std::string>,  setComparator> > dictionary;

	std::cin >> numberWords;

	for(int i = 0; i < numberWords; i++)
	{
		std::cin >> word >> frequency;

		frequency *= -1;

		for(int j = 0; j < word.size(); j++)
		{
			symbol = convertToString(word[j]);
			combinationOfNumbers += symbol;
		}

		std::map<std::string, std::multiset<std::pair<int, std::string>, setComparator > >::iterator p;
		p = dictionary.find(combinationOfNumbers);

		if(p == dictionary.end())
		{
			wordPair.insert(std::pair<int, std::string>(frequency, word));

			dictionary.insert(std::pair<std::string, std::multiset<std::pair<int, std::string>, setComparator > >(combinationOfNumbers, wordPair));
		}
		else
		{
			p->second.insert(p->second.begin(), std::pair<int, std::string>(frequency, word));
		}

		combinationOfNumbers.clear();
		wordPair.clear();
	}

	std::string input, task;
	int counter = 0;
	bool space = false, punct = false;
	std::pair<int, std::string> myPair;
	std::string punctuation;
	punctuation += '.';
	punctuation += ',';
	punctuation += '?';

	std::cin.get();
	std::getline(std::cin, input);

	for(int i = 0; i < input.size(); i++)
	{
		if(input[i] == '1')
		{
			punct = true;
		}
		if(i == input.size()-1)
		{
			
			std::map<std::string, std::multiset<std::pair<int, std::string>, setComparator> >::iterator p;
			std::multiset<std::pair<int, std::string>, setComparator>::iterator setIter;
			if(input[i] != '*' && input[i] != '1') task += input[i];
			if(task!="")
			{
				p = dictionary.find(task);
				if(counter >= p->second.size() && p->second.size() != 0)
				{
					counter--;
				}
				setIter = p->second.begin();
				for(int j = 0; j < counter; j++) setIter++;
				std::cout << setIter->second;
			}
			if(punct && input[i] == '*')
			{
				counter++;
				std::cout << punctuation[counter];
				counter = 0;
				task.clear();
				break;
			}
			else if(punct && input[i] != '*')
			{
				counter = 0;
				std::cout << punctuation[counter];
				task.clear();
				counter = 0;
				break;
			}
			task.clear();
			counter = 0;
			break;
		}
		if(input[i] == '*')
		{
			counter++;
			continue;
		}
		if(input[i] != ' ' && !punct)
		{
			task += input[i];
			space = false;
			continue;
		}
		if(input[i] == ' ' && punct)
		{
			std::cout << punctuation[counter] << " ";
			space = true;
			counter = 0;
			punct = false;
		}
		if(!space)
		{
			std::map<std::string, std::multiset<std::pair<int, std::string>, setComparator > >::iterator p;
			p = dictionary.find(task);
			std::multiset<std::pair<int, std::string>, setComparator>::iterator vect = p->second.begin();
			
			for(int j = 0; j < counter; j++) vect++;

			if(punct)std::cout << vect->second;
			else std::cout << vect->second << " ";

			myPair.first = vect->first - 1;
			myPair.second = vect->second;

			p->second.erase(vect);
			if(p->second.size() == 0) p->second.insert(myPair);
			else p->second.insert(p->second.begin(), myPair);

			task.clear();
			counter = 0;
			space = true;
			continue;
		}
	}

	return 0;
}