#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


struct SMYWORD
{
	string str; //�����
	int freq; //��� �������
	int iter;
	int lastmeeting; //���������� �� ���������� �����. ��������� - ���������� ����� � ����� ���������� ��������� ������ ����� � ������� UsedWords
	bool used; //����, �������������� �� ����� ����� ��� ���
};

struct ITERS
{
	int m[20][9];
};


SMYWORD *vwDict;

/* IsStrNum()
���������, �������� �� ������ ����� ������.
*/
bool IsStrNum(string *str);

/* IsCharNum()
���������, �������� �� ������ ������.
*/
bool IsCharNum(char ch);

/* IsCharButton()
���������, ��������� �� ������ ch �� ������ � ������ b.
��������� ����� �� ����������� ���������� Nokia.
2 - a b c
3 - d e f
4 - g h i
5 - j k l 
6 - m n o 
7 - p q r s 
8 - t u v 
9 - w x y z
*/
bool IsCharButton(char ch, int b);

/* FindWords()
���������� � ������ words �����, ��������� � ������� dict.
��������� ���������� � ������ ������������ ������, ��������������� ������� ������������ ��������� �����.
*/
void FindWords(vector<int> *words, vector<int> *buttons, ITERS *iters);

/*UpdateDict()
��������� � ������� �������� ������� ����� word.
*/
bool UpdateDict(vector<SMYWORD> *dict, SMYWORD *word);

/* IsCorrect()
���������� true, ���� ch - ��� ���� ����� (1-9), ���� ������ '*', ���� ������.
*/
bool IsCorrect(char ch);

bool cmpf(SMYWORD w1, SMYWORD w2);
bool cmpfi(int w1, int w2);

int main()
{
	bool bTypingWord = true; //bTypingWord == true, ���� ���� ���� �����
	char cSings[] = {'.',',','?'};
		 //chTemp = '0';
	int N; //���������� ���� � �������
	vector<int> viWord; //�������� �����, �������� �������������
	//vector<MYWORD> vwUsedWords; //�������� ��� ��������� ������������� �����. 
	vector<int> vwWords; //�������� ��������� ��������� � ������� ����
	string Text; //���� ������������ ������ ������������� �������������. � ����� ���������� ���� ������ ������������ � ���� "sms"
	string input;

	ITERS iters;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j<9; j++)
			iters.m[i][j] = -1;

	//Text.clear(); 
	string str;
	char ch;
	int fr;
	SMYWORD wTemp;

	cin>>N;
	vector<SMYWORD> vwDictTemp;
	for (int i = 0; i<N; i++)
	{
		cin>>str;
		wTemp.str = str;
		cin>>fr;
		wTemp.freq = fr;
		//wTemp.iter = i;
		wTemp.used = false;
		wTemp.lastmeeting = 0;
		vwDictTemp.push_back(wTemp);
	}

	//sort;
	sort(vwDictTemp.begin(), vwDictTemp.end(), cmpf);

	vwDict = new SMYWORD [N];
	/*for (int i = 0; i<vwDict.size(); i++)
	{
		cout<<vwDict[i].str<<endl;
	}*/

	for (int i = 0; i<N; i++)
	{
		vwDictTemp[i].iter = i;
		vwDict[i] = vwDictTemp[i];
		if ((vwDict[i].str[0] >= 'w') && (vwDict[i].str[0] <= 'z') && (iters.m[vwDict[i].str.length()-1][7] == -1)) iters.m[vwDict[i].str.length()-1][7] = i;
		else
		if ((vwDict[i].str[0] >= 't') && (vwDict[i].str[0] <= 'v') && (iters.m[vwDict[i].str.length()-1][6] == -1)) iters.m[vwDict[i].str.length()-1][6] = i;
		else
		if ((vwDict[i].str[0] >= 'p') && (vwDict[i].str[0] <= 's') && (iters.m[vwDict[i].str.length()-1][5] == -1)) iters.m[vwDict[i].str.length()-1][5] = i;
		else
		if ((vwDict[i].str[0] >= 'm') && (vwDict[i].str[0] <= 'o') && (iters.m[vwDict[i].str.length()-1][4] == -1)) iters.m[vwDict[i].str.length()-1][4] = i;
		else
		if ((vwDict[i].str[0] >= 'j') && (vwDict[i].str[0] <= 'l') && (iters.m[vwDict[i].str.length()-1][3] == -1)) iters.m[vwDict[i].str.length()-1][3] = i;
		else
		if ((vwDict[i].str[0] >= 'g') && (vwDict[i].str[0] <= 'i') && (iters.m[vwDict[i].str.length()-1][2] == -1)) iters.m[vwDict[i].str.length()-1][2] = i;
		else
		if ((vwDict[i].str[0] >= 'd') && (vwDict[i].str[0] <= 'f') && (iters.m[vwDict[i].str.length()-1][1] == -1)) iters.m[vwDict[i].str.length()-1][1] = i;
		else
		if ((vwDict[i].str[0] >= 'a') && (vwDict[i].str[0] <= 'c') && (iters.m[vwDict[i].str.length()-1][0] == -1)) iters.m[vwDict[i].str.length()-1][0] = i;
	}
	iters.m[19][8] = N;
	for (int i = 19; i >= 0; i--)
	{
		for (int j = 7; j >= 0; j--)
		{
			if (iters.m[i][j] == -1) iters.m[i][j] = iters.m[i][j+1];
		}
		if (i!=0) iters.m[i-1][8] = iters.m[i][0];
	}
	/*for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 9; j++)
			cout<<iters.m[i][j];
		cout<<endl;
	}*/
	
	ch = getchar();
	input.clear();
	int count = 0;
	while(((ch=getchar())!=10)&&(count++ < 100000))
	{
		input += ch;
	}

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
				FindWords(&vwWords, &viWord, &iters); //� ������ vwWords ��������� ����� �� ����� newDictName,
																		 //��������������� ������������������ ���� viWord.
									//��������� vwUsedWords ���������� ��� ����, ����� ���������� ��������� ����� ��� ����������� ���������� ����������
				sort(vwWords.begin(),vwWords.end(), cmpfi); //����������� ����� (� ������ ���� ����������). ���������� ���������� ��������������
													 //������������� � ������ WORD ���������� <
				/*for (int j = 0; j< vwWords.size(); j++)
				{
					cout<<vwWords[j].GetStr()<<endl;
					cout<<vwWords[j].WasUsed()<<endl;
				}*/
				//���� '*' - ������������ ������� ����.
				int iWordNumber = 0;
				while (input[k]=='*')
				{
					if (++iWordNumber==vwWords.size()) iWordNumber=0;
					k++;
					//chTemp = input[++k];
				}

				//update
				vwDict[vwWords[iWordNumber]].freq++;
				vwDict[vwWords[iWordNumber]].used = true;
				vwDict[vwWords[iWordNumber]].lastmeeting = k;
				//

				//Text += vwWords[iWordNumber].GetStr(); //��������� � ��������� ����� � ������ Text. � ����� ������ ��������� ������ Text ����� �������� � ���� "sms"
				cout<<vwDict[vwWords[iWordNumber]].str;
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
	delete [] vwDict;
	return 0;
}

bool IsStrNum(string *str)
{
	bool bTemp = true;
	for (unsigned int i=0; (bTemp) && (i < str->length()); i++ )
	{
		if (!IsCharNum((*str)[i])) bTemp = false;
	}
	return bTemp;
}

bool IsCharNum(char c)
{
	return (c>='0')&&(c<='9');
}

bool IsCharButton(char ch, int b)
{
	switch (b)
	{
	case 2: return (ch>='a')&&(ch<='c');
	case 3: return (ch>='d')&&(ch<='f');
	case 4: return (ch>='g')&&(ch<='i');
	case 5: return (ch>='j')&&(ch<='l');
	case 6: return (ch>='m')&&(ch<='o');
	case 7: return (ch>='p')&&(ch<='s');
	case 8: return (ch>='t')&&(ch<='v');
	case 9: return (ch>='w')&&(ch<='z');
	}
	return false;
}

void FindWords(vector<int> *words, //���� ����� ������� ��������� �����
			vector<int> *buttons, //������������������ ���� (2-9) (������� ������)
			ITERS *iters)
{
	
	words->clear();
	
	for (int i = iters->m[(*buttons).size()-1][(*buttons)[0]-2]; i<iters->m[(*buttons).size()-1][(*buttons)[0]-1]; i++)
	{
		if ((*buttons).size()!=1)
		{
			bool bCoresp = true; //������������� ��� ��� ����� ������������������ ����
			//���� ����� ����� �� ����� ����� ������������������ ��������� ������������� ����, �� ����� bCoresp = false
			//if ((*dict)[i].str.length() != (*buttons).size()) continue;
	
			//��������� ������������ ����� ������������������ ����
			unsigned int n;
			for (n = 0; (bCoresp)&&(n<vwDict[i].str.length()); n++)
				bCoresp = bCoresp && IsCharButton(vwDict[i].str[n],(*buttons)[n]);
			//n - �������, � ������� �� �������
			//cout<<"n = "<<n<<endl;
			if (bCoresp) //���� ��������
			{
				words->push_back(i); //��������� � ������ words ������ ��� �������� ������, ��������������� ������ ���������� �����
			}
			else
			{
				//cout<<"ne podoshlo "<<vwDict[i].str<<endl;
				int itemp = i;
				bool b = true;
				while (b)
				{
					i++;
					b = i<iters->m[(*buttons).size()-1][(*buttons)[0]-1];
					//cout<<"test "<<vwDict[i].str<<endl;
					for (int h = n-1; b && (h>=0); h--)
					{
						/*cout<<"vwDict[i].str[h] "<<vwDict[i].str[h]<<endl
							<<"vwDict[itemp].str[h] "<<vwDict[itemp].str[h]<<endl;*/
						b = b && (vwDict[i].str[h] == vwDict[itemp].str[h]);
					}
					//if (b) cout<<"propysheno "<<vwDict[i].str<<" "<<i<<endl;
				}
				i--;
			}
		}
		else
		{
			//if ((*dict)[i].str.length() != 1) continue;
			if (IsCharButton(vwDict[i].str[0],(*buttons)[0]))
			{
				words->push_back(i); //��������� � ������ words ������ ��� �������� ������, ��������������� ������ ���������� �����
			}
				
		}
	}
	
	if (words->size()==0)  //���� ������ �� �����. �� ������� ������ ������ ���� �� �����.
	{
		cout<<"ERROR. There are no appropriate words in the dictionary";
		exit(1);
	}
	//_getch();
}

bool IsCorrect(char c)
{
	return (c==' ')||(c=='*')||((c-'0'>=0)&&(c-'0'<=9));
}

bool cmpfi(int w1, int w2)
{
	//cout<<"operator"<<endl;
	if (vwDict[w1].freq != vwDict[w2].freq) //���� ������� ������, �� ������ ���������� �������
		return vwDict[w1].freq > vwDict[w2].freq;
	//�����, ���� ������� ����������
	if (vwDict[w1].used && vwDict[w2].used) //���� ��� ����� �����������, �� ������������� �� ����, ����� �� ��� ��������� ��� ��������� �����
		return vwDict[w1].lastmeeting > vwDict[w2].lastmeeting;
	//���� ����������� ������ ���� �����, �� ��������� � ������ ����, ������� �����������
	if (vwDict[w1].used && (!vwDict[w2].used))
		return true;
	if (vwDict[w2].used && (!vwDict[w1].used))
		return false;
	
	//���� ������� ���������� � �� ���� �� ���� �� �����������, �� ��������� �� ��������.
	return (vwDict[w1].str.compare(vwDict[w2].str)<0);
}

bool cmpf(SMYWORD w1, SMYWORD w2)
{
	bool t;
	int l1 = w1.str.length(),
		l2 = w2.str.length();
	if (l1 == l2) return (w1.str.compare(w2.str)<0);
	if (l1 <  l2) return true;
	return false;
}