#include <iostream>
#include <string.h>
using namespace std;

	struct dict
	{
		char word[20];
		short pr;
		float kod;
	};
	int cc(char c)//ÍÓ‰ ÒËÏ‚ÓÎ‡
	{
		if((c>=97)&&(c<=111))
			return (c-97)/3+2;
		if((c>=112)&&(c<=115))
			return (c-97)/7+5;
		if((c>=119)&&(c<=122))
			return (c-97)/7+6;
		if((c>=116)&&(c<=128))
			return 8;
		
	}
	float code(char word[20])//ÍÓ‰ ÒÎÓ‚‡
	{	float res=0;
		float p=0.1;
		for(unsigned short k=0;k<strlen(word);k++)
		{
			res=res+cc(word[k])*p;
			p=p/10;
		}
		res=res+strlen(word);
		return res;
	}
	
	int sort(dict *d1,int i)
	{
		int res=i;
		int j;
		dict sl;
		for(int k=i;k>0;k--)
		{
			if((d1[k].kod<d1[k-1].kod)||((d1[k].kod==d1[k-1].kod)&&(d1[k].pr>d1[k-1].pr)))
			{
				sl.kod=d1[k-1].kod;
				sl.pr=d1[k-1].pr;
				strcpy(sl.word,d1[k-1].word);
				d1[k-1].kod=d1[k].kod;
				d1[k-1].pr=d1[k].pr;
				strcpy(d1[k-1].word,d1[k].word);
				d1[k].kod=sl.kod;
				d1[k].pr=sl.pr;
				strcpy(d1[k].word,sl.word);
				res=k-1;
			}
			j=0;
			if((d1[k].kod==d1[k-1].kod)&&(d1[k].pr==d1[k-1].pr))
			{
				while((d1[k].word[j]==d1[k-1].word[j])&&(d1[k-1].word[j]!='/0')&&(d1[k-1].word[j]!='/0'))
					j++;
				if(d1[k].word[j]<d1[k-1].word[j])
				{
					sl.kod=d1[k-1].kod;
					sl.pr=d1[k-1].pr;
					strcpy(sl.word,d1[k-1].word);
					d1[k-1].kod=d1[k].kod;
					d1[k-1].pr=d1[k].pr;
					strcpy(d1[k-1].word,d1[k].word);
					d1[k].kod=sl.kod;
					d1[k].pr=sl.pr;
					strcpy(d1[k].word,sl.word);
					res=k-1;
				}
			}
		}
		return res;
	}
	
	char *search(dict *d,int f,int n,float id,int kz)
	{
		int l=(n+f)/2;
		if((l==n)&&(d[l].kod!=id))
			return 0;
		if(d[l].kod==id)
		{
			do
			{
				l--;
			}
			while(d[l].kod==id);
			l=l+1+kz;
			d[l].pr++;
			
			return d[sort(d,l)].word;
		}
		if(id>d[l].kod)
			return search(d,l+1,n,id,kz);
		if(id<d[l].kod)
			return search(d,0,l,id,kz);
		
	}
	
int main (int argc, char * const argv[]) {	
	{
		int n,kz,ind;
		float *hz= new float;//
		float p,id;
		dict *d1;
		char  c='\0';//ÁÌ‡Í ÔÂÔËÌ‡ÌËˇ
		char buf[30];//Ò˜ËÚ‡ÌÌÓÂ ÍÓÏ·ËÌ‡ˆËˇ ˆËÙ
		cin>>n;
		d1=new dict[n];
		for(unsigned short i=0;i<n;i++)
		{
			cin>>d1[i].word;
			cin>>d1[i].pr;
			d1[i].kod=code(d1[i].word);
			sort(d1,i);
			
		}
		while(cin.get()!='/n')
		{
			cin>>buf;
			kz=0;
			id=0;
			ind=strlen(buf);
			while((buf[ind-1]=='*')||(buf[ind-1]=='1'))
			{
				if(buf[ind-1]=='*')
					kz++;
				if(buf[ind-1]=='1')
				{
					switch(kz)
					{
						case 0:c='.';
							break;
						case 1:c=',';
							break;
						case 2:c='?';
					}
					kz=0;
				}
				ind--;
			}
			p=0.1;
			for(int i=0;i<ind;i++)
			{
				id=(buf[i]-48)*p+id;
				p=p/10;
			}
			id=id+ind;
			cout<<search(d1,0,n,id,kz)<<' '<<c;
		}
		delete []d1;
		return 0;
	}
}
