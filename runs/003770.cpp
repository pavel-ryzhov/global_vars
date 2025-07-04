#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *com;
char line[100000];

struct dictionary
{
    int c;
    char w[20];
    int q;
}abc[50000];

//функция извлечения словаря из стандартного потока в массив структур
int get_data(void)
{
    char str[25];
    char *a;
    int i,j,k,l;

    gets(str);
    k=atoi(str);
    for(i=0; i<k; i++)
    {
        gets(str);
        for(j=0; j<20; j++)
        {
            if(str[j]!=' ')
                abc[i].w[j]=str[j];
            else
                break;
        }
        a=(char*)calloc(4,sizeof(char));
        for(l=1; l<5; l++)
        {
	    if(str[j+l])
                a[l-1]=str[j+l];
            else
                break;
        }
        l=atoi(a);
        abc[i].q=l;
	free(a);
    }
    com=(char*)malloc(100000*sizeof(char));
    gets(com);
    return k;
}

//процедура, генерирующая комбинации клавиш для каждого слова из словаря
void data_conv(int vol)
{
    int i,j,k;
    char *t;

    for(i=0; i<vol; i++)
    {
        j=strlen(abc[i].w);
        t=(char*)malloc((j+1)*sizeof(char));
        for(k=0; k<j; k++)
        {
            if((abc[i].w[k]=='a')||(abc[i].w[k]=='b')||(abc[i].w[k]=='c'))
                t[k]='2';
            if((abc[i].w[k]=='d')||(abc[i].w[k]=='e')||(abc[i].w[k]=='f'))
                t[k]='3';
            if((abc[i].w[k]=='g')||(abc[i].w[k]=='h')||(abc[i].w[k]=='i'))
                t[k]='4';
            if((abc[i].w[k]=='j')||(abc[i].w[k]=='k')||(abc[i].w[k]=='l'))
                t[k]='5';
            if((abc[i].w[k]=='m')||(abc[i].w[k]=='n')||(abc[i].w[k]=='o'))
                t[k]='6';
            if((abc[i].w[k]=='p')||(abc[i].w[k]=='q')||(abc[i].w[k]=='r')||(abc[i].w[k]=='s'))
                t[k]='7';
            if((abc[i].w[k]=='t')||(abc[i].w[k]=='u')||(abc[i].w[k]=='v'))
                t[k]='8';
            if((abc[i].w[k]=='w')||(abc[i].w[k]=='x')||(abc[i].w[k]=='y')||(abc[i].w[k]=='z'))
                t[k]='9';
        }
        t[j]='\0';
        abc[i].c=atoi(t);
        free(t);
    }
}

int cmp(const void *a, const void *b)
{
    struct dictionary *pa=(struct dictionary*)a;
    struct dictionary *pb=(struct dictionary*)b;
    return pa->c-pb->c;
}

void sort(int vol)
{
    struct dictionary *k;
    
    k=abc;
    qsort(k,vol,sizeof(struct dictionary),cmp);
}

int cmpc(const void *a, const void *b)
{
    struct dictionary *pa=(struct dictionary*)a;
    struct dictionary *pb=(struct dictionary*)b;
    return -(pa->q-pb->q);
}

//сортировка структур по количеству использований в рамках каждой уникальной комбинации
void sortc(int vol)
{
    int a,i,k=0;
    
    a=abc[0].c;
    for(i=0; i<vol; i++)
    {
	if(abc[i].c==a)
	    k++;
	if((abc[i].c!=a)||(k==vol-1))
	{
	    if(k==vol-1)
		qsort(&abc[i-k+1],k+1,sizeof(struct dictionary),cmpc);
	    else
		qsort(&abc[i-k],k,sizeof(struct dictionary),cmpc);
	    k=0;
	    a=abc[i+1].c;
	}
    }
}
//процедура, увеличивающая частоты
//n - номер стркутуры в массиве
//i - номер первой структуры с таким же c
int counter(int n, int i)
{
    int j,k;
    struct dictionary a;

    abc[n].q++;
    a=abc[n];
    if(i==n)
        return 0;
    for(k=n-1; k>=i; k--)
        if(abc[k].q>abc[n].q)
            break;
    if((k!=i)||((k==i)&&(abc[i].q>abc[n].q)))
        k++;
    for(j=n; j>k; j--)
        abc[j]=abc[j-1];
    abc[k]=a;
    return 0;
}

void data_type(char* s, int vol)
{
    int i=0,k=0,l=0,j=0,z=0, a;
    char *t;

    if(s[0]=='1')
    {
        l=strlen(s);
        for(k=0; k<l; k++)
            if(s[k]=='*')
                j++;
        if(j!=0)
            z=j%3;
        else
            z=0;
        switch(z)
        {
            case 0: strcat(line,"."); break;
            case 1: strcat(line,","); break;
            case 2: strcat(line,"?"); break;
        }
    }
    else
    {
        l=strlen(s);
        for(k=0; k<l; k++)
            if(s[k]=='*')
                j++;
	if (j!=0)
	{
	    t=(char*)malloc((l-j)*sizeof(char));
	    strncpy(t,s,l-j);
	    a=atoi(t);
	    free(t);
	}
        else
	    a=atoi(s);
        for(i=0; i<vol; i++)
            if(a==abc[i].c)
                break;
        for(k=i; k<vol; k++)
        {
            if(a==abc[k].c)
                z++;
            else
                break;
        }
        for(k=0; k<l-j; k++)
	    j%=z;
        strcat(line,abc[i+j].w);
        counter(i+j,i);
    }
}

void sms(int vol)
{
    int i=0,k=0,l,d=0,f=0;
    char *s;
    
    s=(char*)malloc(l*sizeof(char));
    l=strlen(com);
    while(i<l)
    {
	while((com[i]!='1')&&(com[i]!=' ')&&(com[i]))
	{
	    s[k]=com[i];
	    i++;
	    k++;
	}
	if(((com[i]=='1')&&(k!=0))||((com[i]==' ')&&(com[i-1]!='1')))
	    k--;
	if((com[i]=='1')&&(k==0)&&(!s[0]))
	{
	    do
	    {
		s[k]=com[i];
		i++;
		k++;
	    }
	    while((com[i])&&(com[i]=='*'));
	    k--;
	}
	while(com[i]==' ')
	{
	    i++;
	    if(com[i])
		d++;
	    f=1;
	}
	if((com[i-1]==' ')&&(f==1))
	    i--;
	if(((com[i]=='1')||(com[i]==' ')||(!com[i]))||(((com[i-1]=='*')||(com[i-1]=='1'))&&((com[i]=='2')||(com[i]=='3')||(com[i]=='4')||(com[i]=='5')||(com[i]=='6')||(com[i]=='7')||(com[i]=='8')||(com[i]=='9'))))
	{
	    s[k+1]='\0';
	    if(strlen(s)==0)
	    {
		free(s);
		break;
	    }
	    data_type(s,vol);
	    free(s);
	    s=(char*)calloc(l,sizeof(char));
	    for(k=0; k<d; k++)
		strcat(line," ");
	    if((com[i]!='1')&&(com[i]!='2')&&(com[i]!='3')&&(com[i]!='4')&&(com[i]!='5')&&(com[i]!='6')&&(com[i]!='7')&&(com[i]!='8')&&(com[i]!='9'))
		i++;
	    k=0;
	    d=0;
	    f=0;
	}
    }
}

int main(void)
{
    int vol;

    vol=get_data();
    data_conv(vol);
    sort(vol);
    sortc(vol);
    sms(vol);
    vol=strlen(line);
    printf("%s\n",line);
    return 0;
}
