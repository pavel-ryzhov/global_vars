#include <iostream> 
#include <vector>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>
#include <time.h>
using namespace std;

struct words // ��������� ��� �������� ������������ �����
{
	char word [21]; // �����
    char  number [21]; // ���������� ����� � �9
	int intensify; // ������������� �����
};

struct kt // ��������� - �������, �������� � ���� ���������� 
{
	char number[21]; // ���������� �������
	int DictID; // ���������� ����� ������, ��� ���������� �������
};

struct box // ��������� "����� ��� ��������"
{
	words ** T9Word;
	int count;
};


class T9class
{
 private:
  unsigned int WCount,GrCount; // ��������� �������� ���������� ���� � �������, � ��� �� ��������� � ����������� �����
  char * CmdLine,PunktMarks[3]; // ��������� ����� �����, ��������� ��� �������� ��������� ������ -> �.�. ������ ������������ ��� ������
  vector <words> dictonary; // ���������� �������������� ��� �������� �����, ������ � ���� �� ������������� �����
  box * GrDict; // ���� ��� �������� ���� �� ����������� �������
  vector <kt> katalog; // ������������ ������, ��� �������� ��������

 public:
  T9class(); // �����������
  bool Input();//����� ������������ ������ �� �����
  void WordsAnalysis();//����� ������� ����������� ����, � ��� ��������� ���������� ��� ������� �����, � ��� �� ����� ����������� � "���� ��� ��������"
  void WordFreqUp(int section, int number);
  bool Output();//����� ���������� � ���� 
};


T9class::T9class()
{
	PunktMarks[0]='.'; //
	PunktMarks[1]=','; // ������� ������ �������������� ������
	PunktMarks[2]='?'; //
	CmdLine = new char [100500]; // ������ ��� �������� ������ ������� �������������
	GrDict = new box[50000]; // ���� ��� �������� ���� �� �����������
	GrCount = 0; // ������������� �������� �����
}

bool T9class::Input()
{
	words structbuf;// ��������� ��������� ��� �������� ����������� ������
	char tempbuf[30],chislo[6];// ��������� ����������� ��� ����������, � ������������ �������� � ����� ���������� ���� � ������� ,������� ������������� ����
	cin.getline(tempbuf,30); // ��������� ���������� ���� � �������
	WCount=atoi(tempbuf); // ������� �������� � �����
	if (WCount<3 || WCount>50000) // �������� �� ���������� ���� � �������
	{
		return false;
	}
	for (int i=0;i<WCount;i++) // ���������� ���� �� �������
	{
		cin.getline(tempbuf,30); // ��������� ����� , �� 20 ��������, ��� �� �������
		for (int j=0;j<strlen(tempbuf);j++)
		{
			if (tempbuf[j]!=' ')
				structbuf.word[j]=tempbuf[j];
			else
			{
				structbuf.word[j]='\0';
				j++;
				for (int k=0;j<strlen(tempbuf);k++,j++)
				{
						chislo[k]=tempbuf[j];
				}
				break;
			}
		}
		structbuf.intensify = atoi(chislo); // ������� ������� ����� �� ��������, � �����
		if (structbuf.intensify < 1) // �������� �������������
			structbuf.intensify = 1;
		if (structbuf.intensify > 1000) // ��� ��
			structbuf.intensify = 1000;
		dictonary.push_back(structbuf); // ��������� � ������������������� ������� �����...
	}
	cin.getline(CmdLine,100000); // ��������� ��������� ������	
	WordsAnalysis();// ������ ������� �� ������ �������, ����� � ���������� �������� ����� ��������������� �� �������, �������� � ��������
	return true;
}


void T9class::WordsAnalysis()
{
	kt buf; // �����, ������������ ��� ���������� �������� ���������� , ����� ����������� � � �������
	bool test = false; // ������� ���������-����, ���������� ��� ��������� � "���� � ��������"
	
	for (int i=0;i<WCount;i++) // ��������� ���������� �� ������
	{
		for (int j=0;j<strlen(dictonary[i].word);j++) // ����������� ����� �����������
		{
			switch (dictonary[i].word[j])
			{
			 case 'a':
			 case 'b':
			 case 'c':
				 dictonary[i].number[j]='2';
			 break;
			 
			 case 'd':
			 case 'e':
			 case 'f':
				 dictonary[i].number[j]='3';
			 break;

			 case 'g':
			 case 'h':
			 case 'i':
				 dictonary[i].number[j]='4';
			 break;

			 case 'j':
			 case 'k':
			 case 'l':
				 dictonary[i].number[j]='5';
			 break;

			 case 'm':
			 case 'n':
			 case 'o':
				 dictonary[i].number[j]='6';
			 break;

        	 case 'p':
			 case 'q':
			 case 'r':
			 case 's':
				 dictonary[i].number[j]='7';
			 break;

			 case 't':
			 case 'u':
			 case 'v':
				 dictonary[i].number[j]='8';
			 break;

			 case 'w':
			 case 'x':
			 case 'y':
			 case 'z':
				 dictonary[i].number[j]='9';
			 break;
			}
			dictonary[i].number[j+1]='\0'; // ��������� ���� ������, ����������� ��� ������ ����������� �������...
		}
	}

	for (int i=0;i<WCount;i++) // ������������� ���� �� �������
	{        
		    test = false;
			if (i==0) // 1� �����, ����������� 1 ������
			{
		     	 GrDict[GrCount].T9Word = new words *[100];
				 GrDict[GrCount].T9Word[0]=&dictonary[i];
				 GrDict[GrCount].count=1;
				 strcpy(buf.number,dictonary[i].number);
				 buf.DictID=GrCount;
				 katalog.push_back(buf);	
				 GrCount++;
				 test = true;
			}
			else
			{
			 for (int j=0;j<GrCount;j++) // ���������� ����� ����������� �� �������
			 {
				if (strcmp(dictonary[i].number,katalog[j].number)==0 ) //�������� �������������� �����, � ����������� ������, � ������ �����, ��������� ����
				{
					if ((dictonary[i].intensify==GrDict[j].T9Word[GrDict[j].count-1]->intensify) || (dictonary[i].intensify<GrDict[j].T9Word[GrDict[j].count-1]->intensify) || (dictonary[i].intensify==1)) // ��������� ������������� ����� � ���������� �������������� � ������, ���� ��� ������, ��� ����� ����������,�� ��������� � �����
					{
						GrDict[j].T9Word[GrDict[j].count]=&dictonary[i];
						GrDict[j].count++;
					}
					else
					if (GrDict[j].count==1)// ���� � ������ �����  1 �����, � ��� �������������� ������ ����������, �� ������� ����������� � �����, ����� �������� �������
					 {
					 	GrDict[j].T9Word[GrDict[j].count]=&dictonary[i];
						GrDict[j].count++;
						if (GrDict[j].T9Word[0]->intensify<GrDict[j].T9Word[1]->intensify)
						 {
						  GrDict[j].T9Word[1]=GrDict[j].T9Word[0];
						  GrDict[j].T9Word[0]=&dictonary[i];
						 } 
					 }
					 else
					  if (dictonary[i].intensify>GrDict[j].T9Word[0]->intensify)// ���� ������������� ����� ������ ��� ��������� ������������� � ������, �� ��� ����� ���������� 1� � �������
					  {
					   GrDict[j].T9Word[GrDict[j].count]=&dictonary[i];
					   GrDict[j].count++;
					   for (int ii=GrDict[j].count-1;ii>0;ii--)
					   {
					    GrDict[j].T9Word[ii]=GrDict[j].T9Word[ii-1];
					   }
					   GrDict[j].T9Word[0]=&dictonary[i];
					  }
					  else
					   for (int k=0;k<GrDict[j].count-1;k++) // ���� ���������� ������, ���� �������� ���� �����
					   {												
						 if ((dictonary[i].intensify>GrDict[j].T9Word[k+1]->intensify && dictonary[i].intensify<GrDict[j].T9Word[k]->intensify) || (dictonary[i].intensify>GrDict[j].T9Word[k+1]->intensify && dictonary[i].intensify==GrDict[j].T9Word[k]->intensify)) //�������
						 {
							GrDict[j].T9Word[GrDict[j].count]=&dictonary[i];
					        GrDict[j].count++;
							for (int ii=GrDict[j].count-1;ii>k+1;ii--)
							{
								GrDict[j].T9Word[ii]=GrDict[j].T9Word[ii-1];//�������� ������
							}
							GrDict[j].T9Word[k+1]=&dictonary[i];//���������
							break;
						 } 
					   }
			    	test = true; // ������ ����, ��� ���� ��� �� ������� � ���������� �����
					break;
				}
			 }		 
			if (test==false) // ���� ����� �� ���� �������� � ������, �� ��������� ����� ������
			 {
			  GrDict[GrCount].T9Word = new words * [100];
              GrDict[GrCount].T9Word[GrDict[GrCount].count]=&dictonary[i];
			  GrDict[GrCount].count=1;
			  strcpy(buf.number,dictonary[i].number);
			  buf.DictID=GrCount;
			  katalog.push_back(buf);		 
			  GrCount++;
			 }
		    }
    }
}

void T9class::WordFreqUp(int section, int number) // ������� �������� ������� �����, � ��� �� �������� ������ ������������ ������
{
	words * buf;
	GrDict[section].T9Word[number]->intensify=GrDict[section].T9Word[number]->intensify+1;
	if (GrDict[section].T9Word[number]->intensify>GrDict[section].T9Word[0]->intensify || GrDict[section].T9Word[number]->intensify==GrDict[section].T9Word[0]->intensify)
	{
		buf = GrDict[section].T9Word[number];
		for (int i=number;i>0;i--)
		{
		  GrDict[section].T9Word[i]=GrDict[section].T9Word[i-1];
	    }
		 GrDict[section].T9Word[0]=buf;
	}
	else
	for (int i=1;i<number;i++)
	{
		if (GrDict[section].T9Word[number]->intensify>GrDict[section].T9Word[i]->intensify || GrDict[section].T9Word[number]->intensify==GrDict[section].T9Word[i]->intensify)
		{
			buf = GrDict[section].T9Word[number];
			for (int j=number;j>i;j--)
			{
				GrDict[section].T9Word[j]=GrDict[section].T9Word[j-1];
			}
			GrDict[section].T9Word[i]=buf;
			break;
		}
	}
	
}


bool T9class::Output() // ������� ���������� � ����, � �� ����, � ��������� ��������� ������ =) 
{
	int count=0,starscount=0; // �������� ������������ � ��������� ��������� �����, �� ��������; ��� �� ������� ���������� * ����� �����/1 
	char * com = new char [21];// ������������ ������ ��������� �������, ������ �� ������ ����� 
 
	for (int i=0;i<=strlen(CmdLine);i++)
	{	
		 if ( (CmdLine[i]!='*') && (CmdLine[i]!=' ') && (CmdLine[i]!='1') && (CmdLine[i]!='\0'))
		 {
			com[count]=CmdLine[i];
			count++;
		 }
		 else
		 {
			com[count]='\0';
			
			if (CmdLine[i]=='*')
			{
				starscount++;
				for (int j=i+1;j<strlen(CmdLine);j++)
				{
					if (CmdLine[j]=='*')
						starscount++;
					if (CmdLine[j]=='\0' || CmdLine[j]=='1' || CmdLine[j]==' ')
						break;
				}
	  		    for(int j=0;j<GrCount;j++)
			    {
			     if ( strcmp(com ,katalog[j].number)==0)
			     {
				  cout << GrDict[katalog[j].DictID].T9Word[starscount]->word;
				  WordFreqUp(katalog[j].DictID,starscount);
			     }
			    }
				i=i+starscount;
				starscount=0;
			}
			else
			{
			  for(int j=0;j<GrCount;j++)
			  {
			   if ( strcmp(com ,katalog[j].number)==0)
			   {
				  cout << GrDict[katalog[j].DictID].T9Word[0]->word ;
				  GrDict[katalog[j].DictID].T9Word[0]->intensify=GrDict[katalog[j].DictID].T9Word[0]->intensify+1;
			   }
			  }
			}

			
			if (CmdLine[i]=='1')
			{
				i++;
			    if (CmdLine[i]=='*')
			    {
				 starscount++;
				 for (int j=i+1;j<strlen(CmdLine);j++)
				 {
					if (CmdLine[j]=='*')
						starscount++;
					if (CmdLine[j]=='\0' || CmdLine[j]=='1' || CmdLine[j]==' ')
						break;
				 }
				 cout << PunktMarks[starscount];
				 starscount--;
				 i=i+starscount;
				 starscount=0;
				}
				else
				{
					cout <<PunktMarks[0];
					i--;
				}
			}
		    if (CmdLine[i]==' ')
		     cout << ' ';
			count=0;
		 }
	}
 return 1;
}



int main()
{
  T9class work;
  if(work.Input())
   work.Output();
  return 0;
}