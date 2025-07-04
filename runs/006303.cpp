#include <iostream>
#include <vector>
#include <list>
#include <string> 
#include <map>

using namespace std;

class t9
{
private:
	map<int, list<pair<int, string> > > dict;
	int n, feq, len; 
	vector<int> seq;
	string total;
	string temp;
	string digits, word;
	int cStar;
	bool stop, one;
	
public:
	t9()
	{
		
		cStar = 0;
		stop = false;
		one = false;

		init();
		char kostil;
		//cin.get(kostil);
		kostil = getchar();

		while(1)
		{	
			//cin.get(kostil);
			kostil = getchar();
			switch(kostil)
			{
			case ' ' : 
				  {
					if(!word.empty())
					{
						followNum();
					}
					word.clear();
					if(one)
					{
						if(cStar == 0) total.push_back('.'); //cout<<'.';
						if(cStar == 1) total.push_back(','); //cout<<',';
						if(cStar == 2) total.push_back('?'); //cout<<'?';
						one = false;
						cStar = 0;
					}
					//cout<<' '; 
					total.push_back(' ');
				  }break;

			case '1' :
				  {
					if(!word.empty())
					{
						followNum();
					}
					word.clear();
					if(one)
					{
						if(cStar == 0) total.push_back('.'); //cout<<'.';
						if(cStar == 1) total.push_back(','); //cout<<',';
						if(cStar == 2) total.push_back('?'); //cout<<'?';
						one = false;
						cStar = 0;
					}
					one = true;
				  }break;

			case '\n':
				  {
					if(!word.empty())
						followNum();
					if(one)
					{
						if(cStar == 0) total.push_back('.'); //cout<<'.';
						if(cStar == 1) total.push_back(','); //cout<<',';
						if(cStar == 2) total.push_back('?'); //cout<<'?';
						one = false;
						cStar = 0;
					}
					stop = true;
				  }break;

			case '*' : 
				  {
					if(one)
					{
						cStar++;
						if(cStar==3) cStar = 0;
					}
					else
					{
						word.push_back(kostil);
					}
				  }break;

			default: 
				{
					if(one)
					{
						if(cStar == 0) total.push_back('.'); //cout<<'.';
						if(cStar == 1) total.push_back(','); //cout<<',';
						if(cStar == 2) total.push_back('?'); //cout<<'?';
						one = false;
						cStar = 0;
					}
					word.push_back(kostil); 
				}break;
			}


			if (stop) break;

		}
	showWord();
	}

	~t9(){}

	void init() 
	{
		cin>>n;
		for (int i=0; i < n; i++)
		{
			cin>>temp>>feq;
			for(int i=0, size=temp.size(); i != size; i++)
			{
				seq.push_back( mapping(temp[i]) );	
			}
			pair<int, string> pos;
			pos.first = feq;
			pos.second = temp;
			int n=0, p=1;
			
			for(int i=seq.size(); i!=0; i--)
			{
				n+= seq[i-1]*p;
				p*=10;
			}
			dict[n].push_back(pos);
			dict[n].sort(compareA);
			dict[n].sort(compareF);
			seq.clear();
		}
	}
	
	int mapping(char s)
	{
		if( s=='a' || s=='b' || s=='c') return 2;
		if( s=='d' || s=='e' || s=='f') return 3;
		if( s=='g' || s=='h' || s=='i') return 4;

		if( s=='j' || s=='k' || s=='l') return 5;
		if( s=='m' || s=='n' || s=='o') return 6;
		if( s=='p' || s=='q' || s=='r' || s=='s') return 7;
		
		if( s=='t' || s=='u' || s=='v') return 8;
		if( s=='w' || s=='x' || s=='y' || s=='z') return 9;

		return 666;
	}





	static bool compareF (pair <int, string> p1, pair <int, string> p2)
	{
		return (p1.first > p2.first);
	}

	static bool compareA (pair <int, string> p1, pair <int, string> p2)
	{
		return (p1.second < p2.second);
	}
	
	void showWord()
	{	
		cout<<total;	
		//printf("%s", total.c_str());
	}

	
	void followNum()
	{
		int f=0, p=1;
		bool brone=false;
		cStar = 0;
		for(int i=0, size = word.size(); i!=size; i++)
		{
			switch(word[i])
			{
			case '*': 
				{
					cStar++;
				}break;

			default: break;
			}
		}
		if(brone==false)
		{
			for(int j=word.size()-cStar; j!=0; j--)\
			{
				f+= (word[j-1]-'0')*p;
				p*=10;
			}
			list<pair<int,string> >::iterator it = dict[f].begin();
			advance(it,cStar);			
			total += it->second.c_str();
			//cout << it->second;
			it->first++;
			pair<int,string> t;
			t.first = it->first;
			t.second = it->second;
			dict[f].erase(it);
			dict[f].push_front(t);
			dict[f].sort(compareF);

			cStar = 0;
			f=0; p =0;
			
		}
	}	
};

int main(int argc, char ** argv)
{
	t9 test;
	
	return 0;
}