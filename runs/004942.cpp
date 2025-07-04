#include<iostream>
#include<vector>
#include<cctype>
#include<stack>
#include<cmath>
//#include<stdio.h>


unsigned int N, M;
struct rib;
struct point // Вершина графа
{
	std::vector<rib> link;
	unsigned int number;
	unsigned long int hight;
};
struct rib
{
	unsigned int weight;
	point *ptr;
};

void getRibs ( std::vector<point>&pt)// разбиение строки на числа ( считывание ребер )
{
	for (unsigned int i = 0; i< N-1; i++)
	{
		unsigned int t1, t2, t3;
		std::cin>>t1>>t2>>t3;
		rib r;
		r.weight=t3;
		r.ptr=&pt[t2-1];
		pt[t1-1].link.push_back(r);
		r.ptr=&pt[t1-1];
		pt[t2-1].link.push_back(r);

	}
	std::cin>>M;
};

void getRequests ( std::vector<unsigned int>&pt)// считываем пары вершин, 
//для которых необходимо найти кратчайшее расстояние
{
	std::cin.ignore();
	for ( unsigned int i = 0; i<M; i++)
	{
		unsigned int d1,d2;
		std::cin>>d1>>d2;
		pt.push_back(d1-1);
		pt.push_back(d2-1);
		std::cin.ignore();
	}
}
void eddPoint ( bool * mas, std::vector<point>&pt, point *iter)// добавление узла дерева + определение высоты
{
	for(std::vector<rib>::iterator i = iter->link.begin(); i < iter->link.end(); i++)
	{
		if( !mas[i->ptr->number] )
		{
			i->ptr->hight = iter->hight + i->weight;
			mas[i->ptr->number] = true;
			eddPoint ( mas, pt, i->ptr);
		}
	}
}
void buildingTree ( std::vector<point>&pt)// построение дерева
{
	bool*mass=new bool[N];
	for (unsigned int j=0; j<N; j++)
		mass[j]=false;
	pt[0].hight = 0;
	mass[0]=true;
	eddPoint(mass,pt,&pt[0]);
	delete [] mass;
}
void dfs ( std::vector<point>&vect,point*t, std::vector <unsigned int> &ord, unsigned int h)// функция для рекурсии при поиске в глубину
{
	if(!t->link.empty())
	{
		for( std::vector<rib>::iterator i = t->link.begin(); i < t->link.end(); i++)
		{
			unsigned int rt = t->number;
			ord.push_back(rt);
			for( std::vector<rib>::iterator j  = i->ptr->link.begin(); j< i->ptr->link.end(); j++)
				if ( j->ptr->number == t->number )
				{
					i->ptr->link.erase(j);
					break;
				};
			dfs(vect, i->ptr, ord, h+1);
		}
	}
	unsigned int rt = t->number;
	ord.push_back(rt);
}

unsigned long int searchOrd ( const unsigned int &val,const std::vector <unsigned int> &ord)
{
	for( unsigned long int i=0; i<ord.size(); i++)
		if ( val == ord[i])
			return i;
	return 0;
}

unsigned long int distance( const unsigned long int &l, const unsigned long int &r, const unsigned long int &m)
{
	return l+r-2*m;
}

unsigned int binSearch (const unsigned long int &val, const std::vector<unsigned long int>&st, unsigned int tl, unsigned int tr)
{
	if ( tr - tl <= 1)
		if (st[tl] == val)
			return tl;
		else
			return tr;
	else if ( val <= st[(tl+tr)/2] )
		return binSearch(val,st,tl,(tl+tr)/2);
	else if ( val <=st[(tl+tr)/2+1])
		return (tl+tr)/2+1;
	else
		return binSearch ( val, st, (tl+tr)/2+1, tr);
}

void sparseTable( std::vector<unsigned int>&bl, std::vector<unsigned int>&T, const std::vector<unsigned long int>&st, const std::vector<point>&pt)
{
	unsigned int n = bl.size();
	unsigned int m = binSearch( n, st, 0, st.size()-1)+1;
	for(unsigned int j=0; j < n; j++)
		T[j*m]=bl[j];
	for(unsigned int i=1; i < m; i++)
		for(unsigned int j = 0; j < n; j++)
		{
			if((j+st[i-1])*m+i-1<n*m)
				T[j*m+i]=pt[T[j*m+i-1]].hight < pt[T[(j+st[i-1])*m+i-1]].hight ? T[j*m+i-1]:T[(j+st[i-1])*m+i-1];
			else
				T[j*m+i] = T[j*m+i-1];
		}
}

unsigned int findMin (const unsigned long int &tl, const unsigned long int &tr, std::vector<unsigned int>&ord, const std::vector<point>&pt)
{
	unsigned int K = ceil(log((double)ord.size())/log(2.0))/2;
	std::vector<unsigned int>::iterator i = ord.begin();
	std::vector<unsigned int>B;
	std::vector<unsigned long int> step;
	unsigned long int m=1;
	unsigned int sz = 0;
	step.push_back(m);
	for ( unsigned long int k =1; k< 2*ord.size();k++)
	{
		if ( m < k)
		{
			m*=2;
			step.push_back(m);
		}
	}
	unsigned int size=step.size();
	sz = binSearch(K,step,0,size-1);
	unsigned int L;
	if ( K != step[sz] )
		L = --sz;
	else
		L = sz;
	while( i != ord.end())
	{
		std::vector<unsigned int>blok;
		unsigned int st;
		for(unsigned int j=0; j<K;j++)
		{
			if ( i!=ord.end())
			{
				blok.push_back(*i);
				i++;
			}
		}
		if ( blok.size() == K )
		{
			st = sz;
			std::vector<unsigned int>T(K*(st+1));
			sparseTable( blok, T, step,pt);
			B.push_back((pt[T[L]].hight<pt[T[(K-step[L])*(st+1)+L]].hight) ? T[L]:T[(K-step[L])*(st+1)+L]);
		}
		else
		{
			st = binSearch( blok.size(), step, 0, size-1 );
			std::vector<unsigned int>T(blok.size()*(st+1));
			sparseTable( blok, T, step,pt);
			unsigned int m;
			if ( blok.size()!= step[st] )
				m = --st;
			else
				m = st;
			B.push_back((pt[T[m]].hight<pt[T[(blok.size()-step[m])*(st+1)+m]].hight) ? T[m]:T[(blok.size()-step[m])*(st+1)+m]);
			break;
		}
	}
	sz=binSearch(B.size(),step, 0, size-1);
	std::vector<unsigned int>T(B.size()*(sz+1));
	sparseTable( B , T, step,pt);
	unsigned int left;
	unsigned int right;
	for(unsigned int i=0; i<B.size(); i++)
		if( tl>=i*K && tl<(i+1)*K)
		{
			left = i;
			break;
		};
	for(unsigned int j=left; j<B.size();j++)
			if ( tr>=j*K && tr<(j+1)*K)
			{
				right = j;
				break;
			};
	if ( left == right)
	{
		std::vector<unsigned int>block;
		for( unsigned long i = tl; i<tr+1; i++)
			block.push_back(ord[i]);
		sz=binSearch( block.size(),step, 0, size-1);
		std::vector<unsigned int>ST(block.size()*(sz+1));
		sparseTable( block , ST, step,pt);
		unsigned int m;
		if ( block.size()!= step[sz] )
			m = --sz;
		else
			m = sz;
		return (pt[ST[m]].hight<pt[ST[(block.size()-step[m])*(sz+1)+m]].hight) ? ST[m]:ST[(block.size()-step[m])*(sz+1)+m];
	}
	else
	{
		unsigned int m1, m2;
		{
			std::vector<unsigned int>block;
			for( unsigned long i = tl; i<left*K+K; i++)
				block.push_back(ord[i]);
			sz=binSearch(block.size(),step, 0, size-1);
			std::vector<unsigned int>ST(block.size()*(sz+1));
			sparseTable( block, ST, step, pt);
			unsigned int m;
			if ( block.size()!= step[sz] )
				m = --sz;
			else 
				m = sz;
			m1 = (pt[ST[m]].hight<pt[ST[(block.size()-step[m])*(sz+1)+m]].hight) ? ST[m]:ST[(block.size()-step[m])*(sz+1)+m];
		}
		{
			std::vector<unsigned int>block;
			for( unsigned long i = right*K; i<tr+1; i++)
				block.push_back(ord[i]);
			sz=binSearch(block.size(),step, 0, size-1);
			std::vector<unsigned int>ST(block.size()*(sz+1));
			sparseTable( block, ST, step, pt);
			unsigned int m;
			if ( block.size()!= step[sz] )
				m = --sz;
			else 
				m = sz;
			m2 = (pt[ST[m]].hight<pt[ST[(block.size()-step[m])*(sz+1)+m]].hight) ? ST[m]:ST[(block.size()-step[m])*(sz+1)+m];
		}
		if (right-left == 1)
			return pt[m1].hight <pt[m2].hight ? m1:m2;
		else
		{
			m1 = (m1 < m2) ? m1:m2;
			left+=1;
			right-=1;
			unsigned int st = binSearch( right-left+1, step,0, size-1);
			if ( right-left+1 != step[st] )
				st--;
			unsigned int S = 1+binSearch(B.size(),step, 0, size-1);
			m2 = (pt[T[left*S+st]].hight<pt[T[(right-step[st]+1)*S+st]].hight) ? T[left*S+st]:T[(right-step[st]+1)*S+st];
			return pt[m1].hight <pt[m2].hight ? m1:m2;
		}
	}
}

int main()
{
	std::cin>>N;
	std::vector <point> tree;
	for(unsigned int i=0; i<N; i++)
	{
		point p;
		p.hight = 0;
		p.number = i;
		tree.push_back(p);
	}
	std::cin.ignore();
	getRibs( tree );
	buildingTree ( tree );
	std::vector <unsigned int> Order;
	dfs( tree, &tree[0], Order,0);
	std::vector<unsigned int>REQ;
	//std::vector<unsigned int> REQ;
	getRequests( REQ );
	for ( unsigned int i=0; i<M; i++)
	{
		if ( REQ[i*2] != REQ[2*i+1])
		{
			unsigned long int left = searchOrd( REQ[i*2], Order);
			unsigned long int right = searchOrd( REQ[2*i+1], Order);
			if ( left > right )
			{
				unsigned long int t = left;
				left = right;
				right = t;
			}
			unsigned int M = findMin(left,right,Order,tree);
			unsigned long int L = distance( tree[Order[left]].hight, tree[Order[right]].hight, tree[M].hight);//!
			std::cout<< L << std::endl;
		}
		else
			std::cout<< 0 <<std::endl;
	}
	return 0;
}