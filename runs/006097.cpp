#include <map>
#include <vector>
#include <iostream>
using namespace std;

class myTree
{
	map<int,vector< pair<int,int> > > m;

	int find(int _this, int end, int prev=-1)
	{
		vector< pair<int,int> > v = m[_this];

		for(int i=0;i<v.size() ;i++ )
			if(v[i].first==end)
			{
				return	v[i].second;
			}

		for(int i=0;i<v.size() ;i++ )
			if(v[i].first!=prev)
			{
				int temp = find(v[i].first ,end,_this);
				if(temp) return v[i].second+temp;
			}
		return 0;
	}
	public:

	myTree()
	{
		int N,M;

		cin>>N;
		//Заполняем граф
		for(int i=0;i<N-1;i++)
		{
			int a,b,c;
			cin>>a>>b>>c;
			m[a].push_back(pair<int,int>(b,c));
			m[b].push_back(pair<int,int>(a,c));
		}

		cin>>M;
		//Поиск
		vector<int> out;
		for(int i=0;i<M;i++)
		{
			int a,b;
			cin>>a>>b;
			out.push_back( find(a,b) );
		}

		//Вывод
		for(int i=0;i<out.size();i++)
			cout<< out[i] <<'\n';
	}
};
int main()
{
	myTree t;
	return 0;
}

