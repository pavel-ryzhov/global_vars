#include <iostream>
#include <string.h>
using namespace std;

class wds
{
  public:
    char wd[21];
    //char dc[21];
    long freq;
    unsigned prior;
};

unsigned PR;

long maxfind(wds *wd, long len)
{
  long maxi;
  maxi=0;
  for (unsigned l=0; l<len; l++)
    {
      if (wd[l].freq > wd[maxi].freq)
      {
	maxi=l;
      }
      else if ((wd[l].freq == wd[maxi].freq)&&((wd[l].prior > wd[maxi].prior)))
      {
	maxi=l;
      }   
    }
    wd[maxi].freq=0;
    return(maxi);
}

void SORT(wds *a, long n)
{
  long i=0;
  long j=n;
  wds temp, p;
  p=a[n>>1]; 
  do
  {
    while ((a[i].freq > p.freq)||((a[i].freq == p.freq)&&(a[i].prior > p.prior))) 
      i++;
    while ((a[j].freq < p.freq)||((a[j].freq == p.freq)&&(a[j].prior < p.prior)))
      j--;
    if (i<=j)
    {
      temp=a[i];
      a[i]=a[j];
      a[j]=temp;
      i++;
      j--;
    }
  } while (i<=j);
  if (j>0)
    SORT(a,j);
  if (n>i)
    SORT(a+i,n-i);
}

bool compare(char *c1, char *c2, long ln)
{
  bool equal;
  equal=true;
  long l=0;
  while ((l<ln)&&(equal==true))
  {
    switch (c1[l])
    {
      case '2':
	if ((c2[l]!='a')&&(c2[l]!='b')&&(c2[l]!='c'))
	{ 
	  equal=false;
	}
	break; 
      case '3':
	if ((c2[l]!='d')&&(c2[l]!='e')&&(c2[l]!='f'))
	{ 
	  equal=false;
	}
	break;
	case '4':
	if ((c2[l]!='g')&&(c2[l]!='h')&&(c2[l]!='i'))
	{ 
	  equal=false;
	}
	break;
	case '5':
	if ((c2[l]!='j')&&(c2[l]!='k')&&(c2[l]!='l'))
	{ 
	  equal=false;
	}
	break;
	case '6':
	if ((c2[l]!='m')&&(c2[l]!='n')&&(c2[l]!='o'))
	{ 
	  equal=false;
	}
	break;
	case '7':
	if ((c2[l]!='p')&&(c2[l]!='q')&&(c2[l]!='r')&&(c2[l]!='s'))
	{ 
	  equal=false;
	}
	break;
	case '8':
	if ((c2[l]!='t')&&(c2[l]!='u')&&(c2[l]!='v'))
	{ 
	  equal=false;
	}
	break;
	case '9':
	if ((c2[l]!='w')&&(c2[l]!='x')&&(c2[l]!='y')&&(c2[l]!='z'))
	{ 
	  equal=false;
	}
	break;
    }
    l++;
  }
  return(equal);
}



bool compare2(char *c1, char *c2, long ln)
{
  bool equal;
  equal=true;
  long i=0;
  while ((equal)&&(i<ln))
  {
    if (c1[i]!=c2[i])
    {
      equal=false;
    }
    i++;
  }
  return(equal);
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

void decode(char *ch, wds **dic, long zv, long len, long ln)
{
  wds tmp;
  long i,cnt,maxi;
  i=0;
  maxi=-1;
  if (zv==0)
  {
    while (maxi==-1)
      {
	if (compare(ch,dic[ln-1][i].wd,ln))
	{
	  maxi=i;
	}
	i++;
      }
    for (unsigned l=i; l<len; l++)
    {
      if (compare(ch,dic[ln-1][l].wd,ln))
      {
	if (dic[ln-1][l].freq > dic[ln-1][maxi].freq)
	{
	  maxi=l;
	}
	else if ((dic[ln-1][l].freq == dic[ln-1][maxi].freq)&&((dic[ln-1][l].prior > dic[ln-1][maxi].prior)))
	{
	  maxi=l;
	}
      }
    }
    for (unsigned l=0; l<ln; l++)
      {
	ch[l]=dic[ln-1][maxi].wd[l];
      }
    PR++;
    dic[ln-1][maxi].freq++;
    dic[ln-1][maxi].prior=PR;
  }
  else
  {
  cnt=0;
  wds *fnd = new wds[len];
  for (unsigned l=0; l<len; l++)
  {
    if (compare(ch,dic[ln-1][l].wd,ln))
    {
      fnd[cnt]=dic[ln-1][l];
      cnt++;
    }
  }

//  SORT(fnd,cnt-1);
  for (long k=0; k<=zv; k++)
    maxi=maxfind(fnd,cnt);

  for (unsigned l=0; l<ln; l++)
  {
    ch[l]=fnd[maxi].wd[l];
  } 
  PR++;
  for (unsigned k=0; k<len; k++)
  {
    if (compare2(ch,dic[ln-1][k].wd,ln))
    {
      dic[ln-1][k].freq++;
      dic[ln-1][k].prior=PR; 
    }   
  }  
  delete[] fnd;
  }
}

int main() 
{
  long N;
  long LNG;
  long lmas[20];
  char STR[100000];
  char OUT[100000];
  wds *dictionary;
  wds **DICT;
  wds tmp;
  std::cin >> N;
  dictionary = new wds[N];
  
  DICT=new wds*[20];
  for (long j=0; j<20; j++)
    DICT[j]= new wds[50000];


  for (long i=0; i<20; i++)
    lmas[i]=0;
  for (long i=0; i<N; i++)
  {
    std::cin >> dictionary[i].wd >> dictionary[i].freq;
    for (long l=0; l<strlen(dictionary[i].wd); l++)
      DICT[strlen(dictionary[i].wd)-1][lmas[strlen(dictionary[i].wd)-1]].wd[l]=dictionary[i].wd[l];
    DICT[strlen(dictionary[i].wd)-1][lmas[strlen(dictionary[i].wd)-1]].freq=dictionary[i].freq;
    DICT[strlen(dictionary[i].wd)-1][lmas[strlen(dictionary[i].wd)-1]].prior=N-i;
//    code(DICT[strlen(dictionary[i].wd)-1][lmas[strlen(dictionary[i].wd)-1]].wd,DICT[strlen(dictionary[i].wd)-1][lmas[strlen(dictionary[i].wd)-1]].dc);
    lmas[strlen(dictionary[i].wd)-1]++;
  }
  PR=N;
  
  cin >> STR[0];
  LNG=1;
  
  while (std::cin.get(STR[LNG]))
  {
    if (STR[LNG]=='\n')
      break;
    LNG++;
  }
  
  bool fnd;
  fnd=true;
  char rec[21];
  long z=0;
  long w=0;
  long q=0;
  unsigned count=0;
  while (fnd)
  {
    rec[z]=STR[w];
    if (STR[w]=='1')
    {
      if (z>0)
      {
	decode(rec,DICT,0,lmas[z-1],z);
	for (long l=q; l<q+z;l++)
	{
	  OUT[l]=rec[l-q];
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
      if (count==0)
      {
	OUT[q]='.';
	q++;
      }
      else if (count==1)
      {
	OUT[q]=',';
	q++;
      }
      else
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
	decode(rec,DICT,0,lmas[z-1],z);
	for (long l=q; l<q+z;l++)
	{
	  OUT[l]=rec[l-q];
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
	decode(rec,DICT,0,lmas[z-1],z);
	for (long l=q; l<q+z;l++)
	{
	  OUT[l]=rec[l-q];
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
	decode(rec,DICT,count,lmas[z-1],z);
	for (long l=q; l<q+z;l++)
	{
	  OUT[l]=rec[l-q];
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
