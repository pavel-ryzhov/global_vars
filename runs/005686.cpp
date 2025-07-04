#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

struct wrd
{
	int word;
	string str;
	int rate;
};

int transl(char a)
{
	switch (a)
	{
	case 'a':
	case 'b':
	case 'c':
		return 2;
		break;
	case 'd':
	case 'e':
	case 'f':
		return 3;
		break;
	case 'g':
	case 'h':
	case 'i':
		return 4;
		break;
	case 'j':
	case 'k':
	case 'l':
		return 5;
		break;
	case 'm':
	case 'n':
	case 'o':
		return 6;
		break;
	case 'p':
	case 'q':
	case 'r':
	case 's':
		return 7;
		break;
	case 't':
	case 'u':
	case 'v':
		return 8;
		break;
	case 'w':
	case 'x':
	case 'y':
	case 'z':
		return 9;
		break;
	default:
		cout<<"Error of input #1"<<endl;
		return 0;
	}
}

int search(wrd *vcb,int num,int sm)
{
	int ind=-1;
	int max_rate=0;
	for (int i=0;i<num;i++)
	{
		if (vcb[i].word==sm&&vcb[i].rate>max_rate)
		{
			max_rate=vcb[i].rate;
			ind=i;
		}
	}
	vcb[ind].word=0;

	return ind;
}

int rebilding (wrd *vcblr, int ind)
{
	string buf,neo;
	neo=vcblr[ind].str;
	for (int i=0;i<=ind;i++)
	{
		if (vcblr[i].word==vcblr[ind].word&&vcblr[i].rate==vcblr[ind].rate)
		{
			buf=vcblr[i].str;
			vcblr[i].str=neo;
			neo=buf;
		}
	}
	return 0;
}

void reading (wrd *vcblr, int number)
{
	char a;
	int word,rate;
	word=rate=0;
	cin>>a;
	for (int i=0;i<number;)
	{
		if (isalpha(a)||a=='.'||a=='?'||a==',')
		{
			word=word*10 + transl(a);
			vcblr[i].str+=a;
		}

		if (isdigit(a))
			rate=rate*10 + a - 48;

		if (a=='\n')
		{
			vcblr[i].rate=rate;
			vcblr[i].word=word;
			word=0;
			rate=0;
			i++;
		}

		if (i<number)
			a=cin.get();
	}
}

int SMSing (wrd *vcblr, int number)
{
	char a;
	int sms=0;
		a=cin.get();
	bool flag=true;

	while(cin&&flag)
	{
		if(isdigit(a)&&a!='1')
		{
			sms=sms*10+a-48;
			a=cin.get();
		}
		else
		{
			if (sms!=0)
			{
				int index=0;
				wrd *vcbl;
				vcbl=new wrd[number];
				for (int i=0;i<number;i++)
				{
					vcbl[i].rate=vcblr[i].rate;
					vcbl[i].str=vcblr[i].str;
					vcbl[i].word=vcblr[i].word;
				}
				index=search(vcbl,number,sms);

				while (a=='*')
				{
					index=search(vcbl,number,sms);
					a=cin.get();
				}

				if (index>=0)
				{
					vcblr[index].rate++;
					cout<<vcblr[index].str;
					rebilding (vcblr,index);
				}
				else
					cout<<" Указанного сочетания не найдено ";
				sms=0;
			}
			else
				if (a=='1')
				{
					a=cin.get();
					switch(a)
					{
					case '1':
					case ' ':
						cout<<'.';
						break;
					case '\n':
						cout<<'.'<<endl;
						flag=false;
						break;
					case '*':
						char zn='.';
						while (a=='*')
						{
							switch (zn)
							{
								case '.':
									zn=',';
									break;
								case ',':
									zn='?';
									break;
								case '?':
									zn='.';
									break;
							}
							a=cin.get();
						}
						cout<<zn;
					}
				}
				else
				{
					if (a==' ')
					{
						cout<<' ';
						a=cin.get();
					}

					if (a=='\n')
					{
						cout<<endl;
						break;
					}
				}
		}

	}
	return 0;
}

int main()
{
	int number;
	cin>>number;
	if (number<3)
	{
		cout<<"Слишком малепнький словарь!"<<endl;
		exit(1);
	}
	if (number>5000)
	{
		cout<<"Слишком крупный словарь!"<<endl;
		exit(1);
	}

	wrd *vocabulary;
	vocabulary=new wrd[number];

	reading (vocabulary,number);
	SMSing(vocabulary,number);
	return 0;
}
