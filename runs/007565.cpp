//1.192
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//��������� MYWORD ������������ �����
struct MYWORD
{
	MYWORD(){};
	string str; //���� �����
	int freq; //������� ������� �������������
};

int main()
{
	//���� ������� ������ �� �������� ������. � ������ ����� ����� ���������� �����. ������ ����� �������� ������������� ��������(STL).
	//���� - ��� ������������������ ���� (���� ������������). 
	//�������� - ��� ������������� ������ ���������� ������� ����� ���� (������, ���������� �� �����).
	map< vector<int> , vector<MYWORD*> > Dict[20];

	//input - ������������������ ����, �������� �������������
	vector<int> input;

	//� ������� [����� - 'a'] ����� ����� ��������������� ������
	//           a b c  d e f  g h i  j k l  m n o  p q r s  t u v  w x y z
	int mas[] = {2,2,2, 3,3,3, 4,4,4, 5,5,5, 6,6,6, 7,7,7,7, 8,8,8, 9,9,9,9};

	//temp
	vector<MYWORD*> vwTemp;
	//pair< map< vector<int>  ,  vector<MYWORD*>  >::iterator, bool> mp2;
	int N;
	MYWORD *w;

	cin>>N; // ������ ���������� ���� � �������
	for (int i = 0; i<N; i++) //� ��� �� ������� � �������
	{
		MYWORD *w = new MYWORD; //����������� ������ ��� ������ �����
		cin>>w->str>>w->freq; //��������� ����� � ��� �������
		
		unsigned int len = w->str.length(); // len = ����� �����
		vector<int> vi; //������ ��� ������������������ ������, ��������������� ������� �����
		for (unsigned int i = 0; i < len; i++) //��������� �� �����
		{
			vi.push_back(mas[w->str[i] - 'a']); //� ��������� � vi ����� ������, ��������������� ��������� ����� �����
		}

		//�������� ����� � ��� ����� �������, ������� ������ ����� ����� len, �������, ���� �������� ��������� � vi. 
		map< vector<int>  ,  vector<MYWORD*>  >::iterator mp = Dict[len-1].find(vi);
		if (mp==Dict[len-1].end()) //���� ������ �� �����, ������ � ������� ��� �� ���� ���� � ����� ������������������� ������� ������
		{
			vwTemp.clear();
			vwTemp.push_back(w);
			Dict[len-1].insert(pair< vector<int>  , vector<MYWORD*>  > (vi, vwTemp)); //��������� � ����� ����� �������
			//mp2.first->second.push_back(w); //� ��������� � ������(���� ��� ������) ���� ����� �������� ����� �����.
		}
		else //���� ������� �����. mp - 
		{
			vector<MYWORD*>::iterator iwt = mp->second.end();
			while ((iwt!=mp->second.begin())&&((*(iwt-1))->freq < w->freq)) iwt--;
			mp->second.insert(iwt,w);
		}
	}
	
	getchar();
	input.clear();
	bool bTypingWord = true;
	char cSings[] = {'.',',','?'};
	bool bFileEndSpace = false;
	char ch = getchar();
	while (ch != 10)
	{
		if ((ch>='2')&&(ch<='9'))
		{
			bTypingWord = true;
			input.push_back(ch-'0');
			ch = getchar();
		}
		if ((ch==' ')||(ch=='1')||(ch=='*')||(ch==10))
		{
			if (bTypingWord)
			{
				bTypingWord = false;
				map< vector<int>  ,  vector<MYWORD*>  >::iterator mp = Dict[input.size()-1].find(input);
				vector<MYWORD*>::iterator iWordNumber = mp->second.begin();
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
				if ((mp->second.size() > 1)&&(iWordNumber!=mp->second.begin())&&((*iWordNumber)->freq >= (*(iWordNumber-1))->freq))
				{
					w = *iWordNumber;
					mp->second.erase(iWordNumber);
					iWordNumber = mp->second.begin() + pos;
					while ((iWordNumber!=mp->second.begin())&&((*(iWordNumber-1))->freq <= w->freq)) iWordNumber--;
					mp->second.insert(iWordNumber,w);
				}
				input.clear();
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