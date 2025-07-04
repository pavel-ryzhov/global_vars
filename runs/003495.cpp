// task3.cpp: определяет точку входа для консольного приложения.
//


#include <stdio.h>
//#include <tchar.h>
#include <vector>
#include <iostream>
#include <string>
//#include <fstream>
#include <stdlib.h>

using namespace std;
FILE *fp,*fp1;


class Word
{
	public:
	string n;
	int num,freak;
	
	
	
	void init_num()
	{
		int i=0;
		while(i!=(n.length()))
		{
			if (n[i]<97)
			{cerr<<"error";}
			else if (((n[i]-97)/3)+1<2)
			{num=num*10+2;}
			else if (((n[i]-97)/3)+1<3)
			{num=num*10+3;}
			else if (((n[i]-97)/3)+1<4)
			{num=num*10+4;}
			else if (((n[i]-97)/3)+1<5)
			{num=num*10+5;}
			else if (((n[i]-97)/3)+1<6)
			{num=num*10+6;}
			else if (n[i]<115)
			{num=num*10+7;}
			else if (n[i]<118)
			{num=num*10+8;}
			else if (n[i]<122)
			{num=num*10+9;}
			else 
			{cerr<<"error";}
			i++;
		}
		

	}
	Word(){num=0;}
	~Word(){}
	
private:
	Word(string N,int &x,int &y)
	{
		n=N;
		freak=x;
		num=y;
	}


};
int main()
{
	
	int N,x=0,y=0,i,m;
	//fp=fopen("input","r");
	//fp1=fopen("output","w");
	//ofstream to("output");

	string c;
	char p;
	p=char(getchar());
	N=atoi(&p);
	vector<Word>dict(N);
	p=char(getchar());
	p=char(getchar());
	for(i=0;i<N;i++)
	{
		while(p!=' ')
		{
		//p=char(getc(fp));
		c.push_back(p);
		p=char(getchar());
		};
		while(p!='\n')
		{
		
		x=10*x+atoi(&p);
		p=char(getchar());
		};
		dict[i].freak=x;
		dict[i].n=c;
		dict[i].init_num();
		c.erase();
		x=0;
		p=char(getchar());

	};
	int f=0;
	vector<int>s;
	while(p!=EOF)
	{
		i=0;
		
		y=0;
		while(((p!=' ')&&(p!='*'))&&(p!='1'))
		{
		y=y*10+atoi(&p);
		p=char(getchar());
		};
		
		s.clear();
	
		for(x=0;x<N;x++)
		{
			if(dict[x].num==y){s.push_back(x);i++;}
		}
		
		for(x=0;x<i-1;x++)
			for(y=i-1;y>x;y--)
			{
				if (dict[s[y]].freak > dict[s[y-1]].freak){swap(s[y],s[y-1]);}
			}
		
		i=1;
		if(p=='*')
		{
			while((p=char(getchar()))=='*'){i++;}
			
			cout<<dict[s[i]].n;
			dict[s[i]].freak++;
			dict.insert(dict.begin(),dict[s[i]]);
			dict.erase(dict.begin()+s[i]+1);
			i=1;
		}
	
		else if(p=='1')
		{
			cout<<dict[s[0]].n;
			dict[s[0]].freak++;
			dict.insert(dict.begin(),dict[s[0]]);
			dict.erase(dict.begin()+s[0]+1);
			
		}
		else{
			cout<<dict[s[0]].n;
			dict[s[0]].freak++;
			dict.insert(dict.begin(),dict[s[0]]);
			dict.erase(dict.begin()+s[0]+1);
		}
if((p!='1')&&(p!=EOF))
{cout<<' ';p=char(getchar());}
else{if((p=char(getchar()))=='*')
			{
				while((p=char(getchar()))=='*'){i++;}
				if(i==1){cout<<',';}
				else{cout<<'?';}
			}
	else{cout<<'.';}
	p=char(getchar());if(p!=EOF){cout<<' ';} }
	
	};

	
	//system("PAUSE");
	return 0;
}

