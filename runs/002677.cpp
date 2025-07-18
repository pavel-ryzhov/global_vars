#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

typedef unsigned int dword;

vector < vector < pair < string, int> > > dict;
int high;//��� ����������
int low = 0;//��� ����������
pair<string, int> t;

int transform(char*);
int step (int, int p);//�������
bool with1(char[]);//���� �� 1 � �����
int stars(char []);//������� ����� �������� * � �����
int stars_before(char[]);//������� �������� * ������������ 1 � �����
int stars_after(char[]);//������� �������� * ������� ����� 1 � �����
void moveup(vector < pair <string, int> > &, int);//����� ��������������� ����� ����� �� ������
string conv(int);
struct mysort//comparator ��� ����������
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
enum constants 
{
    any_one_char = '?'
};

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
// partial match search
// e.g. 
size_t partial_match_search(const CHAR *s, std::vector<dword>& result_set ) const
{
  partial_match_search(0,s,result_set);
  return result_set.size();
}

//
// neighbour search 
//
// 'd' is Hamming distance of a query word: 
//      A measure of the difference between two strings, 
//      expressed by the number of characters that need to be changed to 
//      obtain one from the other. 
//      E.g., 0101 and 0110 has a Hamming distance of two 
//      whereas "Butter" and "ladder" are four characters apart.
//
size_t neighbour_search(const CHAR *s, int d, std::vector<dword>& result_set) const
{
  neighbour_search(0, s, result_set, d);
  return result_set.size();
}

//protected:
//typedef unsigned int node_index;

struct node 
{
   CHAR       splitchar;
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
dword       max_no;

size_t      total_nodes() const { return (dword) nodes.size(); }

node_index  insert(node_index nid, const CHAR *s)
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

//partial match search
void partial_match_search(node_index nid, const CHAR *s, std::vector<dword>& result_set ) const 
{    
     if (nid >= total_nodes()) 
       return;
     const node& n = nodes[nid];
     if (*s == any_one_char || *s < n.splitchar)
        partial_match_search(n.lokid, s, result_set);
     if (*s == any_one_char || *s == n.splitchar)
        if (n.splitchar && *s)
            partial_match_search(n.eqkid, s+1, result_set);
     if (*s == 0 && n.splitchar == 0)
            result_set.push_back( (dword) n.value());
     if (*s == any_one_char || *s > n.splitchar)
            partial_match_search(n.hikid, s, result_set);
}

static int  length(const CHAR* s)
{
  const CHAR* ps = s; while(*s) ++s; return s - ps;
}

void neighbour_search(node_index nid, const CHAR *s, std::vector<dword>& result_set, int d) const
{   
    if (nid >= total_nodes() || d < 0) return;

    const node& n = nodes[nid];      

    if (d > 0 || *s < n.splitchar)
        neighbour_search(n.lokid, s, result_set, d);
    if (n.splitchar == 0) 
    {
       if ( length(s) <= d)
          result_set.push_back(n.value());
    } 
    else
       neighbour_search(n.eqkid, *s ? s+1:s, result_set, (*s == n.splitchar) ? d:d-1 );
    if (d > 0 || *s > n.splitchar)
       neighbour_search(n.hikid, s, result_set, d);
}

};
//ifstream fin;
int main()
{
	ternary_tree<char> tstree;
	char buf[25];
	char ch[25];
	char s[25];
	char x[25];
	int N = 0;
	int key;
	//fin.open("dic.txt");
	//������� ������� ������
	cin >> buf;
	N = atoi(buf);
	//���������� ������ tstree � ��������� dict
	dict.resize(N);
	for (int i = 0; i < N; i++)
	{
		cin >> buf;//��������� �����
		strcpy(s, buf);
		char *c = new char[strlen(conv(transform(s)).c_str())];
		strcpy(c, conv(transform(s)).c_str());
		for(int j = 0; j < 25; j++)
		{
			strcpy(x, c);
		}
		//x = itoa(transform(buf), ch, 10)
		if (tstree.search(x) == 0)
		{
			tstree.insert(x);
			cin >> buf;//��������� �������
			dict[tstree.search(x) - 1].push_back(make_pair(s, atoi(buf)));
		}
		else
		{
			cin >> buf;//��������� �������
			dict[tstree.search(x) - 1].push_back(make_pair(s, atoi(buf)));
		}
		//delete []c;//
	}

	//������������� dict
	
	high = dict[0].size() - 1;
	sort(dict[0].begin(), dict[0].end(), mysort());
	
	//����� ���������
	while(cin >> buf)
	{
		if(!with1(buf))//��� 1 � �����.
		{
			if (stars_before(buf) != 0)//���� ������, ���� ���������
			{
				int i = 0;
				while(buf[i] != '*')
				{
					curr[i] = buf[i];
					i++;
				}
				cout << dict[tstree.search(curr) - 1][stars_before(buf)].first << " ";
				dict[tstree.search(curr) - 1][stars_before(buf)].second += 1;//���������� ������� �������������
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
			/*	cout << " after: ";
				cout << dict[0][0].first << " " << dict[0][0].second;
				cout << " ";
				cout << dict[0][1].first << " " << dict[0][1].second;
				cout << " ";
				cout << dict[0][2].first << " " << dict[0][2].second;
				cout << endl;*/
			}
			else//��� �����, ������ � ����� ����� ����. moveup �� ����������
			{
				cout << dict[tstree.search(buf) - 1][0].first << " ";
				dict[tstree.search(buf) - 1][0].second += 1;//���������� ������� �������������
				/*cout << " after: ";
				cout << dict[0][0].first << " " << dict[0][0].second;
				cout << " ";
				cout << dict[0][1].first << " " << dict[0][1].second;
				cout << " ";
				cout << dict[0][2].first << " " << dict[0][2].second;
				cout << endl;*/
			} 
		}
		else //���� 1 � ����� ���������� ������� stars_before ��� ������ ����� � stars_after ��� ����� ����������
		{
			if ((stars_before(buf) == 0)/* && (stars_after(buf) == 0)*/)//��� ���� ���� 2341**, moveup �� ����������, ��� ��� ����� ����
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
					/*cout << " after: ";
					cout << dict[0][0].first << " " << dict[0][0].second;
					cout << " ";
					cout << dict[0][1].first << " " << dict[0][1].second;
					cout << " ";
					cout << dict[0][2].first << " " << dict[0][2].second;
					cout << endl;*/
				}
				if (stars_after(buf) == 1)
				{
					cout << dict[tstree.search(curr) - 1][0].first << ", ";
					dict[tstree.search(curr) - 1][0].second += 1;
					/*cout << " after: ";
					cout << dict[0][0].first << " " << dict[0][0].second;
					cout << " ";
					cout << dict[0][1].first << " " << dict[0][1].second;
					cout << " ";
					cout << dict[0][2].first << " " << dict[0][2].second;
					cout << endl;*/
				}
				if (stars_after(buf) == 2)
				{
					cout << dict[tstree.search(curr) - 1][0].first << "? ";
					dict[tstree.search(curr) - 1][0].second += 1;
					/*cout << " after: ";
					cout << dict[0][0].first << " " << dict[0][0].second;
					cout << " ";
					cout << dict[0][1].first << " " << dict[0][1].second;
					cout << " ";
					cout << dict[0][2].first << " " << dict[0][2].second;
					cout << endl;*/
				}
			}

			if ((stars_before(buf) != 0)/* && (stars_after(buf) == 0)*/)//��� ���� ���� 234**1** ��� 234**1
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
					/*cout << " after: ";
					cout << dict[0][0].first << " " << dict[0][0].second;
					cout << " ";
					cout << dict[0][1].first << " " << dict[0][1].second;
					cout << " ";
					cout << dict[0][2].first << " " << dict[0][2].second;
					cout << endl;*/
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
					/*cout << " after: ";
					cout << dict[0][0].first << " " << dict[0][0].second;
					cout << " ";
					cout << dict[0][1].first << " " << dict[0][1].second;
					cout << " ";
					cout << dict[0][2].first << " " << dict[0][2].second;
					cout << endl;*/
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
					/*cout << " after: ";
					cout << dict[0][0].first << " " << dict[0][0].second;
					cout << " ";
					cout << dict[0][1].first << " " << dict[0][1].second;
					cout << " ";
					cout << dict[0][2].first << " " << dict[0][2].second;
					cout << endl;*/
				}
			}

		}
	}
	cin.get();
	return 0;
}

//�������� ���������� �����
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