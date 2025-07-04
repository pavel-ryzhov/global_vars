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
			p->second.insert(p->second.end(), std::pair<int, std::string>(frequency, word));
		}

		combinationOfNumbers.clear();
		wordPair.clear();
	}

	std::string input, task;
	int counter = 0;
	bool punct = false;
	std::pair<int, std::string> myPair1, myPair2, myPair3;

	myPair1.first = -3000;
	myPair1.second = '.';
	myPair2.first = -2000;
	myPair2.second = ',';
	myPair3.first = -1000;
	myPair3.second = '?';

	wordPair.insert(myPair1);
	wordPair.insert(myPair2);
	wordPair.insert(myPair3);
	dictionary.insert(std::pair<std::string, std::multiset<std::pair<int, std::string>, setComparator> >("1", wordPair));

	std::cin.get();
	std::getline(std::cin, input);

	std::map<std::string, std::multiset<std::pair<int, std::string>,  setComparator> >::iterator dict;
	std::multiset<std::pair<int, std::string>, setComparator>::iterator value;

	for(int i = 0; i < input.size(); i++)
	{
		if(i == input.size()-1)
		{
			if(input[i] == ' ')
			{
				if(task != "")
				{
					dict = dictionary.find(task);
					value = dict->second.begin();

					for(int j = 0; j < counter; j++) value++;

					if(task != "")std::cout << value->second << ' ';
				}
				else std::cout << ' ';
				break;
			}
			if(input[i] == '1')
			{
				dict = dictionary.find(task);
				value = dict->second.begin();

				for(int j = 0; j < counter; j++) value++;

				if(task != "")std::cout << value->second << '.';
				else std::cout << ".";
				break;
			}
			if(input[i] == '*' && punct)
			{
				counter++;
				dict = dictionary.find(task);
				task.clear();
				value = dict->second.begin();

				for(int j = 0; j < counter; j++) value++;

				std::cout << value->second;

				break;
			}
			else if(input[i] == '*' && !punct)
			{
				counter++;
				dict = dictionary.find(task);
				value = dict->second.begin();

				for(int j = 0; j < counter; j++) value++;

				std::cout << value->second;

				break;
			}
			else
			{
				task += input[i];

				dict = dictionary.find(task);
				value = dict->second.begin();

				for(int j = 0; j < counter; j++) value++;

				std::cout << value->second;
				break;
			}
		}
		if(input[i] == '*')
		{
			counter++;
			continue;
		}
		if(input[i] == '1')
		{
			if(task != "")
			{
				dict = dictionary.find(task);
				value = dict->second.begin();

				for(int j = 0; j < counter; j++) value++;

				std::cout << value->second;

				myPair1.first = value->first - 1;
				myPair1.second = value->second;

				if(task != "1")
				{	
					dict->second.erase(value);
					dict->second.insert(myPair1);
				}
			}
			counter = 0;
			task = "1";
			punct = true;
			continue;
		}
		else if(!punct && input[i] != ' ')
		{
			task += input[i];
		}
		else if(punct)
		{
			dict = dictionary.find(task);
			task.clear();
			value = dict->second.begin();

			for(int j = 0; j < counter; j++) value++;

			if(input[i] != ' ')
			{
				std::cout << value->second;
				task += input[i];
			}
			else std::cout << value->second << ' ';

			counter = 0;
			punct = false;
		}
		else
		{
			if(task != "")
			{	
				dict = dictionary.find(task);
				value = dict->second.begin();

				for(int j = 0; j < counter; j++) value++;

				std::cout << value->second << ' ';

				myPair1.first = value->first - 1;
				myPair1.second = value->second;

				if(task != "1")
				{
					dict->second.erase(value);
					dict->second.insert(dict->second.begin(), myPair1);
				}

				counter = 0;
				task.clear();
			}
			else std::cout << ' ';
		}
	}

	return 0;
}