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


map<string,vectorint> dni;//карта <слово в Т9,его частоты встречаемости>
map<string,vectorstr> dns;//карта <слово в Т9,слова>
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


	dni[dict_num[i]].resize(dni[dict_num[i]].size()+1);
	dni[dict_num[i]][dni[dict_num[i]].size()-1]=freq[i];
	dns[dict_num[i]].resize(dns[dict_num[i]].size()+1);
	dns[dict_num[i]][dns[dict_num[i]].size()-1]=dict[i];

	gets(s);
}

//перестраиваем словари, dict, dict_num, freq

map<string,vectorint>::iterator iterdni=dni.begin();
vector<int>::iterator iterfreq=freq.begin();
vector<string>::iterator iterdict=dict.begin();
vector<string>::iterator iterdictn=dict_num.begin();
for(int i=0;i<=dni.size()-1;++i)
{
	for(int j=0;j<=dni[(*iterdni).first].size()-1;++j)
	{ 
		*iterfreq=dni[(*iterdni).first][j];
		++iterfreq;
		*iterdict=dns[(*iterdni).first][j];
		++iterdict;
		*iterdictn=(*iterdni).first;
		++iterdictn;
	}
	++iterdni;
}



map<string,pairint> index;//карта из пар <слово в T9, пара <1й индекс в массиве вектора слов,2й индекс там же>>
map<string,vectorint> dnfreq;//карта из пар <слово в T9, вектор его частот встречаемости>

string str_loop=dict_num[0];
int ii=0;
int jj=ii;
while(ii!=dict_num.size()-1)
{
	++ii;
	if(str_loop!=dict_num[ii])
	{
		index[dict_num[jj]].first=jj;
		index[dict_num[jj]].second=ii-1;
		str_loop=dict_num[ii];
		dnfreq[dict_num[jj]]=vector<int>(freq.begin()+jj,freq.begin()+ii);
		std::sort(dnfreq[dict_num[jj]].begin(),dnfreq[dict_num[jj]].end(),greater<int>());
		jj=ii;
	}
}
index[dict_num[ii]].first=jj;
index[dict_num[ii]].second=ii;
dnfreq[dict_num[ii]]=vector<int>(freq.begin()+jj,freq.begin()+ii+1);
std::sort(dnfreq[dict_num[ii]].begin(),dnfreq[dict_num[ii]].end(),greater<int>());


char buffer[100000]={0}; 
gets(buffer);
string str=buffer;
vector<string> input_w;//массив слов на запрос
input_w.resize(50000);


basic_string <char>::iterator iter_str=str.begin();
basic_string <char>::iterator iter_str2=str.begin();
vector<pairint> space(50000);
int iii=0;
iter_str=find(iter_str2,str.end(),' ');
if(iter_str!=str.end())
{
	while(iter_str!=str.end()&&iter_str2!=str.end())
	{
	   iter_str=find(iter_str2,str.end(),' ');
	   //if(iter_str==str.end())break;
	   space[iii].first=iter_str-str.begin();
	   iter_str2=find(iter_str+1,str.end(),' ');
	   while((iter_str2-iter_str)==1&&iter_str2!=str.end())
	   {
		   iter_str=iter_str2;
		   iter_str2=find(iter_str2+1,str.end(),' ');
	   }
	   space[iii].second=iter_str-str.begin();
	   ++iii;
	}
}
space.resize(iii);

iter_str=str.begin();
iter_str2=str.begin();
vector<pairint> vsign(50000);
iii=0;
iter_str=find(iter_str2,str.end(),' ');
if(iter_str!=str.end())
{
	while(iter_str!=str.end()&&iter_str2!=str.end())
	{
	   iter_str=find(iter_str2,str.end(),'1');
	   //if(iter_str==str.end())break;
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
}
vsign.resize(iii);
vsign.insert(vsign.begin(),space.begin(),space.end());
sort(vsign.begin(),vsign.end());


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
		char* s=(char*) malloc(dict[index[input_w[i]].first].length()+1);
		int ind=find(freq.begin()+index[input_w[i]].first,freq.begin()+index[input_w[i]].second,*dnfreq[input_w[i]].begin())
			-freq.begin();//индекс слова в векторе dict

		strcpy(s,dict[ind].c_str());
		printf("%s",s);
        freq[ind]+=1;
		++(*(dnfreq[input_w[i]].begin()));
		sort(dnfreq[input_w[i]].begin(),dnfreq[input_w[i]].end(),greater<int>());
		continue;
	}

	
	//if (star!=-1)//случай когда * левее 1 или есть *, но нет 1
	//{
		    
		int n_star=input_w[i].find_last_of('*')+1-star;
	    input_w[i]=string(input_w[i].begin(),input_w[i].end()-n_star);
		
		char* s=(char*) malloc(dict[index[input_w[i]].first].length()+1);

		int n=dnfreq[input_w[i]].begin()+n_star-find(dnfreq[input_w[i]].begin(),dnfreq[input_w[i]].end(),
			*(dnfreq[input_w[i]].begin()+n_star))+1;//нужное число раз повторений искомой частоты в векторе частот (всегда >=1)
		
		vector<int>::iterator iter0=find(freq.begin()+index[input_w[i]].first,freq.begin()+index[input_w[i]].second,
			*(dnfreq[input_w[i]].begin()+n_star));//1е вхождение слова в векторе dict 
		for (int ii=2;ii<=n;++ii)
		{
		    iter0=find(iter0+1,freq.begin()+index[input_w[i]].second+1,*(dnfreq[input_w[i]].begin()+n_star));
			   //нужное вхождение слова в векторе dict 
		}
		
		int ind2=iter0-freq.begin();//индекс искомого вхождения
		strcpy(s,dict[ind2].c_str());
		printf("%s",s);

		
		vector<int>::iterator iter=find(freq.begin()+index[input_w[i]].first,freq.begin()+index[input_w[i]].second+1,
			*(freq.begin()+ind2)+1);

		if(iter!=(freq.begin()+index[input_w[i]].second+1))
		{
			int d=iter-freq.begin();
            int x=freq[ind2]+1;
			string y=*(dict.begin()+ind2);
			freq.erase(freq.begin()+ind2);
			dict.erase(dict.begin()+ind2);
			freq.insert(freq.begin()+d,x);
			dict.insert(dict.begin()+d,y);
		}
		else
		{
			freq[ind2]+=1;
		}
		++(*(dnfreq[input_w[i]].begin()+n_star));
		sort(dnfreq[input_w[i]].begin(),dnfreq[input_w[i]].end(),greater<int>());

	//}

    

}

//while(int i=1){};

}
