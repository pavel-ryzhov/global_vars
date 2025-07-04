#include <iostream>
using namespace std;

class word
{
 public:
  char mention[21];
  int freq;
  long prior;
  int num;
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
void decodeword(char *p, word **mas, int stars, int wordlr)
{
 long dictl=0,quantOk=0,nm=0;
 lcount++;
 word max;
 word *choice=new word[50000];
 for(long j=1;j<=mas[wordlr-1][0].num;j++)		
 {
   bool flag=true;
   int i=0;
   while((flag)&&(i<wordlr))		
   {
    if(!compareMap(mas[wordlr-1][j].mention[i], p[i]))
    {
     flag=false;	
    }
    i++;
   }
   if (flag==true)
   {
    choice[quantOk]=mas[wordlr-1][j];
    if (quantOk==0)
    {
     max=choice[0];
    }
    if (choice[quantOk].freq>max.freq)
    {
     max=choice[quantOk];
     nm=quantOk;
    }
    else if (choice[quantOk].freq==max.freq)
    {
     if (choice[quantOk].prior>max.prior)
     {
      max=choice[quantOk];
      nm=quantOk;
     }
    }
    quantOk++;
   }
 }
 if (stars==0)
  stars=nm;
 else if (quantOk!=1)
 {
  word pol;
  bool flsort=true;
  long m=quantOk-1;
  while (flsort)
  {
   flsort=false;
   for(int j=0;j<m;j++)
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
    }
   }
  m--;
  } 
 }
 mas[wordlr-1][choice[stars].num].freq++;
 mas[wordlr-1][choice[stars].num].prior=lcount;
 std::cout<<choice[stars].mention;
 delete []choice;
 p=0;
};
int main()
{
 word **mas;
 bool pr;
 char str[100000]={0};
 long ln=0;
 int wln=0;
 char x[21]={0};
 std::cin>>N;
 mas=new word * [20];
 for (int i=0;i<20;i++)
  mas[i]=new word[50000];
 word inp;
 for (int i=0;i<N;i++)
 {
  pr=true;
  std::cin>>inp.mention>>inp.freq;
  inp.prior = 0;
  inp.num=i;
  int l=0;
  int length;
  while((pr)&&(l<=21))
   {
     if (inp.mention[l]==0)
     {
      length=l;
      pr=false;
     }
     l++;
   }
  mas[length-1][0].num++;
  mas[length-1][mas[length-1][0].num]=inp;
  mas[length-1][mas[length-1][0].num].num=mas[length-1][0].num;
 }
 long c=0;
 while (cin.get(str[c]))
 {
  if ((str[c]=='\n')&&(c!=0))
   break;
  c++;
 }
 ln=c-1;
 int j=0;
 int i=1;
 long st=0;
 while (i<=ln)
 {
  if (str[i]=='1')
  {
   if (x[0]!=0)
   {
    decodeword(x,mas,st,wln);
    j=0;
    for (int s=0;s<21;s++)
     x[s]=0;
    st=0;
    wln=0;
   }
   if ((str[i+1]=='*')&&(str[i+2]=='*'))
   {
    std::cout<<'?';
    i+=2;
   }
   else if (str[i+1]=='*')
   {
    std::cout<<',';
    i++;
   }
   else
   {
    std::cout<<'.';
   }
  }
  else if (str[i]=='*')
  {
   while (str[i]=='*')
   {
    st++;
    i++;
   }
   i--;
  }
  else if (str[i]==' ')
  {
   if (x[0]!=0)
   {
    decodeword(x,mas,st,wln);
    j=0;
    for (int s=0;s<21;s++)
     x[s]=0;
    st=0;
    wln=0;
    std::cout<<' ';
   }
   else
   {
    std::cout<<' ';
   } 
  }
  else if ((i==ln)&&(x[0]!=0))
  {
   x[j]=str[i];
   j++;
   wln=j;
   decodeword(x,mas,st,wln);
  }
  else
  {
   x[j]=str[i];
   j++;
   wln=j;
  } 
 i++; 
 }
 delete []mas;
 std::cout<<endl;
 return 0;
}

