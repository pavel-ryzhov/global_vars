#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <list>
//#include <vector>
using namespace std;
struct Button // кнопка
{
	int dig; // цифра
	string letters; // соответствующие ей буквы (3 или 4)
};
//-------------------------------------------------------------------------------
struct Word // слово в словаре
{
	string word; // слово
	int freq; // частота встречаемости
//	bool prir; // приоритет, в случае если есть слова с такой же частотой встречаемости
	int order; // порядок утверждения слов
};
typedef list <Button> ButMass; // клавиатура мобильного телефона
typedef list <Word> Dictionary; // словарь слов
typedef list <string> StringMass; // массив строк
//-------------------------------------------------------------------------------
const char* p_EXPR1 = "Enter your inputfile name\n";
const char* p_EXPR2 = "File opening error!\n";
const char* p_EXPR3 = "To stop executing program enter: end\n";
const char* p_SYMBS[] = { ".,?", "abc", "def", "ghi", "jkl", "mno", "qrs", "tuv", "wxyz"};
const int INFILENAMESIZE = 100; // максимальное число символов в названии входного файла 
//--------------------------------------------------------------------------------
class CSms 
{
private:
	StringMass m_InStrs; // строки из входного файла
	ButMass m_keyboard; // клавиатура
	Dictionary m_dict; // словарь
	Dictionary m_CurrWords; // текущие расматриваемые слова (которые подходят 
	//под набранную комбинацию цифр) 
	Dictionary m_SameFreq; // слова с одинаковой частотой 
	// выбираются либо из массива m_CurrWords, либо из массива m_dict
	unsigned long m_WordsCol; // количество слов в словаре
	string m_LastStr; // последняя строка из входного файла
	string m_Message; // строка, содержащая итоговое сообщение
	int order; // порядок утверждения слов
public:
	CSms();
	~CSms(){}
	void FileRead(); // чтение из входного файла
	void FinaleMessForm(); // формирование сообщения
	void DictForm(); // формирование словаря слов
	void Str1Analyse(string& CurrStr); // анализ строки
	Dictionary::iterator FindWord(string& Lett, Dictionary* mass); // поиск слова в словаре
	void CurrWord(string& currStr); // обработка текущего слова
	string DigitAnalys (string c); // анализ цифры
    void FindDWords(string& str); // нахождение интересующего подмножества слов
	bool CheckPres(string& s, string& w);
	string ChooseAlpha(); // выбор слов по алфавиту
	void Sign (int & k, string str); // обработка знака
	Dictionary::iterator FindMax(); // поиск слова с макс частотой
	void FindSameFreq (int freq, Dictionary* mass); // поиск слов с одинаковой частотой
    void PriorClear(); // очистка приоритетов
    void DigitsAnalyse(); // обработка слова (комбинации цифр без * и 1)
	void Out(); // вывод на экран
	void OutFile(); // вывод в файл
	void FileReadStream(); // чтение из потока
};
//--------------------------------------------------------------------------------
int main()
{

		CSms sms;
//	    sms.FileRead();
		sms.FileReadStream();
	    sms.DictForm();
	    sms.FinaleMessForm();
	    sms.Out();
//	    sms.OutFile();
		return 0;
}
//---------------------------------------------------------------------------------
//формирование клавиатуры
CSms::CSms()
{
	Button currBut;
	for (int i = 2; i <= 9; i++)
	{
		currBut.dig = i;
	    currBut.letters = p_SYMBS[i - 1];
	    m_keyboard.push_back(currBut); 
	}
	order = 0;
}
//---------------------------------чтение из потока----------------------------------
void CSms::FileReadStream()
{
	int strcol = 0;
	char symb = ' '; // текущиц символ
	int i = 0;
	string StrFromFile; // считываемая строка
    symb = getchar();
	while (symb != '\n')
	{
		StrFromFile += symb;
		symb = getchar();
	}
	strcol = atoi(StrFromFile.c_str());
    m_InStrs.push_back(StrFromFile); // заносим в массив прочитанную из файла строку 
    StrFromFile = "";
	for (i = 0; i < strcol; i++)
	{
		symb = getchar();
		while (symb != '\n')
		{
			StrFromFile += symb;
			symb = getchar();
		}
        m_InStrs.push_back(StrFromFile); // заносим в массив прочитанную из файла строку 
        StrFromFile = "";
	}
    symb = getchar();
	while (symb != '\n')
	{
	    StrFromFile += symb;
		symb = getchar();
	}
	
    m_InStrs.push_back(StrFromFile); // заносим в массив прочитанную из файла строку 
}
//---------------------------------------------------------------------------------
/*void CSms::FileRead()
{
	char inFileName[INFILENAMESIZE]; // название входного файла
	char symb = '!'; // текущиц символ
	string StrFromFile; // считываемая из файла строка
	FILE * inFile; // указатель на входной файл
	printf(p_EXPR1);
	scanf("%s",inFileName);
	if ((string)inFileName == "end")
		exit(1);
	inFile = fopen (inFileName, "r"); // открываем входной файл
	if (inFile == NULL) 
	{
		perror (p_EXPR2);
		exit(1);
	}
	else
	{
		while (symb != EOF)
        {
            while (symb != '\n' && symb != EOF )
            {
                if (symb != '!')
				    StrFromFile += symb;
				symb = fgetc(inFile);
            }
            symb = fgetc(inFile);
			m_InStrs.push_back(StrFromFile); // заносим в массив прочитанную из файла строку 
            StrFromFile = "";
		}
		fclose(inFile);
	}
}*/
//-----------------------------------------------------------------------------------
void CSms::DictForm() // формирование словаря
{
	m_WordsCol = atoi (m_InStrs.begin()->c_str());
	int j = 0; // счетчик слов
    StringMass::iterator i;
	for (i = ++m_InStrs.begin(); i !=m_InStrs.end() && j < m_WordsCol; i++)
	{ 
		Str1Analyse(*i); // анализ текущей строки
		j++;
	}
	m_LastStr = *i; // последняя строка
}
//--------------------функция анализа строки--------------------------------------
void CSms::Str1Analyse(string& CurrStr)
{
	Word currw;
	string curr;
	int k = 0;
	while (CurrStr[k] != ' ')
	{
		curr += CurrStr[k];
		k++;
	}
	currw.word = curr;
	curr = "";
	k++;
    while (k < CurrStr.length())
	{
		curr += CurrStr[k];
		k++;
	}
	currw.freq = atoi(curr.c_str());
	currw.order = 0;
	m_dict.push_back(currw);
}
//-------------------------формирование сообщения-------------------------------
void CSms::FinaleMessForm()
{
	string curr;
	int k = 0;
	// цикл до конца
	while (k < m_LastStr.length())
	{
		if ( m_LastStr[k] == ' '  && (curr != "")  )
		{
			CurrWord(curr);
			curr = "";
			m_Message += ' ';
			if (m_LastStr[k] == ' ')
			   k++; // пропускаем пробел 
		}
		curr += m_LastStr[k];
		k++;
	}
	if (curr != "")
		CurrWord(curr);
}
//--------------------поиск слова в словаре-----------------------------------
Dictionary::iterator CSms::FindWord(string& Letters, Dictionary* mass)
{
	Dictionary::iterator i;
	for ( i =  mass->begin(); i != mass->end(); i++)
	{
		if (i->word == Letters)
			return i;
	}
	return i;
}
//---------------------обработка текущего слова-------------------------------
void CSms::CurrWord(string& currStr)
{
	string curr;
	int k = 0;
	while (k < currStr.length())
	{
		curr += currStr[k]; 
		if (currStr[k] == '1') // знак
        {
			// обрабатываем знак - передаем в функцию ссылку на k, обрабатываем слово перед знаком 
			// - помещаем слово в message и измененяем частоты и приоритеты слов в m_dict, 
			// стираем старые приоритеты, обрабатываем знак - если после него идет *, то предлагаем 
			// др знак и тд., если цифра или конец строки - возвращаемся в главный цикл
			string curr2;
			curr2 = curr.substr(0, curr.size() - 1);
			curr = "";
			curr = curr2;
			if (curr != "")
			{
				FindDWords (curr); // находим интересующее множество слов
				DigitsAnalyse();
				curr = "";
                // освобождение текущего подмножества слов
			    m_CurrWords.clear(); 
			}
			Sign (k, currStr);
		} 
		if (currStr[k] == '*')
		{
		 // ищем подходящее слово, затем исключаем его из CurrWords и опять ищем слово
         // если после * идет цифра или конец строки - помещаем слово в message и 
		 // измененяем частоты и приоритеты слов в m_dict, стираем старые приоритеты 
             string curr2;
			 curr2 = curr.substr(0, curr.size() - 1);
			 curr = "";
			 curr = curr2;
			 FindDWords (curr); // находим интересующее множество слов
             while (currStr[k] == '*' )
			 {
			     Dictionary::iterator w = FindMax(); // находим слово с макс частотой
		         // (приоритетом, по алфавиту)
				 m_CurrWords.erase(w); // исключаем его из рассматриваемых слов
			     k++;
			 }
             DigitsAnalyse(); // обработка комбинации цифр
			 curr = "";
			 // освобождение текущего подмножества слов
			 m_CurrWords.clear();
			 k--;
		}
		k++;
	}
	
	if (curr != "")
	{
		FindDWords (curr); // находим интересующее множество слов
		DigitsAnalyse();
		curr = "";
		// освобождение текущего подмножества слов
		m_CurrWords.clear();
	}
}
//------------------нахождение интересующего подмножества слов-----------------
void CSms::FindDWords(string& str) // str - набранные цифры
{
	int scount = 0; // количество совпадений
	string digit;
	// цикл по словарю
	for (Dictionary::iterator i = m_dict.begin(); i != m_dict.end(); i++)
	{
		// цикл по набранным цифрам
		for (int k = 0; k < str.length(); k++)
		{
			string s;
			s += str[k];
			digit = DigitAnalys(s);
            if ( CheckPres(digit, i->word ) == true )
				scount++;
		}
        if (scount == i->word.length())
			// помещаем слово в интересующее подмножество
			m_CurrWords.push_back(*i);
		scount = 0;
	}
}
//----------------анализ цифры (выдача соответствующих ей букв)--------------------------
string CSms::DigitAnalys (string c)
{
	string s;
	int d = atoi(c.c_str());
	for (ButMass::iterator i = m_keyboard.begin(); i != m_keyboard.end(); i++)
	{
		if (i->dig == d)
			s = i->letters;
	}
    return s;
}
//---------------функция проверки, присутствует ли одна из букв s строки в слове w -----
bool CSms::CheckPres(string& s, string& w)
{
	bool f = false;
	for (int k = 0; k < s.length(); k++ )
		if (strchr(w.c_str(), s[k]) != NULL )
			return true;
    return false;
}
//---------------поиск максимума - интересующего нас слова (с макс. частотой и приоритетом)
Dictionary::iterator CSms::FindMax()
{
	string Res;
    // ищем максимальную частоту
	int max = 0; // максимальная частота
	for (Dictionary::iterator i = m_CurrWords.begin(); i != m_CurrWords.end(); i++ )
	{
		if (i->freq > max)
			max = i->freq;
	}
	// в массиве CurrWords ищем слова с max частотой
    FindSameFreq (max, &m_CurrWords);
    // несколько слов с максимальной частотой: 
	if (m_SameFreq.size() != 1) 
	{
		max = 0;
        Dictionary::iterator m;
		for (Dictionary::iterator k = m_SameFreq.begin(); k != m_SameFreq.end(); k++ )
		{
			if (k->order > max)
			{
				max = k->order;
				m = k;
			}
		}
		// выбираем первое по алфавиту:
		if (max == 0) 
			Res = ChooseAlpha();
		else
			Res = m->word; // выбираем более востребованное
	}
	// если слово с max частотой одно
	else
	{	
		Res = m_SameFreq.begin()->word;
	}
	// ищем данное слово в массиве m_CurrWords
	Dictionary::iterator w = FindWord (Res, &m_CurrWords);
	return w;
}
//-----------------------обработка знака---------------------------------------
void CSms:: Sign (int & k, string str)
{
	int i = 0;
	k++;
	while (str[k] == '*')
	{
		i++;
		k++;
	}
	m_Message += p_SYMBS[0][i];
}
//-----------------------поиск слов с одинаковой частотой----------------------
void CSms:: FindSameFreq (int freq, Dictionary* mass)
{
	// очищаем старый массив
	m_SameFreq.clear();
    for (Dictionary::iterator i = mass->begin(); i != mass->end(); i++)
		if (i->freq == freq)
			m_SameFreq.push_back(*i);
}

//-----------------------выбор слова по алфавиту среди  нескольких-------------
string CSms::ChooseAlpha()
{
	StringMass Mass;
	string res;
	for (Dictionary::iterator i = m_SameFreq.begin(); i != m_SameFreq.end(); i++)
		Mass.push_back(i->word);
	Mass.sort();
	return *(Mass.begin());
}

//---------------------обработка слова (комбинации цифр)----------------------
void CSms:: DigitsAnalyse()
{
	Dictionary::iterator w = FindMax(); // находим слово с макс частотой
    // (приоритетом, по алфавиту)
	// добавляем слово в итоговое сообщение
    m_Message += w->word;
	// изменяем его частоту и приоритет
	Dictionary::iterator d = FindWord(w->word, &m_dict);
	d->freq ++;
	// находим слова с такой же частотой
//	FindSameFreq(d->freq, &m_dict);
	// очищаем приоритеты
//	PriorClear();
	order++;
	d->order = order;
}
//------------------------------вывод результата на экран------------------------
void CSms::Out()
{
	printf("%s\n", m_Message.c_str());

}
//-----------------------------вывод результата в файл-----------------------------
void CSms::OutFile()
{
	FILE* out;
	out = fopen("out", "w");
	fprintf(out, "%s\n", m_Message.c_str());
}
