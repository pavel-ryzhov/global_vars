#include <iostream>
#include <vector>
#include <list>
#include <string> 



using namespace std;

class t9
{
private:
	vector<vector<list<pair<int, string> > > > dict;
	int n, feq, len; 
	vector<int> seq;
	string total;
	string temp;
	string digits, word;
	int cNode, cLeavel, cStar;
	
public:
	t9()
	{
		dict.resize(10, vector<list<pair<int, string> > > (21));
		cStar = 0;
		cNode = 0;
		cLeavel = 0;
		
		init();
		char kostil;
		cin.get(kostil);

		while(1)
		{	
			cin.get(kostil);
			if(kostil == '\n')
			{
				followNum(0);
				break;
			}	
			if(kostil != ' ')
				word.push_back(kostil);
			if(kostil == ' ')
			{
				followNum(0);
				word.clear();
			}
				
		}

			//cin >> word;
			//	followNum(0);
			//cout<<'\n'<<' '<<EndTime-StartTime;
	}

	~t9(){}

	void init() 
	{
		cin>>n;
		for (int i=0; i < n; i++)
		{
			cin>>temp>>feq;
			for(int i=0; i != temp.size(); i++)
			{
				seq.push_back( mapping(temp[i]) );	
			}
			put(0, 0);
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


	
	void put(int node, int leavel=0)
	{
		
		if(leavel != seq.size())
		{
			node = seq[leavel];
			put(node, leavel+1);
		}
		if(leavel == seq.size())
		{
			pair<int, string> pos;
			pos.first = feq;
			pos.second = temp;
			dict[node][leavel].push_back(pos);
			dict[node][leavel].sort(compareA);
			dict[node][leavel].sort(compareF);
			leavel = 0;
		}
		
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
	}

	
	void followNum(int node, int leavel=0)
	{
		
		if (leavel != word.size())
			switch(word[leavel])
			{
			case '*' : 
				{
					
					do
					{
						cStar++;
					}while(word[leavel+cStar] == '*');
					
					if(word.size()-(leavel + cStar) == 0)
						break;
					
					if((word[leavel+cStar]) == '1')
					{
						
						list<pair<int,string> >::iterator it = dict[node][leavel].begin();
						advance(it,cStar);			
						total += it->second.c_str();
						cout << it->second;
						it->first++;

						pair<int,string> t;
						t.first = it->first;
						t.second = it->second;
						dict[node][leavel].erase(it);
						dict[node][leavel].push_front(t);

						dict[node][leavel].sort(compareF);
						if((word.size() - leavel-cStar-1)==0){ total.push_back('.'); cout<<'.';}
						if((word.size() - leavel-cStar-1)==1){ total.push_back(','); cout<<',';}
						if((word.size() - leavel-cStar-1)==2){ total.push_back('?'); cout<<'?';}
						cout<<' ';
						total.push_back(' ');
						cStar = 0;
						leavel = 0;
					}
				}break;
			case '1' : 
				{ 
					list<pair<int,string> >::iterator it = dict[node][leavel].begin();
					advance(it,cStar);			
					total += it->second.c_str();
					cout << it->second;
					it->first++;

					pair<int,string> t;
					t.first = it->first;
					t.second = it->second;
					dict[node][leavel].erase(it);
					dict[node][leavel].push_front(t);

					cStar=0;
					dict[node][leavel].sort(compareF);
					if((word.size() - leavel)==1){ total.push_back('.'); cout<<'.';}
					if((word.size() - leavel)==2){ total.push_back(','); cout<<',';}
					if((word.size() - leavel)==3){ total.push_back('?'); cout<<'?';}
					cout<<' ';
					total.push_back(' ');
					leavel = 0;
				}break;
			default: 
				{	
					followNum(word[leavel]-'0', leavel+1);
				}
			}

		if ((leavel + cStar) == word.size())
		{
			list<pair<int,string> >::iterator it = dict[node][leavel].begin();
			advance(it,cStar);			
			total += it->second.c_str();
			cout << it->second;
			it->first++;
			pair<int,string> t;
			t.first = it->first;
			t.second = it->second;
			dict[node][leavel].erase(it);
			dict[node][leavel].push_front(t);
			cStar=0;
			//dict[node][leavel].sort(compareA);
			dict[node][leavel].sort(compareF);
			cout<<' ';
			total.push_back(' ');
		}
	}

};

int main(int argc, char ** argv)
{
	t9 test;
	return 0;
}