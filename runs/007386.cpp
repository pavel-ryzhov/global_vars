#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
//#include <conio.h>

using namespace std;

struct SMYWORD
{
	string str;
	int freq;
};

int CharToButton(char *ch);

int main()
{
	vector<SMYWORD>::iterator iwt;
	map< vector<int> , vector<SMYWORD> > mwDict[20];
	bool bTypingWord = true;
	char cSings[] = {'.',',','?'};
	int N;
	vector<int> viWord, lastviWord[20];
	string input;
	char ch;
	SMYWORD wTemp;
	map< vector<int>  ,  vector<SMYWORD>  >::iterator mp;
	pair< map< vector<int>  ,  vector<SMYWORD>  >::iterator, bool> mp2[20];
	vector<SMYWORD> vwDictTemp;
	bool bFileEndSpace = false;
	unsigned int k = 0;

	cin>>N;
	for (int i = 0; i<N; i++)
	{
		cin>>wTemp.str;
		cin>>wTemp.freq;
		viWord.clear();
		for (unsigned int i = 0; i<wTemp.str.length(); i++)
		{
			viWord.push_back(CharToButton(&wTemp.str[i]));
		}
		if (mwDict[wTemp.str.length()-1].empty())
		{
			vwDictTemp.clear();
			mp2[wTemp.str.length()-1] = (mwDict[wTemp.str.length()-1].insert(pair< vector<int>  , vector<SMYWORD>  > (viWord, vwDictTemp)));
			mp2[wTemp.str.length()-1].first->second.push_back(wTemp);
		}
		else
		{
			if (lastviWord[wTemp.str.length()-1] != viWord)
			{
				mp2[wTemp.str.length()-1].first = mwDict[wTemp.str.length()-1].find(viWord);
				if (mp2[wTemp.str.length()-1].first==mwDict[wTemp.str.length()-1].end())
				{
					vwDictTemp.clear();
					mp2[wTemp.str.length()-1] = (mwDict[wTemp.str.length()-1].insert(pair< vector<int>  , vector<SMYWORD>  > (viWord, vwDictTemp)));
					mp2[wTemp.str.length()-1].first->second.push_back(wTemp);
				}
				else
				{
					iwt = mp2[wTemp.str.length()-1].first->second.end();
					while ((iwt!=mp2[wTemp.str.length()-1].first->second.begin())&&((iwt-1)->freq < wTemp.freq)) iwt--;
					mp2[wTemp.str.length()-1].first->second.insert(iwt,wTemp);
					mp2[wTemp.str.length()-1].first = mp;
				}
			}
			else
			{	
				iwt = mp2[wTemp.str.length()-1].first->second.end();
				while ((iwt!=mp2[wTemp.str.length()-1].first->second.begin())&&((iwt-1)->freq < wTemp.freq)) iwt--;
				mp2[wTemp.str.length()-1].first->second.insert(iwt,wTemp);
			}
		}
		lastviWord[wTemp.str.length()-1] = viWord;
	}
	ch = getchar();
	input.clear();
	while((ch=getchar())!=10)
	{
		input += ch;
	}

	viWord.clear();
	do
	{
		switch (input[k])
		{
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			
			bTypingWord = true;
			viWord.push_back(input[k]-'0');
			k++;
			if (k==input.size())
				bFileEndSpace = true; 
			else break;
		case ' ':
		case '1':
		case '*':
			if (bTypingWord)
			{
				
				bTypingWord = false;
				mp = mwDict[viWord.size()-1].find(viWord);
				vector<SMYWORD>::iterator iWordNumber = mp->second.begin();
				while (input[k]=='*')
				{
					if (++iWordNumber== mp->second.end()) iWordNumber=mp->second.begin();
					k++;
				}
				cout<<iWordNumber->str;
				if (mp->second.size() > 1)
				{
					wTemp = *iWordNumber;
					wTemp.freq++;
					mp->second.erase(iWordNumber);
					iwt = mp->second.begin();
					while ((iwt!=mp->second.end())&&(iwt->freq > wTemp.freq)) iwt++;
					mp->second.insert(iwt,wTemp);
				}
				viWord.clear();
			}
			if ((bFileEndSpace)||(input[k] == ' '))
			{
				if (!bFileEndSpace) 
				{
					cout<<' ';
					k++;
				}
				break;
			}
			if (input[k] == '1')
			{
				int iSignNumber = 0;
				k++;
				while (input[k]=='*')
				{
					if (iSignNumber==2) iSignNumber=0;
					else iSignNumber++;
					k++;
				}
				cout<<cSings[iSignNumber];
			}
			break;
		default:
			return 1;
			break;
		}
	} while (k<input.size());
	//_getch();
	return 0;
}

int CharToButton(char *ch)
{
	if ((*ch>='a')&&(*ch<='c')) return 2;
	if ((*ch>='d')&&(*ch<='f')) return 3;
	if ((*ch>='g')&&(*ch<='i')) return 4;
	if ((*ch>='j')&&(*ch<='l')) return 5;
	if ((*ch>='m')&&(*ch<='o')) return 6;
	if ((*ch>='p')&&(*ch<='s')) return 7;
	if ((*ch>='t')&&(*ch<='v')) return 8;
	if ((*ch>='w')&&(*ch<='z')) return 9;
	return -1;
}