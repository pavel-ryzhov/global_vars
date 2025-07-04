#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ����� ������ ������� � ������ ���������� ������
bool isPresent(int value, vector<int> values)
{
	return (find(values.begin(), values.end(), value) != values.end());
}

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

	// ������ �����
	vector<Way> _ways;

	// �������� �� �����
	void step(Way &way, Edge edge, vector<int> &vertexes)
	{
		// ����������� ����� ����
		way.weight += edge.weight;
		vertexes.push_back(edge.endVertex);

		// ��������� ����� ����
		if (edge.endVertex == way.endVertex)
		{
			way.isCalculated = true;
			return;
		}

		// ������������� ����������� �����
		for (int i = 0; i < (int)this->_content.size(); i++)
		{
			Edge tmpEdge;
			if (edge.endVertex == this->_content[i].beginVertex)
			{
				tmpEdge = this->_content[i];
				if (!isPresent(tmpEdge.endVertex, vertexes))
					this->step(way, tmpEdge, vertexes);
				if (way.isCalculated)
					return;
			}
			else if (edge.endVertex == this->_content[i].endVertex)
			{
				tmpEdge = this->_content[i];
				tmpEdge.swapBeginEnd();	
				if (!isPresent(tmpEdge.endVertex, vertexes))
					this->step(way, tmpEdge, vertexes);
				if (way.isCalculated)
					return;
			}
			
		}

		way.weight -= edge.weight;
	}
public:
	// ����������� ���������� ������
	void setVertexCount(int vertexCount)
	{
		this->_vertexCount = vertexCount;
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
			// ������� ��������� �����
			Edge emptyEdge;
			emptyEdge.beginVertex = -1;
			emptyEdge.endVertex = this->_ways[i].beginVertex;
			emptyEdge.weight = 0;
			
			vector<int> vertexes;
			// ��������� ��������� ������ �����
			this->step(this->_ways[i], emptyEdge, vertexes);

			// ������� ���������
			cout << this->_ways[i].weight << endl;
		}
	}
};

int main(void)
{
	Graph g;
	g.getInputData();
	system("cls");

	g.calculateWays();
	return 0;
}