#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <conio.h>

using namespace std;


//������ ������ WORD �������� ����� � ����������� �������������� ���������� (��� ���������� � ��);
class MYWORD
{
public:
	MYWORD();
	~MYWORD();
	void SetStr(string *);
	void SetFreq(int);
	void SetPos(ios::pos_type);
	friend bool operator< (MYWORD,MYWORD); //���������� ����� ��� ����������
	string& GetStr();
	int GetFreq();
	ios::pos_type GetPos();
	void Used(); //��������� �����, ������������, ��� ����� ����� ��� ���������
	bool WasUsed(); //���������� �������� ����� �����
	void ClearUsed();
	void SetLast(int c); //������������� ���������� �� ���� �������, ����� ����� ����� � ��������� ��� ���������
	int GetLast();
	void SetIter(int i);
	int GetIter();
private:
	string str; //�����
	int freq; //��� �������
	int iter;
	int lastmeeting; //���������� �� ���������� �����. ��������� - ���������� ����� � ����� ���������� ��������� ������ ����� � ������� UsedWords
	bool used; //����, �������������� �� ����� ����� ��� ���
};

struct ITERS2
{
	int m[26][9];
};


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
void FindWords(vector<MYWORD> *dict, vector<MYWORD> *words, vector<int> *buttons, int *iters, ITERS2 *iters2);

/*UpdateDict()
��������� � ������� �������� ������� ����� word.
*/
bool UpdateDict(vector<MYWORD> *dict, MYWORD *word);

/* IsCorrect()
���������� true, ���� ch - ��� ���� ����� (1-9), ���� ������ '*', ���� ������.
*/
bool IsCorrect(char ch);

int main()
{
	bool bTypingWord = true; //bTypingWord == true, ���� ���� ���� �����
	char cSings[] = {'.',',','?'},
		 chTemp;
	int N; //���������� ���� � �������
	vector<int> viWord; //�������� �����, �������� �������������
	//vector<MYWORD> vwUsedWords; //�������� ��� ��������� ������������� �����. 
	vector<MYWORD> vwWords; //�������� ��������� � ������� �����
	vector<MYWORD> vwDict;
	string Text; //���� ������������ ������ ������������� �������������. � ����� ���������� ���� ������ ������������ � ���� "sms"
	string input;

	int iters[27];
	ITERS2 iters2;
	for (int i = 0; i<26; i++)
		for (int j = 0; j<9; j++)
			iters2.m[i][j] = -1;

	for (int i = 0; i < 27; i++)
		iters[i] = -1;

	//Text.clear(); 
	string str;
	char ch;
	int fr;
	MYWORD wTemp;

	cin>>N;
	for (int i = 0; i<N; i++)
	{
		cin>>str;
		if ((iters[(int)(str[0]-'a')] == -1)) iters[(int)(str[0]-'a')] = i;
			
		wTemp.SetStr(&str);
		cin>>fr;
		wTemp.SetFreq(fr);
		wTemp.SetIter(i);
		vwDict.push_back(wTemp);
	}
	iters[26] = vwDict.size();
	for (int i = 25; i>=0; i--)
	{
		if (iters[i] == -1) iters[i] = iters[i+1];
	}
	/*for (int i = 0; i < 27; i++)
	{
		cout<<(char)(i+'a')<<iters[i]<<endl;
		//cout<<vwDict[iters[i]].GetStr()<<endl;
	}*/
	
	for (int it1 = 0; it1<26; it1++)
	{
		//cout<<"iters[it1+1]: "<<iters[it1+1]<<"   iters[it1]: "<<iters[it1]<<endl;
		for (int it2 = 0; it2 < iters[it1+1] - iters[it1]; it2++)
		{
			//cout<<"vwDict[iters[it1]+it2].GetStr(): "<<vwDict[iters[it1]+it2].GetStr()<<endl;
			if (vwDict[iters[it1]+it2].GetStr().size() == 1) ;
			else
			{
				if ((vwDict[iters[it1]+it2].GetStr()[1] >= 'w') && (vwDict[iters[it1]+it2].GetStr()[1] <= 'z') && (iters2.m[it1][7] == -1)) iters2.m[it1][7] = it2;
				if ((vwDict[iters[it1]+it2].GetStr()[1] >= 't') && (vwDict[iters[it1]+it2].GetStr()[1] <= 'v') && (iters2.m[it1][6] == -1)) iters2.m[it1][6] = it2;
				if ((vwDict[iters[it1]+it2].GetStr()[1] >= 'p') && (vwDict[iters[it1]+it2].GetStr()[1] <= 's') && (iters2.m[it1][5] == -1)) iters2.m[it1][5] = it2;
				if ((vwDict[iters[it1]+it2].GetStr()[1] >= 'm') && (vwDict[iters[it1]+it2].GetStr()[1] <= 'o') && (iters2.m[it1][4] == -1)) iters2.m[it1][4] = it2;
				if ((vwDict[iters[it1]+it2].GetStr()[1] >= 'j') && (vwDict[iters[it1]+it2].GetStr()[1] <= 'l') && (iters2.m[it1][3] == -1)) iters2.m[it1][3] = it2;
				if ((vwDict[iters[it1]+it2].GetStr()[1] >= 'g') && (vwDict[iters[it1]+it2].GetStr()[1] <= 'i') && (iters2.m[it1][2] == -1)) iters2.m[it1][2] = it2;
				if ((vwDict[iters[it1]+it2].GetStr()[1] >= 'd') && (vwDict[iters[it1]+it2].GetStr()[1] <= 'f') && (iters2.m[it1][1] == -1)) iters2.m[it1][1] = it2;
				if ((vwDict[iters[it1]+it2].GetStr()[1] >= 'a') && (vwDict[iters[it1]+it2].GetStr()[1] <= 'c') && (iters2.m[it1][0] == -1)) 
				{
					iters2.m[it1][0] = it2;
				}
			}
		}
		iters2.m[it1][8] = iters[it1+1] - iters[it1];
		for (int i = 7; i>=0; i--)
		{
			if (iters2.m[it1][i] == -1) iters2.m[it1][i] = iters2.m[it1][i+1];
		}
	}
	//cout<<"qqqq"<<endl;
	/*for (int i = 0; i<26; i++)
	{
		for (int j = 0; j<9; j++)
			cout<<iters2.m[i][j]<<' ';
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
	chTemp = input[0];
	bool bFileEndSpace = false;
	do
	{
		switch (chTemp)
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
			viWord.push_back(chTemp-'0'); //����������� � ������� viWord �����. ����� ���� ����� ����� ��������, �� ���� 
										  //������������������ ����� ���������� ����� ���� � �������.
			chTemp = input[++k]; //��������� ��������� ������

			//���� ����� ��������� ���� � ������ input ������ �� �����
			//�� ���� ������������ ����� ���������� ����� �� ����� ������, 1 ��� *, �� ����� ��� ����� ������ ���� �������.
			if (k==input.size()) //���� ����� �����
			{
				bFileEndSpace = true; 
				chTemp = ' '; //���������� �� ���, ����� ������������ ���� ������. Break'� ��� ���, ��� ��� �� switcha �� �������, � �������� � case' ':
				//� ��������� ������������ �����. ��� ���� ���� ������ ������ �� ��������� � Text ��������� ����� bFileEndSpace.
			}
			else break;
		case ' ':
		case '1':
		case '*':
			if (bTypingWord) //���� �� ����� ��������� �����
			{
				
				bTypingWord = false; //���� ����� ��������
				FindWords(&vwDict, &vwWords, &viWord, iters, &iters2); //� ������ vwWords ��������� ����� �� ����� newDictName,
																		 //��������������� ������������������ ���� viWord.
									//��������� vwUsedWords ���������� ��� ����, ����� ���������� ��������� ����� ��� ����������� ���������� ����������
				sort(vwWords.begin(),vwWords.end()); //����������� ����� (� ������ ���� ����������). ���������� ���������� ��������������
													 //������������� � ������ WORD ���������� <
				/*for (int j = 0; j< vwWords.size(); j++)
				{
					cout<<vwWords[j].GetStr()<<endl;
					cout<<vwWords[j].WasUsed()<<endl;
				}*/
				//���� '*' - ������������ ������� ����.
				int iWordNumber = 0;
				while (chTemp=='*')
				{
					if (++iWordNumber==vwWords.size()) iWordNumber=0;
					chTemp = input[++k];
				}

				//update
				vwDict[vwWords[iWordNumber].GetIter()].SetFreq(1+vwWords[iWordNumber].GetFreq());
				vwDict[vwWords[iWordNumber].GetIter()].Used();
				vwDict[vwWords[iWordNumber].GetIter()].SetLast(k);
				//

				//Text += vwWords[iWordNumber].GetStr(); //��������� � ��������� ����� � ������ Text. � ����� ������ ��������� ������ Text ����� �������� � ���� "sms"
				cout<<vwWords[iWordNumber].GetStr();
				viWord.clear();
			}
			if (chTemp == ' ')
			{
				if (!bFileEndSpace) //���� ��� �� ��� ������������ ������, ������������ ��� ��������� ��������, ����� ����� ���������� �����
									//�� ����� �� ������, �� ���� ����������, �� *
				{
					//Text += ' ';
					cout<<' ';
					chTemp = input[++k];
				}
				break;
			}
			if (chTemp == '1') //���� ����������
			{
				int iSignNumber = 0;
				chTemp = input[++k]; //��������� ��������� ������
				while (chTemp=='*') //���� (� ����) ��� '*' - ���������� ����� ����������, ���������� � ������� cSings[] = {'.',',','?'}
				{
					if (iSignNumber==2) iSignNumber=0;
					else iSignNumber++;
					chTemp = input[++k];
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
	case 2: return (ch=='a')||(ch=='A')||(ch=='b')||(ch=='B')||(ch=='c')||(ch=='C');
	case 3: return (ch=='d')||(ch=='D')||(ch=='e')||(ch=='E')||(ch=='f')||(ch=='F');
	case 4: return (ch=='g')||(ch=='G')||(ch=='h')||(ch=='H')||(ch=='i')||(ch=='I');
	case 5: return (ch=='j')||(ch=='J')||(ch=='k')||(ch=='K')||(ch=='l')||(ch=='L');
	case 6: return (ch=='m')||(ch=='M')||(ch=='n')||(ch=='N')||(ch=='o')||(ch=='O');
	case 7: return (ch=='p')||(ch=='P')||(ch=='q')||(ch=='Q')||(ch=='r')||(ch=='R')||(ch=='s')||(ch=='S');
	case 8: return (ch=='t')||(ch=='T')||(ch=='u')||(ch=='U')||(ch=='v')||(ch=='V');
	case 9: return (ch=='w')||(ch=='W')||(ch=='x')||(ch=='X')||(ch=='y')||(ch=='Y')||(ch=='z')||(ch=='Z');
	}
	return false;
}

void FindWords(vector<MYWORD> *dict, 
			vector<MYWORD> *words, //���� ����� ������� ��������� �����
			vector<int> *buttons, //������������������ ���� (2-9) (������� ������)
			int *iters, //����� ��� ��������� ����� �����
			ITERS2 *iters2)
{
	
	words->clear();
	
	
	int its, ite;
	if ((*buttons)[0]==9) its = 22;
	if ((*buttons)[0]==8) its = 19;
	if ((*buttons)[0]==7) its = 15;
	if ((*buttons)[0]<7)  its = 3 * ((*buttons)[0]-2);
	
	if ((*buttons)[0]==9) ite = 26;
	if ((*buttons)[0]==8) ite = 22;
	if ((*buttons)[0]==7) ite = 19;
	if ((*buttons)[0]<7)  ite = 3 * ((*buttons)[0]-1);
	//cout<<"buttons: "<<(*buttons)[0]<<"  its: "<<its<<"  its: "<<ite<<endl;
	for (int i = iters[its]; i<iters[ite]; i++)
	{
		if ((*buttons).size()!=1)
		{
			bool bg1, bg2, bg3 = false, bg0, b79b;
			b79b = ((*buttons)[0] == 7)||((*buttons)[0] == 9);
			bg0 = ( iters[its] + iters2->m[its][(*buttons)[1]-2] <= i) && (i <  iters[its] + iters2->m[its][(*buttons)[1]-1]);
			bg1 = ( iters[its+1] + iters2->m[its+1][(*buttons)[1]-2] <= i) && (i <  iters[its+1] + iters2->m[its+1][(*buttons)[1]-1]);
			bg2 = ( iters[its+2] + iters2->m[its+2][(*buttons)[1]-2] <= i) && (i <  iters[its+2] + iters2->m[its+2][(*buttons)[1]-1]);
			if (b79b) bg3 = ( iters[its+3] + iters2->m[its+3][(*buttons)[1]-2] <= i) && (i <  iters[its+3] + iters2->m[its+3][(*buttons)[1]-1]);
			
			/*cout<<"buttons01: "<<(*buttons)[0]<<(*buttons)[1]<<endl;
			cout<<"i: "<<i<<endl;
			cout<<"iters[its]: "<<iters[its]<<endl;
			cout<<"iters[ite]: "<<iters[ite]<<endl;
			cout<<"iters2->m[its][(*buttons)[1]-2]: "<<iters2->m[its][(*buttons)[1]-2]<<endl;
			cout<<"iters2->m[its+1][(*buttons)[1]-2]: "<<iters2->m[its+1][(*buttons)[1]-2]<<endl;
			cout<<"iters2->m[its+2][(*buttons)[1]-2]: "<<iters2->m[its+2][(*buttons)[1]-2]<<endl;

			cout<<"b79b "<<b79b<<endl;
			cout<<"bg0 "<<bg0<<endl;
			cout<<"bg1 "<<bg1<<endl;
			cout<<"bg2 "<<bg2<<endl;
			cout<<"bg3 "<<bg3<<endl;*/
			if ((b79b&&(bg0||bg1||bg2||bg3))  ||  (!b79b&&(bg0||bg1||bg2)))
			{
				MYWORD wTemp;
				bool bCoresp = true; //������������� ��� ��� ����� ������������������ ����
				//���� ����� ����� �� ����� ����� ������������������ ��������� ������������� ����, �� ����� bCoresp = false
				if ((*dict)[i].GetStr().length() != (*buttons).size()) continue;
		
				//��������� ������������ ����� ������������������ ����
				unsigned int n;
				for (n = 0; (bCoresp)&&(n<(*dict)[i].GetStr().length()); n++)
					bCoresp = bCoresp && IsCharButton((*dict)[i].GetStr()[n],(*buttons)[n]);
				//cout<<"n = "<<n<<endl;
				//n - ������� � �����, ��� ������� �� ������� ����� � �����.
				if (bCoresp) //���� ��������
				{
					wTemp.SetStr(&(*dict)[i].GetStr());
					wTemp.SetFreq((*dict)[i].GetFreq());
					wTemp.SetIter((*dict)[i].GetIter());
					if ((*dict)[i].WasUsed()) wTemp.Used();
						wTemp.SetLast((*dict)[i].GetLast());
					//���������, ��������� �� ��� ��� �����. �� ����, ���� ��� � ������� used.
				
					words->push_back(wTemp); //��������� � ������ words ������ ��� �������� ������, ��������������� ������ ���������� �����
				}
				else
				{
					bool flag = false;
					int itemp = i;
					while ((!flag)&&(i<iters[(*buttons)[0]-1]-1))
					{
						if ((*dict)[i+1].GetStr().size() < n+1) 
						{
							flag = true;
							break;
						}
						for (int h = n; h>=0; h--)
						{
							if ((*dict)[i+1].GetStr()[h] != (*dict)[itemp].GetStr()[h]) 
							{
								flag = true;
								break;
							}
						}
						if (flag) break;
							i++;
					}	
				}
			}
		}
	}
	
	if (words->size()==0)  //���� ������ �� �����. �� ������� ������ ������ ���� �� �����.
	{
		cout<<"ERROR. There are no appropriate words in the dictionary";
		exit(1);
	}
}

bool IsCorrect(char c)
{
	return (c==' ')||(c=='*')||((c-'0'>=0)&&(c-'0'<=9));
}

bool UpdateDict(vector<MYWORD> *dict, MYWORD *word)
{
	
	return true;
}

MYWORD::MYWORD()
{
	str = "";
	freq = -1;
	used = false; //���������� ����� �� ��������������
	lastmeeting = 0; //���� used == false, �������� lastmeeting �� ����� ��������
}

MYWORD::~MYWORD()
{
}

void MYWORD::SetStr(string *s)
{
	str = *s;
}

void MYWORD::SetFreq(int f)
{
	freq = f;
}

string& MYWORD::GetStr()
{
	return str;
}

int MYWORD::GetFreq()
{
	return freq;
}

bool operator<(MYWORD w1, MYWORD w2)
{
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

void MYWORD::Used()
{
	used = true;
}

bool MYWORD::WasUsed()
{
	return used;
}

int MYWORD::GetLast()
{
	return lastmeeting;
}

void MYWORD::SetLast (int c)
{
	lastmeeting = c;
}

void MYWORD::SetIter(int i)
{
	iter = i;
}

int MYWORD::GetIter()
{
	return iter;
}

void MYWORD::ClearUsed()
{
	used = false;
}