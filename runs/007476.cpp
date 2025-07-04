#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

char* DigitsToLetters[] = {".,?", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

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

class Dictionary
{
public:
	Dictionary(): Words(20)
	{
		Add("?", 1);
		Add(",", 2);
		Add(".", 3);
	}
	void Add(T9Word aT9Word)
	{
		Words[aT9Word.Word.length()-1].push_back(aT9Word); //записываем слова в разные массивы в зависимости от длины
	}
	void Add(std::string str, int f)
	{
		T9Word t9Word;
		t9Word.Word = str;
		t9Word.Frequent = f;
		Add(t9Word);
	}
	void Sort()
	{
		for (int i=0;i<Words.size();i++)
		{
			std::sort(Words[i].begin(), Words[i].end());
		}
	}
	void InitList(std::string str);
	std::string Get();
	void Next()
	{
		++CurWord;
		if (CurWord >= WordList.end())
			CurWord = WordList.begin();
	}
private:
	std::vector<std::vector<struct T9Word> > Words; //база слов
	std::vector<T9Word> WordList; //список подошедших слов
	std::vector<T9Word>::iterator CurWord;
};

std::string Dictionary::Get()
{
	if (WordList.size() == 0)
		return "";
	if ( !((CurWord->Word == ".") ||
		(CurWord->Word == ",") || 
		(CurWord->Word == "?")) )
	{
		std::vector<T9Word>::iterator iter = Words[CurWord->Word.length()-1].begin(); //ищем слово в базе
		while (iter != Words[CurWord->Word.length()-1].end())
		{
			if (iter->Word == CurWord->Word)
			{
				break;
			}
			++iter;
		}
		iter->Frequent++;
		std::vector<T9Word>::iterator iter2 = iter;
		while ( (iter2 > Words[CurWord->Word.length()-1].begin()) && //перемещаем его вверх по списку
			( ((iter2-1)->Frequent) <= (iter->Frequent) ) )
		{
			--iter2;
		}
		if (iter != iter2)
		{
			T9Word w = *iter;
			Words[CurWord->Word.length()-1].erase(iter);
			Words[CurWord->Word.length()-1].insert(iter2, w);
		}
	}
	return CurWord->Word;
}

void Dictionary::InitList(std::string str)
{
	WordList.clear();
	std::vector<T9Word>::iterator iter = Words[str.length()-1].begin();
	bool IsMatch = false;
	while (iter < Words[str.length()-1].end())
	{
		IsMatch = true;
		for (size_t i = 0;i<str.length(); i++)
		{
			if (!strchr(DigitsToLetters[str[i]-'0'-1], (*iter).Word[i]))
			{
				IsMatch = false;
				break;
			}
		}
		if (IsMatch)
			WordList.push_back(*iter);
		++iter;
	}
	CurWord = WordList.begin();
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
	//cin.get();
	return 0;
}