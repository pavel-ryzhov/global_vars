#include <vector>
#include <stdio.h>

#define UI unsigned int
#define US unsigned short

using namespace std;

struct Vertex
{
	US parent, level;
	UI depth;
	bool used;
};

vector< pair<US, US> > *e;
pair<US, US> *p;
Vertex *v;

void Precalc(US cV, US pV, UI depth, US level)
{
	v[cV].used = true;
	v[cV].parent = pV;
	v[cV].depth = depth;
	v[cV].level = level;
	for (int i = 0; i < e[cV].size(); i++)
		if (!v[e[cV][i].first].used)
			Precalc(e[cV][i].first, cV, depth + e[cV][i].second, level + 1);
}

int main(int argc, char **argv)
{
	US vCount, pCount, v1, v2, cost;
	
	scanf("%hu", &vCount);
	e = new vector< pair<US, US> >[vCount];
	v = new Vertex[vCount];
	for (int i = 0; i < vCount - 1; i++)
	{
		scanf("%hu %hu %hu", &v1, &v2, &cost);
		e[v1 - 1].push_back(pair<US, US>(v2 - 1, cost));
		e[v2 - 1].push_back(pair<US, US>(v1 - 1, cost));
	}
	
	scanf("%hu", &pCount);
	p = new pair<US, US>[pCount];
	for (int i = 0; i < pCount; i++)
	{
		scanf("%hu %hu", &v1, &v2);
		p[i] = pair<US, US>(v1, v2);
	}
	
	Precalc(0, 0, 0, 0);
	
	for (int i = 0; i < pCount; i++)
	{
		v1 = p[i].first - 1;
		v2 = p[i].second - 1;
		while (v[v1].level != v[v2].level)
			if (v[v1].level > v[v2].level)
				v1 = v[v1].parent;
			else
				v2 = v[v2].parent;
		while (v1 != v2)
		{
			v1 = v[v1].parent;
			v2 = v[v2].parent;
		}
		printf("%u\n", v[p[i].first - 1].depth + v[p[i].second - 1].depth - 2 * v[v1].depth);
	}
	
	delete[] v;
	delete[] p;
	delete[] e;
	
	return 0;
}
