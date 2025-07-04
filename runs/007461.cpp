//1.412
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
//#include <conio.h>

using namespace std;

struct SMYWORD
{
	//SMYWORD(){};
	string str;
	int freq;
};

int CharToButton(char *ch);

int main()
{
	vector<SMYWORD*>::iterator iwt;
	map< vector<int> , vector<SMYWORD*> > mwDict[20];
	bool bTypingWord = true;
	char cSings[] = {'.',',','?'};
	int N;
	vector<int> viWord, lastviWord[20];
	string input;
	char ch;
	SMYWORD *w;
	map< vector<int>  ,  vector<SMYWORD*>  >::iterator mp;
	pair< map< vector<int>  ,  vector<SMYWORD*>  >::iterator, bool> mp2[20];
	vector<SMYWORD*> vwDictTemp;
	bool bFileEndSpace = false;
	unsigned int k = 0;

	cin>>N;
	for (int i = 0; i<N; i++)
	{
		w = new SMYWORD;
		cin>>w->str;
		unsigned int len = w->str.length();
		cin>>w->freq;
		viWord.clear();
		for (unsigned int i = 0; i< len; i++)
		{
			viWord.push_back(CharToButton(&(w->str[i])));
		}
		if (mwDict[len-1].empty())
		{
			vwDictTemp.clear();
			mp2[len-1] = (mwDict[len-1].insert(pair< vector<int>  , vector<SMYWORD*>  > (viWord, vwDictTemp)));
			mp2[len-1].first->second.push_back(w);
		}
		else
		{
			if (lastviWord[len-1] != viWord)
			{
				mp = mwDict[len-1].find(viWord);
				if (mp==mwDict[len-1].end())
				{
					vwDictTemp.clear();
					mp2[len-1] = (mwDict[len-1].insert(pair< vector<int>  , vector<SMYWORD*>  > (viWord, vwDictTemp)));
					mp2[len-1].first->second.push_back(w);
				}
				else
				{
					iwt = mp->second.end();
					while ((iwt!=mp->second.begin())&&((*(iwt-1))->freq < w->freq)) iwt--;
					mp->second.insert(iwt,w);
					mp2[len-1].first = mp;
					mp2[len-1].second = true;
				}
			}
			else
			{	
				iwt = mp2[len-1].first->second.end();
				while ((iwt!=mp2[len-1].first->second.begin())&&((*(iwt-1))->freq < w->freq)) iwt--;
				mp2[len-1].first->second.insert(iwt,w);
			}
		}
		lastviWord[len-1] = viWord;
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
				vector<SMYWORD*>::iterator iWordNumber = mp->second.begin();
				while (input[k]=='*')
				{
					if (++iWordNumber == mp->second.end()) iWordNumber = mp->second.begin();
					k++;
				}
				cout<<(*iWordNumber)->str;
				if (mp->second.size() > 1)
				{
					w = *iWordNumber;
					w->freq++;
					mp->second.erase(iWordNumber);
					iwt = mp->second.begin();
					while ((iwt!=mp->second.end())&&((*iwt)->freq > w->freq)) iwt++;
					mp->second.insert(iwt,w);
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