#include <iostream>
#include <string.h>
using namespace std;

class wds
{
  public:
    char wd[20];
    char dc[20];
    long freq;
};

bool compare(char *c1, char *c2, long ln)
{
  bool equal;
  equal=true;
  for (long i=0; i<ln; i++)
  {
    if (c1[i]!=c2[i])
    {
      equal=false;
    }
  }
  return equal;
}

void code(char *w, char *d)
{
  long l;
  l=strlen(w);
  for (long i=0; i<l; i++)
  {
    if ((w[i]=='a')||(w[i]=='b')||(w[i]=='c'))
      d[i]='2';
    else if ((w[i]=='d')||(w[i]=='e')||(w[i]=='f'))
      d[i]='3';
    else if ((w[i]=='g')||(w[i]=='h')||(w[i]=='i'))
      d[i]='4';
    else if ((w[i]=='j')||(w[i]=='k')||(w[i]=='l'))
      d[i]='5';
    else if ((w[i]=='m')||(w[i]=='n')||(w[i]=='o'))
      d[i]='6';
    else if ((w[i]=='p')||(w[i]=='q')||(w[i]=='r')||(w[i]=='s'))
      d[i]='7';
    else if ((w[i]=='t')||(w[i]=='u')||(w[i]=='v'))
      d[i]='8';
    else if ((w[i]=='w')||(w[i]=='x')||(w[i]=='y')||(w[i]=='z'))
      d[i]='9';
  }
}

void decode(char *ch, char *ch1, wds **dic, long zv, long len, long ln)
{
  wds w;
  long i;
  long prev,cur;
  i=0;
  bool poisk;
  poisk=true;
  bool SRAVN,zam;
  for (long l=0; l<ln; l++)
  {
    w.dc[l]=ch[l];
  }
  while (poisk)
  {	
    SRAVN=compare(w.dc,dic[ln-1][i].dc,ln);
    if ((SRAVN) && (zv==0))
    {
      for (long l=0; l<ln; l++)
      {
	w.wd[l]=dic[ln-1][i].wd[l];
	ch1[l]=w.wd[l];
      }
      poisk=false;
      zv--;
      prev=i;
    }
    if ((SRAVN==true) && (zv!=0))
    {
      zv--;
    }  
    i++;
    if (i==len)
    {
      i=0;
    }
  } 
  poisk=true;
  zam=false;
  i=0;
  dic[ln-1][prev].freq++;
  while (poisk && (i<len+1))
  {
    if (dic[ln-1][i].freq == (dic[ln-1][prev].freq))
    {
      cur=i;
      poisk=false;
      zam=true;
    }
    i++;
  }
  if ((dic[ln-1][0].freq == (dic[ln-1][prev].freq-1)) && (prev!=0))
    {
      cur=0;
      zam=true;
    }  
  
  if (zam)
  {
  w=dic[ln-1][prev];
  for (long l=prev; l>cur; l--)
    dic[ln-1][l]=dic[ln-1][l-1];
  dic[ln-1][cur]=w;
  }
}

int main() 
{
  long N,k;
  long LNG;
  long lmas[20];
  char X[20];
  char STR[100000];
  char OUT[100000];
  wds *dictionary;
  wds **DICT;
  wds tmp,test;
  std::cin >> N;
  dictionary = new wds[N];
  
  for (long i=0; i<20; i++)
    lmas[i]=0;
  for (long i=0; i<N; i++)
  {
    std::cin >> dictionary[i].wd >> dictionary[i].freq;
    code(dictionary[i].wd,dictionary[i].dc);
    lmas[strlen(dictionary[i].wd)-1]++;
  }
    
  DICT=new wds*[20];
  for (long j=0; j<20; j++)
    DICT[j]= new wds[lmas[j]];
 
  for (long i=0; i<20; i++)
    lmas[i]=0;
  for (long i=0; i<N; i++)
  {
    for (long j=0; j<strlen(dictionary[i].wd); j++)
    {
      DICT[strlen(dictionary[i].wd)-1][lmas[strlen(dictionary[i].wd)-1]].dc[j]=dictionary[i].dc[j];
      DICT[strlen(dictionary[i].wd)-1][lmas[strlen(dictionary[i].wd)-1]].wd[j]=dictionary[i].wd[j];
    }
    DICT[strlen(dictionary[i].wd)-1][lmas[strlen(dictionary[i].wd)-1]].freq=dictionary[i].freq;
    lmas[strlen(dictionary[i].wd)-1]++;
  }
  
  
  
  
  for (long k=0; k<20; k++)
  {
    for (long i=0; i<(lmas[k])-1; i++)
    {
      for (long j=(i+1); j<lmas[k]; j++)
      {
	if (DICT[k][i].freq<DICT[k][j].freq)
	{
	  tmp=DICT[k][j];
	  DICT[k][j]=DICT[k][i];
	  DICT[k][i]=tmp;
	}
      }
    }
  }

  
  cin >> STR[0];
  k=1;
  
  while (std::cin.get(STR[k]))
  {
    if (STR[k]=='\n')
      break;
    k++;
  }
  LNG=k;
  
  bool fnd;
  fnd=true;
  char rec[20];
  long z=0;
  long w=0;
  long q=0;
  long count=0;
  while (fnd)
  {
    rec[z]=STR[w];
    if (STR[w]=='1')
    {
      if (z>0)
      {
	for (long l=0; l<z; l++)
	{
	  test.dc[l]=rec[l];
	}
	decode(test.dc,test.wd,DICT,0,lmas[z-1],z);
	for (long l=q; l<q+z;l++)
	{
	  OUT[l]=test.wd[l-q];
	}
	q=q+z;
      }
      w++;
      count=0;
      while (STR[w]=='*')
      {
	count++;
	w++;
      }
      if (count%3==0)
      {
	OUT[q]='.';
	q++;
      }
      if (count%3==1)
      {
	OUT[q]=',';
	q++;
      }
      if (count%3==2)
      {
	OUT[q]='?';
	q++;
      }
      count=0;      
      z=-1;
    }
    else if (STR[w]==' ')
    {
      if (z>0)
      {
	for (long l=0; l<z; l++)
	{
	  test.dc[l]=rec[l];
	}
	decode(test.dc,test.wd,DICT,0,lmas[z-1],z);
	for (long l=q; l<q+z;l++)
	{
	  OUT[l]=test.wd[l-q];
	}
	q=q+z;
      }
      OUT[q]=' ';
      q++;
      z=-1;
      w++;
    }    
    else if (STR[w]=='\n')
    {
      if (z>0)
      {
	for (long l=0; l<z; l++)
	{
	  test.dc[l]=rec[l];
	}
	decode(test.dc,test.wd,DICT,0,lmas[z-1],z);
	for (long l=q; l<q+z;l++)
	{
	  OUT[l]=test.wd[l-q];
	}
	q=q+z;
      }
      z=-1;
      w++;
    }
    else if (STR[w]=='*')
    {
      count=1;
      w++;
      while (STR[w]=='*')
      {
	count++;
	w++;
      }
      for (long l=0; l<z; l++)
	{
	  test.dc[l]=rec[l];
	}
	decode(test.dc,test.wd,DICT,count,lmas[z-1],z);
	for (long l=q; l<q+z;l++)
	{
	  OUT[l]=test.wd[l-q];
	}
	q=q+z;    
      z=-1;
    } 
    else
      w++;
    z++;
    if (w>LNG)
	fnd=false;
  }	
      
  std::cout << OUT << '\n';
  
  for (long i=0; i<20; i++)
  {
    delete[]DICT[i];    
  }
  delete[]DICT;
  delete[]dictionary;
  return 0;
}
