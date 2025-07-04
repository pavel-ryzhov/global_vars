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
  if (strlen(c2)!=ln)
  {
    equal=false;
  }
  else
  {
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
  }
  return(equal);
}


int firstC(char c)
{
  switch (c)
  {
    case 'a': return(0); break;
    case 'b': return(0); break;
    case 'c': return(0); break;
    case 'd': return(1); break;
    case 'e': return(1); break;
    case 'f': return(1); break;
    case 'g': return(2); break;
    case 'h': return(2); break;
    case 'i': return(2); break;
    case 'j': return(3); break;
    case 'k': return(3); break;
    case 'l': return(3); break;
    case 'm': return(4); break;
    case 'n': return(4); break;
    case 'o': return(4); break;
    case 'p': return(5); break;
    case 'q': return(5); break;
    case 'r': return(5); break;
    case 's': return(5); break;
    case 't': return(6); break;
    case 'u': return(6); break;
    case 'v': return(6); break;
    case 'w': return(7); break;
    case 'x': return(7); break;
    case 'y': return(7); break;
    case 'z': return(7); break;
  }
}

int firstC2(char c)
{
  switch (c)
  {
    case '2': return(0); break;
    case '3': return(1); break;
    case '4': return(2); break;
    case '5': return(3); break;
    case '6': return(4); break;
    case '7': return(5); break;
    case '8': return(6); break;
    case '9': return(7); break;
  }
}



bool compare2(char *c1, char *c2, long ln)
{
  bool equal;
  equal=true;
  long i=0;
  if (strlen(c2)!=ln)
  {
    equal=false;
  }
  else
  {
    while ((equal)&&(i<ln))
    {
      if (c1[i]!=c2[i])
      {
	equal=false;
      }
      i++;
    }
  }
  return(equal);
}

void decode(char *ch, wds **dic, long zv, long len, long ln)
{
  wds tmp;
  long i,cnt,maxi,inclen;
  bool fl;
  i=0;
  unsigned num=firstC2(ch[0]);
  maxi=-1;
  if (zv==0)
  {
    while (maxi==-1)
      {
	if (compare(ch,dic[num][i].wd,ln))
	{
	  maxi=i;
	}
	i++;
      }
    for (unsigned l=i; l<len; l++)
    {
      if (compare(ch,dic[num][l].wd,ln))
      {
	if (dic[num][l].freq > dic[num][maxi].freq)
	{
	  maxi=l;
	}
	else if ((dic[num][l].freq == dic[num][maxi].freq)&&((dic[num][l].prior > dic[num][maxi].prior)))
	{
	  maxi=l;
	}
      }
    }
    std::cout << dic[num][maxi].wd;
    PR++;
    dic[num][maxi].freq++;
    dic[num][maxi].prior=PR;
  }
  else
  {
  cnt=0;
  wds *fnd = new wds[len];
  for (unsigned l=0; l<len; l++)
  {
    if (compare(ch,dic[num][l].wd,ln))
    {
      fnd[cnt]=dic[num][l];
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
    if (compare2(fnd[zv].wd,dic[num][k].wd,ln))
    {
      dic[num][k].freq++;
      dic[num][k].prior=PR; 
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


  for (long i=0; i<8; i++)
    lmas[i]=0;
  for (long i=0; i<N; i++)
  {
    std::cin >> dictionary[i].wd >> dictionary[i].freq;
    DICT[firstC(dictionary[i].wd[0])][lmas[firstC(dictionary[i].wd[0])]]=dictionary[i];
    DICT[firstC(dictionary[i].wd[0])][lmas[firstC(dictionary[i].wd[0])]].prior=N-i;
    lmas[firstC(dictionary[i].wd[0])]++;
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
	decode(rec,DICT,count,lmas[firstC2(rec[0])],z);  
	z=-1;
	break;
      case ' ':
	if (z>0)
	{
	  decode(rec,DICT,0,lmas[firstC2(rec[0])],z);
	}
	std::cout << ' ';
	z=-1;
	w++;
	break;
      case '1':
	if (z>0)
	{
	  decode(rec,DICT,0,lmas[firstC2(rec[0])],z);
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
	  decode(rec,DICT,0,lmas[firstC2(rec[0])],z);
	}
	fnd=false;
      default: w++;
    }
    z++;
  }
	
  std::cout << '\n';
  
  for (long i=0; i<20; i++)
  {
    delete[]DICT[i];    
  }
  delete[]DICT;
  delete[]dictionary;
  return 0;
}
