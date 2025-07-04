#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;


unsigned long int str_to_num(string &str)
{
	unsigned long int res = 0;
	for (size_t i = 0; i!=str.size(); i++)
	{
		res*=10;
		switch (str[i])
		{
			case 'a':
			case 'b':
			case 'c':
				res+=2;
				break;
			case 'd':
			case 'e':
			case 'f':
				res+=3;
				break;
			case 'g':
			case 'h':
			case 'i':
				res+=4;
				break;
			case 'j':
			case 'k':
			case 'l':
				res+=5;
				break;
			case 'm':
			case 'n':
			case 'o':
				res+=6;
				break;
			case 'p':
			case 'q':
			case 'r':
			case 's':
				res+=7;
				break;
			case 't':
			case 'u':
			case 'v':
				res+=8;
				break;
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				res+=9;
				break;
		}
	}
	return res;
}

struct wrd
{
	string str;
	int freq;
	wrd(string s, int f){ str = s; freq = f;}
	wrd(){ str = ""; freq = 0;}
};

void out1 (string &str, int &num)
{
	switch(--num%3)
	{
		case 0:
			str+='.';
			break;
		case 1:
			str+=',';
			break;
		case 2:
			str+='?';
			break;
	}
	num=0;
}

void outword (string &str, list<wrd>::iterator &it, map<unsigned long int, list<wrd> > &dict, unsigned long int &num)
{
	str+=it->str;
	it->freq++;
	list<wrd>::iterator ti=it;
	while((ti!=dict[num].begin()) & (ti->freq<=it->freq))
		{--ti;}
	if (ti!=dict[num].begin()){++ti;}
	dict[num].splice(ti, dict[num], it);
	num=0;
	it=dict[0].begin();
}

void outword (string &str, map<unsigned long int, list<wrd> > &dict, unsigned long int &num)
{
	list<wrd>::iterator it=dict[num].begin();
	str+=it->str;
	it->freq++;
	num=0;
}

int main()
{
	int N = 0;
	int F = 0;
	string row;
	cin>>N;
	map<unsigned long int, list<wrd> > dict;
	for(int i = 0; i!=N; i++)
	{
		cin>>row>>F;
		int code = str_to_num(row);
		list<wrd>::iterator it=dict[code].begin();
		for (it; it!=dict[code].end(); ++it)
		{
			if (it->freq <= F)
			{
				if (it->freq == F)
				{
					if (row<=it->str)
					{break;}
				}
				else
				{break;}
			}
		}
		dict[code].insert(it, wrd(row, F));
	}
	dict[0].insert(dict[0].begin(), wrd("", 0));
	string outstr="";
	int state=0;
	unsigned long int wordcode=0;
	int num_of_1=0;
	list<wrd>::iterator priorword=dict[0].begin();
	cin.get();
	char c=cin.get();
	while(true)
	{
        //0 - чтение цифр
        //1 - подгонка слова
        //2 - чтение единицы
        //3 - пробел
        //4 - подгонка единицы

		switch (c)
		{
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (state==1)
				{
					outword(outstr, priorword, dict, wordcode);
				}
				if ((state==2) | (state==4))
				{
					out1(outstr, num_of_1);
				}

				state=0;
				wordcode*=10;
				wordcode+=atoi(&c);
				break;

			case '*':
				if (state==0)
				{
                    state=1;
                    if (priorword->freq==0)
                        {priorword=dict[wordcode].begin();}
                    if (dict[wordcode].end()==++priorword)
                        {priorword=dict[wordcode].begin();}
                }
                if ((state==2) | (state==4))
                {
                    num_of_1++;
                    state=4;
                }
				break;


			case '1':
				switch (state)
				{
				    case 0:
                        outword(outstr, dict, wordcode);
                        break;
                    case 1:
                        outword(outstr, priorword, dict, wordcode);
                        break;
                    case 2:
                        outstr+='.';
                        break;
                    case 4:
                        out1(outstr, num_of_1);
                        break;
				}
				state=2;
				num_of_1=1;
				break;

			case ' ':
				switch (state)
				{
				    case 0:
                        outword(outstr, dict, wordcode);
                        break;
                    case 1:
                        outword(outstr, priorword, dict, wordcode);
                        break;
                    case 2:
                        outstr+='.';
                        num_of_1=0;
                        break;
                    case 4:
                        out1(outstr, num_of_1);
                        break;
				}
				state=3;
				outstr+=' ';
				//state=0;
				break;

            case 10:
                switch (state)
				{
                    case 0:
                        outword(outstr, dict, wordcode);
                        break;
                    case 1:
                        outword(outstr, priorword, dict, wordcode);
                        break;
                    case 2:
                        outstr+='.';
                        break;
                    case 4:
                        out1(outstr, num_of_1);
                        break;
				}
                break;
		}
        if (c==10) {break;}
		c=cin.get();

	}
	cout<<outstr;
	return 0;
}
