#define MAX_STR 20
#include <iostream>
#include <list>      
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;  

struct words
{
  char word [MAX_STR+1];
  int length;
  unsigned short int F; //частота
};

struct num
{
  int code [MAX_STR+1];
  int length;
  unsigned short int Priority;// число звездочек
};

void Get_Word ( words &Str)
{
  cin >> Str.word;
  cin >> Str.F;
  for (int i=0;i<=MAX_STR;i++)
  {
    if (Str.word[i]=='\0')
    {
      Str.length=i;
      break;
    }
  }
}

bool Get_Number ( num & Number, list <char> & Points) // 0 - есть еще, 1 - все
{
  char c;
  int i=0;
  while ((c=getchar())&& (c!=' ')&&(c!='*')&&(c!=EOF)&&(c!='1'))
  {
    if (c=='\n') c = getchar();
    Number.code[i]=(unsigned short int)c-0x30;
    i++;
  }
  Number.length=i;
  Number.Priority=0;
  if (c=='*')
  {
    Number.Priority=1;
    while ((c=getchar())&& (c!=' ')&&(c!=EOF)&&(c!='1'))
    {
      Number.Priority++;
    }
  }
  while ((c=='1'))
  {
    //cout << "points " << c << endl;
    int Point_Priority=0;
    while ((c=getchar())&&(c=='*'))
      Point_Priority++;
    //cout << "prior " << Point_Priority << endl;
    switch (Point_Priority)
    {
      //cout << "switch" << endl;
      case 0 :
	    Points.push_back('.');
	    break;
      case 1 :
	    Points.push_back(',');
	    break;
      case 2 :
	    Points.push_back('?');
	    break;
    }
  }
  
  if (c==EOF)
  {
    return true;
  }
  else
    return false;
}


void Print_Points (list <char> Points)
{
  
  if (!(Points.empty()))
  {
    //cout << "points" << endl;
    for(list< char>::iterator  i = Points.begin();  i != Points.end(); i++)
    {
      char value = *i;
      cout << value;
    }
  }
}


//можно ускорить по формуле через аски код!!!
int Char_To_Num (char c)
{
  switch (c)
  {
    case 'a' : case 'b' : case 'c' :
      return 2;
    case 'd' : case 'e' : case 'f' :
      return 3;
    case 'g' : case 'h' : case 'i' :
      return 4;
    case 'j' : case 'k' : case 'l' :
      return 5;
    case 'm' : case 'n' : case 'o' :
      return 6;
    case 'p' : case 'q' : case 'r' : case 's':
      return 7;
    case 't' : case 'u' : case 'v' :
      return 8;
    case 'w' : case 'x' : case 'y' : case 'z' :
      return 9;
  }
}

void Print_Word( words Str)
{
  for (int i=0;i<Str.length;i++)
    cout << Str.word[i];
  //cout << " " ;
}

void Print_Num (num Code)
{
    for (int i=0;i<Code.length;i++)
      cout << Code.code[i];
  cout << endl;
}

struct node
{
  list <words> Priority_List;
  node * Suns [10]; //по числу кнопок 9+1
};

class Word_Tree
{
  public:
    Word_Tree() //конструктор
    {
	Root = new node;
      	//if (!(Root = new node))  //хватает ли  памяти на новый узел
     	//exit(EXIT_FAILURE);
    }
    
    //удаляет поддерево заданного узла MyNode 
    void Delete_All ( node * My_Node )
	    {
	      if (My_Node !=NULL)
	      {
		for (int i=2;i<=9;i++)
		  Delete_All(My_Node->Suns[i]);
		delete My_Node;
		My_Node=NULL;
	      }
	    }
    
    ~Word_Tree()//деструктор
    {
      Delete_All( Root);
    }
    
    
    //добавить слово  в поддерево с указанным корнем MyNode на глубину Deep;
  void Add_Word_Node ( words Str , int Deep, node * My_Node)
  {
	if (Deep==Str.length) 
	{
	  Add_To_List_Dict (My_Node, Str);
	}
	 else 
	 {
	   //cout << Char_To_Num (Str.word[Deep]) << endl;
	   if (My_Node->Suns[Char_To_Num (Str.word[Deep])] ==NULL)
	   My_Node->Suns[Char_To_Num (Str.word[Deep])] = new node;
	   Add_Word_Node (Str, Deep+1, My_Node->Suns[Char_To_Num (Str.word[Deep])]);
	 }
	  //cout << "Sdd_Word_Node_end!" << endl;
	
  }
    
    //добавляет слово в словарь
    void Add_Word (words Str)
    {
    if (Root->Suns[Char_To_Num(Str.word[0])]==NULL)
      Root->Suns[Char_To_Num(Str.word[0])]= new node;
      Add_Word_Node (Str,1,Root->Suns[Char_To_Num(Str.word[0])]);
    }
    
    //ищет слово в поддереве с заданной глубиной
    void Find_Word_Node (num Code, int Deep, node * My_Node)
    {
      if (Deep ==Code.length) //последнюю букву сравнить осталось
      {
	      Find_In_List ( Code.Priority, My_Node->Suns[Code.code[Code.length-1]]);
      }
      else
      {
	Find_Word_Node (Code,Deep+1, My_Node->Suns[Code.code[Deep-1]]);
      }

    }
    
    //ищет слово по коду с  заданным приоритетом
    void Find_Word ( num & Code)
    {
      /*
      if (Code.code[Code.length-1]==1) //слово слилось со знаком препинания
      {
	cout << "слово слилось" << endl;
	Code.length--;
	int Point_Priority = Code.Priority;
	Code.Priority=0;
	Find_Word(Code);
	switch (Point_Priority)
	{
	  case 0 :
	    cout << '.';
	    break;
	  case 1 :
	    cout << ',';
	    break;
	  case 2 :
	    cout << '?';
	    break;
	}	
      }
      */
	Find_Word_Node (Code,2,Root->Suns[Code.code[0]]);
    }
    
  private:
    node * Root;
    
    
    //процедура добавления слова в список в зависимости от приоритета 
    //пока сохраняем словарь
    void Add_To_List_Dict (node * My_Node, words Str)
    {
      bool Success_Add=false;
      for(list< words>::iterator  i = My_Node->Priority_List.begin();  i != My_Node->Priority_List.end(); i++)
      {
           words  value =  *i;
	   if (Str.F > value.F)
	   {
	     My_Node->Priority_List.insert(i,Str);
	     Success_Add=true;
	     break;
	   }
      }
      if (!(Success_Add)) My_Node->Priority_List.push_back(Str);
    }

    //процедура добавления слова в список в зависимости от приоритета 
    //когда меняем приоритет
    void Add_To_List (node * My_Node, words Str)
    {
      bool Success_Add=false;
      for(list< words>::iterator  i = My_Node->Priority_List.begin();  i != My_Node->Priority_List.end(); i++)
      {
           words  value =  *i;
	   if (Str.F >= value.F)
	   {
	     My_Node->Priority_List.insert(i,Str);
	     Success_Add=true;
	     break;
	   }
      }
      if (!(Success_Add)) My_Node->Priority_List.push_back(Str);
    }

    //найти слово в списке
   words Find_In_List (unsigned short int Prior, node * My_Node)
   {     
     int k=0;
     words result;
     for(list< words>::iterator  i = My_Node->Priority_List.begin();  i != My_Node->Priority_List.end(); i++)
     {
       if (k==Prior) 
       {
	 result=*i;
	 words value = *i;
	 value.F=value.F++;
	 My_Node->Priority_List.erase(i);
	 Add_To_List (My_Node,value );
	 Print_Word(result);
	 return result;
       }
       k++;
     }
   }
};

int main ()
{
  int N; //число слов в словаре
  cin >> N;
  // заполняем словарь
  Word_Tree Dictionary;
  for (int i=1;i<=N;i++)
  {
    words Str;
    Get_Word(Str); //считали слово и его частоту
    Dictionary.Add_Word(Str);
   // cout << i << endl;
  }
  
  //считываем нажатые клавишы
  num Code;
  bool Is_End=false;
  int i=1;
  while ( !Is_End)
  {
    list <char> Points; //список следующих за словом знаково препинания
    Is_End=Get_Number(Code, Points);
    if (i!=1)
      cout <<" ";
    if (Code.length>0)
    {
      Dictionary.Find_Word(Code);
    }
    Print_Points(Points);
    Points.clear();
    i++;
  }
 // cout << endl;
}