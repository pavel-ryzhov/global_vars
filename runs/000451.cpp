#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <list>
//#include <vector>
using namespace std;
struct Button // ������
{
	int dig; // �����
	string letters; // ��������������� �� ����� (3 ��� 4)
};
//-------------------------------------------------------------------------------
struct Word // ����� � �������
{
	string word; // �����
	int freq; // ������� �������������
//	bool prir; // ���������, � ������ ���� ���� ����� � ����� �� �������� �������������
	int order; // ������� ����������� ����
};
typedef list <Button> ButMass; // ���������� ���������� ��������
typedef list <Word> Dictionary; // ������� ����
typedef list <string> StringMass; // ������ �����
//-------------------------------------------------------------------------------
const char* p_EXPR1 = "Enter your inputfile name\n";
const char* p_EXPR2 = "File opening error!\n";
const char* p_EXPR3 = "To stop executing program enter: end\n";
const char* p_SYMBS[] = { ".,?", "abc", "def", "ghi", "jkl", "mno", "qrs", "tuv", "wxyz"};
const int INFILENAMESIZE = 100; // ������������ ����� �������� � �������� �������� ����� 
//--------------------------------------------------------------------------------
class CSms 
{
private:
	StringMass m_InStrs; // ������ �� �������� �����
	ButMass m_keyboard; // ����������
	Dictionary m_dict; // �������
	Dictionary m_CurrWords; // ������� �������������� ����� (������� �������� 
	//��� ��������� ���������� ����) 
	Dictionary m_SameFreq; // ����� � ���������� �������� 
	// ���������� ���� �� ������� m_CurrWords, ���� �� ������� m_dict
	unsigned long m_WordsCol; // ���������� ���� � �������
	string m_LastStr; // ��������� ������ �� �������� �����
	string m_Message; // ������, ���������� �������� ���������
	int order; // ������� ����������� ����
public:
	CSms();
	~CSms(){}
	void FileRead(); // ������ �� �������� �����
	void FinaleMessForm(); // ������������ ���������
	void DictForm(); // ������������ ������� ����
	void Str1Analyse(string& CurrStr); // ������ ������
	Dictionary::iterator FindWord(string& Lett, Dictionary* mass); // ����� ����� � �������
	void CurrWord(string& currStr); // ��������� �������� �����
	string DigitAnalys (string c); // ������ �����
    void FindDWords(string& str); // ���������� ������������� ������������ ����
	bool CheckPres(string& s, string& w);
	string ChooseAlpha(); // ����� ���� �� ��������
	void Sign (int & k, string str); // ��������� �����
	Dictionary::iterator FindMax(); // ����� ����� � ���� ��������
	void FindSameFreq (int freq, Dictionary* mass); // ����� ���� � ���������� ��������
    void PriorClear(); // ������� �����������
    void DigitsAnalyse(); // ��������� ����� (���������� ���� ��� * � 1)
	void Out(); // ����� �� �����
	void OutFile(); // ����� � ����
	void FileReadStream(); // ������ �� ������
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
//������������ ����������
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
//---------------------------------������ �� ������----------------------------------
void CSms::FileReadStream()
{
	int strcol = 0;
	char symb = ' '; // ������� ������
	int i = 0;
	string StrFromFile; // ����������� ������
    symb = getchar();
	while (symb != '\n')
	{
		StrFromFile += symb;
		symb = getchar();
	}
	strcol = atoi(StrFromFile.c_str());
    m_InStrs.push_back(StrFromFile); // ������� � ������ ����������� �� ����� ������ 
    StrFromFile = "";
	for (i = 0; i < strcol; i++)
	{
		symb = getchar();
		while (symb != '\n')
		{
			StrFromFile += symb;
			symb = getchar();
		}
        m_InStrs.push_back(StrFromFile); // ������� � ������ ����������� �� ����� ������ 
        StrFromFile = "";
	}
    symb = getchar();
	while (symb != '\n')
	{
	    StrFromFile += symb;
		symb = getchar();
	}
	
    m_InStrs.push_back(StrFromFile); // ������� � ������ ����������� �� ����� ������ 
}
//---------------------------------------------------------------------------------
/*void CSms::FileRead()
{
	char inFileName[INFILENAMESIZE]; // �������� �������� �����
	char symb = '!'; // ������� ������
	string StrFromFile; // ����������� �� ����� ������
	FILE * inFile; // ��������� �� ������� ����
	printf(p_EXPR1);
	scanf("%s",inFileName);
	if ((string)inFileName == "end")
		exit(1);
	inFile = fopen (inFileName, "r"); // ��������� ������� ����
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
			m_InStrs.push_back(StrFromFile); // ������� � ������ ����������� �� ����� ������ 
            StrFromFile = "";
		}
		fclose(inFile);
	}
}*/
//-----------------------------------------------------------------------------------
void CSms::DictForm() // ������������ �������
{
	m_WordsCol = atoi (m_InStrs.begin()->c_str());
	int j = 0; // ������� ����
    StringMass::iterator i;
	for (i = ++m_InStrs.begin(); i !=m_InStrs.end() && j < m_WordsCol; i++)
	{ 
		Str1Analyse(*i); // ������ ������� ������
		j++;
	}
	m_LastStr = *i; // ��������� ������
}
//--------------------������� ������� ������--------------------------------------
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
//-------------------------������������ ���������-------------------------------
void CSms::FinaleMessForm()
{
	string curr;
	int k = 0;
	// ���� �� �����
	while (k < m_LastStr.length())
	{
		if ( m_LastStr[k] == ' '  && (curr != "")  )
		{
			CurrWord(curr);
			curr = "";
			m_Message += ' ';
			if (m_LastStr[k] == ' ')
			   k++; // ���������� ������ 
		}
		curr += m_LastStr[k];
		k++;
	}
	if (curr != "")
		CurrWord(curr);
}
//--------------------����� ����� � �������-----------------------------------
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
//---------------------��������� �������� �����-------------------------------
void CSms::CurrWord(string& currStr)
{
	string curr;
	int k = 0;
	while (k < currStr.length())
	{
		curr += currStr[k]; 
		if (currStr[k] == '1') // ����
        {
			// ������������ ���� - �������� � ������� ������ �� k, ������������ ����� ����� ������ 
			// - �������� ����� � message � ���������� ������� � ���������� ���� � m_dict, 
			// ������� ������ ����������, ������������ ���� - ���� ����� ���� ���� *, �� ���������� 
			// �� ���� � ��., ���� ����� ��� ����� ������ - ������������ � ������� ����
			string curr2;
			curr2 = curr.substr(0, curr.size() - 1);
			curr = "";
			curr = curr2;
			if (curr != "")
			{
				FindDWords (curr); // ������� ������������ ��������� ����
				DigitsAnalyse();
				curr = "";
                // ������������ �������� ������������ ����
			    m_CurrWords.clear(); 
			}
			Sign (k, currStr);
		} 
		if (currStr[k] == '*')
		{
		 // ���� ���������� �����, ����� ��������� ��� �� CurrWords � ����� ���� �����
         // ���� ����� * ���� ����� ��� ����� ������ - �������� ����� � message � 
		 // ���������� ������� � ���������� ���� � m_dict, ������� ������ ���������� 
             string curr2;
			 curr2 = curr.substr(0, curr.size() - 1);
			 curr = "";
			 curr = curr2;
			 FindDWords (curr); // ������� ������������ ��������� ����
             while (currStr[k] == '*' )
			 {
			     Dictionary::iterator w = FindMax(); // ������� ����� � ���� ��������
		         // (�����������, �� ��������)
				 m_CurrWords.erase(w); // ��������� ��� �� ��������������� ����
			     k++;
			 }
             DigitsAnalyse(); // ��������� ���������� ����
			 curr = "";
			 // ������������ �������� ������������ ����
			 m_CurrWords.clear();
			 k--;
		}
		k++;
	}
	
	if (curr != "")
	{
		FindDWords (curr); // ������� ������������ ��������� ����
		DigitsAnalyse();
		curr = "";
		// ������������ �������� ������������ ����
		m_CurrWords.clear();
	}
}
//------------------���������� ������������� ������������ ����-----------------
void CSms::FindDWords(string& str) // str - ��������� �����
{
	int scount = 0; // ���������� ����������
	string digit;
	// ���� �� �������
	for (Dictionary::iterator i = m_dict.begin(); i != m_dict.end(); i++)
	{
		// ���� �� ��������� ������
		for (int k = 0; k < str.length(); k++)
		{
			string s;
			s += str[k];
			digit = DigitAnalys(s);
            if ( CheckPres(digit, i->word ) == true )
				scount++;
		}
        if (scount == i->word.length())
			// �������� ����� � ������������ ������������
			m_CurrWords.push_back(*i);
		scount = 0;
	}
}
//----------------������ ����� (������ ��������������� �� ����)--------------------------
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
//---------------������� ��������, ������������ �� ���� �� ���� s ������ � ����� w -----
bool CSms::CheckPres(string& s, string& w)
{
	bool f = false;
	for (int k = 0; k < s.length(); k++ )
		if (strchr(w.c_str(), s[k]) != NULL )
			return true;
    return false;
}
//---------------����� ��������� - ������������� ��� ����� (� ����. �������� � �����������)
Dictionary::iterator CSms::FindMax()
{
	string Res;
    // ���� ������������ �������
	int max = 0; // ������������ �������
	for (Dictionary::iterator i = m_CurrWords.begin(); i != m_CurrWords.end(); i++ )
	{
		if (i->freq > max)
			max = i->freq;
	}
	// � ������� CurrWords ���� ����� � max ��������
    FindSameFreq (max, &m_CurrWords);
    // ��������� ���� � ������������ ��������: 
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
		// �������� ������ �� ��������:
		if (max == 0) 
			Res = ChooseAlpha();
		else
			Res = m->word; // �������� ����� ��������������
	}
	// ���� ����� � max �������� ����
	else
	{	
		Res = m_SameFreq.begin()->word;
	}
	// ���� ������ ����� � ������� m_CurrWords
	Dictionary::iterator w = FindWord (Res, &m_CurrWords);
	return w;
}
//-----------------------��������� �����---------------------------------------
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
//-----------------------����� ���� � ���������� ��������----------------------
void CSms:: FindSameFreq (int freq, Dictionary* mass)
{
	// ������� ������ ������
	m_SameFreq.clear();
    for (Dictionary::iterator i = mass->begin(); i != mass->end(); i++)
		if (i->freq == freq)
			m_SameFreq.push_back(*i);
}

//-----------------------����� ����� �� �������� �����  ����������-------------
string CSms::ChooseAlpha()
{
	StringMass Mass;
	string res;
	for (Dictionary::iterator i = m_SameFreq.begin(); i != m_SameFreq.end(); i++)
		Mass.push_back(i->word);
	Mass.sort();
	return *(Mass.begin());
}

//---------------------��������� ����� (���������� ����)----------------------
void CSms:: DigitsAnalyse()
{
	Dictionary::iterator w = FindMax(); // ������� ����� � ���� ��������
    // (�����������, �� ��������)
	// ��������� ����� � �������� ���������
    m_Message += w->word;
	// �������� ��� ������� � ���������
	Dictionary::iterator d = FindWord(w->word, &m_dict);
	d->freq ++;
	// ������� ����� � ����� �� ��������
//	FindSameFreq(d->freq, &m_dict);
	// ������� ����������
//	PriorClear();
	order++;
	d->order = order;
}
//------------------------------����� ���������� �� �����------------------------
void CSms::Out()
{
	printf("%s\n", m_Message.c_str());

}
//-----------------------------����� ���������� � ����-----------------------------
void CSms::OutFile()
{
	FILE* out;
	out = fopen("out", "w");
	fprintf(out, "%s\n", m_Message.c_str());
}
