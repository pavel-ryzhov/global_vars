#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>
using namespace std;

//структура, слово в словаре
	struct Word		        
{
	string s_word;			// слово в базе словаря
	unsigned int s_count;	// приоритет слова
	Word()
	{s_word = "", s_count = 0;}
};

	//операция сравнения, необходимая для работы сортировки
	bool operator<(const Word& lpt,const Word& rpt){
		if(rpt.s_count < lpt.s_count)
			return true;
		else
			if(lpt.s_count == rpt.s_count)
			if(lpt.s_word < rpt.s_word)
				return true;

		return false;
	}
	bool operator==(const Word& lpt, const Word& rpt){
		if(lpt.s_word == rpt.s_word && lpt.s_count == rpt.s_count)
			return true;
		return false;
	}

class T9
{
private:
	vector<Word> m_dictionary;	// вектор слов
public:	
	void strart_t9();											//запуск режима Т9
	void vvod_word();											// ввод слов в словарь
	void vvod_text();											// ввод текста с клавиатуры
	void transform_text(const string& text,int bukw, int cifr);	// преобразвание введенной лексемы в выходное слово
	bool opr_word(char num, char str);
	bool opr_word(const string& num, const string& str);
};


bool T9::opr_word(char num, char str)
{
	switch(num)
	{
	case '2': if(str == 'a' || str == 'b' || str == 'c') return true; else break;
	case '3': if(str == 'd' || str == 'e' || str == 'f') return true; else break;
	case '4': if(str == 'g' || str == 'h' || str == 'i') return true; else break;
	case '5': if(str == 'j' || str == 'k' || str == 'l') return true; else break;
	case '6': if(str == 'm' || str == 'n' || str == 'o') return true; else break;
	case '7': if(str == 'p' || str == 'q' || str == 'r' || str == 's') return true; else break;
	case '8': if(str == 't' || str == 'u' || str == 'v') return true; else break;
	case '9': if(str == 'w' || str == 'x' || str == 'y' || str =='z') return true; else break;
	}

	return false;
}

bool T9::opr_word(const string& num, const string& str)
{
	for(int i=0;i<num.size();++i){
		if(!opr_word(num.at(i),str.at(i)))
			return false;
	}
	return true;
}

void T9::vvod_word()
{
	int n = 0;	//количество слов в словаре 

	cin>>n;

	for(int i=0;i<n;++i){
		Word word;
		cin>>word.s_word>>word.s_count;
		cin.ignore(1);
		m_dictionary.push_back(word);					//добавим слово в словарь

	}

	vector<Word>::iterator iter = m_dictionary.begin();
	sort(iter,iter+m_dictionary.size());				//отсортируем наш словарь по приоритету и алфавиту

}

void T9::vvod_text()
{

	string text = "";
	getline(cin,text);
	
	if(text.at(text.size()-1)!=' ')
		text.push_back(' ');
	while(text.at(0) == ' ')
		text.erase(0,1);

	int start_pos = 0, end_pos = 0;

	while((end_pos = text.find(' ',start_pos)) != -1 )
	{
		string word = "", num = "";
		int count_bukw = 0, count_cifr = 0;
		bool opr_cifr = false, opr_bukw = false;

		word.assign(text,start_pos,end_pos-start_pos);
		if(word == ""){
			cout<<" ";
			start_pos+=1;
			continue;
		}


		for(int i=0;i<word.size();++i){
			if(word.at(i) == '1'){
				if(opr_bukw || opr_cifr)
				{
					transform_text(num,count_bukw,count_cifr);
					num.clear();
					count_bukw = count_cifr = 0;
					opr_bukw = false;
				}
				opr_cifr = true;
				count_cifr++;
			}
			else
				if(isdigit(word.at(i)))
				{
					if(opr_cifr)
					{
						transform_text("0",count_bukw,count_cifr);
						count_bukw = count_cifr = 0;
						opr_cifr = false;
					}
					opr_bukw = true;
					num.push_back(word.at(i));
				}
				else
					if(word.at(i) == '*')
					{
						if(opr_bukw)
							count_bukw++;
						else
							if(opr_cifr)
								count_cifr++;
					}

					if(i == word.size()-1)
					{
						if(num == "")
							transform_text("0",count_bukw,count_cifr);
						else
							transform_text(num,count_bukw,count_cifr);
					}
		}

		start_pos = end_pos+1;
		cout<<" ";
		
	}
}

void T9::transform_text(const string& text, int bukw, int cifr)
{
		int index=0;

		int count = 0;
		for(int i=0; i<m_dictionary.size(); ++i){
			if(m_dictionary.at(i).s_word.size() == text.size())
				if(opr_word(text,m_dictionary.at(i).s_word))
					count++;
		}
	
		

		if(text != "0" )
		{
		count = bukw%count ;
		
		for(int i=0; i<m_dictionary.size(); ++i){
			if(m_dictionary.at(i).s_word.size() == text.size())
				if(opr_word(text,m_dictionary.at(i).s_word))
					if(count == 0){
						index = i;
						break;
					}
					else
						--count;
		}

		
		m_dictionary.at(index).s_count++;
		cout<<m_dictionary.at(index).s_word;

		

		Word word = m_dictionary.at(index);
		m_dictionary.erase(m_dictionary.begin()+index);
		bool opr = false;

		for(int i=0;i<m_dictionary.size();++i)
			if(m_dictionary.at(i).s_count == word.s_count)
			{
				m_dictionary.insert(m_dictionary.begin()+i,word);
				opr  = true;
				break;
			}

			if(m_dictionary.size() == 0)
				m_dictionary.push_back(word);
		if(!opr)
			for(int i=0;i<m_dictionary.size();++i)
				if(m_dictionary.at(i).s_count < word.s_count)
				{
					m_dictionary.insert(m_dictionary.begin()+i,word);
					break;
				}

		}
		if(cifr){
		count = cifr%3;
		if(count == 0)
			count = 3;
			switch(count)
			{
			case 1: cout<<".";break;
			case 2: cout<<",";break;
			case 3: cout<<"?";
			}
		
		}
}
void T9::strart_t9()
{
	vvod_word();
	vvod_text();
}
int main()
{
	T9 nokia;				//объект нашего класса, имитирующий телефон
	nokia.strart_t9();		//запуск режима Т9
	char ch = cin.get();	//задержка экрана

	return 0;
}