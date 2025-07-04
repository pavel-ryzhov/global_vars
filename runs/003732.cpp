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
        a=(char*)malloc(4*sizeof(char));
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
    char *p, *q, *s, c[100000];
    int l,k,m,i=0;

    l=strlen(com);
    strcpy(c,com);
    while(l!=0)
    {
	i=0;
        strcpy(com,c);
	l=strlen(com);
	while(com[i]==' ')
	    i++;
	com=&com[i];
	if(((strlen(com)==1)&&(com[0]==' '))||(!com[0]))
	    break;
	if((strstr(com,"1")!=NULL)||(strstr(com,"2")!=NULL)||(strstr(com,"3")!=NULL)||(strstr(com,"4")!=NULL)||(strstr(com,"5")!=NULL)||(strstr(com,"6")!=NULL)||(strstr(com,"7")!=NULL)||(strstr(com,"8")!=NULL)||(strstr(com,"9")!=NULL))
	    for(m=0; m<i; m++)
		strcat(line," ");
        p=strstr(com," ");
        q=strstr(com,"1");
        if(com==q)
            q=0;
        if(com==p)
            p=0;
        if(p==q)
        {
	    q=strstr(com,"1");
	    com=q+1;
	    p=strstr(com,"1");
	    com=q;
	    if(p==NULL)
	    {
		s=(char*)malloc((l+1)*sizeof(char));
		strcpy(s,com);
		s[l]='\0';
		l=0;
	    }
	    else
	    {
		k=p-com;
		s=(char*)malloc((k+1)*sizeof(char));
                strncpy(s,com,k);
                s[k]='\0';
                com=p;
	    }
	    q=0;
	    p=0;
        }
        if((p!=NULL)&&(q!=NULL))
        {
            if(p>q)
            {
                k=q-com;
                s=(char*)malloc((k+1)*sizeof(char));
                strncpy(s,com,k);
                s[k]='\0';
                com=q;
                l-=k;
            }
            if(p<q)
            {
                k=p-com;
		if(k==0)
		    strcat(line," ");
		else
		{
		    s=(char*)malloc((k+1)*sizeof(char));
		    strncpy(s,com,k);
		    s[k]='\0';
		}
		    com=p;
		    l-=k;
            }
        }
        if((q==NULL)&&(p!=NULL))
        {
            k=p-com;
	    q=strstr(com,"1");
	    com=q+1;
	    if((strstr(com,"1")!=NULL)&&(strstr(com,"1")<p))
	    {
		k=strstr(com,"1")-com;
		p=strstr(com,"1");
	    }
	    com=q;
            s=(char*)malloc((k+1)*sizeof(char));
            strncpy(s,com,k);
            s[k]='\0';
            com=p;
            l-=k;
	    q=0;
        }
        if((p==NULL)&&(q!=NULL))
        {
            k=q-com;
            s=(char*)malloc((k+1)*sizeof(char));
            strncpy(s,com,k);
            s[k]='\0';
            com=q;
            l-=k;
        }
        strcpy(c,com);
        data_type(s,vol);
        free(s);
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
