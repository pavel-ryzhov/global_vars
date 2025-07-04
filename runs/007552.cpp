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

int main()
{
	map< vector<int> , vector<SMYWORD*> > mwDict[20];
	vector<int> viWord;
	vector<SMYWORD*> vwDictTemp;

	pair< map< vector<int>  ,  vector<SMYWORD*>  >::iterator, bool> mp2;

	
	int N;
	SMYWORD *w;

	int mas[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
	cin>>N;
	for (int i = 0; i<N; i++)
	{
		SMYWORD *w = new SMYWORD;
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
	bool bTypingWord = true;
	char cSings[] = {'.',',','?'};
	bool bFileEndSpace = false;
	char ch = getchar();
	while (ch != 10)
	{
		if ((ch>='2')&&(ch<='9'))
		{
			bTypingWord = true;
			viWord.push_back(ch-'0');
			ch = getchar();
		}
		if ((ch==' ')||(ch=='1')||(ch=='*')||(ch==10))
		{
			if (bTypingWord)
			{
				bTypingWord = false;
				map< vector<int>  ,  vector<SMYWORD*>  >::iterator mp = mwDict[viWord.size()-1].find(viWord);
				vector<SMYWORD*>::iterator iWordNumber = mp->second.begin();
				int pos = 0;
				while (ch=='*')
				{
					if (++iWordNumber == mp->second.end()) 
					{
						iWordNumber = mp->second.begin();
						pos = 0;
					}
					pos++;
					ch = getchar();
				}
				cout<<(*iWordNumber)->str;
				(*iWordNumber)->freq++;
				if ((mp->second.size() > 1)&&(iWordNumber!=mp->second.begin()))
				{
					//w = *iWordNumber;
					//mp->second.erase(iWordNumber);
					//pos--;
					//iWordNumber = mp->second.begin() + pos;
					while ((iWordNumber!=mp->second.begin())&&((*(iWordNumber-1))->freq <= (*iWordNumber)->freq))
					{
						w = *iWordNumber;
						*iWordNumber = *(--iWordNumber);
						*iWordNumber = w;
					}/*
					if (iWordNumber==mp->second.begin())
					{
						if ((*iWordNumber)->freq <= w->freq) mp->second.insert(iWordNumber,w);
						else mp->second.insert(iWordNumber+1,w);
					}
					else mp->second.insert(iWordNumber+1,w);*/
				}
				viWord.clear();
			}
			if (ch == ' ')
			{
				cout<<' ';
				ch = getchar();
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
		}
	}
	//_getch();
	return 0;
}