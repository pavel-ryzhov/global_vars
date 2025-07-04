#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
using namespace std;

//структура, слово в словаре
	struct Word		        
{
	pair<unsigned long, unsigned long> m_number;// номер, введенный с телефона, соответствующий слову
	char* s_word;			// слово в базе словаря
	unsigned short s_count;	// приоритет слова

	//операция сравнения, необходимая для работы сортировки
	Word()
	{m_number.first=m_number.second =0, s_word = NULL, s_count = 0;}
};
	bool operator<(const Word& lpt,const Word& rpt){
		if(rpt.s_count < lpt.s_count)
			return true;
		else
			if(lpt.s_count == rpt.s_count)
			if(strcmp(lpt.s_word, rpt.s_word)<0)
				return true;

		return false;
	}
	bool operator==(const Word& lpt, const Word& rpt){
		if(strcmp(lpt.s_word,rpt.s_word)==0 && lpt.s_count == rpt.s_count)
			return true;
		return false;
	}

class T9
{
private:
	vector<Word> m_dictionary;	// вектор слов
public:
	void strart_t9();									//запуск режима Т9
	void vvod_word();									// ввод слов в словарь
	void vvod_text();									// ввод текста с клавиатуры
	void transform_text(const pair<unsigned long, unsigned long>& num, int bukw, int cifr);	// преобразвание введенной лексемы в выходное слово
	unsigned long atoll(const char* test);
	char itoa(int n);									// перевод числа в строку
};

int c_find(const char* str, char ch, int start)
{
	for(int i = start; i<strlen(str); ++i){
		if(str[i]==ch)
			return i;
	}

	return -1;
}

char T9::itoa(int n)
{
        std::stringstream stream;
        stream <<n;
		return stream.str().at(0);
}

unsigned long T9::atoll(const char* text)
{
	if(strcmp(text,"") == 0)
		return 0;

	unsigned long num = text[0]-'0';

	for(int i=1;i<strlen(text);++i){
		num*=10;
		num+=text[i]-'0';
	}
	return num;
}

void T9::vvod_word()
{
	int n = 0;	//количество слов в словаре 
	cin>>n;


	for(int i=0;i<n;++i){
		Word word;
		word.s_word = new char[21];
		cin>>word.s_word>>word.s_count;
		cin.ignore(1);
		char* buf_num = new char[21];
		for(int i=0;i<21;++i)
			buf_num[i]=' ';

		for(int i = 0;i<strlen(word.s_word); ++i){
			if(word.s_word[i] >= 'p' && word.s_word[i] <='s')
				buf_num[i]='7';
			else
				if(word.s_word[i] >= 't' && word.s_word[i] <='v')
					buf_num[i]='8';
				else
					if(word.s_word[i] >= 'w' && word.s_word[i] <='z')
						buf_num[i]='9';
					else 
						if(word.s_word[i] >= 'a' && word.s_word[i] <= 'v')
							buf_num[i]=itoa(int(word.s_word[i]-'a')/3 + 2);
			buf_num[i+1]='\0';
		}

		if(strlen(buf_num)>10)
		{
			char* num1 = new char[11];
			char* num2 = new char[11];
			strncpy(num1,buf_num,10);
			num1[10]='\0';
			for(int i = 10,c=0;i<strlen(buf_num);++i){
				num2[c++]=buf_num[i];
				num2[c]='\0';
			}
			word.m_number.first = atoll(num2);
			word.m_number.second = atoll(num1);
		}
		else
			word.m_number.second = atoll(buf_num);
		m_dictionary.push_back(word);					//добавим слово в словарь
	}

	vector<Word>::iterator iter = m_dictionary.begin();
	sort(iter,iter+m_dictionary.size());				//отсортируем наш словарь по приоритету и алфавиту



}

void T9::vvod_text()
{

	char* text = new char[100001];
	cin.getline(text,100001,'\n');
	int index = 0;

	if(text[strlen(text)] !=' '){
		text[strlen(text)]=' ';
		text[strlen(text)+1]='\0';
	}


	while(text[index] == ' ')
		index++;

	int start_pos = 0, end_pos = 0;

	while((end_pos = c_find(text,' ',start_pos)) != -1 )
	{
		string word = "", lnum = "", rnum = "";
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
					pair<unsigned long, unsigned long> num;
					num.first = atoll(lnum.c_str());
					num.second = atoll(rnum.c_str());
					transform_text(num,count_bukw,count_cifr);
					lnum.clear();
					rnum.clear();
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
						pair<unsigned long, unsigned long> num(0,0);
						transform_text(num,count_bukw,count_cifr);
						count_bukw = count_cifr = 0;
						opr_cifr = false;
					}
					opr_bukw = true;
					if(rnum.size()<10)
						rnum.push_back(word.at(i));
					else
						lnum.push_back(word.at(i));
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
						if(rnum == "0")
						{
							pair<unsigned long, unsigned long> num(0,0);
							transform_text(num,count_bukw,count_cifr);
						}
						else
						{
							pair<unsigned long, unsigned long> num;
							num.first = atoll(lnum.c_str());
							num.second = atoll(rnum.c_str());
							transform_text(num,count_bukw,count_cifr);
						}
					}
		}

		start_pos = end_pos+1;
		cout<<" ";
		
	}
}

void T9::transform_text(const pair<unsigned long, unsigned long>& num, int bukw, int cifr)
{
		int index=0;
		int count = 0;

		if(num.second != 0 )
		{	
		for(int i=0; i<m_dictionary.size(); ++i){
			if(m_dictionary.at(i).m_number.first == num.first && m_dictionary.at(i).m_number.second== num.second)
				if(count == bukw){
					index = i;
					break;
				}
				else
					++count;
			if(i==m_dictionary.size()-1)
				i=0;
		}

		
		m_dictionary.at(index).s_count++;
		cout<<m_dictionary.at(index).s_word;

		for(int i=0;i<m_dictionary.size();++i)
			if(m_dictionary.at(i).s_count <= m_dictionary.at(index).s_count)
			{
				Word word = m_dictionary.at(index);
				m_dictionary.erase(m_dictionary.begin()+index);
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