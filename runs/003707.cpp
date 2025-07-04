#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

char *com;
char line[100000];

struct dictionary
{
    int c;
    char w[20];
    int q;
}a,abc[50000];

//функция извлечения словаря из стандартного потока в массив структур
int get_data(void)
{
    char str[25],a[4];
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
        for(l=1; l<5; l++)
        {
            if(str[j+l])
                a[l-1]=str[j+l];
            else
                break;
        }
        l=atoi(a);
        abc[i].q=l;
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
        t=(char*)malloc(j*sizeof(char));
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
        abc[i].c=atoi(t);
        free(t);
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
    if((k!=i)||((k==i)&&(abc[k].q>abc[k].q)))
        k++;
    for(j=n; j>k; j--)
        abc[j]=abc[j-1];
    abc[k]=a;
    return 0;
}

void data_type(char* s, int f, int vol)
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
        t=(char*)malloc((l-j)*sizeof(char));
        strncpy(t,s,l-j);
        a=atoi(t);
        free(t);
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
    if(f==1)
        strcat(line," ");
}

void sms(int vol)
{
    char *p, *q, *s, c[100000];
    int l,k,f;

    l=strlen(com);
    strcpy(c,com);
    while(l!=0)
    {
        f=0;
        strcpy(com,c);
        p=strstr(com," ");
        q=strstr(com,"1");
        if(com==q)
            q=0;
        if(com==p)
            p=0;
        if(p==q)
        {
            s=(char*)malloc((l+1)*sizeof(char));
            strcpy(s,com);
            s[l+1]='\0';
            l=0;
        }
        if((p!=NULL)&&(q!=NULL))
        {
            if(p>q)
            {
                k=q-com;
                s=(char*)malloc((k+1)*sizeof(char));
                strncpy(s,com,k);
                s[k]='\n';
                com=q;
                l-=k;
            }
            if(p<q)
            {
                k=p-com;
                s=(char*)malloc((k+1)*sizeof(char));
                strncpy(s,com,k);
                s[k]='\0';
                com=p+1;
                l-=k;
                f=1;
            }
        }
        if((q==NULL)&&(p!=NULL))
        {
            k=p-com;
            s=(char*)malloc((k+1)*sizeof(char));
            strncpy(s,com,k);
            s[k]='\n';
            com=p+1;
            l=l-(k+1);
        }
        if((p==NULL)&&(q!=NULL))
        {
            k=q-com;
            s=(char*)malloc((k+1)*sizeof(char));
            strncpy(s,com,k);
            s[k]='\n';
            com=q;
            l-=k;
        }
        strcpy(c,com);
        data_type(s,f,vol);
        free(s);
    }
    free(com);
}

int main(void)
{
    int vol;

    vol=get_data();
    data_conv(vol);
    sms(vol);
    printf("%s\n",line);
    return 0;
}
