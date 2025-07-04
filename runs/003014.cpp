#include <vector>
#include <stdio.h>
#include <string>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;
using std::vector;
using std::multimap;
using std::string;
using std::map;

vector<string> dict;//вектор слов
vector<string> dict_num;//вектор слов в формате Т9
vector<int> freq;//вектор частоты встречаемости слов

map<char,char> keyboard;
typedef std::pair<int,int> pairint;
typedef std::pair<char,char> pairchar;
typedef vector<int>::const_iterator const_graph_iter;
typedef vector<int> vectorint;
typedef vector<string> vectorstr;
typedef std::pair<int,string> pairintstr;
typedef vector<pairintstr> vectorintstr;
typedef std::pair<int*,string*> p_pairintstr;

bool SortPair(const pairintstr &p1, const pairintstr &p2)
{
    return p1.first > p2.first;
}


int main()
{

map<string,string> sign;
sign["1"]=".";
sign["1*"]=",";
sign["1**"]="?";

pairchar kb[26];
kb[0]=pairchar('a','2');
kb[1]=pairchar('b','2');
kb[2]=pairchar('c','2');
kb[3]=pairchar('d','3');
kb[4]=pairchar('e','3');
kb[5]=pairchar('f','3');
kb[6]=pairchar('g','4');
kb[7]=pairchar('h','4');
kb[8]=pairchar('i','4');
kb[9]=pairchar('j','5');
kb[10]=pairchar('k','5');
kb[11]=pairchar('l','5');
kb[12]=pairchar('m','6');
kb[13]=pairchar('n','6');
kb[14]=pairchar('o','6');
kb[15]=pairchar('p','7');
kb[16]=pairchar('q','7');
kb[17]=pairchar('r','7');
kb[18]=pairchar('s','7');
kb[19]=pairchar('t','8');
kb[20]=pairchar('u','8');
kb[21]=pairchar('v','8');
kb[22]=pairchar('w','9');
kb[23]=pairchar('x','9');
kb[24]=pairchar('y','9');
kb[25]=pairchar('z','9');

for(int i=0;i<=25;++i)
{
	keyboard.insert(kb[i]);
}

int N;
scanf("%d",&N);
dict.resize(N);
dict_num.resize(N);
freq.resize(N);

map<string,vectorintstr> dnis;
for(int i=0;i<=N-1;++i)
{
    char s[22]={0};
	scanf("%s%d",s,&freq[i]);
	dict[i]=s;
	dict_num[i]=s;
	for(int j=0;j<=dict[i].size()-1;++j)
	{
		std::replace(&dict_num[i][j],&dict_num[i][j+1],dict_num[i][j],keyboard[dict[i][j]]);
	}	

	dnis[dict_num[i]].resize(dnis[dict_num[i]].size()+1);
	dnis[dict_num[i]][dnis[dict_num[i]].size()-1].first=freq[i];
	dnis[dict_num[i]][dnis[dict_num[i]].size()-1].second=dict[i];

	gets(s);
}


for(int i=0;i<=dnis.size()-1;++i)
{  
   map<string,vectorintstr>::iterator iterdnis=dnis.begin();
   sort((iterdnis->second).begin(),(iterdnis->second).end(),SortPair);
   ++iterdnis;
   
}


char buffer[100000]={0}; 
gets(buffer);
string str=buffer;
vector<string> input_w(50000);//массив слов на запрос


basic_string <char>::iterator iter_str=str.begin();
basic_string <char>::iterator iter_str2=str.begin();
vector<pairint> space(50000);//вектор пар <1й индекс в серии пробелов, последний индекс в серии пробелов>
int iii=0;
while((iter_str!=str.end())&&(iter_str2!=str.end()))
{
   iter_str=find(iter_str2,str.end(),' ');
   if(iter_str==str.end())break;
   space[iii].first=iter_str-str.begin();
   iter_str2=find(iter_str+1,str.end(),' ');
   while(((iter_str2-iter_str)==1)&&(iter_str2!=str.end()))
   {
	   iter_str=iter_str2;
	   iter_str2=find(iter_str2+1,str.end(),' ');
   }
   space[iii].second=iter_str-str.begin();
   ++iii;
}
space.resize(iii);


iter_str=str.begin();
iter_str2=str.begin();
vector<pairint> vsign(50000);//вектор пар <1й индекс в серии "1***...", последний индекс там же>
iii=0;
while(iter_str!=str.end()&&iter_str2!=str.end())
{
   iter_str=find(iter_str2,str.end(),'1');
   if(iter_str==str.end())break;
   vsign[iii].first=iter_str-str.begin();
   iter_str2=find(iter_str+1,str.end(),'*');
   while((iter_str2-iter_str)==1&&iter_str2!=str.end())
   {
	   iter_str=iter_str2;
	   iter_str2=find(iter_str2+1,str.end(),'*');
   }
   vsign[iii].second=iter_str-str.begin();
   iter_str2=iter_str+1;
   ++iii;
}
vsign.resize(iii);
vsign.insert(vsign.end()-1,space.begin(),space.end());//объединение векторов vsign & space
sort(vsign.begin(),vsign.end());


//заполнение вектора слов input_w на запрос
if(vsign.size()!=0)
{
if(vsign[0].first==0)
{
	int j=0;
	int i=0;
    int sizex=vsign.size();
	int nnn=sizex-2;
	for(i=0;i<=nnn;++i)
	{
		input_w[j]=str.substr(vsign[i].first,vsign[i].second-vsign[i].first+1);
		++j;
		if((vsign[i+1].first-1)!=vsign[i].second)
		{
		   input_w[j]=str.substr(vsign[i].second+1,vsign[i+1].first-vsign[i].second-1);
		   ++j;
		}
	}

	if(vsign[vsign.size()-1].second==str.size()-1)
	{
		input_w[j]=str.substr(vsign[i].first,vsign[i].second-vsign[i].first+1);
	}
	else
	{
        input_w[j]=str.substr(vsign[i].first,vsign[i].second-vsign[i].first+1);
		++j;
		input_w[j]=str.substr(vsign[i].second+1,str.end()-(str.begin()+vsign[i].second)-1);
	}
	input_w.resize(j+1);
}
else
{
    int j=1;
	int i=0;
	input_w[0]=str.substr(0,vsign[0].first);
	int sizex=vsign.size();
	int nnn=sizex-2;
	for(i=0;i<=nnn/*(vsign.size()-2)*/;++i)//если вместо nnn писать vsign.size()-2,почему-то заходит в цикл
	{
		input_w[j]=str.substr(vsign[i].first,vsign[i].second-vsign[i].first+1);
		++j;
		if((vsign[i+1].first-1)!=vsign[i].second)
		{
		   input_w[j]=str.substr(vsign[i].second+1,vsign[i+1].first-vsign[i].second-1);
		   ++j;
		}
	}
	if(vsign[vsign.size()-1].second==str.size()-1)
	{
		input_w[j]=str.substr(vsign[i].first,vsign[i].second-vsign[i].first+1);
	}
	else
	{
        input_w[j]=str.substr(vsign[i].first,vsign[i].second-vsign[i].first+1);
		++j;
		input_w[j]=str.substr(vsign[i].second+1,str.end()-(str.begin()+vsign[i].second)-1);
	}
	input_w.resize(j+1);
}
}
else
{
  input_w[0]=str.substr(0,str.end()-str.begin());
  input_w.resize(1);
}

for (int i=0;i<input_w.size();++i)
{
	if (input_w[i][0]==' ')
	{ 
        char* s=(char*) malloc(input_w[i].length()+1);
		strcpy(s,input_w[i].c_str());
		printf("%s",s);
		continue;
	}
	if (input_w[i][0]=='1')
	{ 
        char* s=(char*) malloc(input_w[i].length()+1);
		strcpy(s,sign[input_w[i]].c_str());
		printf("%s",s);
		continue;
	}

	int star=input_w[i].find_first_of('*');
	if (star==-1)
	{
		char* s=(char*) malloc(input_w[i].length()+1);

		strcpy(s,(dnis[input_w[i]].begin())->second.c_str());
		printf("%s",s);
		((dnis[input_w[i]].begin())->first)+=1;
		continue;
	}

		    
		const int n_star=input_w[i].find_last_of('*')+1-star;
	    input_w[i]=string(input_w[i].begin(),input_w[i].end()-n_star);
		
		char* s=(char*) malloc(input_w[i].length()+1);

		strcpy(s,(dnis[input_w[i]].begin()+n_star)->second.c_str());
        printf("%s",s);

		
		vector<pairintstr>::iterator iter=dnis[input_w[i]].begin()+n_star;/*,dnis[input_w[i]].end(),(dnis[input_w[i]].end()-1-n_star)->first+1);*/
		int s_freq=(dnis[input_w[i]].begin()+n_star)->first;
		int s_freq2=s_freq+1;
		int s_ind=-1;
		const int x0=0;
		const int xn=n_star-1;
		for(int j=xn;j>=x0;--j)
		{
            --iter;
			if(iter->first==s_freq) s_ind=j;
			else
			{ 
                if(iter->first==s_freq2) 
			    {
				   s_ind=j;
			    }
				else break;
				int nnn=j-1;
				for(int jj=nnn;jj>=x0;--jj)
				{
				   --iter;
                   if(iter->first==s_freq2) 
				   {
					   s_ind=jj;
				   }
				   else break;
                }
				break;
			}
		} //поиск частоты, на 1 большей найденной

		if(s_ind!=-1)
		{
			pairintstr pis=*(dnis[input_w[i]].begin()+n_star);
			pis.first+=1;
			dnis[input_w[i]].erase((dnis[input_w[i]].begin()+n_star));
			dnis[input_w[i]].insert(dnis[input_w[i]].begin()+s_ind,pis);
		}
		else
		{
			(dnis[input_w[i]].begin()+n_star)->first+=1;
		}   

}

}
