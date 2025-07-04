//============================================================================
// Name        : T9.cpp
// Author      : Alexander
// Version     :
// Copyright   : 
// Description : T9, Ansi-style
//============================================================================

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

typedef std::vector <std::pair <std::string, std::pair <int, std::string> > > Dictionary;
typedef std::pair <std::string, std::pair <int, std::string> > Element;

class ConverterToT9
{
private:
	typedef std::map< char, std::string> Map;
	Map data;
public:
	ConverterToT9()
	{
		data.insert(std::make_pair('1',".,?"));
		data.insert(std::make_pair('2',"abc"));
		data.insert(std::make_pair('3',"def"));
		data.insert(std::make_pair('4',"ghi"));
		data.insert(std::make_pair('5',"jkl"));
		data.insert(std::make_pair('6',"mno"));
		data.insert(std::make_pair('7',"pqrs"));
		data.insert(std::make_pair('8',"tuv"));
		data.insert(std::make_pair('9',"wxyz"));
	}

	std::string Execute(const std::string& str)const
	{
		std::string res;
		for(std::string::const_iterator i=str.begin();i!=str.end();++i)
		{
			res.push_back(CharToT9(*i));
		}

		return res;
	}

private:
	ConverterToT9(const ConverterToT9& );
	ConverterToT9& operator=(const ConverterToT9& );

	class CmpChar
	{
	public:
		char s_;

		CmpChar(char s): s_(s) {}

		bool operator()(const std::pair<const char, std::string >& i) const
		{
			return i.second.find(s_)!=std::string::npos;
		}
	};

	char CharToT9(char s) const
	{
		Map::const_iterator i=std::find_if( data.begin(), data.end(), CmpChar(s) );
		return i->first;
	}
};

void c_shift(const Dictionary::iterator& begin, const Dictionary::iterator& end)  //функция циклического сдвига только на 1 позицию
{
	/*Т.к. сдвиг вправо будет осуществляться только на одну позицию,
	 * поэтому выбран прямой алгоритм обмена,
	 * цикл выполняется в худшем случае n-1 раз, в данном частном случае алгоритм переворотами
	 * работал бы дольше*/

	for(int i=0;i<std::distance(begin, end); ++i)
	{
		if((end-i-1)->second.first > (end-i)->second.first)
			break;
		std::swap(*(end-i-1), *(end-i));
	}
}


void LoadDict( Dictionary& res, const ConverterToT9& conv)
{
	int N;
	std::cin>>N;
	std::pair<int, std::string > word;
	for(int i=0;i<N;++i)
	{
		std::cin>>word.second>>word.first;
		res.push_back(std::make_pair(conv.Execute(word.second),word));
	}
}

class EqComp //отношение эквивалентности
{
public:
	bool operator()(const Element& left, const Element& right) const
	{
		return left.first < right.first;
	}

	bool operator()(const Element& left, const std::string& right) const
	{
		return left.first < right;
	}
	bool operator()(const std::string& left, const Element& right) const
	{
		return left < right.first;
	}
};

class FreqComp	//сравнения по частоте
{
public:
	bool operator()(const Element& left, const Element& right) const
	{
		return left.first == right.first ?
			(left.second.first == right.second.first ? left.second.second < right.second.second
			: left.second.first > right.second.first)
			: left.first < right.first;
	}
};

std::string answer(Dictionary& dict, const std::string& request) //обработка нажатых клавиш
{
	bool one=false;
	std::string punctuation=".,?";

	std::string current="";
	std::string total="";
	int i1=0;

	Dictionary::iterator it;
	std::pair <Dictionary::iterator, Dictionary::iterator > range;

	for (size_t i=0; i<request.size(); ++i)
	{
		switch(request[i])
		{
		case ' ':
			if (current=="" && one==false)
			{
				total+=" ";
				break;
			}

			if (one==true)
			{
				one=false;
				total+=punctuation[i1];
				if( (i+1)!=request.size() )
					total+=" ";
				i1=0;
				break;
			}

			if (current!="" && request[i-1]=='*')
			{
				total+=(*it).second.second+" ";
				++ (*it).second.first;
				c_shift(range.first, it);
				current="";
				break;
			}
			else
			{
				if (current!="")
				{
					range.first=std::lower_bound(dict.begin(), dict.end(), current, EqComp());
					it=range.first;
					total+=(*it).second.second+" ";
					++ (*it).second.first;
					c_shift(range.first, it);
					current="";
					break;
				}
				break;
			}

		case '*':
			if((i+1)!=request.size())
			{
				if (current!="" && request[i-1]=='*')
				{
					++it;
					break;
				}

				if (current!="" && one==false)
				{
					range=std::equal_range(dict.begin(), dict.end(), current, EqComp());
					if(range.second == dict.end())
						range.second=--dict.end();
					it=range.first;
					++it;
					break;
				}

				if (one==true && request[i+1]!='*')
				{
					one=false;
					++i1;
					total+=punctuation[i1];
					i1=0;
					current="";
					break;
				}

				if (one==true && request[i+1]=='*')
				{
					++i1;
					break;
				}
			}
			else
			{
				if (current!="" && one==false)
				{
					range=std::equal_range(dict.begin(), dict.end(), current, EqComp());
					if(range.second == dict.end())
						range.second=--dict.end();
					it=range.first;
					++it;
					break;
				}

				if (one==true && request[i+1]!='*')
				{
					one=false;
					++i1;
					total+=punctuation[i1];
					i1=0;
					current="";
					break;
				}
			}
			break;

		case '1':
			one=true;
			if(current!="")
			{
				if (current!="" && request[i-1]!='*')
				{
					range.first=std::lower_bound(dict.begin(), dict.end(), current, EqComp());
					it=range.first;
				}

				total+=(*it).second.second;
				++ (*it).second.first;
				c_shift(range.first, it);
				current="";
			}
			if ((i+1)==request.size())
				total+=punctuation[i1];
			break;

		default:
			if ((i+1)==request.size())
			{
				range.first=std::lower_bound(dict.begin(), dict.end(), current, EqComp());
				it=range.first;
				total+=(*it).second.second;
				++ (*it).second.first;
				c_shift(range.first, it);
				current="";
				break;
			}
			current+=request[i];
			break;
		}
	}

	return total;

}

int main() {
	ConverterToT9 conv;
	Dictionary res;
	LoadDict(res, conv);

	std::string request="";
	std::getline(std::cin,request);
	std::getline(std::cin,request);

	std::sort(res.begin(), res.end(), FreqComp());

	std::cout<<answer(res,request);
	return 0;
}
