#include <iostream>
//#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
//#include <sstream>

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
//string conv(int);
char* itoa(int, char*, int) ;
bool only1(char*);//является ли проверяемое слово одним лишь знаком препинания

struct mysort//comparator для сортировки
{
	bool operator () ( const pair<string, int> & a, const pair<string, int> & b )
	{
		return (a.second > b.second);
	}
};

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

protected:
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

	dword/*size_t*/ total_nodes() const 
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
	   //cout << "nid = " << nid;
	   return nid;
	}
};
//ofstream fout;
ifstream fin;
int main()
{
	//fout.open("out.txt");
	fin.open("dic.txt");
	ternary_tree<char> tstree;
	tstree.insert("123456789");
	tstree.insert("123546789");
	char symb;//для посимольного просмотра строки запроса
	char buf[25];
	char ch[25];
	char str[25];
	char x[25];
	char curr[25];
	int N = 0;
	
	//решение главной задачи
	//cin >> buf;
	//fin >> buf;//для тестирования
	cin >> buf;
	N = atoi(buf);
	//заполнение дерева tstree и структуры dict
	dict.resize(N);
	//cout << "words N = " << N << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> buf;//считываем слово
		//fin >> buf;//для тестирования
		strcpy(str, buf);
		strcpy(x, itoa(transform(str), ch, 10));
		if (tstree.search(x) == 0)
		{
			tstree.insert(x);
			cin >> buf;//считываем частоту
			//fin >> buf;//для тестирования
			dict[tstree.search(x) - 3].push_back(make_pair(str, atoi(buf)));
		}
		else
		{
			cin >> buf;//считываем частоту
			//fin >> buf;//для тестирования
			dict[tstree.search(x) - 3].push_back(make_pair(str, atoi(buf)));
		}
		//упорядочиваем dict
		high = dict[tstree.search(x) - 3].size() - 1;
		sort(dict[tstree.search(x) - 3].begin(), dict[tstree.search(x) - 3].end(), mysort());
	}
	//до этого момента все все порядке
	//вывод сообщения
	char q[100002];//последняя строка с запросом
	int index = 0;
	while(cin.get(q[index])/*fin.get(q[index])//для тестирования*/)
		index++;
	q[index] = (char)32;//признак последнего слова
	q[index + 1] = '\0';//обрезаем по длине входящей строки
	int pos = 0;
	int ind = 1;
	while (q[ind] != '\0')//+
	{
		symb = q[ind];
		if (symb == (char)32)
		{
			cout << "+" << buf << "+";
			buf[pos] = '\0';//обязательно символ конца строки
			if(buf[0] != '\0')
			{	//обработка запроса
				//cout << "+" << buf << "+";
				//вывод слова из словаря
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
						curr[i] = '\0';
						cout << dict[tstree.search(curr) - 3][stars_before(buf)].first;
						dict[tstree.search(curr) - 3][stars_before(buf)].second += 1;//обновление частоты встречаемости
			
						pair<string, int> p;
						int b = stars_before(buf);
						int a = tstree.search(curr) - 3;
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
						cout << dict[tstree.search(buf) - 3][0].first;
						dict[tstree.search(buf) - 3][0].second += 1;//обновление частоты встречаемости
					} 
				}
				else //есть 1 в слове используем функции stars_before для поиска слова и stars_after для знака препинания
				{
					//добавить обработку слов вида 1**, то есть просто знаков препинания
					if (only1(buf))
					{
						if(stars_after(buf) == 0)
							cout << ".";
						if(stars_after(buf) == 1)
							cout << ",";
						if(stars_after(buf) == 2)
							cout << "?";
					}
					else
					{
						if ((stars_before(buf) == 0))//для слов вида 2341**, moveup не используем, так как слово одно
						{
							int i = 0;
							while(buf[i] != '1')
							{
								curr[i] = buf[i];
								i++;
							}
							curr[i] = '\0';
							if (stars_after(buf) == 0)
							{
								cout << dict[tstree.search(curr) - 3][0].first << ".";
								dict[tstree.search(curr) - 3][0].second += 1;
							}
							if (stars_after(buf) == 1)
							{
								cout << dict[tstree.search(curr) - 3][0].first << ",";
								dict[tstree.search(curr) - 3][0].second += 1;
							}
							if (stars_after(buf) == 2)
							{
								cout << dict[tstree.search(curr) - 3][0].first << "?";
								dict[tstree.search(curr) - 3][0].second += 1;
							}
						}

						if ((stars_before(buf) != 0))//для слов вида 234**1** или 234**1
						{
							int i = 0;
							while(buf[i] != '*')
							{
								curr[i] = buf[i];
								i++;
							}
							curr[i] = '\0';
							if (stars_after(buf) == 0)
							{
								cout << dict[tstree.search(curr) - 3][stars_before(buf)].first << ".";
								dict[tstree.search(curr) - 3][stars_before(buf)].second += 1;
								
								pair<string, int> p;
								int b = stars_before(buf);
								int a = tstree.search(curr) - 3;
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
								cout << dict[tstree.search(curr) - 3][stars_before(buf)].first << ",";
								dict[tstree.search(curr) - 3][stars_before(buf)].second += 1;
								
								pair<string, int> p;
								int b = stars_before(buf);
								int a = tstree.search(curr) - 3;
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
								cout << dict[tstree.search(curr) - 3][stars_before(buf)].first << "?";
								dict[tstree.search(curr) - 3][stars_before(buf)].second += 1;
								
								pair<string, int> p;
								int b = stars_before(buf);
								int a = tstree.search(curr) - 3;
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

				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				cout << " ";//пробел между словами
				pos = 0;//обнуляем позицию индекса
				for(int k = 0; k < sizeof(buf); k++)		//обнуляем buf
					buf[k] = '\0';
			}
			else//то есть buf пусто
			{
				cout << " ";//выводим пробел
			}
		}//symb == (char)32

		else//symb != (char)32
		{
			buf[pos] = symb;
			pos++;
		}
		ind++;//следующий символ строки
	}

	//fout.close();
	//fin.close();//для тестирования
	cin.get();
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
/*string conv(int n)
{
    stringstream buf;
    string s;
    buf << n;
    buf >> s;
    buf.clear();
	return s;
}*/

char* itoa(int value, char* result, int base) 
{
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	//cout << "#";
	return result;
}

bool only1(char* ch)
{	
	bool is_only1 = false;
	if (ch[0] == '1')
		is_only1 = true;
	return is_only1;
}

		//		if(!with1(buf))//нет 1 в слове.
		//		{
		//			if (stars_before(buf) != 0)//есть звезды, слов несколько
		//			{
		//				int i = 0;
		//				while(buf[i] != '*')
		//				{
		//					curr[i] = buf[i];
		//					i++;
		//				}
		//				curr[i] = '\0';
		//				//cout << tstree.search(curr) - 3 << " ";// << dict[tstree.search(curr) - 3][stars_before(buf)].second;
		//				cout << dict[tstree.search(curr) - 3][stars_before(buf)].first;
		//				dict[tstree.search(curr) - 3][stars_before(buf)].second += 1;//обновление частоты встречаемости
		//				//moveup(dict[tstree.search(curr) - 1], stars_before(buf));
		//				pair<string, int> p;
		//				int b = stars_before(buf);
		//				int a = tstree.search(curr) - 3;
		//				while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
		//				{
		//					p.first = dict[a][b].first;
		//					p.second = dict[a][b].second;
		//					dict[a][b].first = dict[a][b - 1].first;
		//					dict[a][b].second = dict[a][b - 1].second;
		//					dict[a][b - 1].first = p.first;
		//					dict[a][b - 1].second = p.second;
		//					b--;
		//				}
		//			}
		//			else//нет звезд, значит и слово всего одно. moveup не используем
		//			{
		//				cout << dict[tstree.search(buf) - 3][0].first;
		//				dict[tstree.search(buf) - 3][0].second += 1;//обновление частоты встречаемости
		//			} 
		//		}
		//		else //есть 1 в слове используем функции stars_before для поиска слова и stars_after для знака препинания
		//		{
		//			//добавить обработку слов вида 1**, то есть просто знаков препинания
		//			if (only1(buf))
		//			{
		//				if(stars_after(buf) == 0)
		//					cout << ".";
		//				if(stars_after(buf) == 1)
		//					cout << ",";
		//				if(stars_after(buf) == 2)
		//					cout << "?";
		//			}
		//			else
		//			{
		//				if ((stars_before(buf) == 0)/* && (stars_after(buf) == 0)*/)//для слов вида 2341**, moveup не используем, так как слово одно
		//				{
		//					int i = 0;
		//					while(buf[i] != '1')
		//					{
		//						curr[i] = buf[i];
		//						i++;
		//					}
		//					curr[i] = '\0';
		//					if (stars_after(buf) == 0)
		//					{
		//						cout << dict[tstree.search(curr) - 3][0].first << ".";
		//						dict[tstree.search(curr) - 3][0].second += 1;
		//					}
		//					if (stars_after(buf) == 1)
		//					{
		//						cout << dict[tstree.search(curr) - 3][0].first << ",";
		//						dict[tstree.search(curr) - 3][0].second += 1;
		//					}
		//					if (stars_after(buf) == 2)
		//					{
		//						cout << dict[tstree.search(curr) - 3][0].first << "?";
		//						dict[tstree.search(curr) - 3][0].second += 1;
		//					}
		//				}

		//				if ((stars_before(buf) != 0)/* && (stars_after(buf) == 0)*/)//для слов вида 234**1** или 234**1
		//				{
		//					int i = 0;
		//					while(buf[i] != '*')
		//					{
		//						curr[i] = buf[i];
		//						i++;
		//					}
		//					curr[i] = '\0';
		//					if (stars_after(buf) == 0)
		//					{
		//						cout << dict[tstree.search(curr) - 3][stars_before(buf)].first << ".";
		//						dict[tstree.search(curr) - 3][stars_before(buf)].second += 1;
		//						//moveup(dict[tstree.search(curr) - 1], stars_before(buf));
		//						
		//						pair<string, int> p;
		//						int b = stars_before(buf);
		//						int a = tstree.search(curr) - 3;
		//						while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
		//						{
		//							p.first = dict[a][b].first;
		//							p.second = dict[a][b].second;
		//							dict[a][b].first = dict[a][b - 1].first;
		//							dict[a][b].second = dict[a][b - 1].second;
		//							dict[a][b - 1].first = p.first;
		//							dict[a][b - 1].second = p.second;
		//							b--;
		//						}
		//					}
		//					if (stars_after(buf) == 1)
		//					{
		//						cout << dict[tstree.search(curr) - 3][stars_before(buf)].first << ",";
		//						dict[tstree.search(curr) - 3][stars_before(buf)].second += 1;
		//						//moveup(dict[tstree.search(curr) - 1], stars_before(buf));
		//						
		//						pair<string, int> p;
		//						int b = stars_before(buf);
		//						int a = tstree.search(curr) - 3;
		//						while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
		//						{
		//							p.first = dict[a][b].first;
		//							p.second = dict[a][b].second;
		//							dict[a][b].first = dict[a][b - 1].first;
		//							dict[a][b].second = dict[a][b - 1].second;
		//							dict[a][b - 1].first = p.first;
		//							dict[a][b - 1].second = p.second;
		//							b--;
		//						}
		//					}
		//					if (stars_after(buf) == 2)
		//					{
		//						cout << dict[tstree.search(curr) - 3][stars_before(buf)].first << "?";
		//						dict[tstree.search(curr) - 3][stars_before(buf)].second += 1;
		//						//moveup(dict[tstree.search(curr) - 1], stars_before(buf));
		//						
		//						pair<string, int> p;
		//						int b = stars_before(buf);
		//						int a = tstree.search(curr) - 3;
		//						while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
		//						{
		//							p.first = dict[a][b].first;
		//							p.second = dict[a][b].second;
		//							dict[a][b].first = dict[a][b - 1].first;
		//							dict[a][b].second = dict[a][b - 1].second;
		//							dict[a][b - 1].first = p.first;
		//							dict[a][b - 1].second = p.second;
		//							b--;
		//						}
		//					}
		//				}
		//			}
		//		}