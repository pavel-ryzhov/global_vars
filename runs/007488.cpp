#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <map>

char* DigitsToLetters[] = {".,?", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
char LettersToDigits[] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6', '6', '6', '7', '7', '7', '7', '8', '8', '8', '9', '9', '9', '9'};


struct T9Word
{
public:
	std::string Word;
	int Frequent;
	bool operator < (const T9Word aWord) const;
};

bool T9Word::operator < (const T9Word aWord) const
{
	if (Frequent < aWord.Frequent)
		return false;
	else if (Frequent > aWord.Frequent)
		return true;
	else if (Word > aWord.Word)
		return false;
	return true;
}

typedef std::map<std::string,std::vector<T9Word> > amap;

class Dictionary
{
public:
	Dictionary()
	{
		Add("?", 1);
		Add(",", 2);
		Add(".", 3);
	}
	void Add(const T9Word& aT9Word)
	{
		std::string str;
		for (size_t i=0; i<aT9Word.Word.length(); i++)
		{
			if (aT9Word.Word[i] == '.' || 
				aT9Word.Word[i] == ',' ||
				aT9Word.Word[i] == '?')
				str += '1';
			else
				str += LettersToDigits[aT9Word.Word[i]-'a'];
		}
		if (!Words.count(str))
		{
			std::vector<T9Word> v;
			v.push_back(aT9Word);
			Words.insert(std::pair<std::string,std::vector<T9Word> >(str, v));
		}
		else
			Words[str].push_back(aT9Word);
	}
	void Add(const std::string& str, int f)
	{
		T9Word t9Word;
		t9Word.Word = str;
		t9Word.Frequent = f;
		Add(t9Word);
	}
	void Sort()
	{
		for (amap::iterator iter = Words.begin(); iter != Words.end(); ++iter)		
			std::sort(iter->second.begin(), iter->second.end());
	}
	void InitList(const std::string& str);
	std::string Get();

	void Next()
	{
		++CurWord;
		if (CurWord == LastWord)
			CurWord = FirstWord;
	}
private:
	std::vector<T9Word>* CurVector;
	amap Words; //база слов
	std::vector<T9Word>::iterator CurWord, FirstWord, LastWord;
	
};

std::string Dictionary::Get()
{
	if ( !((CurWord->Word == ".") ||
		(CurWord->Word == ",") || 
		(CurWord->Word == "?")) )
	{
		CurWord->Frequent++;
		std::vector<T9Word>::iterator iter = CurWord;
		while ( (iter != FirstWord) && ((iter-1)->Frequent <= CurWord->Frequent) )
			iter--;
		T9Word w = *CurWord;
		if (iter != CurWord)
		{
			CurVector->erase(CurWord);
			CurVector->insert(iter, w);
		}
		return w.Word;
	}
	return CurWord->Word;
}

void Dictionary::InitList(const std::string& str)
{
	CurVector = &Words[str];
	FirstWord = CurVector->begin();
	CurWord = FirstWord;
	LastWord = CurVector->end();
}

int main()
{
	using namespace std;
	Dictionary Dict;
	int n = 0;
	cin>>n;
	T9Word t9Word;
	for (int i=0;i<n;i++)
	{
		cin>>t9Word.Word;
		cin>>t9Word.Frequent;
		Dict.Add(t9Word);
	}
	Dict.Sort();
	cin.ignore(1); //игнорируем последний знак конца строки
	string In, Out = "";
	getline(cin, In);
	string::iterator iter = In.begin();
	string buf = "";
	bool WordAdded = true;
	while (iter < In.end())
	{
		buf = "";
		while ((iter < In.end()) && (*iter != ' ') && (*iter != '1') && (*iter != '*') )
		{
			buf+= *iter;
			++iter;
		}
		if (buf.length())
		{
			if (!WordAdded)
				Out+=Dict.Get();
			Dict.InitList(buf);
			WordAdded = false;
		}
		if (iter >=In.end() || *iter == ' ' )
		{
			if (!WordAdded)
			{
				Out+=Dict.Get();
			}
			if (iter < In.end())
			{

				Out += *iter;
				++iter;
			}
			WordAdded = true;
			continue;
		}
		if (*iter == '*')
			Dict.Next();

		if (*iter == '1')
		{
			if (!WordAdded)
			{
				Out+=Dict.Get();
			}
			Dict.InitList("1");
			WordAdded = false;
		}
		++iter;
		if (iter >=In.end())
			Out+=Dict.Get();
	}
	cout<<Out;
	return 0;
}