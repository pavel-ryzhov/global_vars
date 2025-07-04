// YandeC.cpp : main project file.
#include <iostream>
#include <vector>  
#include <algorithm>
#include <string.h>
#include <map>

using namespace std;

struct T9Keys{
	char digits[21];
	int freq;
    bool operator < (const T9Keys & b) const
	{
		bool result=false; //(a<b)
		int eq=strcmp(digits,b.digits);
		if (eq==0)
		{
			if (freq>b.freq) result=true;
		}
		if (eq<0) result=true;
		return result;
	}
};
struct T9Datas{
	char symbols[21];
};
multimap <T9Keys, T9Datas> T9s;
multimap <T9Keys, T9Datas>::iterator its;
struct T9Key{
	char digits[21];
    bool operator < (const T9Key & b) const
	{
		bool result=false;
		int eq=strcmp(digits,b.digits);
		if (eq<0) result=true;
		return result;
	}
};
struct T9Data{
	char symbols[21];
	int freq;
};
multimap <T9Key, T9Data> T9;
multimap <T9Key, T9Data>::iterator it,itlow,itnew;

char znaki[4]=".,?";

void abc123(char *symbols, char *digits)
{
    int i;
	strcpy(digits,symbols);
	for (i=0; symbols[i]!=NULL; i++)
	{
		switch(symbols[i]){
			case 'a':
			case 'b':
			case 'c':
				digits[i]='2';
				break;
			case 'd':
			case 'e':
			case 'f':
				digits[i]='3';
				break;
			case 'g':
			case 'h':
			case 'i':
				digits[i]='4';
				break;
			case 'j':
			case 'k':
			case 'l':
				digits[i]='5';
				break;
			case 'm':
			case 'n':
			case 'o':
				digits[i]='6';
				break;
			case 'q':
			case 'r':
			case 's':
				digits[i]='7';
				break;
			case 't':
			case 'u':
			case 'v':
				digits[i]='8';
				break;
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				digits[i]='9';
				break;
		}
	}
}

void writenewznak(int zvezda)
{
	cout << znaki[zvezda];
}

void writenewword(char *digits ,int zvezda)
{
	T9Key tkey;
	T9Data tdata;
	strcpy(tkey.digits,digits);
	itlow=T9.lower_bound(tkey);
	int i;
	if (zvezda==0)
	{
		cout << (*itlow).second.symbols;
		(*itlow).second.freq++;
	}
	else
	{
		for (it=itlow, i=0; i!=zvezda; it++, i++);
		cout << (*it).second.symbols;
		(*it).second.freq++;
		tdata=(*it).second;
		for (itnew=it; itnew!=itlow; itnew--)
		{
			if ((*itnew).second.freq>tdata.freq) break;
		}
		T9.erase(it);
		if (itnew==itlow)
		{
			if ((*itlow).second.freq<=tdata.freq) T9.insert(itlow,pair<T9Key,T9Data>(tkey,tdata));
			else
			{
				itnew=itlow;
				itnew++;
				T9.insert(itnew,pair<T9Key,T9Data>(tkey,tdata));
			}
		}
		else
		{
			itnew++;
			T9.insert(itnew,pair<T9Key,T9Data>(tkey,tdata));
		}
	}
}

int main()
{
   	//freopen("input.txt","rt",stdin);
    //freopen("output.txt","wt",stdout);

	int n;
	cin >> n;
	T9Keys TKeys;
	T9Datas TDatas;
	for (int i=0; i<n; i++)
    {
      cin >>TDatas.symbols;
	  cin >>TKeys.freq;
	  abc123(TDatas.symbols,TKeys.digits);
	  T9s.insert(pair<T9Keys,T9Datas>(TKeys,TDatas));
    }
	T9Key tkey;
	T9Data tdata;
	for (its=T9s.begin(), it=T9.begin(); its!=T9s.end(); its++)
	{
		strcpy(tkey.digits,(*its).first.digits);
		tdata.freq=(*its).first.freq;
		strcpy(tdata.symbols,(*its).second.symbols);
		T9.insert(T9.end(),pair<T9Key,T9Data>(tkey,tdata));
	}
	char digits[21]="";
	int zvezda=0;
	int workmode=2;
	char nextchar;
	while (cin.get(nextchar))
	{
		switch(workmode){
			case 2: // пишем слово
				switch(nextchar){
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						sprintf(digits,"%s%c",digits,nextchar);
						zvezda=0;
						break;
					case '*':
						zvezda++;
						break;
					case ' ':
						writenewword(digits,zvezda);
						zvezda=0;
						strcpy(digits,"");
						workmode=0;
						break;
					case '1':
						writenewword(digits,zvezda);
						zvezda=0;
						strcpy(digits,"");
						workmode=1;
						break;
				}
				break;
			case 1: //пишем знак .,?
				switch(nextchar){
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						writenewznak(zvezda);
						workmode=2;
						sprintf(digits,"%s%c",digits,nextchar);
						zvezda=0;
						break;
					case '*':
						zvezda++;
						break;
					case ' ':
						writenewznak(zvezda);
						zvezda=0;
						strcpy(digits,"");
						workmode=0;
						break;
					case '1':
						writenewznak(zvezda);
						zvezda=0;
						strcpy(digits,"");
						workmode=1;
						break;
				}
				break;
			case 0: //пишем пробел
				cout <<' ';
				switch(nextchar){
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						workmode=2;
						sprintf(digits,"%s%c",digits,nextchar);
						break;
					case '*':	//так не бывает
						zvezda++;
						break;
					case ' ': //всё сделано до нас
						break;
					case '1':
						workmode=1;
						break;
				}
		}
	}
	switch(workmode){
		case 2: // пишем слово
			writenewword(digits,zvezda);
			break;
		case 1: // пишем знак
			writenewznak(zvezda);
			break;
		case 0: // пишем пробел
			cout <<' ';
			break;
	}
	return 0;
}
