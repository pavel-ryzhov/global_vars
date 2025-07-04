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

void decode(char *ch, wds *dic, long zv, long len, long ln)
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
	if (compare(ch,dic[i].wd,ln))
	{
	  maxi=i;
	}
	i++;
      }
    for (unsigned l=i; l<len; l++)
    {
      if (compare(ch,dic[l].wd,ln))
      {
	if (dic[l].freq > dic[maxi].freq)
	{
	  maxi=l;
	}
	else if ((dic[l].freq == dic[maxi].freq)&&((dic[l].prior > dic[maxi].prior)))
	{
	  maxi=l;
	}
      }
    }
    std::cout << dic[maxi].wd;
    PR++;
    dic[maxi].freq++;
    dic[maxi].prior=PR;
    if (ln==20)
    {
      inclen=maxi;
      fl=true;
      while ((inclen > 0)&&(fl))
      {
	fl=false;
	if (dic[inclen].freq > dic[inclen-1].freq)
	{
	  fl=true;
	  tmp=dic[inclen];
	  dic[inclen]=dic[inclen-1];
	  dic[inclen-1]=tmp;
	}
	else if ((dic[inclen].freq == dic[inclen-1].freq)&&(dic[inclen].prior > dic[inclen-1].prior))
	{
	  fl=true;
	  tmp=dic[inclen];
	  dic[inclen]=dic[inclen-1];
	  dic[inclen-1]=tmp;
	}
	inclen--;
      }  
    }
  }
  else
  {   
    if (ln==20)
    {
      inclen=0;
      while (zv!=-1)
      {
	if (compare(ch,dic[inclen].wd,ln))
	{
	  zv--;
	}
	inclen++;
      }
      inclen--;
      std::cout << dic[inclen].wd;
      PR++;
      dic[inclen].freq++;
      dic[inclen].prior=PR;
      fl=true;
      while ((inclen > 0)&&(fl))
      {
	fl=false;
	if (dic[inclen].freq > dic[inclen-1].freq)
	{
	  fl=true;
	  tmp=dic[inclen];
	  dic[inclen]=dic[inclen-1];
	  dic[inclen-1]=tmp;
	}
	else if ((dic[inclen].freq == dic[inclen-1].freq)&&(dic[inclen].prior > dic[inclen-1].prior))
	{
	  fl=true;
	  tmp=dic[inclen];
	  dic[inclen]=dic[inclen-1];
	  dic[inclen-1]=tmp;
	}
	inclen--;
      } 
    }
    else
    {  
      cnt=0;
      wds *fnd = new wds[len];
      for (unsigned l=0; l<len; l++)
      {
	if (compare(ch,dic[l].wd,ln))
	{
	  fnd[cnt]=dic[l];
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
	if (compare2(fnd[zv].wd,dic[k].wd,ln))
	{
	  dic[k].freq++;
	  dic[k].prior=PR; 
	}   
      }  
      delete[] fnd;
      }
  }
}

int main() 
{
  long N;
  long LNG;
  long lmas[20][8];
  char STR[100000];
  char OUT[100000];
  unsigned x,y;
  wds *dictionary;
  wds ***DICT;
  wds tmp;
  std::cin >> N;
  dictionary = new wds[N];
  
  DICT=new wds**[20];
  for (long i=0; i<20; i++)
  {
    DICT[i]=new wds*[8];
    for (long j=0; j<8; j++)
      DICT[i][j]= new wds[50000];
  }

  for (long i=0; i<20; i++)
    for (long j=0; j<8; j++)
      lmas[i][j]=0;
  for (long i=0; i<N; i++)
  {
    std::cin >> dictionary[i].wd >> dictionary[i].freq;
    x=strlen(dictionary[i].wd)-1;
    y=firstC(dictionary[i].wd[0]);
    DICT[x][y][lmas[x][y]]=dictionary[i];
    DICT[x][y][lmas[x][y]].prior=N-i;
    lmas[x][y]++;
  }
  PR=N+1;
  
  for (unsigned i=0; i<8; i++)
    SORT(DICT[19][i],lmas[19][i]);
  
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
	decode(rec,DICT[z-1][firstC2(rec[0])],count,lmas[z-1][firstC2(rec[0])],z);  
	z=-1;
	break;
      case ' ':
	if (z>0)
	{
	  decode(rec,DICT[z-1][firstC2(rec[0])],0,lmas[z-1][firstC2(rec[0])],z);
	}
	std::cout << ' ';
	z=-1;
	w++;
	break;
      case '1':
	if (z>0)
	{
	  decode(rec,DICT[z-1][firstC2(rec[0])],0,lmas[z-1][firstC2(rec[0])],z);
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
	  decode(rec,DICT[z-1][firstC2(rec[0])],0,lmas[z-1][firstC2(rec[0])],z);
	}
	fnd=false;
      default: w++;
    }
    z++;
  }
	
  std::cout << '\n';
  
  for (long j=0; j<20; j++)
    for (long i=0; i<8; i++)
      delete[]DICT[j][i];
  for (long i=0; i<20; i++)
  {
    delete[]DICT[i];    
  }
  delete[]DICT;
  delete[]dictionary;
  return 0;
}
