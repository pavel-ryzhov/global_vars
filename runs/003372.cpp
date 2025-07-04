// ya.problem3.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <string>

#define COUNT 8
#define N_MIN 3
#define N_MAX 50000
#define F_MAX 1000
#define MAX_LEN 20
#define MAX_LEN_SMS 100000

using namespace std;

int DefineLetter(char ch);

struct word_struct
{
	string word;
	int freq;
};

struct result_word_struct
{
	string word;
	int freq;
	size_t number;
};

typedef struct word_struct word_type;
typedef struct result_word_struct result_word_type;

vector<string> Punctuation;

//часть словаря, включающая буквы, соответствующие нажатой цифре 
class PartDictionary
{
private:
	vector<word_type> VectorWord; //слова начинающиеся с буквы, соответствующей нажатой кнопке с цифрой
	vector<vector<size_t> > Key; //ключи
public:
	void Init_Key ();   //инициализация ключей
	void Add_Word (word_type);   //добавление слова
	void Add_Key (size_t, size_t);   //добавление ключа	
	size_t Number_Current_Word();   //номер текущего слова
	vector<result_word_type>  Find_Variant (string);   //поиск вариантов введенного слова
	void Change_Dictionary (result_word_type);   //внесение изменений в словарь
};

vector<PartDictionary> Dictionary;

int N;
string SMS, RESULT_SMS;

//описание функций класса:

void PartDictionary::Init_Key ()
{
	Key.resize(MAX_LEN);
}

void PartDictionary::Add_Word (word_type word)
{
	VectorWord.push_back (word);
}


size_t PartDictionary::Number_Current_Word ()
{
	return VectorWord.size() - 1;
}

void PartDictionary::Add_Key(size_t length, size_t number)
{
	Key[length].push_back (number);
}

vector<result_word_type> PartDictionary::Find_Variant (string word)
{
	vector<result_word_type> variants;
	result_word_type res;
	if (word.size() == 1)
	{
		for (size_t i = 0; i < Key[0].size(); i++)
		{
			res.freq = VectorWord[Key[0][i]].freq;
			res.word = VectorWord[Key[0][i]].word;
			res.number = Key[0][i];
			variants.push_back (res);
		}
		return variants;
	}
	else
	{
		vector<size_t> temp (Key[word.size()-1]);
		vector<size_t>::iterator it;

		for (size_t i = 1; i < word.size(); i++)
			for (int j = 0; j < (int)temp.size(); j++)
			{
				it = temp.begin();
				string s = VectorWord[temp[j]].word;
				if ( (DefineLetter(s[i]) + 50) != word[i] )
				{
					temp.erase(it + j);
					j--;
				}
			}
		for (size_t i = 0; i < temp.size(); i++)
		{
			res.freq = VectorWord[temp[i]].freq;
			res.word = VectorWord[temp[i]].word;
			res.number = temp[i];
			variants.push_back (res);
		}
		return variants;
	}
}

void PartDictionary::Change_Dictionary (result_word_type word)
{
	VectorWord[word.number].freq = VectorWord[word.number].freq + 1;
	
	size_t index,
		   num = word.word.size() - 1;
	for (size_t i = 0; i < Key[num].size(); i++)
	{
		if (Key[num][i] == word.number)
			index = i;
	}

	vector<size_t>::iterator it = Key[num].begin();
	if (index != 0)
	{
		Key[num].erase(it + index);
		if (Key[num].size() != 0)
			Key[num].insert(it, word.number);
		else
			Key[num].push_back (word.number);
	}
}

//поиск слова с заданой частотой встречаемости
result_word_type Equal_Freq(vector<result_word_type> w, int M, size_t &pos, bool &flag)
{
	result_word_type res = w[pos];

	for (size_t i = pos + 1; i < w.size(); i++)
		if ((w[i].freq == M) && (!flag))
		{
			pos = i;
			flag = true;
			res = w[i];
		}
	return res;
}

//поиск наиболее часто используемого слова
result_word_type Max_Freq(vector<result_word_type> w, int M, size_t &pos)
{
	int max = 0;
	result_word_type res;

	for (size_t i = 0; i < w.size(); i++)
		if ((w[i].freq > max) && (w[i].freq < M))
		{
			max = w[i].freq;
			res = w[i];
			pos = i;
		}
	return res;
}

//определение итогового слова
result_word_type Result_Word(vector<result_word_type> var, size_t type)
{
	int M = F_MAX;
	size_t pos;
	bool flag;

	result_word_type result = Max_Freq(var, M, pos);
	M = result.freq; 
	
	for (size_t i = 1; i <= type; i++)
	{
		flag = false;
		size_t p = pos;
		result_word_type temp_res = Equal_Freq(var, M, p, flag);
		if (flag)
		{
			result = temp_res;
			pos = p;
		}
		else
		{
			result = Max_Freq(var, M, pos);
			M = result.freq; 
		}
	}
	return result;
}


//поиск нужного слова
void Find_Word(string word, size_t type, string punct)
{
	vector<result_word_type> variants; 
	result_word_type res_word;

	//возможные варианты слова
	int number = word[0] - 50;
	variants = Dictionary[number].Find_Variant (word);
	
	//полученное слово
	res_word = Result_Word(variants, type);
	RESULT_SMS = RESULT_SMS + res_word.word + punct + " ";

	//внесение изменений в словарь
	Dictionary[number].Change_Dictionary (res_word);
}

//определение знака препинания
string Punctuation_Mark(string s, size_t pos)
{
	size_t number = s.size() - pos - 1;
	number = number % 3;
	return Punctuation[number];
}

//выделение слова и количества нажатий *
void Out_Word(string s, size_t pos, size_t &type, string &punct)
{
		s = s.substr(pos, s.size() - pos); 
		size_t pos_one = s.find ('1', 0);

		if (pos_one != string::npos)
		{
			type = pos_one;
			punct = Punctuation_Mark(s, pos_one);
		}
		else
			type = s.size();
}

//определение слов сообщения
void Read_SMS(string temp)
{
	string current_word;
	size_t type;
	string punct = "";

	size_t end_word = temp.find_first_of ("1*", 0); 

	if (end_word != string::npos)
	{
		current_word = temp.substr (0, end_word);
		Out_Word(temp, end_word, type, punct);		
	}
	else
	{
		current_word = temp;
		type = 0;
	}
	Find_Word(current_word, type, punct);
}

//написание сообщения
void SMS_T9()
{
	size_t space = SMS.find (' ', 0);
	string temp;
	if (space != string::npos)
	{
		temp = SMS.substr (0, space);
		SMS = SMS.substr (space + 1, SMS.size() - 1);
	}
	else
	{
		temp = SMS;
		SMS = "";
	}
	if (temp.size() != 0)
		Read_SMS(temp);
}

//определение введенной цифры
int DefineLetter(char ch)
{
	if ( (ch >= 'a') && (ch <= 'c')) return 0;
	else
		if ( (ch >= 'd') && (ch <= 'f')) return 1;
		else
			if ( (ch >= 'g') && (ch <= 'i')) return 2;
			else
				if ( (ch >= 'j') && (ch <= 'l')) return 3;
				else
					if ( (ch >= 'm') && (ch <= 'o')) return 4;
					else
						if ( (ch >= 'p') && (ch <= 's')) return 5;
						else
							if ( (ch >= 't') && (ch <= 'v')) return 6;
							else
								if ( (ch >= 'w') && (ch <= 'z')) return 7;
								else
									if ( (ch == '.') || (ch == ',') || (ch == '?')) 
										return 8;
									else
										return -1;
}

//распределение слов
void Set_Word(string str, int f)
{
	word_type w;
	w.word = str;
	w.freq = f;

	int index = DefineLetter(str[0]);
	if (index != 8)
	{
		Dictionary[index].Add_Word (w);
		size_t number = Dictionary[index].Number_Current_Word ();
		Dictionary[index].Add_Key (str.size()-1, number);
	}
}

//инициализация вектора знаков препинания
void Init_Punctuation()
{
	Punctuation.resize(3);
	Punctuation[0] = ".";
	Punctuation[1] = ",";
	Punctuation[2] = "?";
}

//инициализация словаря
void Init_Dictionary()
{
	for (size_t i = 0; i < COUNT; i++)
		Dictionary[i].Init_Key ();
}

//чтение данных
void Read_Data()
{	
	string s;
	int F;
	
	Dictionary.resize (COUNT);
	Init_Dictionary();
	Init_Punctuation();
	
	cin>>N;
	for (int i = 0; i < N; i++)
	{
		cin>>s>>F;
		Set_Word(s, F);
	}

	SMS = "";
	RESULT_SMS = "";
	
	cin.ignore(1);
	getline(cin, SMS,  '\n');

}

//вывод данных
void Out_Data()
{
	RESULT_SMS = RESULT_SMS.substr(0, RESULT_SMS.size()-1);

	cout<<RESULT_SMS<<"\n";
}

int main(int argc, char* argv[])
{
	Read_Data();
	
	while (SMS.size() != 0)
		SMS_T9();

	Out_Data();

	return 0;
}
