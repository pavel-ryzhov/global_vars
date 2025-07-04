#include <vector>
#include <iostream>

//class Vars
namespace StCat
{
	class Vars
	{
	public:
		Vars(int first, int second);

	public:
		void AddLength(int length, int vertex);
		int GetLength() const;
		int GetPathCoef() const;
		void SetPathCoef(int pathCoef);
		bool IsComplete() const;
		void AbsLength();
		void SetNumberOfVertexes(int vertexCount);
		void SetVertexComplete(int vertex);

		bool CheckVertex(int vertexNumber);
		void Swap();

	private:
		std::vector<int> oneTimeVertex_;
		bool complete_;
		int pathCoef_;
		int first_;
		int second_;
		int length_;
	};
}

//class Vertex
namespace StCat
{
	class Vertex
	{
	public:
		Vertex();

	public:
		void SetNCount(int count);
		void IncreaseNCount();
		int GetNCount() const;

		void SetPathThrough(int pathThrough);
		void IncreasePathThrough();
		int GetPathThrough() const;

		bool ComparePathWithCount() const;

	private:
		int count_;
		int pathThrough_;
	};
}


//class graph
namespace StCat
{
	class Graph
	{
		typedef std::vector<Vertex> VertexVector_t;
		typedef VertexVector_t::iterator VertexIteratorVector_t;

		typedef std::vector<std::vector<int> > IncMatrix_t;
		typedef IncMatrix_t::iterator IncMatrixIterator_t;

	public:
		Graph(int vertexesCount);

	public:
		void AddLimb(int x, int y, int size);
		void FindStartVertex();
		void SetVeryBigNumber();
		int DecreaseEmptyVertexesCount();
		int GetSize() const;
		bool ComparePathWithCount() const;
		int GetCurrentVertex() const;
		int GetPathThrough() const;
		int GetNCount() const;

		void GetNextVertex();

	private:
		int vertexesCount_;
		int emptyVertexesCount_;
		int currentVertex_;
		int size_;

		VertexVector_t vertexes_;
		IncMatrix_t incMatrix_;
	};
}


int main(int argc, char* argv[])
{

	std::vector<StCat::Vars> vars;
	int vertexCount;
	std::cin >> vertexCount;
//	vertexCount = 14;
	StCat::Graph g(vertexCount);
/*
	g.AddLimb(0, 1, 5);
	g.AddLimb(1, 2, 6);
	g.AddLimb(2, 3, 7);
	g.AddLimb(3, 4, 4);
	g.AddLimb(4, 5, 8);
	g.AddLimb(3, 7, 20);
	g.AddLimb(7, 8, 15);
	g.AddLimb(8, 9, 10);
	g.AddLimb(3, 10, 14);
	g.AddLimb(10, 12, 11);
	g.AddLimb(12, 11, 22);
	g.AddLimb(12, 13, 33);
	g.AddLimb(3, 6, 30);
*/
	int first, second, size;

	if (1 == vertexCount)
	{
		std::cin >> first;
		second = first;
		size = 0;
		g.AddLimb(first - 1, second - 1, size);
	}
	for (int i = 0; i < vertexCount - 1; ++i)
	{
		std::cin >> first >> second >> size;
		g.AddLimb(first - 1, second - 1, size);
	}

	g.FindStartVertex();

	int qSize;
	std::cin >> qSize;

/*
	vars.push_back(StCat::Vars(5, 6));
	vars.push_back(StCat::Vars(2, 6));
	vars.push_back(StCat::Vars(7, 13));
	vars.push_back(StCat::Vars(7, 12));
	vars.push_back(StCat::Vars(7, 11));
	vars.push_back(StCat::Vars(1, 8));
	vars.push_back(StCat::Vars(1, 9));
	vars.push_back(StCat::Vars(1, 13));
	vars.push_back(StCat::Vars(1, 11));
	vars.push_back(StCat::Vars(1, 12));
	qSize = vars.size();
*/

	for (int i = 0; i < qSize; ++i)
	{
		int first, second;
		std::cin >> first >> second;
		vars.push_back(StCat::Vars(first - 1, second - 1));
	}

	int currVertex = g.GetCurrentVertex();
	for (int i = 0; i < qSize; ++i)
	{
		if (vars[i].IsComplete())
			continue;
		
		vars[i].CheckVertex(currVertex);
		vars[i].SetNumberOfVertexes(vertexCount);
	}
	
	int complete = g.DecreaseEmptyVertexesCount();
//	int pathCoef = 0;
	bool checkVertex = false;
//	std::cout << "[" << g.GetCurrentVertex() + 1 << "] ";

	for (;complete != 0;)
	{
		g.GetNextVertex();
		currVertex = g.GetCurrentVertex();
//		std::cout << "[" << currVertex + 1 << "] ";

		size = g.GetSize();

//		if (g.GetNCount() > 1)
//			pathCoef = 1;
//		else 
//			pathCoef = 1;

		if (g.ComparePathWithCount())
		{
			g.SetVeryBigNumber();
		}
		if (1 == g.GetPathThrough())
		{
			complete = g.DecreaseEmptyVertexesCount();
		}

		for (int i = 0; i < qSize; ++i)
		{
			if (vars[i].IsComplete())
				continue;

			checkVertex = vars[i].CheckVertex(currVertex);
			if (vars[i].IsComplete())
			{
//				vars[i].SetPathCoef(1);
				vars[i].AddLength(size, currVertex);

				continue;
			}
			if (checkVertex)
			{
				vars[i].SetVertexComplete(currVertex);

				continue;
			}

			if (0 != vars[i].GetPathCoef())
			{
//				vars[i].SetPathCoef(pathCoef);
//				vars[i].SetPathCoef(pathCoef * vars[i].GetPathCoef());
				vars[i].AddLength(size, currVertex);
//				if (g.GetPathThrough() > 2)
//					vars[i].AbsLength();
			}
		}
	}
	std::cout << std::endl;

	for (int i = 0; i < qSize; ++i)
	{
		std::cout << vars[i].GetLength() << std::endl;
	}

	return 0;
}


//class Vars
namespace StCat
{
	Vars::Vars(int first, int second): first_(first), second_(second), pathCoef_(0), length_(0), complete_(false)
	{
		if (first_ == second_)
			complete_ = true;
	}

	void Vars::SetNumberOfVertexes(int vertexCount)
	{
		oneTimeVertex_.resize(vertexCount);
	}

	int Vars::GetLength() const
	{
		return length_;
	}

	void Vars::SetVertexComplete(int vertex)
	{
		oneTimeVertex_[vertex] = 1;
	}

	void Vars::AddLength(int length, int vertex)
	{
		if (0 == oneTimeVertex_[vertex])
		{
			oneTimeVertex_[vertex] = 1;
			length_ += length;
//			std::cout << "+" << length << " ";

			return;
		}
		length_ -= length;
//		std::cout << "-" << length << " ";

//		length_ += length * pathCoef_;
	}


	void Vars::AbsLength()
	{
//		length_ = abs(length_);
	}

	bool Vars::CheckVertex(int vertexNumber)
	{
		if ((vertexNumber == first_ ) && (pathCoef_ == 0))
		{
			pathCoef_ = 1;

			return true;
		}
		else if ((vertexNumber == second_) && (pathCoef_ == 0))
		{
			Swap();
			pathCoef_ = 1;

			return true;
		}

		if ((vertexNumber == second_) && (pathCoef_ == 1))
		{
			complete_ = true;

			return true;
		}

		return false;
	}

	void Vars::SetPathCoef(int pathCoef)
	{
		pathCoef_ = pathCoef;
	}

	void Vars::Swap()
	{
		int tmp = first_;
		first_ = second_;
		second_ = tmp;

	}

	bool Vars::IsComplete() const
	{
		return complete_;
	}

	int Vars::GetPathCoef() const
	{
		return pathCoef_;
	}
}



//class Vertex definition
namespace StCat
{
	Vertex::Vertex(): count_(0), pathThrough_(0)
	{
	}

	void Vertex::SetNCount(int count)
	{
		count_ = count;
	}

	void Vertex::IncreaseNCount()
	{
		++count_;
	}

	int Vertex::GetNCount() const
	{
		return count_;
	}

	void Vertex::SetPathThrough(int pathThrough)
	{
		pathThrough_ = pathThrough;
	}

	int Vertex::GetPathThrough() const
	{
		return pathThrough_;
	}

	void Vertex::IncreasePathThrough()
	{
		++pathThrough_;
	}

	bool Vertex::ComparePathWithCount() const
	{
		return pathThrough_ == count_;
	}
}


//class graph definition
namespace StCat
{
	const int VERYBIGNUMBER = 40001;
	Graph::Graph(int vertexesCount): vertexesCount_(vertexesCount), emptyVertexesCount_(0), size_(0)
	{
		vertexes_.resize(vertexesCount_);
		incMatrix_.resize(vertexesCount_);
		for (IncMatrixIterator_t i = incMatrix_.begin(); i != incMatrix_.end(); ++i)
			i->resize(vertexesCount_);
	}

	int Graph::GetPathThrough() const
	{
		return vertexes_[currentVertex_].GetPathThrough();
	}

	void Graph::AddLimb(int x, int y, int size)
	{
		vertexes_[x].IncreasePathThrough();
		vertexes_[y].IncreasePathThrough();
		incMatrix_[x][y] = incMatrix_[y][x] = size;
	}

	void Graph::FindStartVertex()
	{
		if (1 == vertexesCount_)
		{
			currentVertex_ = 0;
			emptyVertexesCount_ = 1;

			return;
		}
		for (int i = 0; i < vertexesCount_; ++i)
		if (1 == vertexes_[i].GetPathThrough())
		{
			currentVertex_ = i;
			++emptyVertexesCount_;
		}
		SetVeryBigNumber();
	}

	bool Graph::ComparePathWithCount() const
	{
		return vertexes_[currentVertex_].ComparePathWithCount();
	}

	int Graph::GetCurrentVertex() const
	{
		return currentVertex_;
	}

	void Graph::SetVeryBigNumber()
	{
		vertexes_[currentVertex_].SetNCount(VERYBIGNUMBER);
	}

	int Graph::GetNCount() const
	{
		return vertexes_[currentVertex_].GetNCount();
	}

	int Graph::DecreaseEmptyVertexesCount()
	{
		return --emptyVertexesCount_;
	}

	int Graph::GetSize() const
	{
		return size_;
	}

	void Graph::GetNextVertex()
	{
		if (!emptyVertexesCount_)
			return;

		int tmpCurrentVertex = currentVertex_;
		int min = VERYBIGNUMBER;

		for (int i = 0; i < vertexesCount_; ++i)
		{
			if (i == currentVertex_)
				continue;

			if (0 == incMatrix_[i][currentVertex_])
				continue;

			if (vertexes_[i].GetNCount() >= VERYBIGNUMBER)
				continue;

			if (vertexes_[i].GetNCount() == 0)

			{
				tmpCurrentVertex = i;

				break;
			}
			if (min > vertexes_[i].GetPathThrough())
			{
				min = vertexes_[i].GetPathThrough();
				tmpCurrentVertex = i;
//				size_ = incMatrix_[i][currentVertex_];
//				currentVertex_ = i;
//				vertexes_[currentVertex_].IncreaseNCount();
			}
		}
		size_ = incMatrix_[tmpCurrentVertex][currentVertex_];
		currentVertex_ = tmpCurrentVertex;
		vertexes_[currentVertex_].IncreaseNCount();
	}
}