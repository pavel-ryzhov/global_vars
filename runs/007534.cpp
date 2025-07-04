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

//int CharToButton(char *ch);

int main()
{
	map< vector<int> , vector<SMYWORD*> > mwDict[20];
	vector<int> viWord;
	vector<SMYWORD*> vwDictTemp;

	pair< map< vector<int>  ,  vector<SMYWORD*>  >::iterator, bool> mp2;

	bool bTypingWord = true;
	char cSings[] = {'.',',','?'};
	int N;
	bool bFileEndSpace = false;
	char ch;
	SMYWORD *w;

	int mas[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
	cin>>N;
	for (int i = 0; i<N; i++)
	{
		w = new SMYWORD;
		cin>>w->str;
		unsigned int len = w->str.length();
		cin>>w->freq;
		vector<int> vi;
		for (unsigned int i = 0; i < len; i++)
		{
			vi.push_back(mas[w->str[i] - 'a']);
		}
		map< vector<int>  ,  vector<SMYWORD*>  >::iterator mp = mwDict[len-1].find(vi);
		if (mp==mwDict[len-1].end())
		{
			vwDictTemp.clear();
			mp2 = (mwDict[len-1].insert(pair< vector<int>  , vector<SMYWORD*>  > (vi, vwDictTemp)));
			mp2.first->second.push_back(w);
		}
		else
		{
			vector<SMYWORD*>::iterator iwt = mp->second.end();
			while ((iwt!=mp->second.begin())&&((*(iwt-1))->freq < w->freq)) iwt--;
			mp->second.insert(iwt,w);
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
				map< vector<int>  ,  vector<SMYWORD*>  >::iterator mp = mwDict[viWord.size()-1].find(viWord);
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
					vector<SMYWORD*>::iterator iwt = mp->second.begin();
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

/*int CharToButton(char *ch)
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
}*/