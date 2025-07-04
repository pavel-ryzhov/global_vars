#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

class p{
public:
	int id,dist,root;
};

class Ancestor{
public:
	int id,dist;
};

int log2(int x){
	return (int) (floor(log((double) x)/log(2.0)));
}

class tree{
public:
	int depth;
	map <int,int> child;
	map <int,Ancestor> anc;
};

	vector <tree> T; //Tree

#define REP(i, n) for (int i(0), _n(n); i < _n; ++i)

int main(){
	map<int,int>::iterator it;
	int n,src,dest,dist,flag,depth,M,a,b,up,path;
	vector <p> tomark;
	int tms,tme;
	double ts;
	
	cin >> n;
	T.resize(40001); // ����� �� ��������, ��� ������ ����� ���� �� �������....
	tomark.resize(40002);
	REP(i,n-1){
		cin >> src >> dest >> dist;
		T[src].child[dest]=dist;
		T[dest].child[src]=dist;
	}

	tms=tme=0;
//����� ���� �� ������� ��, ��� �������� ���� - �������� (��������� �� ������� ��������), �� ��� �� ����-��������
	tomark[0].id = n/2;
	tomark[0].dist = -1;
	tomark[0].root = 0;
	T[0].depth = -1;
	tme++;
	while(tms<tme){
		T[tomark[tms].id].child.erase(tomark[tms].root);
		T[tomark[tms].id].anc[0].id = tomark[tms].root;
		T[tomark[tms].id].depth = T[tomark[tms].root].depth+1;
		T[tomark[tms].id].anc[0].dist = tomark[tms].dist;
		it = T[tomark[tms].id].child.begin();
		while(it != T[tomark[tms].id].child.end()){
			tomark[tme].id = (*it).first;
			tomark[tme].root = tomark[tms].id;
			tomark[tme].dist = (*it).second;
			it++;
			tme++;
		}
		tms++;
	}
	tomark.clear();

	T[n/2].anc.erase(0);

//������ ��������� (�� ��� ����� ���, �� ������������ �� ����� �����)

	flag=1;
	depth=0;
	while(flag){
		flag=0;
		REP(i,n+1){
			if(T[i].anc.find(depth)!= T[i].anc.end()){
				if(T[T[i].anc[depth].id].anc.find(depth)!=T[T[i].anc[depth].id].anc.end()){
					T[i].anc[depth+1].dist = T[T[i].anc[depth].id].anc[depth].dist + T[i].anc[depth].dist;
					T[i].anc[depth+1].id = T[T[i].anc[depth].id].anc[depth].id;
					flag=1;
				}
			}
		}
		depth++;
	}
	depth--;
//����������� ������� �������. ����� ������������ vector ������ map - �������� ����� �������, �� ������ ��������� ������ (�� ��� �������������� ������ �����)

	cin >> M;
	REP(i,M){
		path=0;
		cin >> a >> b;	
		if(T[a].depth < T[b].depth){
			a=a+b;
			b=a-b;
			a=a-b;
		}
		up = T[a].depth - T[b].depth;
		while(up>0){
			path+=T[a].anc[log2(T[a].depth - T[b].depth)].dist;
			a = T[a].anc[log2(T[a].depth - T[b].depth)].id;

			up = T[a].depth - T[b].depth;
		}

		depth = log2(T[a].depth);
		while(a!=b){
			if(T[a].anc[depth].id!=T[b].anc[depth].id || depth<1){
				path+=T[a].anc[depth].dist;
				path+=T[b].anc[depth].dist;
				a = T[a].anc[depth].id;
				b = T[b].anc[depth].id;
				depth = log2(T[a].depth);
			} else {
				depth--;
			}

			
		}
		cout << path << endl;
	}
	return 0;
}