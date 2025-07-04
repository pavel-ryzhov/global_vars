#include <iostream> 
#include <vector>
#include <stdlib.h>
#include <string>
//#include <conio.h>
#include <string.h>
#include <fstream>
#include <time.h>
using namespace std;

struct words // структура для хранения загруженного слова
{
	char word [21]; // слово
    char  number [21]; // комбинация слова в Т9
	int intensify; // интенсивность слова
};

struct kt // структура - каталог, хранящий в себе комбинацию 
{
	char number[21]; // комбинация клавишь
	int DictID; // порядковый номер группы, для комбинации клавишь
};

struct box // структура "ящика для хранения"
{
	vector <words> T9Word;
	int counts;
	bool sorted;
};


class T9class
{
 private:
  unsigned int WCount,GrCount; // перменная хранящая количество слов в словаре, а так же перменная с количеством групп
  char * CmdLine,PunktMarks[3]; // перменная имени файла, перменная для хранения командной строки -> т.е. команд пользователя при наборе
  vector <words> dictonary; // переменная использующаяся при загрузке файла, хранит в себе не упорядоченные слова
  box * GrDict; // ящик для хранения слов по комбинациям клавишь
  vector <kt> katalog; // динамический массив, для хранения каталога

 public:
  T9class(); // конструктор
  bool Input();//метод осуществляет чтение из файла
  void WordsAnalysis();//метод анализа загруженных слов, в нем находятся комбинации для каждого слова, а так же слова размещаются в "ящик для хранения"
  void WordFreqUp(int section, int number);
  void NumberSort(int section);
  bool Output();//метод сохранения в файл 
};


T9class::T9class()
{
	PunktMarks[0]='.'; //
	PunktMarks[1]=','; // Создаем массив пунктуационных знаков
	PunktMarks[2]='?'; //
	CmdLine = new char [100001]; // строка для хранения команд введенх пользователем
	GrDict = new box[50000]; // Ящик для хранения слов по комбинациям
	GrCount = 0; // инициализация счетчика групп
}

bool T9class::Input()
{
	words structbuf;// временная перменная для хранения загружаемых данных
	char tempbuf[30],chislo[6];// перменная необходимая для сохранения, и последующего перевода в число количества слов в словаре ,частоты использования слов

	cin.getline(tempbuf,30); // получение количества слов в словаре
	WCount=atoi(tempbuf); // перевод символов в число
	if (WCount<3 || WCount>50000) // проверка на количество слов в словаре
	{
		return false;
	}
	for (int i=0;i<WCount;i++) // считывание слов со словаря
	{
		cin.getline(tempbuf,30); // получение слова , до 20 символов, или до пробела
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
		structbuf.intensify = atoi(chislo); // перевод частоты слова из символов, в число
		if (structbuf.intensify < 1) // проверка интенсивности
			structbuf.intensify = 1;
		if (structbuf.intensify > 1000) // она же
			structbuf.intensify = 1000;
		dictonary.push_back(structbuf); // Добавляем в неотформатированный словарь слова...
	}
	cin.getline(CmdLine,100000); // получение командной строки	
	WordsAnalysis();// запуск функции на анализ словаря, после её выполнения получаем слова отсортированные по группам, алфавиту и частотам
	return true;
}


void T9class::WordsAnalysis()
{
	kt buf; // буфер, используется для временного хранения информации , перед добавлением её в каталог
	bool test = false; // булевая перменная-флаг, необходима при помещении в "ящик с группами"
	
	for (int i=0;i<WCount;i++) // разбиение информации по словам
	{
		for (int j=0;j<strlen(dictonary[i].word);j++) // анализируем слово посимвольно
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
			dictonary[i].number[j+1]='\0'; // добавляем нуль символ, необходимый при вызове стандартных функций...
		}
	}

	for (int i=0;i<WCount;i++) // распределение слов по группам
	{        
		    test = false;
			if (i==0) // 1е слово, добавляется 1 группа
			{
				 GrDict[GrCount].T9Word.push_back(dictonary[i]);
				 GrDict[GrCount].counts=1;
				 GrDict[GrCount].sorted=false;
				 strcpy(buf.number,dictonary[i].number);
				 buf.DictID=GrCount;
				 katalog.push_back(buf);	
				 GrCount++;
				 test = true;
			}
			else
			{
			 for (int j=0;j<GrCount;j++) // последущие слова проверяются по группам
			 {
				if (strcmp(dictonary[i].number,katalog[j].number)==0 ) //проверка принадлежности слова, к опредленной группе, в случае удачи, добавляем туда
				{
					 GrDict[j].T9Word.push_back(dictonary[i]);			
					 GrDict[j].counts++;
				     test = true; // ставим флаг, для того что бы перейти к следующему слову
					 break;
				}
			 }		 
			if (test==false) // если слово не было помещено в группу, то создается новая группа
			 {
              GrDict[GrCount].T9Word.push_back(dictonary[i]);
			  GrDict[GrCount].counts=1;
			  GrDict[GrCount].sorted=false;
			  strcpy(buf.number,dictonary[i].number);
			  buf.DictID=GrCount;
			  katalog.push_back(buf);		 
			  GrCount++;
			 }
		    }
    }
}

void T9class::NumberSort(int section)
{
 
	struct temp
	{
	 vector <words> sortdWord;
	};
	temp * buffer = new temp[1001];
	int c[1001],b=0;
	int k=1001;
	

	for (int i=0;i<k;i++)
		c[i]=0;
	for (int i=GrDict[section].counts-1;i>=0;i--)
	{
		c[GrDict[section].T9Word[i].intensify]=c[GrDict[section].T9Word[i].intensify]+1;
		buffer[GrDict[section].T9Word[i].intensify].sortdWord.push_back(GrDict[section].T9Word[i]);
	}
	for (int j=k-1;j>=0;j--)
		for (int i=c[j]-1;i>=0;i--)
		{
			GrDict[section].T9Word[b]=buffer[j].sortdWord[i];
			b++;
		}

 /*for (int i=0;i<GrDict[section].counts;i++)
 		cout << GrDict[section].T9Word[i].word << "\n";
 	getch();*/

	GrDict[section].sorted=true;
}

void T9class::WordFreqUp(int section, int number) // функция повышает частоту слова, а так же сдвигает список относительно частот
{
	words buf;
	GrDict[section].T9Word[number].intensify=GrDict[section].T9Word[number].intensify+1;
	if (GrDict[section].T9Word[number].intensify>GrDict[section].T9Word[0].intensify || GrDict[section].T9Word[number].intensify==GrDict[section].T9Word[0].intensify)
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
		if (GrDict[section].T9Word[number].intensify>GrDict[section].T9Word[i].intensify || GrDict[section].T9Word[number].intensify==GrDict[section].T9Word[i].intensify)
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


bool T9class::Output() // функция сохранения в файл, а за одно, и обработка командной строки =) 
{
	int count=0,starscount=0; // счетчики используемые в разбиение командной стрки, по командам; так же счетчик количества * после слова/1 
	char * com = new char [21];// максимальная длинна отдельной команды, исходя из длинны слова 
 
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
				  if (GrDict[katalog[j].DictID].sorted==false)
				   NumberSort(katalog[j].DictID);
				  
				  cout << GrDict[katalog[j].DictID].T9Word[starscount].word;
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
				  if (GrDict[katalog[j].DictID].sorted==false)
				   NumberSort(katalog[j].DictID);
				  cout << GrDict[katalog[j].DictID].T9Word[0].word ;
				  GrDict[katalog[j].DictID].T9Word[0].intensify=GrDict[katalog[j].DictID].T9Word[0].intensify+1;
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
 // getch();
  return 0;
}