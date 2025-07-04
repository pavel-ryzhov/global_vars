#include <map>
#include <vector>
#include <string>
#include <algorithm>
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

struct myStruct
{
	bool operator() (std::pair<int, std::string> pair1, std::pair<int, std::string> pair2) {return (pair1.first < pair2.first);}
} myObject;

int main()
{
	int numberWords, frequency;
	char symbol;
	std::string word, combinationOfNumbers;
	std::vector<std::pair<int, std::string> > wordPair;
	std::map<std::string, std::vector<std::pair<int, std::string> > > dictionary;

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

		std::map<std::string, std::vector<std::pair<int, std::string> > >::iterator p;
		p = dictionary.find(combinationOfNumbers);

		if(p == dictionary.end())
		{
			wordPair.push_back(std::pair<int, std::string>(frequency, word));

			dictionary.insert(std::pair<std::string, std::vector<std::pair<int, std::string> > >(combinationOfNumbers, wordPair));
		}
		else
		{
			p->second.push_back(std::pair<int, std::string>(frequency, word));
		}

		combinationOfNumbers.clear();
		wordPair.clear();
	}

	for(std::map<std::string, std::vector<std::pair<int, std::string> > >::iterator p = dictionary.begin(); p != dictionary.end(); p++)
	{
		std::sort(p->second.begin(), p->second.end());
	}

	std::string input, task;
	int counter = 0;
	bool space = false, punct = false;
	std::pair<int, std::string> myPair;
	char punctuation[] = ".,?";

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
			std::map<std::string, std::vector<std::pair<int, std::string> > >::iterator p;
			if(input[i] != '*' && input[i] != '1') task += input[i];
			else counter++;
			if(task!="")
			{
				p = dictionary.find(task);
				if(counter == p->second.size() && p->second.size() != 0)
				{
					counter -= 1;
				}
				std::cout << p->second[counter].second;
			}
			if(punct && input[i] == '*')
			{
				std::cout << punctuation[counter];
				counter = 0;
			}
			else if(punct && input[i] != '*')
			{
				counter = 0;
				std::cout << punctuation[counter];
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
			std::map<std::string, std::vector<std::pair<int, std::string> > >::iterator p;
			p = dictionary.find(task);
			/*if(counter >= p->second.size() && p->second.size() != 0)
			{
				p++;
				counter = 0;
			}*/

			if(punct)std::cout << p->second[counter].second;
			else std::cout << p->second[counter].second << " ";

			p->second[counter].first -=1;

			myPair.first = p->second[counter].first;
			myPair.second = p->second[counter].second;
			std::vector<std::pair<int, std::string> >::iterator p1 = p->second.begin();

			for(int j = 0; j < counter; j++)
			{
				p1++;
			}

			p->second.erase(p1);
			p->second.insert(p->second.begin(), myPair);

			std::sort(p->second.begin(), p->second.end(), myObject);
			task.clear();
			counter = 0;
			space = true;
			continue;
		}
	}

	return 0;
}