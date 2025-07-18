#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const int N=8;

const int buttons[]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
const char default_char[]={'a','d','g','j','m','p','t','w'};
const char def_prep[]={'.',',','?'};

class Dictionary
{
	map<int, vector<string> > dict;
	int nWords;
	Dictionary *p[N];
	void m_push(const string& word, int nFreq, int nDeep);
	void push_word(const string& word, int nFreq);
	int get_n_button(char c);
	string m_get(const string &comb, int nStars, int nDeep);
	string defaul_string(const string &comb);
	string m_get_word(const string &comb, int nStars);
public:
	Dictionary();
	~Dictionary();
	void push(const string &word, int nFreq);
	string get(const string &comb, int nStars);
};

Dictionary::~Dictionary()
{
	for(int i = 0; i< N; ++i)
	{
		if (p[i])
		{
			delete p[i];
			p[i] = NULL;
		}
	}
}

Dictionary::Dictionary()
{
	for(int i=0; i < N; ++i)
	{
		p[i] = NULL;
	}
	nWords=0;
}

void Dictionary::push(const string& word, int nFreq)
{
	m_push(word, nFreq, 1);
}

int Dictionary::get_n_button(char c)
{
	return buttons[c-'a'];
}

void Dictionary::m_push(const string& word, int nFreq, int nDeep)
{
	if (nDeep == (int)word.size())
	{
		push_word(word, nFreq);
		return;
	}

	int nButton=get_n_button(word[nDeep-1]); //2-9

	if (NULL == p[nButton-2])  
	{
		p[nButton-2]=new Dictionary();
	}
	p[nButton-2]->m_push(word, nFreq, nDeep+1);
	return;
}

void Dictionary::push_word(const string& word, int nFreq)
{
	dict[nFreq].push_back(word);//��� ��� ����� ���� �� �������
	
	++nWords;
}

string Dictionary::get(const string &comb, int nStars)
{
	return m_get(comb, nStars, 1);
}

string Dictionary::defaul_string(const string &comb)
{
	string res;
	for(int i = 0 ; i<(int)comb.size() ; ++i)
		res+=default_char[comb[i]-'2'];
	return res;
}

string Dictionary::m_get(const string &comb, int nStars, int nDeep)
{
	if (nDeep == (int)comb.size())
	{
		return m_get_word(comb,nStars);
	}
	int nPos=comb[nDeep-1]-'2';

	if (NULL == p[nPos])
	{
		//�� ������ ���� ��������
		return defaul_string(comb);
	}
	else
	{
		return p[nPos]->m_get(comb, nStars, nDeep+1);
	}
}

string Dictionary::m_get_word(const string &comb, int nStars)
{
	string sRes;
	int nFreq;

	if (0 == nWords)
		return defaul_string(comb);
	nStars%=nWords;	
	map<int, vector<string> >::reverse_iterator p = dict.rbegin();

	for(;(int)p->second.size() <= nStars; ++p)
	{
		nStars-=(int)p->second.size();
	}
	sRes=p->second[nStars];
	nFreq=p->first;
	
	//�����������

	p->second.erase(p->second.begin()+nStars);
	dict[nFreq+1].insert(dict[nFreq+1].begin()+0,sRes);
	
	return sRes;
}

void  Proc_New_Word(string &word,int &nStars,bool bPunct, Dictionary *Dict)
{
	if (bPunct)
	{
		cout<<def_prep[nStars%3];
	}
	else if (!word.empty())
	{
      cout<<Dict->get(word,nStars);		
	}
	word="";
	nStars=0;
	
}

int main()
{
	Dictionary *Dict=new Dictionary();

	int nWords;
	cin>>nWords;

	for(int i=0; i< nWords; ++i)
	{
		string sWord;
		int nFreq;
		cin>>sWord>>nFreq;
		Dict->push(sWord, nFreq);
	}

	char c;
	bool bStars=false, bPunct=false;
	int nStars=0;
	string word;


	while(cin>>c)
	{
		if (c!=' ' &&  c!='1')
		{
			if (c == '*')
			{
				bStars=true;
				++nStars;
			}
			else//'2'..'9'
			{
				if (bStars || bPunct)
				{
					Proc_New_Word(word,nStars,bPunct,Dict);
				}
				bStars=false;
				bPunct=false;
				word+=c;
			}
		}
		else if (c == '1')
		{
			Proc_New_Word(word,nStars,bPunct,Dict);
			bPunct=true;
			bStars=false;
		}
		else //' '
		{
			Proc_New_Word(word,nStars,bPunct,Dict);
			cout<<' ';
			bPunct=false;
			bStars=false;
		}

	}
	Proc_New_Word(word,nStars,bPunct,Dict);

	delete Dict;

	return 0;
}