#include<iostream>
#include<vector>
#include<cctype>
//#include<stdio.h>


unsigned int N, M;
struct rib;
struct point // Вершина графа
{
	std::vector<rib> link;
	bool color;
	unsigned int number;
	unsigned long int hight;
};
struct rib
{
	unsigned int weight;
	point *ptr;
};
struct elemOrder
{
	unsigned int num;
	unsigned long int length;
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
void dfs ( std::vector<point>&pt, point *elem, std::vector <elemOrder> &ord )// функция для рекурсии при поиске в глубину
{
	if(!elem->link.empty())
	{
		for( std::vector<rib>::iterator i = elem->link.begin(); i< elem->link.end(); i++)
		{
			if ( i->ptr->color)
			{
				elemOrder rt;
				rt.length = elem->hight;
				rt.num = elem->number;
				ord.push_back(rt);
				for( std::vector<rib>::iterator j  = i->ptr->link.begin(); j< i->ptr->link.end(); j++)
					if ( j->ptr->number == elem->number )
					{
						i->ptr->link.erase(j);
						break;
					}
				dfs(pt, i->ptr, ord);
			}
		}
	}
	elemOrder rt;
	rt.length = elem->hight;
	rt.num = elem->number;
	ord.push_back(rt);
	elem->color = false;
}
void dfSearch ( std::vector<point>&pt, std::vector <elemOrder> &ord)// поиск в глубину
{
	for ( std::vector<point>::iterator i=pt.begin(); i<pt.end(); i++)
	{
		if ( i->color)
			dfs( pt, &*i, ord);
	}
}

unsigned long int identSize( const unsigned long int &n)
{
	if (n == 0)
	{
		return 0;
	}
	else
	{
		unsigned long int m = 1, S = 1;
		unsigned long int k = ( n/2 > n-n/2) ? n/2 : n-n/2;
		while ( k > 1 )
		{
			m *= 2;
			S = S + m;
			k = ( k/2 > k-k/2) ? k/2 : k-k/2;
		}
		return S;
	}
}
void treeMin ( const std::vector <elemOrder> &ord, std::vector<unsigned long int>&min, unsigned long int v, unsigned long int tl, unsigned long int tr) 
{
	if (tl == tr)
		min[v] = ord[tl].length;
	else {
		unsigned long int tm = (tl + tr) / 2;
		treeMin (ord, min, 2*v+1, tl, tm);
		treeMin (ord, min, v*2+2, tm+1, tr);
		min[v] = ( min[v*2+1]<min[v*2+2]) ? min[v*2+1] : min[v*2+2];
	}
}
unsigned long int searchOrd ( const unsigned int &val,const std::vector <elemOrder> &ord)
{
	for( unsigned long int i=0; i<ord.size(); i++)
		if ( val == ord[i].num )
			return i;
	return 0;
}

unsigned long int minLineSegment( unsigned long int l, const unsigned int r, unsigned long int indl, unsigned long int indr,const std::vector<unsigned long int>&min, unsigned long int t)
{
	if ( l == indl && r == indr )
		return min [t];
	else if ( r <= (indl+indr)/2)
		return minLineSegment (l, r, indl, (indl+indr)/2, min, t*2+1);
	else if ( l> (indl+indr)/2)
		return minLineSegment ( l, r, (indl+indr)/2+1,indr, min, t*2+2);
	else
	{
		unsigned long int m1 = minLineSegment ( l, (indl+indr)/2, indl, (indl+indr)/2, min, t*2+1);
		unsigned long int m2 = minLineSegment ( (indl+indr)/2+1, r, (indl+indr)/2+1, indr , min, t*2+2);
		return ( m1 < m2) ? m1 : m2;
	}
}
unsigned long int distance( const unsigned long int &l, const unsigned long int &r, const unsigned long int &m,const std::vector<elemOrder> &ord)
{
	return ord[l].length+ord[r].length-2*m;
}
int main()
{
	std::cin>>N;
	std::vector <point> tree;
	for(unsigned int i=0; i<N; i++)
	{
		point p;
		p.color = true;
		p.hight = 0;
		p.number = i;
		tree.push_back(p);
	}
	std::cin.ignore();
	getRibs( tree );
	buildingTree ( tree );
	std::vector <elemOrder> Order;
	dfSearch ( tree, Order );
	tree.~vector();
	unsigned int k = identSize( Order.size() );
	std::vector<unsigned long int>min(k);
	treeMin( Order, min, 0, 0, Order.size()-1);
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
			unsigned long int M = minLineSegment ( left, right, 0, Order.size()-1, min, 0);
			M = distance( left, right, M, Order);
			//printf("%u\n", M);
			std::cout<< M << std::endl;
		}
		else
			std::cout<< 0 <<std::endl;
	}
	return 0;
}