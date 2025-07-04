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

	// �����, ������� ������ ������� � ����� �������
	void swapBeginEnd()
	{
		swap(this->beginVertex, this->endVertex);
	}
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

	// ����, ������������, ��������� ����� ���� ��� ���
	bool isCalculated;
};



// ����
class Graph
{
private:
	// ���������� ������
	int _vertexCount;

	// ���������� �����
	int _waysCount;

	// ������ �����
	vector<Edge> _content;

	// ������ ������
	vector<Vertex> _vertexes;

	// ������ �����
	vector<Way> _ways;
public:
	// ��� �� ����
	void step_2(int &vertex, int &weight)
	{
		Vertex v = this->_vertexes[vertex - 1];
		weight += this->_vertexes[v.number - 1].wayToParent;
		vertex = this->_vertexes[v.number - 1].parentNumber;
	}

	// ����������� ���������� ������
	void setVertexCount(int vertexCount)
	{
		this->_vertexCount = vertexCount;
	}


	// ���
	void step(int previous, int current, vector<Vertex> &vertexes, int &level)
	{
		level++;
		for  (int i = 0; i < (int)this->_content.size(); i++)
		{			
			Edge e = this->_content[i];
			if ((e.beginVertex == current) && (e.endVertex != previous))
			{
				Vertex v;
				v.number = e.endVertex;
				v.level = level;
				v.parentNumber = e.beginVertex;
				v.wayToParent = e.weight;
				vertexes[v.number - 1] = v;
				step(current, v.number, vertexes, level);
			}
			else if ((e.endVertex == current) && (e.beginVertex != previous))
			{
				Vertex v;
				v.number = e.beginVertex;
				v.level = level;
				v.parentNumber = e.endVertex;
				v.wayToParent = e.weight;
				vertexes[v.number - 1] = v;
				step(current, v.number, vertexes, level);
			}
		}
		level--;
	}
	// ����� ���������� ������� ������
	void getInputData()
	{
		char buffer[1024];

		// ��������� ���������� ������
		cin.getline(buffer, sizeof(buffer) - 1);
		this->_vertexCount = atoi(buffer);
		if (this->_vertexCount <= 0)
			return;

     	// ��������� �����
		while (cin.getline(buffer, sizeof(buffer) - 1))
		{
			string s = buffer;

			int firstSpacePos = s.find_first_of(" ");
			// �������� ��� �����
			if (firstSpacePos <= 0)
			{
				// ���������� ����� �����
				this->_waysCount = atoi(buffer);
				break;
			}

			// ���������� ������ �����, ����� ����� � ��� �����
			int lastSpacePos = s.find_last_of(" ");
			int beginVertex = atoi(s.substr(0, firstSpacePos).data());
			int endVertex= atoi(s.substr(firstSpacePos + 1, lastSpacePos -(firstSpacePos + 1)).data());
			int weight = atoi(s.substr(lastSpacePos + 1, s.length() - (lastSpacePos + 1)).data());

			if (beginVertex > endVertex)
				swap(beginVertex, endVertex);

			Edge edge;
			edge.beginVertex = beginVertex;
			edge.endVertex = endVertex;
			edge.weight = weight;

			// ������� ����� � ������ �����
			this->_content.push_back(edge);
		}

		// �������������� �������
		this->_vertexes.resize(this->_vertexCount);
		int level = 1;
		Vertex v;
		v.level = 1;
		v.number = this->_content[0].beginVertex;
		v.parentNumber = -1;
		v.wayToParent = -1;

		this->_vertexes[v.number - 1] = v;
		this->step(-1, v.number, this->_vertexes, level);
		
		if (this->_waysCount <= 0)
			return;

		// ��������� ����
		for (int i = 0; i < this->_waysCount; i++)
		{
			cin.getline(buffer, sizeof(buffer) - 1);
			string s = buffer;

			int spacePos = s.find_first_of(" ");
			Way way;

			// ���������� ������ � ����� ����
			way.beginVertex = atoi(s.substr(0, spacePos).data());
			way.endVertex = atoi(s.substr(spacePos + 1, s.length() - (spacePos + 1)).data());
			way.weight = 0;
			way.isCalculated = false;

			if (way.beginVertex > way.endVertex)
				swap(way.beginVertex, way.endVertex);
			
			// ������� ���� � ������ �����
			this->_ways.push_back(way);
		}
	}

	// ����� ���������� �����
	void calculateWays()
	{
		// �������� �� ���� ����� � ������
		for (int i = 0; i < this->_waysCount; i++)
		{
			Vertex vb = this->_vertexes[this->_ways[i].beginVertex - 1];
			Vertex ve = this->_vertexes[this->_ways[i].endVertex - 1];
			int weight = 0;
			while (vb.number != ve.number)
			{				
				if (vb.level < ve.level)
				{
					int n = ve.number;
					this->step_2(n, weight);
					ve = this->_vertexes[n - 1];
				}
				else
				{
					int n = vb.number;
					this->step_2(n, weight);
					vb = this->_vertexes[n - 1];
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