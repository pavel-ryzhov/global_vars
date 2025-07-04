#include <iostream>
#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

class CombinationList
{
	struct WordFreq{
		std::string word;
		int freq;
		WordFreq(std::string _word,int _freq): word(_word),freq(_freq) {}
		bool operator<(const WordFreq &Right)const
		{ 
			if(freq < (Right.freq))
				return false;
			if(freq > (Right.freq))
				return true;

			return std::lexicographical_compare(word.begin(),word.end(),Right.word.begin(),Right.word.end());
		}
	};
	std::list<WordFreq> words;
public:
	

	void Add(const std::string& word,int freq)
	{
		words.push_back(WordFreq(word,freq));
		words.sort();
	}

	std::string Get(int Number)
	{
		if(words.size() == 0)
		{
			std::cerr << "Invalid word combination" << std::endl;
			return "";
		}
		if(Number == 0) 
		{
			words.front().freq++;
			return words.front().word;
		}
		std::list<WordFreq>::iterator it=words.begin();
		for(int i=0;i<Number;i++)
			it++;
		WordFreq temp = (*it);
		temp.freq++;
		words.erase(it);
		for(it=words.begin();it!=words.end();it++)
			if((*it).freq<=temp.freq)
			{
				words.insert(it,temp);
				return temp.word;
			}

		if(it == words.end())
			words.push_back(temp);
		return temp.word;
	}
};

std::map<std::string,CombinationList> Dictionary;

std::string string2keys(const std::string& text)
{
	std::vector<std::string> LetterButtons;
	LetterButtons.push_back(".,?");
	LetterButtons.push_back("abc");
	LetterButtons.push_back("def");
	LetterButtons.push_back("ghi");
	LetterButtons.push_back("jkl");
	LetterButtons.push_back("mno");
	LetterButtons.push_back("pqrs");
	LetterButtons.push_back("tuv");
	LetterButtons.push_back("wxyz");
	
	std::string result = text;
	for(std::size_t i=0;i<text.length();i++)
	{
		for(std::size_t j=0; j<LetterButtons.size(); j++)
			if(LetterButtons[j].find( text[i] ) != std::string::npos)
			{
				char buff[10]={0};
				sprintf(buff,"%d",j+1);
				result[i]=buff[0];
			}
	}
	return result;
}

void ReadDictionary()
{
	int Count = 0;
	std::cin >> Count;

	if(Count < 3 || Count > 50000)
		std::cerr << "Invalid dictionary size" << std::endl;

	std::string word;
	int freq=0;
	for(int i=0;i<Count;i++)
	{
		std::cin >> word;
		std::cin >> freq;

		Dictionary[string2keys(word)].Add(word,freq);
	}
}


int main()
{
	ReadDictionary();
	char c=0;
	std::string word;
	int number=0;
	const char DOTS[]={'.',',','?'};
	c=std::cin.get();
	while(true)
	{
		word.clear();
		number=0;

		while(c==' ' || c == '\r' || c=='\n')
		{
			if(c==' ')
				std::cout << c;
			c=std::cin.get();
		}
		if(!std::cin.good())
			break;
		if(c!='1')
		{
			while(c>='2' && c <='9')
			{
				word.push_back(c);
				c=std::cin.get();
			}
			while(c == '*')
			{
				number++;
				c=std::cin.get();
			}
			std::cout << Dictionary[word].Get(number);
		}
		else
		{
			c=std::cin.get();
			while(c == '*')
			{
				number++;
				c=std::cin.get();
			}
			if(number>2)
				std::cerr << "Invalid symbol" << std::endl;
			std::cout << DOTS[number%3];
		}
	}
	return 0;

}