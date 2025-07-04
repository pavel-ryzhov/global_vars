#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
void FindWords(vector<MYWORD> *dict, vector<MYWORD> *words, vector<int> *buttons, vector<MYWORD> *used, int *iters);

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
	vector<MYWORD> vwUsedWords; //�������� ��� ��������� ������������� �����. 
	vector<MYWORD> vwWords; //�������� ��������� � ������� �����
	vector<MYWORD> vwDict;
	//string Text; //���� ������������ ������ ������������� �������������. � ����� ���������� ���� ������ ������������ � ���� "sms"
	string input;

	int iters[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1}; 

	//Text.clear(); 
	string str;
	char ch;
	int fr;
	MYWORD wTemp;

	cin>>N;
	for (int i = 0; i<N; i++)
	{
		cin>>str;
		if ((str[0] >= 'w') && (iters[7] == -1)) iters[7] = i;
		if ((str[0] >= 't') && (iters[6] == -1)) iters[6] = i;
		if ((str[0] >= 'p') && (iters[5] == -1)) iters[5] = i;
		if ((str[0] >= 'm') && (iters[4] == -1)) iters[4] = i;
		if ((str[0] >= 'j') && (iters[3] == -1)) iters[3] = i;
		if ((str[0] >= 'g') && (iters[2] == -1)) iters[2] = i;
		if ((str[0] >= 'd') && (iters[1] == -1)) iters[1] = i;
		if ((str[0] >= 'a') && (iters[0] == -1)) iters[0] = i;
	
		
		wTemp.SetStr(&str);
		cin>>fr;
		wTemp.SetFreq(fr);
		wTemp.SetIter(i);
		vwDict.push_back(wTemp);
	}
	iters[8] = vwDict.size();
	for (int i = 7; i>=0; i--)
	{
		if (iters[i] == -1) iters[i] = iters[i+1];
	}
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
	/*do
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
				FindWords(&vwDict, &vwWords, &viWord, &vwUsedWords, iters); //� ������ vwWords ��������� ����� �� ����� newDictName,
																		 //��������������� ������������������ ���� viWord.
									//��������� vwUsedWords ���������� ��� ����, ����� ���������� ��������� ����� ��� ����������� ���������� ����������
				sort(vwWords.begin(),vwWords.end()); //����������� ����� (� ������ ���� ����������). ���������� ���������� ��������������
													 //������������� � ������ WORD ���������� <

				//���� '*' - ������������ ������� ����.
				int iWordNumber = 0;
				while (chTemp=='*')
				{
					if (++iWordNumber==vwWords.size()) iWordNumber=0;
					chTemp = input[++k];
				}
				if (!UpdateDict(&vwDict, &vwWords[iWordNumber])) return 1; //��������� � ����� �������� ������� ���������� �����
				//Text += vwWords[iWordNumber].GetStr(); //��������� � ��������� ����� � ������ Text. � ����� ������ ��������� ������ Text ����� �������� � ���� "sms"
				cout<<vwWords[iWordNumber].GetStr();
				//
				for (vector<MYWORD>::iterator p = vwUsedWords.begin(); p<vwUsedWords.end();p++)
					if ((*p).GetStr() == vwWords[iWordNumber].GetStr()) 
					{
						p = vwUsedWords.erase(p);
						p--;
					}
				vwUsedWords.push_back(vwWords[iWordNumber]); //������� � ������ �������������� ���� ����� ������ ��� ��������� �����
				//
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
	//cout<<Text<<endl;*/
	
	string news;
	for (int w = 0; w<200000; w++)
		news += "qwe";
	cout<<news;
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
			vector<MYWORD> *used,
			int *iters) //����� ��� ��������� ����� �����
{
	
	words->clear();
	
	string str;
	for (int i = iters[(*buttons)[0]-2]; i<iters[(*buttons)[0]-1]; i++)
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
			//���������, ��������� �� ��� ��� �����. �� ����, ���� ��� � ������� used.
			for (int j = (*used).size() - 1; j>=0; j--)
			{
				if ((*used)[j].GetStr() == (*dict)[i].GetStr()) //��� ���������
				{
					wTemp.Used(); //������������� ���� "��������������". ����� �� ����� ����� ����� ������������ ������ ����������
					wTemp.SetLast((*used).size() - j); //��������� ���������� � ���, ��� ����� ��� ����� ���������. ����� ������������� ��� ����������
					break;
				}
			}
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
					if ((*dict)[i+1].GetStr()[h] != (*dict)[i].GetStr()[h]) 
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
	(*dict)[(*word).GetIter()].SetFreq(1+(*word).GetFreq());
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
		return w1.lastmeeting < w2.lastmeeting;
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