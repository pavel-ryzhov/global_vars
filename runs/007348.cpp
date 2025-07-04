#include <fstream>
#include <iostream>
#include <stdio.h>
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
	map< vector<int> , vector<SMYWORD> > mwDict; //�������, �������������� � ���� �������������� �������. ���� - ������������������ ����, ������� - ������ ����, ���������� ���� ������������������
	bool bTypingWord = true; //bTypingWord == true, ���� ���� ���� �����
	char cSings[] = {'.',',','?'};
	int N; //���������� ���� � �������
	vector<int> viWord; //�������� �����, �������� �������������
	string Text; //���� ������������ ������ ������������� �������������. � ����� ���������� ���� ������ ������������ � ���� "sms"
	string input;

	//Text.clear(); 
	string str;
	char ch;
	int fr;
	SMYWORD wTemp;
	map< vector<int>  ,  vector<SMYWORD>  >::iterator mp;
	vector<SMYWORD> vwDictTemp;

	cin>>N;
	for (int i = 0; i<N; i++)
	{
		cin>>str;
		viWord.clear();
		vwDictTemp.clear();
		for (int i = 0; i<str.length(); i++)
		{
			viWord.push_back(CharToButton(str[i]));
		}
		wTemp.str = str;
		cin>>fr;
		wTemp.freq = fr;
		vwDictTemp.push_back(wTemp);
		mp = mwDict.find(viWord);
		if (mp == mwDict.end())
		{
			mwDict.insert(pair< vector<int>  , vector<SMYWORD>  > (viWord, vwDictTemp));
		}
		else
		{	
			vector<SMYWORD>::iterator iwt = mp->second.begin();
			if ( (fr > iwt->freq) || ((fr==iwt->freq)&&(str.compare(iwt->str)<0)) )
				mp->second.insert(iwt,wTemp);
			else if ( (fr < (mp->second.end()-1)->freq) || ((fr==(mp->second.end()-1)->freq)&&(str.compare((mp->second.end()-1)->str)>0)) )
				mp->second.push_back(wTemp);
			else 
			{
				iwt++;
				while ( ! (  (((iwt-1)->freq > fr)&&(iwt->freq < fr))   ||     
					( ((iwt-1)->freq > fr) && (iwt->freq ==fr) && (str.compare(iwt->str)<0) )  ||
					( ((iwt-1)->freq ==fr) && (iwt->freq < fr) && (str.compare((iwt-1)->str)>0) ) ||
					( ((iwt-1)->freq ==fr) && (iwt->freq ==fr) && (str.compare((iwt-1)->str)>0) && (str.compare(iwt->str)<0)  )
					) ) iwt++;
				mp->second.insert(iwt,wTemp);
			}

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
				mp = mwDict.find(viWord);
				/*cout<<"<";
				for (int i = 0; i < mp->second.size(); i++)
				{
					cout<<mp->second[i].str;
				}
				cout<<">";*/
				//sort(mp->second.begin(),mp->second.end(), cmpf); //����������� ����� (� ������ ���� ����������). ���������� ���������� ��������������
													 //������������� � ������ WORD ���������� <
				//���� '*' - ������������ ������� ����.
				vector<SMYWORD>::iterator iWordNumber = mp->second.begin();
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
					vector<SMYWORD>::iterator itemp = mp->second.begin();
					//cout<<"while{";
					while ((itemp!=mp->second.end())&&(itemp->freq > wTemp.freq)) 
					{
						//cout<<itemp->str;
						itemp++;
					}
					//cout<<"}";
					mp->second.insert(itemp,wTemp);
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