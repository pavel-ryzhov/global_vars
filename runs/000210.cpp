#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// �����
class Edge
{
public:
	// ������ �����
	int beginVertex;

	// ����� �����
	int endVertex;

	// ��� �����
	int weight;
};

// �������
class Vertex
{
public:
	int number;
	int level;
	int parentNumber;
	int wayToParent;
};

// ���� � ������
class Way
{
public:
	// ��������� ������� ����
	int beginVertex;

	// �������� ������� ����
	int endVertex;

	// ����� ����
	int weight;
};

// �����
class Link
{
public:
	int endVertex;
	int weight;
};

// ����
class Graph
{
public:
	// ���������� ������
	int vertexCount;

	// ���������� �����
	int waysCount;

	// ������ �����
	vector<Edge> edges;

	// ������ ������
	vector<Vertex> vertexes;

	// ������ �����
	vector<Way> ways;

	// ����� ������ ���� � ������
	vector< vector<Link> > links;

	// ��� �� ����
	void stepToRoot(int &vertex, int &weight)
	{
		weight += this->vertexes[this->vertexes[vertex - 1].number - 1].wayToParent;
		vertex = this->vertexes[this->vertexes[vertex - 1].number - 1].parentNumber;
	}

	// ���
	void step(int previous, int current, vector<Vertex> &vertexes, int &level)
	{
		level++;
		for (int i = 0; i < (int)this->links[current - 1].size(); i++)
		{
			if ((int)this->links[current - 1][i].endVertex != previous)
			{
				Vertex v;
				v.number = (int)this->links[current - 1][i].endVertex;
				v.level = level;
				v.parentNumber = current;
				v.wayToParent = (int)this->links[current - 1][i].weight;
				vertexes[v.number - 1] = v;
				step(current, v.number, vertexes, level);
			}
		}		
		level--;
	}
	// ����� ���������� ������� ������
	void getInputData()
	{
		char buffer[32];

		// ��������� ���������� ������
		cin.getline(buffer, sizeof(buffer) - 1);
		this->vertexCount = atoi(buffer);

		if (this->vertexCount <= 0)
			return;

		this->links.resize(this->vertexCount);

     	// ��������� �����
		while (cin.getline(buffer, sizeof(buffer) - 1))
		{
			string s = buffer;

			int firstSpacePos = s.find_first_of(" ");
			// �������� ��� �����
			if (firstSpacePos <= 0)
			{
				// ���������� ����� �����
				this->waysCount = atoi(buffer);
				break;
			}

			// ���������� ������ �����, ����� ����� � ��� �����
			int lastSpacePos = s.find_last_of(" ");
			int beginVertex = atoi(s.substr(0, firstSpacePos).data());
			int endVertex= atoi(s.substr(firstSpacePos + 1, lastSpacePos -(firstSpacePos + 1)).data());
			int weight = atoi(s.substr(lastSpacePos + 1, s.length() - (lastSpacePos + 1)).data());

			// �������������� �����
			Edge edge;
			edge.beginVertex = beginVertex;
			edge.endVertex = endVertex;
			edge.weight = weight;

			// ������� ����� ������
			Link l;
			l.endVertex = endVertex;
			l.weight = weight;
			this->links[beginVertex - 1].push_back(l);
			l.endVertex = beginVertex;
			this->links[endVertex - 1].push_back(l);

			// ������� ����� � ������ �����
			this->edges.push_back(edge);
		}

		// ���������� ������� ������
		this->vertexes.resize(this->vertexCount);
		int level = 1;
		Vertex v;
		v.level = 1;
		if (this->vertexCount > 1)
		{
			v.number = this->edges[0].beginVertex;
			v.parentNumber = -1;
			v.wayToParent = -1;

			this->vertexes[v.number - 1] = v;
			this->step(-1, v.number, this->vertexes, level);
		}
		
		if (this->waysCount <= 0)
			return;

		// ��������� ����
		for (int i = 0; i < this->waysCount; i++)
		{
			cin.getline(buffer, sizeof(buffer) - 1);
			string s = buffer;

			int spacePos = s.find_first_of(" ");
			
			// ���������� ������ � ����� ����
			Way way;			
			way.beginVertex = atoi(s.substr(0, spacePos).data());
			way.endVertex = atoi(s.substr(spacePos + 1, s.length() - (spacePos + 1)).data());
			way.weight = 0;

			if (way.beginVertex > way.endVertex)
				swap(way.beginVertex, way.endVertex);
			
			// ������� ���� � ������ �����
			this->ways.push_back(way);
		}
	}

	// ����� ���������� �����
	void calculateWays()
	{
		// �������� �� ���� ����� � ������
		for (int i = 0; i < this->waysCount; i++)
		{
			if (this->ways[i].beginVertex == this->ways[i].endVertex)
			{
				cout << 0 << endl;
				continue;
			}
			Vertex vb = this->vertexes[this->ways[i].beginVertex - 1];
			Vertex ve = this->vertexes[this->ways[i].endVertex - 1];
			int weight = 0;
			while (vb.number != ve.number)
			{				
				if (vb.level < ve.level)
				{
					int n = ve.number;
					this->stepToRoot(n, weight);
					ve = this->vertexes[n - 1];
				}
				else
				{
					int n = vb.number;
					this->stepToRoot(n, weight);
					vb = this->vertexes[n - 1];
				}
			}
			cout << weight << endl;
		}
	}
};

int main(void)
{
	Graph g;
	g.getInputData();
	g.calculateWays();
	return 0;
}