#include <iostream>
#include <string.h>
using namespace std;

class wds
{
  public:
    char wd[21];
    char dc[21];
    long freq;
    unsigned prior;
};

unsigned PR;

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
  wds w,tmp;
  long i,cnt;
  i=0;
  bool poisk;
  poisk=true;
  for (long l=0; l<ln; l++)
  {
    w.dc[l]=ch[l];
  }
  cnt=0;
  wds *fnd = new wds[len];
  for (unsigned l=0; l<len; l++)
  {
    if (compare(w.dc,dic[ln-1][l].dc,ln))
    {
      fnd[cnt]=dic[ln-1][l];
      cnt++;
    }
  }
  
  for (long k=0; k<cnt-1; k++)
    {
      for (long j=cnt-1; j>k; j--)
      {
	if ((fnd[j].freq>fnd[j-1].freq)||(fnd[j].freq==fnd[j-1].freq)&&(fnd[j].prior>fnd[j-1].prior))
	{
	  tmp=fnd[j];
	  fnd[j]=fnd[j-1];
	  fnd[j-1]=tmp;
	}
      }
    }
    
  
  while (poisk)
  {
    if (zv==0)
    {
      for (unsigned l=0; l<ln; l++)
      {
	w.wd[l]=fnd[i].wd[l];
	ch1[l]=w.wd[l];
      }
      poisk=false;
      PR++;
      for (unsigned k=0; k<len; k++)
      {
	if (compare(w.wd,dic[ln-1][k].wd,ln))
	{
	  dic[ln-1][k].freq++;
	  dic[ln-1][k].prior=PR;
	}
      }
    }
    i++;
    zv--;
    if (i==cnt)
    {
      i=0;
    }
  }
  delete[] fnd;
}

int main() 
{
  long N,k;
  long LNG;
  long lmas[20];
  char X[21];
  char STR[100000];
  char OUT[100000];
  wds *dictionary;
  wds **DICT;
  wds tmp,test;
  PR=0;
  std::cin >> N;
  dictionary = new wds[N];
  
  for (long i=0; i<20; i++)
    lmas[i]=0;
  for (long i=0; i<N; i++)
  {
    std::cin >> dictionary[i].wd >> dictionary[i].freq;
    dictionary[i].prior=0;
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
    DICT[strlen(dictionary[i].wd)-1][lmas[strlen(dictionary[i].wd)-1]]=dictionary[i];
    lmas[strlen(dictionary[i].wd)-1]++;
  }
  
  
 // for (long i=0; i<20; i++)
  //  std::cout << lmas[i];
  
  
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
  char rec[21];
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
