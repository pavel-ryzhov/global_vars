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

//Тип элементов списка
typedef struct List_Element
{
	std::string m_string;
	int m_frequency;
	List_Element(std::string s, int f) {m_string = s; m_frequency = f;};
} List_Element_Type;		
typedef std::list<List_Element_Type>::iterator list_iterator;

//Массив знаков пунктуации
const char punct_marks[3] = {'.' , ',', '?'};

//Список слов, имеющий одинаковый цифровой T9_код
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

vocabular_type Vocabular;												//Словарь

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
		while (s > it->m_string)
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
//Возвращение слова из словаря
std::string List_Vocabular::return_word(int iPosition)
{
	std::string return_string = "";
	list_iterator it, it_cur = mList.begin();
	for (int i = 0; i < iPosition; i++)
		it_cur++;	

	int new_freq = it_cur->m_frequency += 1;
	
	return_string = it_cur->m_string;

	if (it_cur == mList.begin() )
		return return_string;
	else
	{
		it = it_cur;
		while ( (it_cur->m_frequency >= it->m_frequency) && (it != mList.begin()) )
			it--;
		mList.erase(it_cur);
		mList.insert(it, List_Element(return_string, new_freq));
	}
	
	return return_string;
}

//Получение знака препинания
char Punctuation_Mark(std::string temp, size_t pos_1)
{
	return punct_marks[temp.size() - (pos_1 + 1)];
}
//Поиск слова в словаре
std::string Word_Search(std::string current_word, int type, char punct)
{
	std::string ret_s = Vocabular.find(current_word)->second.return_word(type);
	if (punct != 0)
		ret_s = ret_s + punct;

	return ret_s;
}
//Функция чтения смс
std::string Read_SMS(std::string &SMS, size_t pos)
{
	std::string current_word;
	int type;
	char punct = 0;
	std::string temp = "";

	size_t space = SMS.find (' ', pos);
	if (space == std::string::npos)
	{
		temp = SMS;
		SMS = "";
	}
	else
	{
		temp = SMS.substr (pos, space - pos);
		SMS = SMS.substr(space + 1, SMS.size());
	}

	size_t end_word = temp.find_first_of ("1*", 0); 

	if (end_word != std::string::npos)
	{
		current_word = temp.substr (0, end_word);
		temp = temp.substr(end_word, temp.size() - current_word.size() );
		size_t pos_1 = temp.find ('1', 0);
		if (pos_1 != std::string::npos)
		{
			type = (int) pos_1;
			punct = Punctuation_Mark(temp, pos_1);
		}
		else
			type = (int) temp.size();
	}
	else
	{
		current_word = temp;
		type = 0;
	}
	
	
	return Word_Search(current_word, type, punct);;
	

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
void Fill_Vocabular(std::istream &input, vocabular_type &Vocabular)
{
	int N, f = 0;
	vocabular_iterator it;
	std::string s, T9_string("");

	input>>N;	
	
	for (int i = 0; i < N; i++)
	{
		input>>s>>f;
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
	std::string s, out_s("");

	Fill_Vocabular(std::cin, Vocabular);
	
	std::cin.ignore(1);
	getline(std::cin, s,  '\n');

	while (s != "")
		out_s = out_s + Read_SMS(s, 0) + ' ';
	
	out_s = out_s.substr(0, out_s.size() - 1);

	//Вывод результатa
	std::cout<<out_s<<std::endl;

	return 0;
}