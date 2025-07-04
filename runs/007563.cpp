//1.412
#include <iostream>
#include <string>
#include <vector>
#include <map>
//#include <conio.h>

using namespace std;

/*struct SMYWORD
{
	SMYWORD(){};
	string str;
	int freq;
};*/

int main()
{
	//pair<string,int>
	map< vector<int> , vector<pair<string,int>*> > mwDict[20];
	vector<int> viWord;
	vector<pair<string,int>*> vwDictTemp;
	
	pair< map< vector<int>  ,  vector<pair<string,int>*>  >::iterator, bool> mp2;

	
	int N;
	pair<string,int> *w;

	int mas[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
	cin>>N;
	for (int i = 0; i<N; i++)
	{
		pair<string,int> *w = new pair<string,int>;
		cin>>w->first;
		unsigned int len = w->first.length();
		cin>>w->second;
		vector<int> vi;
		for (unsigned int i = 0; i < len; i++)
		{
			vi.push_back(mas[w->first[i] - 'a']);
		}
		map< vector<int>  ,  vector<pair<string,int>*>  >::iterator mp = mwDict[len-1].find(vi);
		if (mp==mwDict[len-1].end())
		{
			vwDictTemp.clear();
			mp2 = (mwDict[len-1].insert(pair< vector<int>  , vector<pair<string,int>*>  > (vi, vwDictTemp)));
			mp2.first->second.push_back(w);
		}
		else
		{
			vector<pair<string,int>*>::iterator iwt = mp->second.end();
			while ((iwt!=mp->second.begin())&&((*(iwt-1))->second < w->second)) iwt--;
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
				map< vector<int>  ,  vector<pair<string,int>*>  >::iterator mp = mwDict[viWord.size()-1].find(viWord);
				vector<pair<string,int>*>::iterator iWordNumber = mp->second.begin();
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
				cout<<(*iWordNumber)->first;
				(*iWordNumber)->second++;
				if ((mp->second.size() > 1)&&(iWordNumber!=mp->second.begin())&&((*iWordNumber)->second >= (*(iWordNumber-1))->second))
				{
					w = *iWordNumber;
					mp->second.erase(iWordNumber);
					iWordNumber = mp->second.begin() + pos;
					while ((iWordNumber!=mp->second.begin())&&((*(iWordNumber-1))->second <= w->second)) iWordNumber--;
					mp->second.insert(iWordNumber,w);
				}
				viWord.clear();
			}
			if (ch == ' ')
			{
				cout<<' ';
				//putchar(' ');
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
				//putchar(cSings[iSignNumber]);
			}
		}
	}
	//_getch();
	return 0;
}