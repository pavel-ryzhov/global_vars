#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

class wds
{
  public:
    char wd[21];
    long freq;
    unsigned prior;
};

unsigned PR;

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

void decode(char *ch, wds **dic, long zv, long len, long ln)
{
  wds tmp;
  long i,cnt,maxi,inclen;
  bool fl;
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
    std::cout << dic[ln-1][maxi].wd;
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
      inclen=cnt;
      fl=true;
      while ((inclen > 0)&&(fl))
      {
	fl=false;
	if (fnd[inclen].freq > fnd[inclen-1].freq)
	{
	  fl=true;
	  tmp=fnd[inclen];
	  fnd[inclen]=fnd[inclen-1];
	  fnd[inclen-1]=tmp;
	}
	else if ((fnd[inclen].freq == fnd[inclen-1].freq)&&(fnd[inclen].prior > fnd[inclen-1].prior))
	{
	  fl=true;
	  tmp=fnd[inclen];
	  fnd[inclen]=fnd[inclen-1];
	  fnd[inclen-1]=tmp;
	}
	inclen--;
      }	  
      cnt++;
    }
  }

    std::cout << fnd[zv].wd;

  PR++;
  for (unsigned k=0; k<len; k++)
  {
    if (compare2(fnd[zv].wd,dic[ln-1][k].wd,ln))
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
    switch (STR[w])
    {
      case '*':
	count=1;
	w++;
	while (STR[w]=='*')
	{
	  count++;
	  w++;
	}
	decode(rec,DICT,count,lmas[z-1],z);  
	z=-1;
	break;
      case ' ':
	if (z>0)
	{
	  decode(rec,DICT,0,lmas[z-1],z);
	}
	std::cout << ' ';
	z=-1;
	w++;
	break;
      case '1':
	if (z>0)
	{
	  decode(rec,DICT,0,lmas[z-1],z);
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
	  std::cout << '.';
	}
	else if (count==1)
	{
	  std::cout << ',';
	}
	else
	{
	  std::cout << '?';
	}
	count=0;      
	z=-1;
	break;
      case '\n':
	if (z>0)
	{
	  decode(rec,DICT,0,lmas[z-1],z);
	}
	fnd=false;
      default: w++;
    }
    z++;
  }
	
      
//  std::cout << OUT << '\n';
  std::cout << '\n';
  
  for (long i=0; i<20; i++)
  {
    delete[]DICT[i];    
  }
  delete[]DICT;
  delete[]dictionary;
  return 0;
}
