#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
//#include <conio.h>

using namespace std;

struct SMYWORD
{
	string str; //�����
	int freq; //��� �������
};


/*��������� ����� �� ����������� ���������� Nokia.
2 - a b c
3 - d e f
4 - g h i
5 - j k l 
6 - m n o 
7 - p q r s 
8 - t u v 
9 - w x y z
*/
int CharToButton(char ch);

int main()
{
	map< vector<int> , vector<SMYWORD> > mwDict[20]; //�������, �������������� � ���� ������������� ��������. ���� - ������������������ ����, ������� - ������ ����, ���������� ���� ������������������
	vector<SMYWORD>::iterator iwt;
	vector<SMYWORD>::iterator iWordNumber;
	bool bTypingWord = true; //bTypingWord == true, ���� ���� ���� �����
	char cSings[] = {'.',',','?'};
	int N; //���������� ���� � �������
	vector<int> viWord; //�������� �����, �������� �������������
	string input;

	//Text.clear(); 
	//string str;
	char ch;
	SMYWORD wTemp;
	map< vector<int>  ,  vector<SMYWORD>  >::iterator mp;
	pair< map< vector<int>  ,  vector<SMYWORD>  >::iterator, bool> mp2;
	vector<SMYWORD> vwDictTemp;

	cin>>N;
	for (int i = 0; i<N; i++)
	{
		cin>>wTemp.str;
		viWord.clear();
		for (int i = 0; i<wTemp.str.length(); i++)
		{
			viWord.push_back(CharToButton(wTemp.str[i]));
		}
		cin>>wTemp.freq;
		mp = mwDict[wTemp.str.length()-1].find(viWord);
		if (mp == mwDict[wTemp.str.length()-1].end())
		{
			vwDictTemp.clear();
			mp2 = (mwDict[wTemp.str.length()-1].insert(pair< vector<int>  , vector<SMYWORD>  > (viWord, vwDictTemp)));
			mp2.first->second.push_back(wTemp);
		}
		else
		{	
			iwt = mp->second.end();
			while ((iwt!=mp->second.begin())&&((iwt-1)->freq < wTemp.freq)) iwt--;
			mp->second.insert(iwt,wTemp);
		}
	}

	ch = getchar();
	input.clear();
	while((ch=getchar())!=10)
	{
		input += ch;
	}

	viWord.clear();
	unsigned int k = 0; //�������� ��� ���������� ���������� ������� �� ������
	bool bFileEndSpace = false;
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
			
			bTypingWord = true; //��� ������ ����� (2-9), ������ ���� ���� �����, � �� ������ ����������, �������� � ��
			viWord.push_back(input[k]-'0'); //����������� � ������� viWord �����. ����� ���� ����� ����� ��������, �� ���� 
										  //������������������ ����� ���������� ����� ���� � �������.
			k++;
			//��������� ��������� ������

			//���� ����� ��������� ���� � ������ input ������ �� �����
			//�� ���� ������������ ����� ���������� ����� �� ����� ������, 1 ��� *, �� ����� ��� ����� ������ ���� �������.
			if (k==input.size()) //���� ����� �����
			{
				bFileEndSpace = true; 
				//chTemp = ' '; //���������� �� ���, ����� ������������ ���� ������. Break'� ��� ���, ��� ��� �� switcha �� �������, � �������� � case' ':
				//� ��������� ������������ �����. ��� ���� ���� ������ ������ �� ��������� � Text ��������� ����� bFileEndSpace.
			}
			else break;
		case ' ':
		case '1':
		case '*':
			if (bTypingWord) //���� �� ����� ��������� �����
			{
				
				bTypingWord = false; //���� ����� ��������
				//FindWords(&vwWords, &viWord, &iters); //� ������ vwWords ��������� ����� �� ����� newDictName,
																		 //��������������� ������������������ ���� viWord.
									//��������� vwUsedWords ���������� ��� ����, ����� ���������� ��������� ����� ��� ����������� ���������� ����������
				mp = mwDict[viWord.size()-1].find(viWord);
				/*cout<<"<";
				for (int i = 0; i < mp->second.size(); i++)
				{
					cout<<mp->second[i].str;
				}
				cout<<">";*/
				//sort(mp->second.begin(),mp->second.end(), cmpf); //����������� ����� (� ������ ���� ����������). ���������� ���������� ��������������
													 //������������� � ������ WORD ���������� <
				//���� '*' - ������������ ������� ����.
				iWordNumber = mp->second.begin();
				while (input[k]=='*')
				{
					if (++iWordNumber== mp->second.end()) iWordNumber=mp->second.begin();
					k++;
					//chTemp = input[++k];
				}

				cout<<iWordNumber->str;
				if (mp->second.size() > 1)
				{
					wTemp = *iWordNumber;
					wTemp.freq++;
					mp->second.erase(iWordNumber);
					//update
					iwt = mp->second.begin();
					//cout<<"while{";
					while ((iwt!=mp->second.end())&&(iwt->freq > wTemp.freq)) 
					{
						//cout<<itemp->str;
						iwt++;
					}
					//cout<<"}";
					mp->second.insert(iwt,wTemp);
				}
				//

				//Text += vwWords[iWordNumber].GetStr(); //��������� � ��������� ����� � ������ Text. � ����� ������ ��������� ������ Text ����� �������� � ���� "sms"
				viWord.clear();
			}
			if ((bFileEndSpace)||(input[k] == ' '))
			{
				if (!bFileEndSpace) //���� ��� �� ��� ������������ ������, ������������ ��� ��������� ��������, ����� ����� ���������� �����
									//�� ����� �� ������, �� ���� ����������, �� *
				{
					//Text += ' ';
					cout<<' ';
					//chTemp = input[++k];
					k++;
				}
				break;
			}
			if (input[k] == '1') //���� ����������
			{
				int iSignNumber = 0;
				//chTemp = input[++k]; //��������� ��������� ������
				k++;
				while (input[k]=='*') //���� (� ����) ��� '*' - ���������� ����� ����������, ���������� � ������� cSings[] = {'.',',','?'}
				{
					if (iSignNumber==2) iSignNumber=0;
					else iSignNumber++;
					//chTemp = input[++k];
					k++;
				}
				//Text += cSings[iSignNumber]; //������� � Text ��������� ���� ����������
				cout<<cSings[iSignNumber];
			}
			break;
		default:
			cout<<"wrong symbol"<<endl;
			return 1;
			break;
		}
	} while (k<input.size()); //� ��� ������������ ��� ������. 
	//cout<<Text<<endl;
	//delete [] vwDict;
	//_getch();
	return 0;
}

int CharToButton(char ch)
{
	if ((ch>='a')&&(ch<='c')) return 2;
	if ((ch>='d')&&(ch<='f')) return 3;
	if ((ch>='g')&&(ch<='i')) return 4;
	if ((ch>='j')&&(ch<='l')) return 5;
	if ((ch>='m')&&(ch<='o')) return 6;
	if ((ch>='p')&&(ch<='s')) return 7;
	if ((ch>='t')&&(ch<='v')) return 8;
	if ((ch>='w')&&(ch<='z')) return 9;
	return -1;
}