#include <stdio.h>
#include <vector>
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
void FindLength (m &matr, length &L);
bool Find (m &matr, stack<int> &s, set<int> &visited, int v2, long &len);
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
void FindLength (m &matr, length &L)
{
	L.len = 0;
	stack<int> s;
	set<int> visited;
	if (L.v1 == L.v2)
	{
		L.len = 0;
		return;
	}
	s.push (L.v1 -1);
	visited.insert (L.v1 -1);
	Find (matr, s, visited, L.v2 -1, L.len);
}
bool Find (m &matr, stack<int> &s, set<int> &visited, int v2, long &len)
{
	int v1=s.top ();
	if (v1==v2)
	{
		return true;
	}
	else
	{
		bool f = false;
		for (int i = 0; i <= matr.size ()-1; i++)
		{
			if (matr[v1][i] >= 0 && visited.find (i) == visited.end ())
			{
				s.push (i);
				visited.insert (i);
				len+=matr[v1][i];
				f=Find (matr,s, visited, v2,len);
				if (f)
					break;
				else
				{
					s.pop ();
					len-=matr[v1][i];
				}
			}
		}
		return f;
	}
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
	for (int i = 0; i<= M -1; i++)
		FindLength (matr, L[i]);
	for (int i = 0; i <= M -1; i++)
	{
		printf ("%i", L[i].len);
		printf ("%s", "\n");
	}
	return 0;
}