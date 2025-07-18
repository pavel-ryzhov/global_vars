#include <stdio.h>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

struct cifr 
{
	char w[20];
	bool operator<(const cifr& st) const {return std::strcmp(w , st.w) < 0; }
};

struct word
{
	unsigned short int f;
	char w[20];
	bool operator<(const word& w) const {return f<w.f; }
};

bool lesser(const word& a, const word& b)
{
   return a.f>b.f;
}

void conv(char bufs[20], cifr &convs)
{
	int buf;
	int i=0;
	for (; bufs[i] != '\0'; i++)
	{
		buf  = bufs[i];
		if ((buf > 96) && (buf < 100))
			{convs.w[i]= '2'; continue;}
		if ((buf > 99) && (buf < 103))
			{convs.w[i]= '3'; continue;}
		if ((buf > 102) && (buf < 106))
			{convs.w[i]= '4'; continue;}
		if ((buf > 105) && (buf< 109))
			{convs.w[i]= '5'; continue;}
		if ((buf > 108) && (buf< 112))
			{convs.w[i]= '6'; continue;}
		if ((buf > 111) && (buf < 116))
			{convs.w[i]= '7'; continue;}
		if ((buf > 115) && (buf < 119))
			{convs.w[i]= '8'; continue;}
		if ((buf > 118) && (buf < 123))
			{convs.w[i]= '9'; continue;}
	}
	convs.w [i] = '\0';
}

int main(void)
{
	freopen("out.txt","w", stdout);
	freopen("1.txt","r", stdin);
	map< cifr , vector <word> > Slovar;
	map< cifr , vector <word> >::iterator p;
	vector <word> ::iterator pv;
	vector <word> ::iterator pvb;
	unsigned short int N_slov;
	cifr convs;
	word wbuf;

	scanf("%hd\n",&N_slov);
	for (int i=0; i<N_slov; i++)
	{
		scanf("%s %hd\n", wbuf.w, &wbuf.f);
		conv(wbuf.w, convs);
		Slovar[convs].push_back(wbuf); 
	}

	for (p=Slovar.begin(); p!=Slovar.end(); p++) 
		sort(p->second.begin(), p->second.end(), lesser);  

	int c=0, i, ct=0;
	char cbuf;

    for (;;)
	{

		i=0;
		convs.w[0]='\0';
		while ((c = getc(stdin)) > 49)
		{
			convs.w[i]=c;
			i++;
		}
		if (i)
		{
			convs.w[i]='\0';	//конец строки
			if (c==' ')//32
			{
				printf ("%s ",Slovar[convs].begin()->w);
				Slovar[convs].begin()->f++;
				continue;			
			}
			if (c=='1')
			{
				printf ("%s",Slovar[convs].begin()->w);
				Slovar[convs].begin()->f++;			
			}

			if  (c=='*') 
			{
				ct = 1;
				pvb= Slovar[convs].begin();
				while ((c = getc(stdin)) == '*')
					ct++;
				pv=pvb+ct;
				pv->f++;
				while ((pv!=pvb) && (pv->f>=(pv-1)->f))
				{
					iter_swap((pv-1), pv);
					pv --;
				}
				sort(Slovar[convs].begin(), pv, lesser);//пересортировка
				printf ("%s", pv->w);
				if (c==' ') printf(" ");
			}
		}
			
		if  (c=='1') 
		{
			ct = 0;
			while ((c = getc(stdin)) == '*')
				ct++;
			switch (ct)
			{
				case 0: cbuf = '.'; break;
				case 1: cbuf = ','; break;
				case 2: cbuf = '?'; break;
			}
			printf("%c", cbuf);
			if (c==' ') printf(" ");
			continue;
		}

		if  (c==EOF)
		{
			if (convs.w[0]!='\0') 
				printf ("%s",Slovar[convs].begin()->w);
			break;
		}
	}		
	return 0;
}

