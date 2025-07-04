#include <iterator>
#include <iostream>
#include <stdlib.h>

#include <vector>
#include <string>
#include <map>
#include <list>

class Word
//запись об упоминании слова (abc 4)
{
	int count;
	std::string word;
public:
	bool operator<(const Word& Right) const { return count < Right.count; }
	bool operator>(const Word& Right) const { return count > Right.count; }
	bool operator==(const Word& Right) const {return (count == Right.count && word == Right.word); }
	void IncreasePopularity()	{ count++;}
	Word(std::string w, int _Count = 1): count(_Count) { word = w; }
	std::string GetString() { return word; }
	int GetCount() const { return count; }
	bool Equal(int Second=1) {return Second == count; }
};



struct WordCountEqual : public std::binary_function<Word,int,bool> {
  bool operator() (Word a, int b)const  {return (a.GetCount()==b);}
};

struct WordCountGreater : public std::binary_function<Word,int,bool> {
  bool operator() (Word a, int b)const  {return (a.GetCount()>b);}
};

class WordCombinations
//все слова для определенной комбинации (111 = aaa,bbb,ccc,abc ...)
{
	std::list<Word> words;
public:
	void Add(const std::string& word, int count = 1 ) 
	{
		words.push_back( Word(word,count) );
		words.sort(std::greater<Word>());
	}

	std::string Find(int Delta)
	{
		if( !Delta )
		{
			words.front().IncreasePopularity();
			return words.front().GetString();
		}
		if(Delta > words.size())
			std::cerr << "Invalid word position in dictionary!" << std::endl;
		std::list<Word>::iterator it=words.begin();
		for(int i=0;i<Delta;i++)
		{
			it++;
			if(it == words.end())
			{
				std::cerr << "Invalid word index!";
				it = words.begin();
			}
		}
		Word temp = *it;
		temp.IncreasePopularity();
		words.erase(it);
		it=words.begin();
		for(it=words.begin();it!=words.end();it++)
		{
			if( (*it).GetCount() <= temp.GetCount()){
				words.insert(it,temp);
				break;
			}
		}
		if(it == words.end())
			words.push_back(temp);
		return temp.GetString();	
	}
};

typedef std::map<int,WordCombinations> Dictionary;

int string2keys(const std::string& text)
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
	
	int result = 0;
	for(std::size_t i=0;i<text.length();i++)
	{
		for(std::size_t j=0; j<LetterButtons.size(); j++)
			if(LetterButtons[j].find( text[i] ) != std::string::npos)
			{
				result += j+1;
				result *= 10;
			}
	}
	result /= 10;
	return result;
}

void FillDictionary(Dictionary& dict,int number,const std::string& word,int count=1)
{
	dict[number].Add(word,count);
}

void ReadData(Dictionary& dict)
// чтение словаря
{
	std::string Word;

	int DictionarySize = 0,WordCount=0;
	std::cin >> DictionarySize;
	if(DictionarySize < 3|| DictionarySize > 50000)
		std::cerr << "Invalid dictionary size" << std::endl;

	for(int i=0; i < DictionarySize ; i++)
	{
		WordCount=0;
		Word.clear();
		std::cin >> Word;
		std::cin >> WordCount;
		if(WordCount < 1 || WordCount > 1000)
			std::cerr << "Invalid word count" << std::endl;
		FillDictionary(dict,string2keys(Word), Word, WordCount);
	}
}

std::string Read()
//чтение 
{
	std::string result;
	char c;
	while(std::cin.good()) //skipping '    '
	{
		c = std::cin.get();
		if(c==' ')
			std::cout << c;
		if(c != ' ' && c != '\n' && c!='\r')
			break;
	}
	if(!std::cin.good())
		return "";
	result.push_back(c);
	while(std::cin.good()) 
	{
		c = std::cin.get();
		if(!std::cin.good())
			break;
		if(c == ' ' || c == '1' || c == '\n' || c == '\r')
		{
			std::cin.unget();
			break;
		}
		else
			result.push_back(c);
	}
	return result;
}

int main(int argc, char* argv[])
{
	std::map<int,WordCombinations> dict;

	ReadData(dict);

	std::string buffer;
	char PunctDots[]={'.',',','?'};
	int WrongWord=0;
	while(1)
	{
		buffer = Read();
		if(buffer == "")
			break;
		WrongWord=0;
		while(buffer[buffer.length()-1] == '*')
		{
			WrongWord++;
			buffer.erase(buffer.length()-1);
			if(!buffer.size())
				std::cerr << "Invalid word!" << std::endl;
		}
		if(buffer[0] == '1')
		{
			if(WrongWord > 2)
				WrongWord %= 3;
			std::cout << PunctDots[WrongWord];
		}
		else
		{
			int Postition = atoi(buffer.c_str());
			std::cout << dict[Postition].Find(WrongWord);		
		}
	}

	return 0;
}

