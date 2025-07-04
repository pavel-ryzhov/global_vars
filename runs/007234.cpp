#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXN 5000

int  N;
char word[MAXN][20];
int  f[MAXN];
int  out[20];
char button[10][4];

char* wordsearch(int len, int change)
{
  int  i,j,k,l, key=0;
  char cw[MAXN][20];    // correct word
  int  cf[MAXN];        // correct f
  char tw[20];          // temp word
//  int minF=10000;
//  printf("\nlen = %d; change = %d\n", len, change);
  for (i=0; i<20; i++) tw[i]=0;
  if(out[0]==1)
  {
    switch (change) {
    case 0: return ".";
    case 1: return ",";
    case 2: return "?";
    }
  }

  for(i=0,l=0; i<N; i++)
  {
    key=0;
    for(j=0; j<len; j++)
    {
//      printf("Check button %d: \n", out[j]);
      for(k=0; k<4; k++)
      {
//        printf("comparing: %c and %c;\n", word[i][j], button[out[j]][k]);
        if(word[i][j]==button[out[j]][k])
        {
          key++;
//          printf("Correct char %c! Key=%d\n", word[i][j], key);
        }
      }
    }
    if(key==len)
    {
      strcpy(cw[l],word[i]);
      cf[l]=f[i];
      l++;
    }
  }
//  for(i=0; i<l; i++)
//    printf("Look %s. \n",cw[i]);
  // SORT cw by cf
  for(i=0; i<l-1; i++)
    for(j=i; j<l-1; j++)
    {
      if(cf[j]<cf[j+1])
      {
        k=cf[j];
        cf[j]=cf[j+1];
        cf[j+1]=k;
        strcpy(tw,cw[j]);
        strcpy(cw[j],cw[j+1]);
        strcpy(cw[j+1],tw);
      }
    }
//  for(i=0; i<l; i++)
//    printf("Look after sort: %s. \n",cw[i]);
//  printf("returning %s\n", cw[change%l]);
  if(l) return cw[change%(l)];
  return "Error";
}

void wordchange(char *w)
{
  int i,j,num, flag=1;
  char tw[20], tw1[20];
  for(i=0; i<N; i++)
    if(strcmp(word[i],w)==0) {f[i]++; num=i;}
  for(i=0;i<N && flag;i++)
    if(i<num && f[i]==f[num])
    {
      flag=0;
      strcpy(tw,word[i]);
      strcpy(word[i],word[num]);
      for(j=i+1;j<N;j++)
      {
        if(f[j]==f[i])
        {
           strcpy(tw1,word[j]);
           strcpy(word[j],tw);
           strcpy(tw,tw1);
        }
      }
    }
}

int main(int argc, char*argv[])
{
  int i, j=0, flag=1;
  FILE *in;
  char x;
  int change;
  char v;
  char w[20];

  button[1][0]='.'; button[1][1]=','; button[1][2]='?';
  button[2][0]='a'; button[2][1]='b'; button[2][2]='c';
  button[3][0]='d'; button[3][1]='e'; button[3][2]='f';
  button[4][0]='g'; button[4][1]='h'; button[4][2]='i';
  button[5][0]='j'; button[5][1]='k'; button[5][2]='l';
  button[6][0]='m'; button[6][1]='n'; button[6][2]='o';
  button[7][0]='p'; button[7][1]='q'; button[7][2]='r'; button[7][3]='s';
  button[8][0]='t'; button[8][1]='u'; button[8][2]='v';
  button[9][0]='w'; button[9][1]='x'; button[9][2]='y'; button[9][3]='z';

  in=stdin;
//  fopen("dic2.in","r");
  fscanf(in, "%d",&N);
  for(i=0;i<N;i++)
  {
    j=0;
    do {
      fscanf(in, "%c",&v);
      if(v!=10 && v!=32) { word[i][j]=v; j++;}
//      printf("%c: %d ", word[i][j], word[i][j]);
    } while (v!=32);//word[i][j]!=' ');
    fscanf(in, "%d", &f[i]);
  }
//  printf("Dictionary:\n");
//  for(i=0;i<N;i++)
//    printf("%s %d\n", word[i], f[i]);
  fscanf(in, "%c",&x);
  for(i=0, change=0; flag; i++)
  {
    fscanf(in, "%c",&x);
//    printf("Reading: %d\n", x, x);
    switch (x)
    {
      case '2': out[i]=2; break; //printf("case %d; ",out[i]);
      case '3': out[i]=3; break;
      case '4': out[i]=4; break;
      case '5': out[i]=5; break;
      case '6': out[i]=6; break;
      case '7': out[i]=7; break;
      case '8': out[i]=8; break;
      case '9': out[i]=9; break;
      case '1':
                strcpy(w,wordsearch(i, change));
                wordchange(w);
                printf("%s", w);
                i=-1;
                out[0]=1;
                change=0;
                break;
      case 10 :
                flag=0;
                if(out[0]!=1)
                {
                  strcpy(w,wordsearch(i, change));
                  wordchange(w);
                  printf("%s", w);
                  i=-1;
                  change=0;
                }  
                else
                {
                  strcpy(w,wordsearch(i, change));
                  printf("%s", w);
                }
                break;
      case ' ':
                strcpy(w,wordsearch(i, change));
                wordchange(w);
                printf("%s ", w);
                i=-1;
                change=0;
                break;
      case '*': change++; i--; break;// printf("case *; ");
//      case ' ': printf("%s ", wordsearch(i, change)); i=-1;  break;
      default: printf("Error! %c\n", x); flag=0;
    }
  }




//  fclose(in);
  return 0;
}



