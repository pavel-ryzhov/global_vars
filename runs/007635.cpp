#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int n;

vector<int> input;
vector<int>::iterator it_input;
vector< vector<int> > g;

int g_search(int s, int f);

int main (void)
{
	//чтение графа
	copy(istream_iterator<int>(cin),istream_iterator<int>(), back_inserter(input));
//	copy(input.begin(),input.end(),ostream_iterator<int>(cout,"\n"));
	int i = 0;
	n =  *input.begin();
	for(;i<n;i++)
		g.push_back(vector<int>());
	
//	copy(&init, &init+sizeof(init)/4, g.begin());
	vector< vector<int> >::iterator it_g;
/*	for (it_input = input.begin()+1; it_input < input.begin()+(n-1)*3; it_input = it_input + 3) {
		points.insert(it_input, it_input+2);
	}
//	cout << it_input;*/
	
	for (i=1;i<=*(input.begin());i++) { //здесь точки заполняются связями
		for (it_input = input.begin()+1; it_input < input.begin()+(n-1)*3; it_input = it_input + 3) {
			if (*it_input==i)
				g[i-1].push_back(*(it_input+1));
			else
				if(*(it_input+1)==i)
					g[i-1].push_back(*it_input);
		}
	} //заполнились

	vector<int>::iterator it_inp2;

	for (it_inp2 = input.begin()+2+3*(n-1); it_inp2 < input.end(); it_inp2 = it_inp2 + 2)
		g_search(*it_inp2, *(it_inp2+1));
	cout<<'\0';

	return 0;
}

int g_search(int s, int f)
{
	queue<int> q; //горящие вершины
	q.push(s); //подожгли стартовую
	vector<bool> used(n); //была ли вершина посещена
	vector<int> d(n), p(n); //массив длин путей и предка (откуда попали в вершину)
	used[s-1] = true; //побывали в первой
	p[s] = -1;
	while(!q.empty()) { //ку не пустая, вершины горят
		int v = q.front(); //следующая в очереди
		q.pop(); //очередь продвигается
		for(size_t i=0; i<g[v-1].size(); ++i) { //i не больше размера вершины v
			int to = g[v-1][i]; // какую вершину будем поджигать следующей
			if (!used[to-1]) {
				used[to-1] = true; //посетили
				q.push(to); //подожгли
				int dist = 0;
				for (it_input = input.begin()+1; it_input < input.begin()+(n-1)*3; it_input = it_input + 3) {
					if (((*it_input==to)&&(*(it_input+1)==v))||
						((*it_input==v)&&(*(it_input+1)==to)))
						dist = *(it_input+2);
				}
				d[to-1] = d[v-1] + dist; //вершина на один шаг дальше от корня чем предыдущая
				p[to-1] = v; //предок to
			}
			if (used[f-1]) {
				cout << d[f-1] << '\n';
				return 1;
			}
		}
	}
	return 0;
}