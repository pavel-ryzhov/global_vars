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
	int lastmeeting; //���������� �� ���������� �����. ��������� - ���������� ����� � ����� ���������� ��������� ������ ����� � ������� UsedWords
	bool used; //����, �������������� �� ����� ����� ��� ���
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

bool cmpf(SMYWORD w1, SMYWORD w2);

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
		wTemp.used = false;
		wTemp.lastmeeting = 0;
		vwDictTemp.push_back(wTemp);
		mp = mwDict.find(viWord);
		if (mp == mwDict.end())
		{
			mwDict.insert(pair< vector<int>  , vector<SMYWORD>  > (viWord, vwDictTemp));
		}
		else
		{
			(mp->second).push_back(wTemp);
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
				sort(mp->second.begin(),mp->second.end(), cmpf); //����������� ����� (� ������ ���� ����������). ���������� ���������� ��������������
													 //������������� � ������ WORD ���������� <
				//���� '*' - ������������ ������� ����.
				int iWordNumber = 0;
				while (input[k]=='*')
				{
					if (++iWordNumber== mp->second.size()) iWordNumber=0;
					k++;
					//chTemp = input[++k];
				}

				//update
				mp->second[iWordNumber].freq++;
				mp->second[iWordNumber].used = true;
				mp->second[iWordNumber].lastmeeting = k;
				//

				//Text += vwWords[iWordNumber].GetStr(); //��������� � ��������� ����� � ������ Text. � ����� ������ ��������� ������ Text ����� �������� � ���� "sms"
				cout<<mp->second[iWordNumber].str;
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

bool cmpf(SMYWORD w1, SMYWORD w2)
{
	//cout<<"operator"<<endl;
	if (w1.freq != w2.freq) //���� ������� ������, �� ������ ���������� �������
		return w1.freq > w2.freq;
	//�����, ���� ������� ����������
	if (w1.used && w2.used) //���� ��� ����� �����������, �� ������������� �� ����, ����� �� ��� ��������� ��� ��������� �����
		return w1.lastmeeting > w2.lastmeeting;
	//���� ����������� ������ ���� �����, �� ��������� � ������ ����, ������� �����������
	if (w1.used && (!w2.used))
		return true;
	if (w2.used && (!w1.used))
		return false;
	
	//���� ������� ���������� � �� ���� �� ���� �� �����������, �� ��������� �� ��������.
	return (w1.str.compare(w2.str)<0);
}