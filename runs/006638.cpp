#include <stdio.h>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <bitset>
using namespace std;
struct length
{
	int v1, v2;
	long len;
};
struct vertReference
{
	int vert;
	int weight;
	vertReference (){vert = 0; weight = 0;};
};
typedef vector< list<vertReference> > m;
typedef vector<length> l;
void FillGraph (m &vect, const int count);
l FillLengthList (const int count);
void FindLength (m &vect, length &L, vector<int> &level, vector<long> &lengthes);
vector<int> DefLev (m &vect, vector<long> &lengthes);
void FillGraph (m &vect, const int count)
{
	vect.resize (count);
	int v1, v2, weight;
	vertReference vsp;
	for (int i = 0;i <= count -2; i++)
	{
		scanf ("%i", &v1);
		scanf ("%i", &v2);
		scanf ("%i", &weight);
		vsp.vert = v2 -1;
		vsp.weight = weight;
		vect[v1 - 1].push_back(vsp);
		vsp.vert = v1 -1;
		vect[v2 - 1].push_back(vsp);
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
void FindLength (m &vect, length &L, vector<int> &level, vector<long> &lengthes)
{
	stack<int> s1, s2;
	bitset<40000> visited1, visited2;
	if (L.v1 == L.v2)
	{
		L.len = 0;
		return;
	}
	int i = L.v1 -1;
	int i2 = L.v2 -1;
	s1.push (i);
	visited1[i] = 1;
	s2.push (i2);
	visited2[i2] = 1;
	do
	{
		//1 vert
		if (i)
		{
			for (list<vertReference>::iterator itr1 = vect[i].begin(); itr1 != vect[i].end(); itr1++)
				if (level[i] > level [itr1->vert])
				{
					i = itr1->vert;
					break;
				}
			s1.push (i);
			visited1[i] = 1;
			

			if (visited2[i])
			{
				int i1 = s2.top ();
				int v;
				while (i1 != i)
				{
					s2.pop();
					v = s2.top();		
					for (list<vertReference>::iterator itr4 = vect[i1].begin(); itr4 != vect[i1].end(); itr4++)
						if (itr4->vert == v)
							break;
					if (i1 != i)
						i1 = s2.top();
				}
				L.len = (lengthes[L.v1 -1] - lengthes[i1])+(lengthes[L.v2 -1] - lengthes[i1]);
				return;
			}
			if (i == L.v2 -1)
			{
				L.len = lengthes[L.v1 - 1] - lengthes [L.v2 -1];
				return;
			}
		}
		//2 vert
		if (i2)
		{
			for (list<vertReference>::iterator itr2 = vect[i2].begin(); itr2 != vect[i2].end(); itr2++)
				if (level[i2] > level [itr2->vert])
				{
					i2 = itr2->vert;
					break;
				}
			s2.push (i2);
			visited2[i2] = 1;
			

			if (visited1[i2])
			{
				int i1 = s1.top ();
				int v;
				while (i1 != i2)
				{
					s1.pop();
					v = s1.top();		
					for (list<vertReference>::iterator itr3 = vect[i1].begin(); itr3 != vect[i1].end(); itr3++)
						if (itr3->vert == v)
							break;
					if (i1 != i2)
						i1 = s1.top();
				}
				L.len = (lengthes[L.v1 -1] - lengthes[i1])+(lengthes[L.v2 -1] - lengthes[i1]);
				return;
			}
			if (i2 == L.v1 -1)
			{
				L.len = lengthes[L.v2 -1] - lengthes[L.v1 -1];
				return;
			}
		}
	}
	while (true);
}
vector<int> DefLev (m &vect, vector<long> &lengthes)
{
	vector<int> level;
	lengthes.resize (vect.size());
	bitset<40000> visited;
	level.resize (vect.size());
	queue<int> vertexes;
	vertexes.push (0);
	visited[0] = 1;
	vertexes.push (-1);
	level[0] = 0;
	lengthes[0] = 0;
	int curent = 0;
	int curentLev = 1;
	while (!vertexes.empty())
	{
		int vsp = vertexes.front();
		if (vsp == -1)
		{
			vertexes.pop();
			curentLev++;
			continue;
		}
		curent = vertexes.front();
		vertexes.pop ();
		for (list<vertReference>::iterator itr = vect[curent].begin(); itr != vect[curent].end(); itr++)
		{
			if (!visited[itr->vert])
			{
				vertexes.push (itr->vert);
				visited[itr->vert] = 1;
				level[itr->vert] = curentLev;
				lengthes[itr->vert] = lengthes[curent] + itr->weight;
			}
			if (itr->vert == vect[curent].back().vert)
				if (vertexes.back() != -1)
					vertexes.push(-1);
		}
	}
	return level;
}
int main ()
{
	int N;
 	scanf ("%i", &N);
	m vect;
	FillGraph (vect, N);
	int M;
	scanf ("%i", &M);
	l L=FillLengthList (M);
	vector<int> level;
	vector<long> lengthes;
	if (M)
		level = DefLev (vect, lengthes);
	for (int i = 0; i<= M -1; i++)
		FindLength (vect, L[i], level, lengthes);
	for (int i = 0; i <= M -1; i++)
	{
		printf ("%i", L[i].len);
		printf ("%s", "\n");
	}
	return 0;
}