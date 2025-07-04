#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

struct wrd
{
	int word;
	string str;
	int rate;
	bool flag;
	wrd()
	{
		flag=true;
	}
};

int search(wrd *vcb,int num,int sm)
{
	int ind=-1;
	int max_rate=0;
	for (int i=0;i<num;i++)
	{
		if (vcb[i].word==sm&&vcb[i].rate>max_rate&&vcb[i].flag)
		{
			max_rate=vcb[i].rate;
			ind=i;
		}
	}
	vcb[ind].flag=false;

	return ind;
}

int main()
{
	int number;
	cin>>number;

	if (number>2&&number<50001)
	{
		wrd *vcblr;
		vcblr=new wrd[number];
		char a,zn='.';
		int word,rate,sms;
		sms=word=rate=0;
		cin>>a;
		for (int i=0;i<number;)
		{
			if (isalpha(a)||a=='.'||a=='?'||a==',')
			{
				int tr;
				switch (a)
				{
				case 'a':
				case 'b':
				case 'c':
					tr=2;
					break;
				case 'd':
				case 'e':
				case 'f':
					tr=3;
					break;
				case 'g':
				case 'h':
				case 'i':
					tr=4;
					break;
				case 'j':
				case 'k':
				case 'l':
					tr=5;
					break;
				case 'm':
				case 'n':
				case 'o':
					tr=6;
					break;
				case 'p':
				case 'q':
				case 'r':
				case 's':
					tr=7;
					break;
					case 't':
				case 'u':
					case 'v':
					tr=8;
					break;
				case 'w':
				case 'x':
				case 'y':
				case 'z':
					tr=9;
					break;
				default:
					tr=0;
					break;
				}
				word=word*10 + tr;
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
					index=search(vcblr,number,sms);
	
					while (a=='*')
					{
						index=search(vcblr,number,sms);
						a=cin.get();
					}
	
					if (index>=0)
					{
						vcblr[index].rate++;
						cout<<vcblr[index].str;
						string buf,neo;
						neo=vcblr[index].str;
						for (int i=0;i<=index;i++)
						{
							if (vcblr[i].word==vcblr[index].word&&vcblr[i].rate==vcblr[index].rate)
							{
								buf=vcblr[i].str;
								vcblr[i].str=neo;
								neo=buf;
							}
						}
						for (int i=0;i<number;i++)
							vcblr[i].flag=true;
					}
					else
						break;
					sms=0;
				}
				else
					if (a=='1')
					{
						a=cin.get();
						switch(a)
						{
						case '\n':
							cout<<'.'<<endl;
							flag=false;
							break;
						case '*':
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
							zn='.';
							break;
	
						default:
							if (isdigit(a)||a==' ')
							{
								cout<<'.';
								break;
							}
							break;
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
	}
	return 0;
}
