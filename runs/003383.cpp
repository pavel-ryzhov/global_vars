// T9.cpp : Defines the entry point for the console application.
//

#include <map>
#include <list>
#include <iostream>
#include <string>

#define FILENAMESIZE 256
#define N_MIN 3
#define N_MAX 50000
#define F_MAX 1000
#define MAX_LEN 20
#define MAX_SMS_LEN 100000

typedef struct List_Element
{
	std::string m_string;
	int m_frequency;
	List_Element(std::string s, int f) {m_string = s; m_frequency = f;};
} List_Element_Type;
typedef std::list<List_Element_Type>::iterator list_iterator;

const char punct_marks[3] = {'.' , ',', '?'};				//Знаки препинания

//Список слов с одинаковым цифровым индексом
class List_Vocabular
{
private:
	std::list<List_Element_Type> mList;
public:
	void insert (List_Element_Type );
	void push_back (List_Element_Type );
	std::string return_word(int );
};

typedef std::multimap < std::string, List_Vocabular > vocabular_type;
typedef vocabular_type::iterator vocabular_iterator;
typedef std::pair < const std::string, List_Vocabular > make_pair;

vocabular_type Vocabular;					//Словарь

//Добавление слова в словарь
void List_Vocabular::insert (List_Element_Type element)
{
	int freq = element.m_frequency;
	std::string s = element.m_string;
	list_iterator it = mList.begin();
	while (freq < it->m_frequency)
	{
		it++;
		if (it == mList.end())
		{
			mList.insert(it, element);
			return;
		}
	}

	if (freq == it->m_frequency)
		while (s > it->m_string && it->m_frequency == freq )
		{
			it++;
			if (it == mList.end())
				break;
		}

	mList.insert(it, element);
}
void List_Vocabular::push_back (List_Element_Type element)
{
	mList.push_back(element);
}
//Возврат слова из словаря
std::string List_Vocabular::return_word(int iPosition)
{
	std::string return_string = "";
	list_iterator it, it_cur = mList.begin();
	bool bChange_place = false;
	for (int i = 0; i < iPosition; i++)
		it_cur++;	

	int new_freq = it_cur->m_frequency += 1;
	
	return_string = it_cur->m_string;

	if (it_cur == mList.begin() )
		return return_string;
	else
	{
		it = it_cur;
		it--;
		while ( (new_freq >= it->m_frequency)  )
		{
			bChange_place = true;
			if (it == mList.begin())
				break;
			it--;
		}
		if (new_freq < it->m_frequency)
			it++;
		if (bChange_place)
		{
			mList.erase(it_cur);
			mList.insert(it, List_Element(return_string, new_freq));
		}
	}
	
	return return_string;
}
//Получение знака препинания
char Punctuation_Mark(int type)
{
	return punct_marks[type %3];
}
//Поиск слова в словаре
std::string Word_Search(std::string current_word, int type, char punct)
{
	std::string ret_s = "";
	if (current_word != "")
		ret_s = Vocabular.find(current_word)->second.return_word(type);
	if (punct != 0)
		ret_s = ret_s + punct;
	return ret_s;
}
//Выделения слова из строки
std::string get_current_word (std::string &s, size_t delim, int &type)
{
	std::string temp = s.substr(0, delim);
	size_t first_star_pos = temp.find_first_of("*", 0);
	if (first_star_pos == std::string::npos)
		return temp;
	type = (int) (delim - first_star_pos);
	return temp.substr(0, first_star_pos);
	
}
//Выделение разделителя (знак препинания или пробел) из строки
char get_current_delimeter (std::string &s, size_t delim)
{
	size_t sec_delim = s.find_first_not_of("*", delim + 1);
	std::string temp = s.substr(delim, sec_delim - delim);
	if (sec_delim == std::string::npos)
		s = "";
	else
		s = s.substr(sec_delim, s.size());

	size_t star_number = temp.size() - 1;
	if (temp[0] == '1')
		return Punctuation_Mark((int) (star_number) );
	else
	if (temp[0] == ' ')
		return ' ';
	return 0;
}
//Чтение строки СМС
std::string Read_SMS(std::string &SMS, size_t pos)
{
	std::string current_word = "";
	char current_delimeter;
	int type = 0, copy_number = 1;
	char punct = 0;
	std::string temp = "";

	size_t delim = SMS.find_first_of ("1 ", pos);
	//Если не найдено ни пробелов, ни знаков препинания, значит в строке осталось последнее слово
	if (delim == std::string::npos)
		SMS = "";
	else
	{
		current_word = get_current_word(SMS, delim, type);
		current_delimeter = get_current_delimeter(SMS, delim);
	}
		return Word_Search(current_word, type, current_delimeter);
}
//Клавиатура T9
char T9_key(char c)
{
	if (c < 100)
		return '2';
	else
	if (c < 103)
		return '3';
	else
	if (c < 106)
		return '4';
	else
	if (c < 109)
		return '5';
	else
	if (c < 112)
		return '6';
	else
	if (c < 116)
		return '7';
	else
	if (c < 119)
		return '8';

	return '9';

}
//Заполнение словаря
void Fill_Vocabular(vocabular_type &Vocabular)
{
	int N, f = 0;
	vocabular_iterator it;
	std::string s, T9_string("");

	std::cin>>N;	
	
	for (int i = 0; i < N; i++)
	{
		std::cin>>s>>f;
		size_t s_length = s.length();
		for (size_t j = 0; j < s_length; j++)
			T9_string =T9_string + T9_key(s[j]);
		if ( (it = Vocabular.find(T9_string)) == Vocabular.end())
		{
			List_Vocabular List_voc;
			List_voc.push_back(List_Element_Type(s, f));
			Vocabular.insert( make_pair(T9_string, List_voc));
		}
		else
			it->second.insert(List_Element_Type(s, f));
		T9_string = "";
	}
}

int main(int argc, char* argv[])
{
	//Открытие входных и выходных файлов
	std::string s, out_s("");

	Fill_Vocabular(Vocabular);
	
	std::cin.ignore(1);
	getline(std::cin, s,  '\n');

	while (s != "")
		out_s = out_s + Read_SMS(s, 0);
	
	//Вывод результатa в файл
	std::cout<<out_s<<"\n";

	return 0;
}