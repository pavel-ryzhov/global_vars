#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


//������ ������ WORD �������� ����� � ����������� �������������� ���������� (��� ���������� � ��);
class WORD
{
public:
	WORD();
	~WORD();
	void SetStr(string *);
	void SetFreq(int);
	void SetPos(ios::pos_type);
	friend bool operator< (WORD,WORD); //���������� ����� ��� ����������
	string& GetStr();
	int GetFreq();
	ios::pos_type GetPos();
	void Used(); //��������� �����, ������������, ��� ����� ����� ��� ���������
	bool WasUsed(); //���������� �������� ����� �����
	void SetLast(int c); //������������� ���������� �� ���� �������, ����� ����� ����� � ��������� ��� ���������
	int GetLast();
private:
	string str; //�����
	int freq; //��� �������
	ios::pos_type position; //��� ��������� � �����
	int lastmeeting; //���������� �� ���������� �����. ��������� - ���������� ����� � ����� ���������� ��������� ������ ����� � ������� UsedWords
	bool used; //����, �������������� �� ����� ����� ��� ���
};




/* CheckFile()
�������� ����� �������. 
���� ���� ����������, ���������� true, � N - ���������� ���� � �������, � input - ��������� ������ ����� (���� ������������)
���� ���� �� ����������, ���������� false
*/
bool CheckFile(char *filename, int *N, string *input);

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
���������� � ������ words �����, ��������� � ����� filename.
��������� ���������� � ������ ������������ ������, ��������������� ������� ������������ ��������� �����.
*/
void FindWords(char *filename, vector<WORD> *words, vector<int> *buttons, vector<WORD> *used);

/*UpdateFile()
��������� � ����� filename �������� ������� ����� word.
*/
bool UpdateFile(char *filename, WORD *word);

/* IsCorrect()
���������� true, ���� ch - ��� ���� ����� (1-9), ���� ������ '*', ���� ������.
*/
bool IsCorrect(char ch);

/* OutputFile()
������� str � ����.
*/
bool OutputFile(char *filename, string* str);

/*CopyFile()
�������� ���������� ����� fromName � ���� toName.
*/
bool CopyFile(char *fromName, char *toName);

int main()
{
	char   DictName[] = "dict";
	bool bTypingWord = true; //bTypingWord == true, ���� ���� ���� �����
	char cSings[] = {'.',',','?'},
		 chTemp;
	int N; //���������� ���� � �������
	vector<int> viWord; //�������� �����, �������� �������������
	vector<WORD> vwUsedWords; //�������� ��� ��������� ������������� �����. 
	vector<WORD> vwWords; //�������� ��������� � ����� �����
	string Text; //���� ������������ ������ ������������� �������������. � ����� ���������� ���� ������ ������������ � ���� "sms"
	string input;


	Text.clear(); 
	//--------------------------
	//�������� ��� �� ����������, ��� ������� ������ �������� �� � ����� �������, � � ����������
	ofstream fout(DictName);
	if (!fout)
	{
		cout<<"Couldnt create "<<DictName<<endl;
		return 1;
	}
	string str;
	char ch;
	int fr;
	cin>>N;
	fout<<N<<endl;
	for (int i = 0; i<N; i++)
	{
		cin>>str;
		cin>>fr;
		fout<<str<<' '<<fr<<endl;
	}
	ch = getchar();
	str.clear();
	while((ch=getchar())!=10)
	{
		str += ch;
		//if (ch==10) break;
	}

	fout<<str<<endl;
	fout.close();
	//--------------------------

	if (!CheckFile(DictName,&N,&input))
	{
		return 1;
	}
	//������ � ������ input ���������� ������������������ ��������, ��������������� ����� ������������
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
				FindWords(DictName, &vwWords, &viWord, &vwUsedWords); //� ������ vwWords ��������� ����� �� ����� newDictName,
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
				if (!UpdateFile(DictName, &vwWords[iWordNumber])) return 1; //��������� � ����� �������� ������� ���������� �����
				Text += vwWords[iWordNumber].GetStr(); //��������� � ��������� ����� � ������ Text. � ����� ������ ��������� ������ Text ����� �������� � ���� "sms"
				vwUsedWords.push_back(vwWords[iWordNumber]); //������� � ������ �������������� ���� ����� ������ ��� ��������� �����
				viWord.clear();
			}
			if (chTemp == ' ')
			{
				if (!bFileEndSpace) //���� ��� �� ��� ������������ ������, ������������ ��� ��������� ��������, ����� ����� ���������� �����
									//�� ����� �� ������, �� ���� ����������, �� *
				{
					Text += ' ';
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
				Text += cSings[iSignNumber]; //������� � Text ��������� ���� ����������
			}
			break;
		default:
			cout<<"wrong symbol"<<endl;
			return 1;
			break;
		}
	} while (k<input.size()); //� ��� ������������ ��� ������. 
	cout<<Text<<endl;
	if (!OutputFile("sms",&Text)) return 1; //������� ����� ��� � ���� "sms"
	return 0;
}

bool CheckFile(char *filename, int *N, string *input)
{
	ifstream fin(filename);
	if (!fin)
	{
		cout<<"ERROR. Couldn't open file"<<endl;
		return false;
	}
	string strN;
	fin>>strN;
	if (!IsStrNum(&strN)) //� ������ ������ ����� ������� ������ ���� �����
	{
		cout<<"ERROR. Bad file. First string is not a positive number"<<endl;
		//getchar();
		return false;
	}
	fin.seekg(0);
	fin>>*N; //��������� ����� �� ������ ������ �����. �� ������� ��� ���������� ���� � �������

	for (int i = 0; (!fin.eof())&&(i<*N); i++ )
	{
		fin>>strN; //��� �����
		if ((!(fin>>strN))||(!IsStrNum(&strN))) //��������� ��, ��� ����� ����� �����. � ����� �� ���������, ����� �� ��� (� ������ ���� ������ - ��� �������)
		{
			cout<<"ERROR. Bad file."<<endl<<"String number: "<<i<<endl;
			//getchar();
			return false;
		}
	}
	fin.get(); //������� �� ����� ������.

	//����������� ��������� ��������� ������, ������� ��������, ���������� �� ��� �������
	char ch; 
	while ((!fin.eof())&&(IsCorrect(ch = fin.get())))
	{
		*input += ch;
	}
	//cout<<"input = "<<*input<<endl;
	//cout<<"Good file"<<endl;
	
	fin.close();
	return true;
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

void FindWords(char *filename, 
			vector<WORD> *words, //���� ����� ������� ��������� �����
			vector<int> *buttons, //������������������ ���� (2-9) (������� ������)
			vector<WORD> *used) //����� ��� ��������� ����� �����
{
	ifstream in(filename);
	if (!in)
	{
		cout<<"Couldn't open file. FindWords"<<endl;
		exit(1);
	}
	words->clear();
	
	ios::pos_type posTemp; //������� � �����, � ������� ���������� ������ �����
	int N;
	in>>N; //N - ���������� ���� � �������
	string str;
	for (int i = 0; i<N; i++)
	{
		int a;
		WORD wTemp; //������, �������� ����� (������ string) � ����������� �������������� ����������
		posTemp = in.tellg(); //���������� ������� � �����
		in>>str; //��������� �����
		bool bCoresp = true; //������������� ��� ��� ����� ������������������ ����

		//���� ����� ����� �� ����� ����� ������������������ ��������� ������������� ����, �� ����� bCoresp = false
		if (str.length() != (*buttons).size()) bCoresp = false;

		//��������� ������������ ����� ������������������ ����
		for (unsigned int i = 0; (bCoresp)&&(i<str.length()); i++)
			bCoresp = bCoresp && IsCharButton(str[i],(*buttons)[i]);
		if (bCoresp) //���� ��������
		{
			//���������, ��������� �� ��� ��� �����. �� ����, ���� ��� � ������� used.
			for (int i = (*used).size() - 1; i>=0; i--)
			{
				if ((*used)[i].GetStr() == str) //��� ���������
				{
					wTemp.Used(); //������������� ���� "��������������". ����� �� ����� ����� ����� ������������ ������ ����������
					wTemp.SetLast((*used).size() - i); //��������� ���������� � ���, ��� ����� ��� ����� ���������. ����� ������������� ��� ����������
					break;
				}
			}
			wTemp.SetStr(&str); //��������� ���� �����
			in>>a; 
			wTemp.SetFreq(a); //�������
			wTemp.SetPos(posTemp); //� ������� � �����. ����� ����� ������������� ��� ���������� ������� � �����
			words->push_back(wTemp); //��������� � ������ words ������ ��� �������� ������, ��������������� ������ ���������� �����
		}
		else in>>a; //���� ����� �� �������, ��������� �������, ����� ��������� ������ � ���������� �����
	}
	if (words->size()==0)  //���� ������ �� �����. �� ������� ������ ������ ���� �� �����.
	{
		cout<<"ERROR. There are no appropriate words in the dictionary";
		exit(1);
	}
	in.close();
}

bool IsCorrect(char c)
{
	return (c==' ')||(c=='*')||((c-'0'>=0)&&(c-'0'<=9));
}

bool OutputFile(char *filename, string *str)
{
	ofstream fout(filename);
	if (!fout)
	{
		cout<<"Couldn't open file "<<filename<<endl;
		return false;
	}
	fout<<*str;
	fout.close();
	return true;
}

bool UpdateFile(char *filename, WORD *word)
{
	//������� ��������� ���� "temp", ��������� ��� � ����� ��������� ������� ����� word, ������� ������ ����, � ���� ��������������� � dict
	ofstream fout("temp");
	ifstream fin(filename);
	if (!fin)
	{
		cout<<"couldn't open file "<<filename;
		return false;
	}
	if (!fout)
	{
		cout<<"couldn't open file "<<"temp";
		return false;
	}
	string str;
	char ch;
	//� ������� word �������� ������� � �����, � ������� ��������� ������ �����. ������� ������ ����������� �������� ���������� ����� �� ���� �������
	while ((!fin.eof())&&(fin.tellg()<=word->GetPos()))
	{
		ch = fin.get();
		fout.put(ch);
	}
	if (!fin.eof())
	{
		fin>>str>>str;
		fout<<word->GetStr()<<' '<<word->GetFreq() + 1; //������ ����� � ����� �������
	}
	else return false;
	//�������� ���������� ����� �����
	while (!fin.eof())
	{
		ch = fin.get();
		if (!fin.eof())
		fout.put(ch);
	}
	fin.close();
	fout.close();
	if (!(remove(filename)==0)) //������� ������
	{
		cout<<"ne ydalen"<<endl;
		return false;
	}
	rename("temp",filename); //��������������� �����

	return true;
}

WORD::WORD()
{
	str = "";
	freq = -1;
	position = 0;
	used = false; //���������� ����� �� ��������������
	lastmeeting = 0; //���� used == false, �������� lastmeeting �� ����� ��������
}

WORD::~WORD()
{
}

void WORD::SetStr(string *s)
{
	str = *s;
}

void WORD::SetFreq(int f)
{
	freq = f;
}

void WORD::SetPos(ios::pos_type pos)
{
	position = pos;
}

string& WORD::GetStr()
{
	return str;
}

int WORD::GetFreq()
{
	return freq;
}

ios::pos_type WORD::GetPos()
{
	return position;
}

bool operator<(WORD w1, WORD w2)
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
	
	//���� ������� ���������� � �� ���� �� ���� �� �����������, �� ��������� ������� ��� ���� (�� ��������).
	return w1.freq > w2.freq;
}

void WORD::Used()
{
	used = true;
}

bool WORD::WasUsed()
{
	return used;
}

int WORD::GetLast()
{
	return lastmeeting;
}

void WORD::SetLast (int c)
{
	lastmeeting = c;
}
