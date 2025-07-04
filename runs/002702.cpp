#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstring>
//#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

typedef unsigned int dword;

vector < vector < pair < string, int> > > dict;
int high;//для сортировки
int low = 0;//для сортировки
pair<string, int> t;

int transform(char*);
int step (int, int p);//степень
bool with1(char[]);//есть ли 1 в слове
int stars(char []);//сколько всего символов * в слове
int stars_before(char[]);//сколько символов * предшествует 1 в слове
int stars_after(char[]);//сколько символов * следует после 1 в слове
void moveup(vector < pair <string, int> > &, int);//сдвиг использованного слова вверх по списку
string conv(int);
struct mysort//comparator для сортировки
{
	bool operator () ( const pair<string, int> & a, const pair<string, int> & b )
	{
		return (a.second > b.second);
	}
};

char curr[25];

template <typename CHAR>
class ternary_tree
{
	typedef unsigned int node_index;

public:
	ternary_tree(): max_no(0) {}
	// 
	// returns number [1..max uint] of inserted or existing item.
	// does no insertion if item already exists. 
	//
	dword insert(const CHAR *s)
	{
	  return (dword)nodes[insert(0, s)].eqkid;
	}

	// returns n[1..max_no] or zero if not found
	dword search(const CHAR *s) const
	{
	  node_index nid = 0; // root index;
	  while (nid < total_nodes()) 
	  {
		 const node& n = nodes[nid];
		 if (*s < n.splitchar)
			 nid = n.lokid;
		 else if(*s > n.splitchar)
			 nid = n.hikid;
		 else //(*s == p->splitchar) 
		 {
			if (*s++ == 0)
				return n.value();
			nid = n.eqkid;
		 } 
	  }
	  return 0;
	}

//protected:
	//typedef unsigned int node_index;

	struct node 
	{
	   CHAR splitchar;
	   node_index lokid, eqkid, hikid;
	   node():splitchar(0), lokid(-1), eqkid(-1), hikid(-1){}
	   dword value() const 
	   {
		 //assert(splitchar == 0);
		 return (dword) eqkid;
	   }
	   void value(dword v)  
	   {
		 //assert(splitchar == 0);
		 eqkid = (node_index)v;
	   }
	};

	std::vector<node> nodes;
	dword max_no;

	size_t total_nodes() const 
	{ 
		return (dword) nodes.size(); 
	}

	node_index insert(node_index nid, const CHAR *s)
	{ 
	   if (nid >= total_nodes()) 
	   {
			node n; n.splitchar = *s;
			nodes.push_back(n);
			nid = nodes.size() - 1; 
	   }
	   const node& n = nodes[nid];
	   if (*s < n.splitchar)
		  nodes[nid].lokid = insert(n.lokid, s);
	   else if(*s > n.splitchar)
		  nodes[nid].hikid = insert(n.hikid, s);
	   else //*s == p->splitchar 
	   {
		  if (*s == 0)
		  //"...we'll exploit the fact that a node with a 
		  // null splitchar cannot have an eqkid, 
		  // and store the data in that field."
			  nodes[nid].value(++max_no);
		  else
			  nodes[nid].eqkid = insert(n.eqkid, ++s);
	   }
	   return nid;
	}
};

int main()
{
	ternary_tree<char> tstree;
	char buf[25];
	char ch[25];
	char s[25];
	char x[25];
	char *y;
	int N = 0;
	int key;
	
	//решение главной задачи
	cin >> buf;
	N = atoi(buf);
	//заполнение дерева tstree и структуры dict
	dict.resize(N);
	for (int i = 0; i < N; i++)
	{
		cin >> buf;//считываем слово
		strcpy(s, buf);
		char *c = new char[strlen(conv(transform(buf)).c_str())];
		strcpy(c, conv(transform(buf)).c_str());
		y = c;
		//cout << y;
		if (tstree.search(y) == 0)
		{
			tstree.insert(y);//какого insert возвращает не 1, а 2^32 - 1?!
			cin >> buf;//считываем частоту
			dict[tstree.search(x) - 1].push_back(make_pair(s, atoi(buf)));
			//cout << "search s " << tstree.search(y);
		}
		else
		{
			cin >> buf;//считываем частоту
			dict[tstree.search(x) - 1].push_back(make_pair(s, atoi(buf)));
			//cout << "search s " << tstree.search(y);
		}
		//delete []c;//
	}

	//упорядочиваем dict
	high = dict[0].size() - 1;
	sort(dict[0].begin(), dict[0].end(), mysort());
	
	//вывод сообщения
	while(cin >> buf)
	{
		if(!with1(buf))//нет 1 в слове.
		{
			if (stars_before(buf) != 0)//есть звезды, слов несколько
			{
				int i = 0;
				while(buf[i] != '*')
				{
					curr[i] = buf[i];
					i++;
				}
				cout << dict[tstree.search(curr) - 1][stars_before(buf)].first << " ";
				dict[tstree.search(curr) - 1][stars_before(buf)].second += 1;//обновление частоты встречаемости
				//moveup(dict[tstree.search(curr) - 1], stars_before(buf));
				pair<string, int> p;
				int b = stars_before(buf);
				int a = tstree.search(curr) - 1;
				while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
				{
					p.first = dict[a][b].first;
					p.second = dict[a][b].second;
					dict[a][b].first = dict[a][b - 1].first;
					dict[a][b].second = dict[a][b - 1].second;
					dict[a][b - 1].first = p.first;
					dict[a][b - 1].second = p.second;
					b--;
				}
			}
			else//нет звезд, значит и слово всего одно. moveup не используем
			{
				cout << dict[tstree.search(buf) - 1][0].first << " ";
				dict[tstree.search(buf) - 1][0].second += 1;//обновление частоты встречаемости
			} 
		}
		else //есть 1 в слове используем функции stars_before для поиска слова и stars_after для знака препинания
		{
			if ((stars_before(buf) == 0)/* && (stars_after(buf) == 0)*/)//для слов вида 2341**, moveup не используем, так как слово одно
			{
				int i = 0;
				while(buf[i] != '1')
				{
					curr[i] = buf[i];
					i++;
				}
				if (stars_after(buf) == 0)
				{
					cout << dict[tstree.search(curr) - 1][0].first << ". ";
					dict[tstree.search(curr) - 1][0].second += 1;
				}
				if (stars_after(buf) == 1)
				{
					cout << dict[tstree.search(curr) - 1][0].first << ", ";
					dict[tstree.search(curr) - 1][0].second += 1;
				}
				if (stars_after(buf) == 2)
				{
					cout << dict[tstree.search(curr) - 1][0].first << "? ";
					dict[tstree.search(curr) - 1][0].second += 1;
				}
			}

			if ((stars_before(buf) != 0)/* && (stars_after(buf) == 0)*/)//для слов вида 234**1** или 234**1
			{
				int i = 0;
				while(buf[i] != '*')
				{
					curr[i] = buf[i];
					i++;
				}
				if (stars_after(buf) == 0)
				{
					cout << dict[tstree.search(curr) - 1][stars_before(buf)].first << ". ";
					dict[tstree.search(curr) - 1][stars_before(buf)].second += 1;
					//moveup(dict[tstree.search(curr) - 1], stars_before(buf));
					
					pair<string, int> p;
					int b = stars_before(buf);
					int a = tstree.search(curr) - 1;
					while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
					{
						p.first = dict[a][b].first;
						p.second = dict[a][b].second;
						dict[a][b].first = dict[a][b - 1].first;
						dict[a][b].second = dict[a][b - 1].second;
						dict[a][b - 1].first = p.first;
						dict[a][b - 1].second = p.second;
						b--;
					}
				}
				if (stars_after(buf) == 1)
				{
					cout << dict[tstree.search(curr) - 1][stars_before(buf)].first << ", ";
					dict[tstree.search(curr) - 1][stars_before(buf)].second += 1;
					//moveup(dict[tstree.search(curr) - 1], stars_before(buf));
					
					pair<string, int> p;
					int b = stars_before(buf);
					int a = tstree.search(curr) - 1;
					while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
					{
						p.first = dict[a][b].first;
						p.second = dict[a][b].second;
						dict[a][b].first = dict[a][b - 1].first;
						dict[a][b].second = dict[a][b - 1].second;
						dict[a][b - 1].first = p.first;
						dict[a][b - 1].second = p.second;
						b--;
					}
				}
				if (stars_after(buf) == 2)
				{
					cout << dict[tstree.search(curr) - 1][stars_before(buf)].first << "? ";
					dict[tstree.search(curr) - 1][stars_before(buf)].second += 1;
					//moveup(dict[tstree.search(curr) - 1], stars_before(buf));
					
					pair<string, int> p;
					int b = stars_before(buf);
					int a = tstree.search(curr) - 1;
					while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
					{
						p.first = dict[a][b].first;
						p.second = dict[a][b].second;
						dict[a][b].first = dict[a][b - 1].first;
						dict[a][b].second = dict[a][b - 1].second;
						dict[a][b - 1].first = p.first;
						dict[a][b - 1].second = p.second;
						b--;
					}
				}
			}

		}
	}
	cin.get();
	return 0;
}

//цифровой эквивалент слова
int transform(char * ch)
{
	int key = 0;
	int pow = 0;
	int i = 0;
	int mas[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	while(ch[i] != 0)
	{
		if ((ch[i] == 'a') || (ch[i] == 'b') || (ch[i] == 'c'))
			mas[i] = 2;
		if ((ch[i] == 'd') || (ch[i] == 'e') || (ch[i] == 'f'))
			mas[i] = 3;
		if ((ch[i] == 'g') || (ch[i] == 'h') || (ch[i] == 'i'))
			mas[i] = 4;
		if ((ch[i] == 'j') || (ch[i] == 'k') || (ch[i] == 'l'))
			mas[i] = 5;
		if ((ch[i] == 'm') || (ch[i] == 'n') || (ch[i] == 'o'))
			mas[i] = 6;
		if ((ch[i] == 'p') || (ch[i] == 'q') || (ch[i] == 'r') || (ch[i] == 's'))
			mas[i] = 7;
		if ((ch[i] == 't') || (ch[i] == 'u') || (ch[i] == 'v'))
			mas[i] = 8;
		if ((ch[i] == 'w') || (ch[i] == 'x') || (ch[i] == 'y') || (ch[i] == 'z'))
			mas[i] = 9;
		++pow;
		i++;
	}
	for (int i = 0; i < pow; i++)
	{
		key += mas[i] * step(10, pow - i - 1);
		//cout << "key = " << key;
	}
	return key;
}

int step (int ar, int p)
{
	if(!p) return 1;
	else return ar * step(ar, p-1);
}

bool with1(char ch[])
{
	int i = 0;
	bool b = false;
	while (ch[i] != 0)
	{
		if (ch[i] == '1') 
			b = true;
		i++;
	}
	return b;
}

int stars(char ch[])
{
	int cnt = 0;
	int i = 0;
	while(ch[i] != 0)
	{
		if (ch[i] == '*')
			cnt++;
		i++;
	}
	return cnt;
}

int stars_after(char ch[])
{
	int cnt = 0;
	int i = 0;
	bool is1 = false;
	while (ch[i] != 0)
	{
		if (ch[i] == '1')
			is1 = true;
		if ((is1) && (ch[i] == '*'))
			cnt++;
		i++;
	}
	//cout << " after " << cnt;
	return cnt;
}

int stars_before(char ch[])
{
	int cnt = 0;
	int i = 0;
	bool is1 = false;
	while (ch[i] != 0)
	{
		if (ch[i] == '1')
			is1 = true;
		if ((!is1) && (ch[i] == '*'))
			cnt++;
		i++;	
	}
	//cout << " before " << cnt;
	return cnt;
}

void moveup(vector < pair <string, int> > & vect, int pos)
{
	pair<string, int> temp;
	while ((pos != 0) && (vect[pos].second <= vect[pos - 1].second))
	{
		temp.first = vect[pos].first;
		temp.second = vect[pos].second;
		vect[pos].first = vect[pos - 1].first;
		vect[pos].second = vect[pos - 1].second;
		vect[pos - 1].first = temp.first;
		vect[pos - 1].second = temp.second;
		pos--;
	}
}
string conv(int n)
{
    stringstream buf;
    string s;
    buf << n;
    buf >> s;
    buf.clear();
	return s;
}