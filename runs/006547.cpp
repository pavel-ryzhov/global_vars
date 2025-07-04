#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) a>=b? a : b
#define MIN(a,b) a<=b? a : b
#define MINMA 256
#define MAX_INDEX 40000;

template <class T> class Array
{
private:
	T* elements_;

	int limit_;
	int count_;
	bool memoryCopy_;

	void push_part();
public:

	Array<T>();
	Array<T>( const Array& other );
	~Array();

	int size();
	void push(const T t);
	void push();
	void setMemoryCopy(const bool memoryCopy);
	const T& pop();

	const Array<T>& operator = (const Array<T>& other);
	const T& operator [] (int i) const;
	T& operator [] (int i);

	void out();
};

template<class T> Array<T>::Array():
elements_( NULL ),
limit_ (MINMA),
count_ (0),
memoryCopy_ (true)
{
	if ( limit_ > 0 )
	{
		elements_ = new T[limit_];
	}
}

template<class T> Array<T>::Array( const Array& other ):
limit_ (other.limit_),
count_ (other.count_),
memoryCopy_ (other.memoryCopy_)
{
	if (limit_ > 0)
	{
		elements_ = new T[other.limit_];

		if (count_ > 0)
		{

			if (memoryCopy_)
			{
				memcpy(elements_, other.elements_, sizeof(T)*count_);
			}
			else
			{
				for(int i = 0; i < count_; ++i)
				{
					elements_[i] = other.elements_[i];
				}
			}
		}
	}
}

template<class T> Array<T>::~Array()
{
	if (elements_)
		delete [] elements_;
}

template<class T> int Array<T>::size()
{
	return count_;
}

template<class T> void Array<T>::push(const T t)
{
	push_part();
	elements_[count_ - 1] = t;
	return;
}
template<class T> void Array<T>::setMemoryCopy(const bool memoryCopy)
{
	memoryCopy_ = memoryCopy;
	return;
}
template<class T> void Array<T>::push()
{
	push_part();
	return;
}

template<class T> void Array<T>::push_part()
{
	if ( limit_ == 0 )
	{
		limit_ = 1;
		elements_ = new T[limit_];
	}
	else if ( count_ >= limit_ )
	{
		T* oldElements = elements_;

		limit_ = 2 * limit_;

		elements_ = new T[limit_];


		if (memoryCopy_)
		{
			memcpy( elements_, oldElements, sizeof(T) * count_ );
		}
		else
		{
			for(int i = 0; i < count_; ++i)
			{
				elements_[i] = oldElements[i];
			}
		}
		delete [] oldElements;
	}

	++ count_;
	return;
}





template<class T> const T& Array<T>::pop()
{
	-- count_;
	return elements_[count_];
}

template<class T> void Array<T>::out()
{
	int i;

	for(i = 0; i < count_; ++i)
	{
		elements_[i].out();
	}
	return;
}

template<class T> const Array<T>& Array<T>::operator = (const Array<T>& other)
{
	limit_ = other.limit_;
	count_ = other.count_;
	memoryCopy_ = other.memoryCopy_;

	if (elements_)
	{
		delete [] elements_;
	}

	elements_ = new T[limit_];

	if (count_ > 0)
	{
		if (memoryCopy_)
		{
			memcpy( elements_, other.elements_, sizeof(T) * count_);
		}
		else
		{
			for(int i = 0; i < count_; ++i)
			{
				elements_[i] = other.elements_[i];
			}
		}
	}

	return *this;
}

template<class T> const T& Array<T>::operator [] (int i) const
{
	return elements_[i];
}


template<class T> T& Array<T>::operator [] (int i)
{
	return elements_[i];
}
/////////////////////////////////////////////////////////////








////////////////////////////////////////////////////////////

class Tree
{
private:
	struct SearchTree
	{
		int index;
		int deep;
		int lenght;
	};
	struct PeaksList
	{
		int deep;
		int index;
		int frequency;
		Array<int> subPeaks;
	};
	struct Element
	{
		int u;
		int v;
		int lenght;
	};
	PeaksList *peaksList_;
	int *localTreeIndex_;
	int *localTreeLenght_;

	Array<Element> treeElement_;
	typedef Array<SearchTree> ArraySearchTree;
	Array<ArraySearchTree> searchTree_;

	int quantity_;
	int maxDeep_;
	int maxIndex_;
	int minIndex_;

	int qntOfMemPlaces_;
	std::string strFile_;
	int position_;

	int getLenght(const int &u, const int &v);
public:
	Tree();
	~Tree();

	int readFromFile();
	int readFromScreen();
	int initializeTree();

	int	calculLenghtsAndPrint();

};

Tree::Tree()
{
	peaksList_= NULL;
	searchTree_.setMemoryCopy(false);
	localTreeIndex_ = NULL;
	localTreeLenght_=NULL;
};
Tree::~Tree()
{
	if (localTreeIndex_)
	{
		delete[] localTreeIndex_;
	}
	if (localTreeLenght_)
	{
		delete[] localTreeLenght_;
	}
	if (peaksList_)
	{
		delete[] peaksList_;
	}
};


int Tree::readFromScreen()
{
	maxIndex_ = 0;
	minIndex_ = MAX_INDEX;
	int i = 0;
	Element treeE;

	std::cin >> quantity_;
	if (quantity_ < 2)
	{
		int g;
		std::cin >> g;

		for(i = 0; i < quantity_; ++i)
		{
			std::cin >> g;
			std::cin >> g;
		}
        std::cout << "0";
		return -1;
	}
	else
	{
		for(i = 0; i < quantity_ - 1; ++i)
		{
			std::cin >> treeE.u;
			std::cin >> treeE.v;
			std::cin >> treeE.lenght;
			treeElement_.push(treeE);
			maxIndex_ = MAX(maxIndex_, treeE.u);
			maxIndex_ = MAX(maxIndex_, treeE.v);
			minIndex_ = MIN(minIndex_, treeE.u);
			minIndex_ = MIN(minIndex_, treeE.v);
		}


		qntOfMemPlaces_ = maxIndex_ - minIndex_ + 1;
		peaksList_ = new PeaksList[qntOfMemPlaces_];
		memset(peaksList_, 0, sizeof(PeaksList)*(qntOfMemPlaces_));

		for(i = 0; i < quantity_ - 1; ++i)
		{
			peaksList_[treeElement_[i].u - minIndex_].frequency ++;
			peaksList_[treeElement_[i].u - minIndex_].subPeaks.push(treeElement_[i].v - minIndex_);

			peaksList_[treeElement_[i].v - minIndex_].frequency ++;
			peaksList_[treeElement_[i].v - minIndex_].subPeaks.push(treeElement_[i].u - minIndex_);
		}
		return 0;
	}
}

int Tree::initializeTree()
{
	int zeroCntAll = 0;

	maxDeep_ = 0;

	PeaksList **sortList;
	PeaksList **sortListB;

	sortList = new PeaksList *[qntOfMemPlaces_];
	sortListB = new PeaksList *[qntOfMemPlaces_];

	for(int i = 0; i < qntOfMemPlaces_; ++i)
	{
		sortList[i] = &peaksList_[i];
	}

	while (qntOfMemPlaces_ - zeroCntAll)
	{
		maxDeep_++;
		searchTree_.push();

		int r = 0;
		int zeroCnt = 0;

		int lim = qntOfMemPlaces_ - zeroCntAll;
		for(int i = 0 ; i < lim; ++i)
		{
			if((sortList[i]->frequency) == 1 || lim == 1)
			{
				//////////////
				sortList[i]->deep = maxDeep_ - 1;
				searchTree_[maxDeep_ - 1].push();
				sortList[i]->index = searchTree_[maxDeep_ - 1].size() - 1;
				///////////////
				zeroCnt++;
				sortListB[qntOfMemPlaces_ - zeroCnt] = sortList [i];
				zeroCntAll++;
			}
			else
			{
				if (sortList[i]->frequency > 1)
				{
					sortListB[r] = sortList[i];
					r++;
				}
				if (sortList[i]->frequency < 1)
				{
					zeroCntAll++;
				}
			}
		}
		memcpy(sortList, sortListB, r * sizeof(PeaksList *));

		for(int i = qntOfMemPlaces_ - zeroCnt; i < qntOfMemPlaces_; ++i)
		{
			for(int k = 0; k < sortListB[i]->subPeaks.size(); ++k)
			{
				peaksList_[sortListB[i]->subPeaks[k]].frequency--;
			}
		}
	}
	if (sortList)
		delete [] sortList;
	if (sortListB)
		delete [] sortListB;

	if (searchTree_[maxDeep_ - 1].size() > 1)
	{
		searchTree_[maxDeep_ - 1][0].lenght = 0;
		searchTree_[maxDeep_ - 1][1].lenght = 0;
	}

	for(int i = 0; i < quantity_ - 1; ++i)
	{
		int n1 = peaksList_[treeElement_[i].u - minIndex_].deep;
		int m1 = peaksList_[treeElement_[i].u - minIndex_].index;

		int n2 = peaksList_[treeElement_[i].v - minIndex_].deep;
		int m2 = peaksList_[treeElement_[i].v - minIndex_].index;

		if ( n1 <= n2)
		{
			searchTree_[n1][m1].deep = n2;
			searchTree_[n1][m1].index = m2;
			searchTree_[n1][m1].lenght = treeElement_[i].lenght;
		}
		else
		{
			searchTree_[n2][m2].deep = n1;
			searchTree_[n2][m2].index = m1;
			searchTree_[n2][m2].lenght = treeElement_[i].lenght;
		}
	}

	if (searchTree_[maxDeep_ - 1].size() > 1)
	{
		searchTree_[maxDeep_ - 1][0].deep = maxDeep_;
		searchTree_[maxDeep_ - 1][1].deep = maxDeep_;
		searchTree_[maxDeep_ - 1][0].index = 0;
		searchTree_[maxDeep_ - 1][1].index = 0;

		searchTree_[maxDeep_ - 1][0].lenght += searchTree_[maxDeep_ - 1][1].lenght;
		searchTree_[maxDeep_ - 1][1].lenght = 0;
		searchTree_.push();
		maxDeep_++;
		searchTree_[maxDeep_ - 1].push();
	}

	return 0;
}

int	Tree::calculLenghtsAndPrint()
{
	localTreeIndex_ = new int[maxDeep_];
	localTreeLenght_ = new int[maxDeep_];

	int quantityT;
	std::cin >> quantityT;
	for(int i = 0; i < quantityT ; ++i)
	{
		int u;
		std::cin >> u;
		int v;
		std::cin >> v;
		int lenght = getLenght(u - minIndex_, v - minIndex_);
		printf("%d\n", lenght);
	}
	return 0;
}

int Tree::getLenght(const int &u, const int &v)
{
	/////////////////
	memset(localTreeIndex_, -1, sizeof(int) * maxDeep_);
	memset(localTreeLenght_, 0, sizeof(int) * maxDeep_);
	///////////////////
	int level10 = peaksList_[u].deep;
	int index10 = peaksList_[u].index;

	int level20 = peaksList_[v].deep;
	int index20 = peaksList_[v].index;

	if (level10 > level20)
	{
		level10 = peaksList_[v].deep;
		index10 = peaksList_[v].index;

		level20 = peaksList_[u].deep;
		index20 = peaksList_[u].index;
	}


	int level1;
	int index1;

	int lenght = 0;

	while(level10 < maxDeep_ - 1)
	{
		level1 = searchTree_[level10][index10].deep;
		index1 = searchTree_[level10][index10].index;
		lenght += searchTree_[level10][index10].lenght;

		localTreeIndex_[level1] = index1;
		localTreeLenght_[level1] = lenght;

		level10 = level1;
		index10 = index1;
	}

	int lenght2 = 0;
	int level2;
	int index2;


	while(localTreeIndex_[level20] != index20)
	{
		level2 = searchTree_[level20][index20].deep;
		index2 = searchTree_[level20][index20].index;
		lenght2 += searchTree_[level20][index20].lenght;

		level20 = level2;
		index20 = index2;
	}

	return localTreeLenght_[level20] + lenght2;
}
int main()
{
	Tree tr;
	int error = tr.readFromScreen();
	if (!error)
	{
		tr.initializeTree();

		tr.calculLenghtsAndPrint();
	}
	return 0;
}
