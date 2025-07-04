#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <set>
using namespace std;
struct length
{
	int v1, v2;
	long len;
};
typedef vector< vector<int> > m;
typedef vector<length> l;
void FillGraph (m &matr, const int count);
l FillLengthList (const int count);
void FindLength (m &matr, length &L, vector<int> level);
vector<int> DefLev (m &matr);
void FillGraph (m &matr, const int count)
{
	matr.resize (count);
	for (int i = 0; i <= count -1; i++)
		matr[i].resize (count);
	for (int i = 0; i <= count -1; i++)
		for (int j = 0; j <= count -1; j++)
			matr[i][j] = -1;
	int v1, v2, weight;
	for (int i = 0;i <= count -2; i++)
	{
		scanf ("%i", &v1);
		scanf ("%i", &v2);
		scanf ("%i", &weight);
		matr[v1-1][v2-1] = weight;
		matr[v2-1][v1-1] = weight;
	}
}
l FillLengthList (const int count)
{
	l L;
	L.resize (count);
	for (int i = 0; i <= count -1; i++)
	{
		scanf ("%i", &(L[i].v1));
		scanf ("%i", &(L[i].v2));
	}
	return L;
}
void FindLength (m &matr, length &L, vector<int> level)
{
	L.len = 0;
	long len1, len2;
	len1 = 0;
	len2 = 0;
	stack<int> s1, s2;
	set<int> visited1;
	if (L.v1 == L.v2)
	{
		L.len = 0;
		return;
	}
	int i = L.v1 -1;
	s1.push (i);
	visited1.insert (i);
	do
	{
		for (int i1 = 0; i1 <= matr.size() -1; i1++)
			if ((matr[i][i1] >=0) && (level[i] > level [i1]))
			{
				len1 += matr[i][i1];
				i = i1;
				break;
			}
		s1.push (i);
		visited1.insert (i);
		
	}
	while (i);
	bool nfound;
	i = L.v2 -1;
	s2.push (i);
	if (visited1.find (i) == visited1.end())
	{
		do 
		{
			for (int i1 = 0; i1 <= matr.size() -1; i1++)
				if ((matr[i][i1] >=0) && (level[i] > level [i1]))
				{
					len2 += matr[i][i1];
					i = i1;
					break;
				}
				if (nfound=(visited1.find (i) == visited1.end()))
					s2.push (i);
		}
		while (nfound);
	}
	int i1 = s1.top ();
	while (i1 != i)
	{
		s1.pop();
		len1 -= matr[i1][s1.top()];
		i1 = s1.top();
	}
	L.len = len1 + len2;
}
vector<int> DefLev (m &matr)
{
	vector<int> level;
	set<int> visited;
	level.resize (matr.size());
	queue<int> vert;
	vert.push (0);
	visited.insert (0);
	vert.push (-1);
	level[0] = 0;
	int curent = 0;
	int curentLev = 1;
	while (!vert.empty())
	{
		int vsp = vert.front();
		if (vsp == -1)
		{
			vert.pop();
			curentLev++;
			continue;
		}
		curent = vert.front();
		vert.pop ();
		for (int i = 0; i <= matr.size() -1; i++)
		{
			if ((matr[curent][i] >=0) && (visited.find(i) == visited.end()))
			{
				vert.push (i);
				visited.insert (i);
				level[i] = curentLev;
			}
			if (i == matr.size() -1)
				if (vert.back() != -1)
					vert.push(-1);
		}
	}
	return level;
}
int main ()
{
	int N;
 	scanf ("%i", &N);
	m matr;
	FillGraph (matr, N);
	int M;
	scanf ("%i", &M);
	l L=FillLengthList (M);
	vector<int> level;
	level = DefLev (matr);
	for (int i = 0; i<= M -1; i++)
		FindLength (matr, L[i], level);
	for (int i = 0; i <= M -1; i++)
	{
		printf ("%i", L[i].len);
		printf ("%s", "\n");
	}
	return 0;
}