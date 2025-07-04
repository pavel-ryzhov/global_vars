#include <exception>
#include <iostream>
#include <stdio.h>
#include <string.h>

#define UI unsigned int
#define US unsigned short

#define INF 0xFFFFFFFF

struct Edge
{
	US v1, v2, cost;
};

struct Path
{
	US v1, v2;
};

void Trace(Edge *e, UI *d, US vCount, US s)
{
	memset(d, 0xFF, vCount * sizeof(d[0]));
	d[s - 1] = 0;
	UI temp;
	while (true)
	{
		bool flag = false;
		for (int j = 0; j < vCount - 1; j++)
			if (d[e[j].v1] < INF)
			{
				temp = d[e[j].v1] + e[j].cost;
				if (d[e[j].v2] > temp)
				{
					d[e[j].v2] = temp;
					flag = true;
				}
			}
			else
				if (d[e[j].v2] < INF)
				{
					temp = d[e[j].v2] + e[j].cost;
					if (d[e[j].v1] > temp)
					{
						d[e[j].v1] = temp;
						flag = true;
					}
				}
		if (!flag)
			break;
	}
}

int main(int argc, char **argv)
{
	Edge *e;
	US vCount, pCount;
	
	std::cin >> vCount;
	try
	{
		e = new Edge[vCount - 1];
	}
	catch (std::exception &ex)
	{
		std::cerr << "Exception: " << ex.what() << std::endl;
	}
	for (int i = 0; i < vCount - 1; i++)
	{
		std::cin >> e[i].v1 >> e[i].v2 >> e[i].cost;
		e[i].v1--;
		e[i].v2--;
	}
	
	UI *d = new UI[vCount];
	//US p[2], pLast;
	US pLast;
	
	
	std::cin >> pCount;
	/*for (int i = 0; i < pCount; i++)
	{
		std::cin >> p[1] >> p[2];
		if (p[1] != pLast)
			Trace(e, d, vCount, p[1]);
		std::cout << d[p[2] - 1] << std::endl;
		pLast = p[1];
	}*/
	Path *p = new Path[pCount];
	for (int i = 0; i < pCount; i++)
		std::cin >> p[i].v1 >> p[i].v2;
	for (int i = 0; i < pCount; i++)
	{
		if (p[i].v1 != pLast)
			Trace(e, d, vCount, p[i].v1);
		std::cout << d[p[i].v2 - 1] << std::endl;
		pLast = p[i].v1;
	}
	
	delete[] p;
	delete[] d;
	delete[] e;
	
	return 0;
}
