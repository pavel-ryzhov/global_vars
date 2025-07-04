//1.412
#include <iostream>
#include <string>
#include <vector>
#include <map>
//#include <conio.h>

using namespace std;

struct SMYWORD
{
	SMYWORD(){};
	string str;
	int freq;
};

int CharToButton(char *ch);

int main()
{
	vector<SMYWORD*>::iterator iwt;
	map< vector<int> , vector<SMYWORD*> > mwDict[20];
	vector<int> viWord;
	map< vector<int>  ,  vector<SMYWORD*>  >::iterator mp;
	pair< map< vector<int>  ,  vector<SMYWORD*>  >::iterator, bool> mp2;
	//vector<SMYWORD*> vwDictTemp;

	bool bTypingWord = true;
	char cSings[] = {'.',',','?'};
	int N;
	bool bFileEndSpace = false;
	char ch;
	SMYWORD *w;

	cin>>N;
	//vwDictTemp.clear();
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
			mp2 = (mwDict[len-1].insert(pair< vector<int>  , vector<SMYWORD*>  > (viWord, vector<SMYWORD*>())));
			mp2.first->second.push_back(w);
		}
		else
		{
			mp = mwDict[len-1].find(viWord);
			if (mp==mwDict[len-1].end())
			{
				//vwDictTemp.clear();
				mp2 = (mwDict[len-1].insert(pair< vector<int>  , vector<SMYWORD*>  > (viWord, vector<SMYWORD*>())));
				mp2.first->second.push_back(w);
			}
			else
			{
				iwt = mp->second.end();
				while ((iwt!=mp->second.begin())&&((*(iwt-1))->freq < w->freq)) iwt--;
				mp->second.insert(iwt,w);
			}
		}
	}
	
	getchar();
	viWord.clear();
	ch = getchar();
	while (ch != 10)
	{
		switch (ch)
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
			viWord.push_back(ch-'0');
			ch = getchar();
			if (ch!=10) break;
		case ' ':
		case '1':
		case '*':
		case 10:
			if (bTypingWord)
			{
				
				bTypingWord = false;
				mp = mwDict[viWord.size()-1].find(viWord);
				vector<SMYWORD*>::iterator iWordNumber = mp->second.begin();
				while (ch=='*')
				{
					if (++iWordNumber == mp->second.end()) iWordNumber = mp->second.begin();
					ch = getchar();
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
			if (ch == ' ')
			{
				cout<<' ';
				ch = getchar();
				break;
			}
			if (ch == '1')
			{
				int iSignNumber = 0;
				ch = getchar();
				while (ch=='*')
				{
					if (iSignNumber==2) iSignNumber=0;
					else iSignNumber++;
					ch = getchar();
				}
				cout<<cSings[iSignNumber];
			}
			break;
		default:
			break;
		}
	}
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