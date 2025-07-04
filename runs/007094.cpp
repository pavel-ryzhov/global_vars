#include <iostream>
using namespace std;

class word
{
 public:
  char mention[21];
  int freq;
  bool isOk;
  int length;
  long prior;
};

long N,lcount=0;

bool compareMap(char c, char num)
{
 bool fl=false;
 switch (num)
 {
  case '2':
      if ((c=='a') || (c=='b') || (c=='c'))
      { 
       fl=true;
      }
      break; 
  case '3':
      if ((c=='d') || (c=='e') || (c=='f'))
      { 
       fl=true;
      } 
      break;
  case '4':
      if ((c=='g') || (c=='h') || (c=='i'))
      { 
       fl=true;
      } 
      break;
  case '5':
      if ((c=='j') || (c=='k') || (c=='l'))
      { 
       fl=true;
      }
      break; 
  case '6':
      if ((c=='m') || (c=='n') || (c=='o'))
      { 
       fl=true;
      } 
      break;
  case '7':
      if ((c=='p') || (c=='q') || (c=='r') || (c=='s'))
      { 
       fl=true;
      } 
      break;
  case '8':
      if ((c=='t') || (c=='u') || (c=='v'))
      { 
       fl=true;
      } 
      break;
  case '9':
      if ((c=='w') || (c=='x') || (c=='y') || (c=='z'))
      { 
       fl=true;
      } 
      break;
  
 }
 if (fl==true)
 {
  return true;
 } 
 else
 {
  return false;
 }
}

void decodeword(char *p, word *mas)
{
 int wordl=0,stars=0,wordlr=0,dictl=0,quantOk=0;
 char znak[1000]={0};
 bool prepin=false;
 bool len=true;
 long i=80000;
 long onecnt=0;
 lcount++;
 for(long j=0;j<80000;j++)
 {
  if (p[j]=='1')
  {
   prepin=true;
   onecnt++;
  }
 }
 long all=onecnt; 
 onecnt--;
 while((len)&&(i>=0))
 {
  if (p[i]!=0)
  {
   if (p[i]=='1')
   {
    znak[onecnt]='.';
    if (onecnt>0)
    {
     onecnt--;
    }
   }
   else if (p[i]=='*')
   {
    if (p[i-1]=='1')
    {
     znak[onecnt]=',';
     if (onecnt>0)
     {
      onecnt--;
     }
     i--;
    }
    else if (p[i-2]=='1')
    {
     znak[onecnt]='?';
     if (onecnt>0)
     {
      onecnt--;
     }
     i=i-2;
    }
    else
    {
     stars=1;
     int j=i-1;
     while(p[j]=='*')
     {
      stars++;
      j--;
     }
     wordlr=j+1;
     len=false;
    }
   }
   else
   {
    wordlr=i+1;
    len=false;
   }
  } 
  i--;
 }
 for(int j=0;j<N;j++)		
 {

   if (mas[j].length==wordlr)
   {
    bool flag=true;
    int i=0;
	 while((flag)&&(i<wordlr))		
	 {
			if(!compareMap(mas[j].mention[i], p[i]))
			{
				flag=false;	
			}
         i++;
	 }
    if (flag==true)
     {
     mas[j].isOk=true;
     quantOk++;
     }
   }
 }
 word *choice=new word[quantOk];
 int coun=0;
 for (int i=0;i<=N;i++)
 {
  if (mas[i].isOk==true)
  {
   choice[coun]=mas[i];
   coun++;
   
  }
 }
 if (quantOk!=1)
 {
  word pol;
  bool flsort=true;
  int i=0;
  while (flsort)
  {
   flsort=false;
   for(int j=0;j<quantOk-1;j++)
   {
    if (choice[j].freq<choice[j+1].freq)
    {
     flsort=true;
     pol=choice[j+1];
     choice[j+1]=choice[j];
     choice[j]=pol;
    }
    else if (choice[j].freq==choice[j+1].freq)
    {
     if (choice[j].prior<choice[j+1].prior)
     {
      flsort=true;
      pol=choice[j+1];
      choice[j+1]=choice[j];
      choice[j]=pol;
     }
     else if (choice[j].prior==choice[j+1].prior)
     {
      bool sortalph=true;
      int h=0;	
      while ((sortalph)&&(h<wordlr))
      {
       sortalph=false;
       if (choice[j].mention[h]>choice[j+1].mention[h])
       {
        pol=choice[j+1];
        choice[j+1]=choice[j];
        choice[j]=pol;
        sortalph=true;
        std::cout<<choice[j].mention<<' '<<choice[j+1].mention<<endl;
       }
       h++;  
      }
     } 
    }
   }
  i++;
  }
  
 }
 int v=0;
 bool equpr=true;
 while ((equpr)&&(v<N))
 {
  if (mas[v].isOk==true)
  {
   mas[v].isOk=false;
   bool equ=true;
   int j=0;
   while ((equ)&&(j<wordlr))
   {
    if (mas[v].mention[j]!=choice[stars].mention[j])
    {
     equ=false;
    } 
    j++;
   }
   if (equ)
   {
    equpr=false;
    mas[v].freq++;
    mas[v].prior=lcount;
   }
  }
  v++;
 } 
 std::cout<<choice[stars].mention;
 if (prepin)
 {
  for(int i=0;i<all;i++)
  {
   std::cout<<znak[i];
  }
  std::cout<<' ';
 }
 else
 {
  std::cout<<' ';
 }
 delete []choice;
 p=0;
};
int main()
{
 bool pr;
 char x[80000]={0},end;
 int t[5];
 std::cin>>N;
 word *mas=new word[N];
 for (int i=0;i<N;i++)
 {
  pr=true;
  std::cin>>mas[i].mention>>mas[i].freq;
  mas[i].isOk = false;
  mas[i].prior = 0;
  int l=0;
  while((pr)&&(l<21))
   {
     if (mas[i].mention[l]==0)
     {
      mas[i].length=l;
      pr=false;
     }
     l++;
   }
 }
 while (std::cin>>x)
 {
  if (std::cin.get()=='\n')
  {
   decodeword(x,mas);
   break;
  }
  else
  { 
   decodeword(x,mas);
   for (int i=0;i<80000;i++)
   {
    x[i]=0;
   }
  }
 }
 delete []mas;
 std::cout<<endl;
 return 0;
}
