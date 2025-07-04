#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n=0, i=0, j=0, k=0, l=0, m[50000], ind[50000], n1=-1, n2=-1;
	char str[28],s[6];//считываемое слово и его частота
	char sv[100001];//строка набора
	char sr[22];//считанный код слова, после распознавания
	char c[2];//знак
	char words[50000][22];
	char words2[50000][22];

// фукнция сортировки по кодам
void QuickSort1(int a, int b)
{
    int A = a;
    int B = b;
    //double mid;
	char mid[22];
    if ( b > a)
    {
                //mid = atoi(words2[ ind[( a + b ) / 2] ]);
		strcpy(mid,words2[ ind[( a + b ) / 2] ]);
        while( A <= B )
        {
                  //      while( ( A < b ) && ( atoi(words2[ind[A]]) < mid )) ++A;
                    //    while( ( B > a ) && ( atoi(words2[ind[B]]) > mid )) --B;
                        while( ( A < b ) && ( strcmp(words2[ind[A]], mid) < 0)) ++A;
                        while( ( B > a ) && ( strcmp(words2[ind[B]], mid) > 0)) --B;
            if( A <= B )
            {
                double T;
                T = ind[A];
                ind[A] = ind[B];
                ind[B] = T;
                ++A;
                --B;
            }
        }
        if( a < B ) QuickSort1(a, B );
        if( A < b ) QuickSort1(A, b );
    }
}

// фукнция сортировки по релевантности
void QuickSort(int a, int b)
{
    int A = a;
    int B = b;
    double mid;

    if ( b > a)
    {
                mid = m[ ind[( a + b ) / 2] ];
        while( A <= B )
        {
                        while( ( A < b ) && ( m[ind[A]] < mid )) ++A;
                        while( ( B > a ) && ( m[ind[B]] > mid )) --B;
            if( A <= B )
            {
                double T;
                T = ind[A];
                ind[A] = ind[B];
                ind[B] = T;
                ++A;
                --B;
            }
        }
        if( a < B ) QuickSort(a, B );
        if( A < b ) QuickSort(A, b );
    }
}

// фукнция сортировки по алфавиту
void QuickSort2(int a, int b)
{
    int A = a;
    int B = b;
    char mid[21];

    if ( b > a)
    {
		strcpy(mid, words[ ind[( a + b ) / 2] ]);
        while( A <= B )
        {
                        while( ( A < b ) && ( strcmp(words[ind[A]], mid) > 0 )) ++A;
                        while( ( B > a ) && ( strcmp(words[ind[B]], mid) < 0 )) --B;
            if( A <= B )
            {
                double T;
                T = ind[A];
                ind[A] = ind[B];
                ind[B] = T;
                ++A;
                --B;
            }
        }
        if( a < B ) QuickSort2(a, B );
        if( A < b ) QuickSort2(A, b );
    }
}

//перемещение в словаре
void ins(int nn)
{
	int x=0, xx=0, buff=0;
	m[ind[nn]]=m[ind[nn]]+1;
	j=nn;
	x=nn;
	xx=0;
	if(nn!=n-1)
	{	
		while(strcmp(words2[ind[nn]],words2[ind[j+1]])==0 && j<n-1)
		{
			x=j+1;
			j=j+1;
		}
		if(nn!=x)
			for(j=nn+1;j<=x;j++)
				if(m[ind[j]]>m[ind[nn]])
				{
					xx=j-1;
					break;
				}
		if(xx==0)
		{
			xx=x;
		}
	
		if(nn!=xx)
		{
			buff=ind[nn];
			if(nn!=n-1)
				for(j=nn+1;j<=xx;j++)
					ind[j-1]=ind[j];
			ind[xx]=buff;
		}	
	}
}

//вывод слова или знака
void vivod()
{
	bool flag=true;

	if(n1==-1 && n2==-1 && sv[i]==' ') printf(" ");

	if(n1!=-1)
	{
		strncpy(sr,sv+n1,n2-n1+1);
		sr[n2-n1+1]='\0';
		for(j=n-1;j>=0&&flag;j--)
			if(strcmp(words2[ind[j]],sr)==0)
			{
				if(sv[i]==' ')
				{
					for(int h=0;h<strlen(words[ind[j-k]]);h++)
						printf("%c",words[ind[j-k]][h]);
					printf(" ");
				}
				else
					for(int h=0;h<strlen(words[ind[j-k]]);h++) printf("%c",words[ind[j-k]][h]);
				ins(j-k);
				n1=-1;
				n2=-1;
				k=0;
				flag=false;
			}
	}

	if(c[0]=='.')
	{
		if(k==0) printf(".");
		else
			if(k==1) printf(",");
			else
				printf("?");
	c[0]=' ';
	k=0;
	}
/*printf("\n\n");
//вывод считынных данных
for(int ii=0;ii<n;ii++)
{
for(int jj=0;jj<strlen(words[ind[ii]]);jj++)
printf("%c",words[ind[ii]][jj]);
printf(" ");
for(int jj=0;jj<strlen(words[ind[ii]]);jj++)
printf("%c",words2[ind[ii]][jj]);
printf(" %i\n",m[ind[ii]]);
}
printf("\n");*/

}

int main()
{	
c[0]=' ';
//таблица перевода букв в коды
char b[255];
b['a']='2';
b['b']='2';
b['c']='2';
b['d']='3';
b['e']='3';
b['f']='3';
b['g']='4';
b['h']='4';
b['i']='4';
b['j']='5';
b['k']='5';
b['l']='5';
b['m']='6';
b['n']='6';
b['o']='6';
b['p']='7';
b['q']='7';
b['r']='7';
b['s']='7';
b['t']='8';
b['u']='8';
b['v']='8';
b['w']='9';
b['x']='9';
b['y']='9';
b['z']='9';


//Чтение входных данных
	scanf("%i\n",&n);

	for(i=0;i<n;i++)
		{
		gets(str);
		for(j=0;str[j]!=' ';j++)
		words[i][j]=str[j];
		strncpy(s,str+j+1,strlen(str)-j);
		m[i]=atoi(s);
		for(j=0;j<strlen(words[i]);j++)
		words2[i][j]=b[words[i][j]];
		}
	gets(sv);

//массив индексов
for(i=0;i<n;i++)
ind[i]=i;

//сортировка по кодам
	QuickSort1(0,n-1);

//сортировка по релевантности внутри кодов
	int x1=0,x2=0;
	for(i=1;i<n;i=i+1)
		{
			if(strcmp(words2[ind[i]],words2[ind[i-1]]) != 0 )
			{
				x2=i-1;
				QuickSort(x1,x2);
				x1=i;
			}
		if(i==n-1)
			QuickSort(x1,n-1);
		}

//сортировка по алфавиту внутри релевантности

	x1=0,x2=0;
	for(i=1;i<n;i=i+1)
		{
			if(atoi(words2[ind[i]])!=atoi(words2[ind[i-1]]) || m[ind[i]]!=m[ind[i-1]])
			{
				x2=i-1;
				QuickSort2(x1,x2);
				x1=i;
			}
		if(i==n-1)
			QuickSort2(x1,n-1);
		}


//разбор строки
	l=strlen(sv);
	for(i=0;i<l;i++)
	{
		if(sv[i]=='1') { if(sv[i-1] != ' ') vivod(); c[0]='.'; if(sv[i+1]!='*') vivod(); }
		else
			if(sv[i]=='*') { k=k+1; if(sv[i+1]!='*') vivod(); }
			else
				if(sv[i]==' ') vivod();
				else
					{ if(n1==-1)n1=i; if(n2==-1) if(sv[i+1]==' '||sv[i+1]=='*'||sv[i+1]=='1'||i==l-1)n2=i; }
		if(i==l-1 && n2!=-1) vivod();
	}
return 0;
}
