#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

class Direction //Объекты класса содержат информацию о точках, в которые можно попасть через данную
{
public:
	Direction()
	{
	}

	Direction(int val)
	{
		children.push_back(val);
	}

	int find_point (int val_a, int val) //Была ли уже учтена рассматриваемая точка в данном направлении
	{
		it_ch = find(children.begin(), children.end(), val);
		if (it_ch != children.end())
		{
			children.push_back(val_a);
			return 1;
		}
		else
			return 0;
	}

	int find_way (int way_to) //Возвращает имя направления (первый символ в векторе children) если оно ведёт к искомой точке way_to
	{
		for (it_ch=children.begin(); it_ch!=children.end(); ++it_ch)
		{
			if ((*it_ch)==way_to)
				return *children.begin();
		}
		return 0;
	}

	int dir_empty(void)
	{
		if (children.size()==0)
			return 1;
		else
			return 0;
	}

private:
	vector<int> children; //"Наследники" направления (содержит список точек, в находящихся за данной)
	vector<int>::iterator it_ch;
};

class Point
{
public:

	Point(int val)
	{
		dirs.push_back(Direction());
		pte.push_back(val);
		it_pte = -1;
		Point_name = val;
	}

	int add_point (int extern_Point, int to_find) //Просматривает все вектора направлений
	{
		pte.push_back(extern_Point);
		it_dirs = dirs.begin();
		do
		{
			if (!(*it_dirs).find_point(extern_Point, to_find))
				++it_dirs;
			else return 0;

		}while(it_dirs!=dirs.end());
		if ((*dirs.begin()).dir_empty())
			*(dirs.begin()) = Direction(extern_Point);
		else
			dirs.push_back(Direction(extern_Point));
		return 1; //возвращает единицу только после создания нового вектора направления
	}

	int find_way (int way_to) //Ищет в направлениях заданную way_to
	{
		it_dirs = dirs.begin();
		int way = 0,
			count = 0;
		while(!way)
		{
			way = (*(it_dirs+count)).find_way(way_to);
			count++;
		}
		Dist = *(Distances.begin()+count-1); //Возвращает расстояние до ближайшей годной точки
			return way; //И её номер
	}

	int next_point(void)
	{
		it_pte++;
		int result = *(pte.begin()+it_pte);
		return result;
	}

	void add_Dist (int val)
	{
		Distances.push_back(val);
	}

	int Point_name;
	vector<int> pte; //points to explore
	int it_pte,
		Dist;
private:
	vector<int> Distances;
	vector<Direction> dirs;
	vector<Direction>::iterator it_dirs;
};

int main (void)
{
	vector<int> input;
	vector<int>::iterator it;
	int instant_input;
	int count = 1;

	copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(input));

    count = 1; //Создание вектора векторов рёбер
	vector<vector <int> > edges, edges_copy;
	vector<vector <int> >::iterator it_edges;
	vector<int>::iterator end_of_edges;
	vector<int> arg(2,0);
	for (it=input.begin()+1; it!=input.begin()+(*input.begin()-1)*3+1; ++it)
	{
		if (count%3==1)
		{
			edges.push_back(arg);
			*(*(edges.end()-1)).begin() = *it;
		}
		else if (count%3==2)
			*((*(edges.end()-1)).begin()+1) = *it;
		count++;
	} //конец создания вектора векторов рёбер

	edges_copy = edges;
	vector<Point> P;
	vector<int>::iterator buf;
	int TARGET, global_it_pte = 0;
	vector<Point>::iterator it_P;
	P.push_back(Point(*(input.begin()+1)));

	do //трассировка связей всех точек
	{
		it_P = P.begin() + global_it_pte;
		do //трассировка связей для точки it_P
		{
			TARGET = (*it_P).next_point();
			count = 1; //счётчик указывает на строку входного вектора,
				       //содержащую выбранную в данный момент пару вершин
//			for (it_edges=edges.begin(); it_edges!=edges.end(); ++it_edges) // Проход по вектору векторов рёбер для поиска связей точки
			it_edges = edges.begin();
			while(it_edges!=edges.end())
			{

				buf = find((*it_edges).begin(), (*it_edges).end(), TARGET);  //Поиск в очередной паре вершин

				if (buf!=(*it_edges).end()) //Если find указывает на конец, выбрать следующую точку найденных путей
				{
					if (buf==(*it_edges).begin())
					{
						if((*it_P).add_point(*(buf+1), *buf))
							(*it_P).add_Dist(input.at(count*3));
						//*buf = 0;
						//*(buf+1) = 0;
						edges.erase(it_edges);
						if(!edges.empty())
							it_edges = edges.begin();
					}
					else
					{
						if((*it_P).add_point(*(buf-1), *buf))
							(*it_P).add_Dist(input.at(count*3));;
						//*buf = 0;
						//*(buf-1) = 0;
						edges.erase(it_edges);
						if(!edges.empty())
							it_edges = edges.begin();
					}
				}
				else
				{
//					edges.erase(it_edges);
//					(*it_P).it_pte--;
					++it_edges;
				}
				count++;
				if (edges.empty())
				{
					break;
				}
			}
			if (edges.empty()&&((*it_P).it_pte==*input.begin()-2))
				break;
		}while((*it_P).it_pte<*input.begin()-1); //конец трассировки связей для точки it_P
		global_it_pte++;
		if (global_it_pte == *input.begin())
			break;
		P.push_back(Point(*((*P.begin()).pte.begin()+global_it_pte)));
		edges = edges_copy;
	}while(1);
	//конец трассировки связей для всех точек

	int path_begin, path_end, Path_Length; //Собственно поиск путей
	for(count=1; count<=*(input.begin()+3*(*input.begin()-1)+1); count++)
	{
		path_begin = input.at(1+3*(*input.begin()-1)+2*count-1);
		path_end = input.at(1+3*(*input.begin()-1)+2*count);
		Path_Length = 0;
		it_P = P.begin();
		while (path_begin != path_end)
		{
			if((*it_P).Point_name==path_begin)
			{
				path_begin = (*it_P).find_way(path_end);
				Path_Length += (*it_P).Dist;
			}
			++it_P;
			if (it_P == P.end())
				it_P = P.begin();
		}
		cout << Path_Length << endl;
	}
	return 0;
}
