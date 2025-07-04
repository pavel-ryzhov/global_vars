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
	gets(s);
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
int nw=0;
basic_string <char>::iterator iter_str=find(str.begin(),str.end(),' ');
input_w[nw]=string(str.begin(),iter_str);

for(;iter_str<str.end();)
{
    ++nw;
	basic_string <char>::iterator iter_str0 = iter_str+1;
    iter_str=std::find(iter_str+1,str.end(),' ');
	input_w[nw]=string(iter_str0,iter_str);
}
input_w.resize(nw+1);

for (int i=0;i<input_w.size()-1;++i)
{
	int star=input_w[i].find_first_of('*');
	int one=input_w[i].find_first_of('1');
	if ((star==-1)&&(one==-1))
	{
		char* s=(char*) malloc(dict[index[input_w[i]].first].length()+1);
		int ind=find(freq.begin()+index[input_w[i]].first,freq.begin()+index[input_w[i]].second,*dnfreq[input_w[i]].begin())
			-freq.begin();//индекс слова в векторе dict

		strcpy(s,dict[ind].c_str());
		printf("%s ",s);
	}

	if( ((one!=-1)&&(one<star))||((one!=-1)&&(star==-1)) )
	{   
		string s_one;
		s_one=string(input_w[i].begin()+input_w[i].find_first_of('1'),input_w[i].end());
        input_w[i]=string(input_w[i].begin(),input_w[i].begin()+input_w[i].find_first_of('1'));

		char* s=(char*) malloc(dict[index[input_w[i]].first].length()+1);
		int ind=find(freq.begin()+index[input_w[i]].first,freq.begin()+index[input_w[i]].second,*dnfreq[input_w[i]].begin())
			-freq.begin();//индекс слова в векторе dict

		strcpy(s,dict[ind].c_str());
		printf("%s",s);

		s=(char*) malloc(sign[s_one].length()+1);
		strcpy(s,sign[s_one].c_str());
		printf("%s",s);

	}


	
	if ((star!=-1)&&((star<one)||(one==-1)))//случай когда * левее 1 или есть *, но нет 1
	{
		int n_star;
		//int n_star2;
		string s_one;
		bool one_flag=false;
		if (one==-1) 
		{
			n_star=input_w[i].find_last_of('*')+1-star;
		    input_w[i]=string(input_w[i].begin(),input_w[i].end()-n_star);
		}
		else
		{
			one_flag=true;
			n_star=input_w[i].find_first_of('1')-star;
			s_one=string(input_w[i].begin()+input_w[i].find_first_of('1'),input_w[i].end());

			input_w[i]=string(input_w[i].begin(),input_w[i].begin()+input_w[i].find_first_of('*'));
			
			//nstar2=input_w[i].find_last_of('*')-find_first_of('1');
			//if(nstar2==-1)nstar2=0;
		}
		
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
		if(one_flag)printf("%s",s);
		else printf("%s ",s);
		
		vector<int>::iterator iter=find(freq.begin()+index[input_w[i]].first,freq.begin()+index[input_w[i]].second+1,
			*(freq.begin()+ind2)+1);

		if(iter!=freq.end())
		{
			int d=iter-freq.begin();
			int k=freq.size();
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

		if (one_flag)
		{	
            char* s=(char*) malloc(sign[s_one].length()+1);
			strcpy(s,sign[s_one].c_str());
		    printf("%s",s);
			continue;
        }

	}

    

}

//while(int i=1){};

}
