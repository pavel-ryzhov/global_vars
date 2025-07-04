#include <iterator>
#include <queue>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <functional>


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
	std::vector<Word> words;
public:
	void Add(const std::string& word, int count = 1 ) 
	{
		words.push_back( Word(word,count) );
		std::sort(words.begin(),words.end(),std::greater<Word>());
	}

	std::string Find(int Delta)
	{
		if( !Delta )
		{
			words[Delta].IncreasePopularity();
			return words[Delta].GetString();
		}

		/// 3 3 2 2 1 our
		// need swap out,swap out and last 2, last 2(out) and first 2
		// 3 3 2 2 out 1
		// 3 3 out 2 2 1
		int Count = words[Delta].GetCount(),
			SwapCount = 2; // =)))
		for(std::size_t i = Delta;i>=0 && SwapCount > 0;i--)
		{
			if(i == 0 || words[i-1].GetCount() > Count)
			{
				if(SwapCount == 2) words[Delta].IncreasePopularity();
				if(words[i].GetCount()<=words[Delta].GetCount())
				{
					std::swap(words[i],words[Delta]);
					Delta = i;
				}
				SwapCount--;
			}
			if(!i)		// size_t - unsigned int
				break;
		}
		return words[Delta].GetString();
				
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
{
	std::string WordCount,Word;

	std::cin >> WordCount;
	int count = atoi( WordCount.c_str() ) ; 

	for(int i=0; i < count ; i++)
	{
		WordCount.clear();
		Word.clear();
		std::cin >> Word;
		std::cin >> WordCount;
		FillDictionary(dict,string2keys(Word), Word, atoi(WordCount.c_str()));
	}
}

std::string Read()
{
	std::string result;
	char c;
	while(std::cin.good()) //skipping '    '
	{
		c = std::cin.get();
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
	bool FirstWord = true;
	while(1)
	{
		buffer = Read();
		if(buffer == "")
			break;
		int WrongWord=0;
		while(buffer[buffer.length()-1] == '*')
		{
			WrongWord++;
			buffer.erase(buffer.length()-1);
		}
		if(buffer[0] == '1')
		{
			char PunctDots[]={'.',',','?'};
			std::cout << PunctDots[WrongWord];
		}
		else
		{
			if(FirstWord)
				FirstWord=false;
			else
				std::cout << " ";
			std::cout << dict[atoi(buffer.c_str())].Find(WrongWord);		
		}
	}

	return 0;
}

