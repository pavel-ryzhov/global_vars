#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

/*int Get_Int(void);
void set_keypress(void);
void reset_keypress(void);
int mykbhit(void);*/

class Direction
{
public:
	Direction()
	{
//		children.push_back(0);
	}

	Direction(int val)
	{
		children.push_back(val);
	}

	int find_point (int val_a, int val)
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

	int find_way (int way_to)
	{
		for (it_ch=children.begin(); it_ch!=children.end(); ++it_ch)
		{
			if ((*it_ch)==way_to)
				return *children.begin();
		}
		return 0;
	}

/*	int show_children (void)
	{
		if(children.begin()!=children.end())
			it_ch = children.begin();
		else return 0;
		do
		{
			cout << *it_ch << " ";
			++it_ch;
		}while(it_ch!=children.end());
		cout << endl;
	}*/

	int dir_empty(void)
	{
		if (children.size()==0)
			return 1;
		else
			return 0;
	}

private:
	vector<int> children;
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

	int add_point (int extern_Point, int to_find)
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

/*	int show_dirs (void)
	{
		cout << Point_name << ": ";
		if(dirs.begin()!=dirs.end())
			it_dirs = dirs.begin();
		else
			return 0;
		do
		{
			(*it_dirs).show_children();
			++it_dirs;
		}while(it_dirs!=dirs.end());
		return 1;
	}*/

	int find_way (int way_to)
	{
		it_dirs = dirs.begin();
		int way = 0,
			count = 0;
		while(!way)
		{
			way = (*(it_dirs+count)).find_way(way_to);
			count++;
		}
		Dist = *(Distances.begin()+count-1);
			return way;
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
	copy(input.begin(), input.end(), ostream_iterator<int> (cout));
//	set_keypress();
	/*while (count > 0)
	{
		instant_input = Get_Int();
		if (instant_input < 0)
			continue;
		input.push_back(instant_input);
		if (input.size()==1)
			count += (*(input.begin())-1)*3+1;
		if (input.size()==(2+(*(input.begin())-1)*3))
			count += *(input.end()-1)*2;
		count--;
	}
/*	for(it=input.begin();it!=input.end();++it)
		cout << (*it) << " ";
	cout << endl;*/

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
//			if((*it_P).it_pte<*input.begin()-1)
				TARGET = (*it_P).next_point();
				count = 1; //счётчик указывает на строку входного вектора,
				           //содержащую выбранную в данный момент пару вершин
			for (it_edges=edges.begin(); it_edges!=edges.end(); ++it_edges) // Проход по вектору векторов рёбер для поиска связей точки
			{

				buf = find((*it_edges).begin(), (*it_edges).end(), TARGET);  //Поиск в очередной паре вершин

				if (buf!=(*it_edges).end()) //Если find указывает на конец, выбрать следующую точку найденных путей
				{
					if (buf==(*it_edges).begin())
					{
						if((*it_P).add_point(*(buf+1), *buf))
							(*it_P).add_Dist(input.at(count*3));
						*buf = 0;
						*(buf+1) = 0;
					}
					else
					{
						if((*it_P).add_point(*(buf-1), *buf))
							(*it_P).add_Dist(input.at(count*3));;
						*buf = 0;
						*(buf-1) = 0;
					}
				}
				count++;
			}
		}while((*it_P).it_pte<*input.begin()-1); //конец трассировки связей для точки it_P
//		(*it_P).show_dirs();
		global_it_pte++;
		if (global_it_pte == *input.begin())
			break;
		P.push_back(Point(*((*P.begin()).pte.begin()+global_it_pte)));
		edges = edges_copy;
	}while(1);
	//конец трассировки связей для всех точек

	int path_begin, path_end, Path_Length;
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
//				cout << path_begin << " ";
			}
			++it_P;
			if (it_P == P.end())
				it_P = P.begin();
		}
		cout << Path_Length << endl;
	}
	return 0;
}

/*#include <stdio.h>

int Get_Int(void)
{
	char c='i';
	vector<char> s;
	vector<char>::iterator it_s;
	char *bs;
	vector<int> vec;
	vector<int>::iterator vec_it;
//	setvbuf(stdin,NULL,_IONBF,1);
	while(1)
	{
/*		do
		{
			c = (char)getchar();
		}while ((int)c==0);
		set_keypress();
//		scanf("%c", c);
//		c = mykbhit();
		c = getchar_unlocked();
//		cin >> c;
//		cout << c; //echo
		if ((c==' ')||((int)c==13))
		{
			s.push_back('\n');
			while(1)
			{
				if (s.empty())
					return -1;
				it_s = s.begin();
				if ((((int)(*it_s))<48)||(((int)(*it_s))>57))
					s.erase(s.begin());
				else
					break;
			}
			bs = &(*it_s);
			return atoi(bs);
		}
		s.push_back(c);
	}
}

//Функции переключения терминала:
/*#include <termios.h>

static struct termios stored_settings;

void set_keypress(void)
{
	int res;
	struct termios new_settings;
	tcgetattr(fileno(stdin),&stored_settings);
	new_settings = stored_settings;
	/* Disable canonical mode, and set buffer size to 1 byte 
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	res =  tcsetattr(fileno(stdin),TCSANOW,&new_settings);
//	system("pause");
	return;
}

void reset_keypress(void)
{
	tcsetattr(fileno(stdin),TCSANOW,&stored_settings);
	return;
}

#include <fcntl.h>
int mykbhit(void)
{
	int fd;
	char c;
	fd = fileno(stdin);
	fcntl(fd, F_SETFL, O_NONBLOCK);
	if (read(fd, &c, sizeof(char)) < 0)
		return 0;
	return c;
}*/
