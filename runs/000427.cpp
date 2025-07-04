#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;

class TOP
{
public:
	int timeToOwner;
	int prev;
	bool empty;
};

class INPUT
{
public:
	int first;
	int second;
	int dist;
};

class TREE
{
public:
	int numTop;
	TOP * tree;	

public:
	TREE()
	{   
		cin >> numTop;
		tree = new TOP[numTop];
		for(int i = 1; i < numTop;++i)
		{
			tree[i].empty = true;
		}
		tree[0].prev = -1;
		tree[0].timeToOwner = 0;
		tree[0].empty = false;
		//cout<<numTop<<endl;
	}

	void buildTree()
	{
		INPUT * uncorrect = new INPUT[numTop - 1];
		int indexUnc = 0;
		int out;
		int in;
		int buff;
		int numCorrect = 0;
	
		for(int i = 0; i < numTop - 1; ++i)
		{ 
			cin >> out;
			cin >> in;
			out--;
			in--;			
			
			if(tree[out].empty != tree[in].empty)
			{				
				if(tree[in].empty == false)
				{
					buff = out;
					out = in;
					in = buff;
				}

				cin >> tree[in].timeToOwner;
				tree[in].prev = out;
				tree[in].empty = false;
				//cout<<endl<<tree[in].prev<<"   "<<in<<"   "<<tree[in].timeToOwner<<endl;
			}
			else
			{
				if(tree[in].empty == false && tree[out].empty == false)
				{
					cout<<endl<<"OOOOOOOOOOOOOOSSSHHHHHH!"<<endl;
					break;
				}
				uncorrect[indexUnc].first = out;	
				uncorrect[indexUnc].second = in;
				cin >> uncorrect[indexUnc].dist;
				//cout<<endl<< uncorrect[indexUnc].first<<"???"<< uncorrect[indexUnc].second <<"???"<< uncorrect[indexUnc].dist<<endl;
				indexUnc++;				
			}			
		}

		while( numCorrect !=  indexUnc)
		{
			numCorrect = 0;

			for(int i = 0; i < indexUnc; ++i)
			{
				out = uncorrect[i].first;
				in = uncorrect[i].second;

				if(tree[out].empty != tree[in].empty)
				{				
					if(tree[in].empty == false)
					{
						buff = out;
						out = in;
						in = buff;
					}

					tree[in].timeToOwner = uncorrect[i].dist;
					tree[in].prev = out;
					tree[in].empty = false;
					//cout<<endl<<tree[in].prev<<"   "<<in<<"   "<<tree[in].timeToOwner<<endl;

					uncorrect[i].dist = -1;
				}

				if(uncorrect[i].dist == -1)
				{
					numCorrect++;
				}
			}
		}
		delete uncorrect;
	}

	void readCmd()
	{
		int from;
		int to;

		int numDist;
		long result;

		cin >> numDist;
		//cout << numDist<<endl;

		for( int i = 0; i < numDist; ++i)
		{
			cin >> from;
			cin >> to;

			//cout<<endl<<from<<"  "<<to<<endl;

			result = getWayTime(from - 1, to - 1);
		}
	}

	inline long getWayTime(int from, int to)
	{
		//cout << from << "  " << to;
		long result = 0;		
		long timeToNull = 0;
        int * chainF = new int[numTop];
		int * chainT = new int[numTop];
		int i;
		int j;

		chainF[0] = from;		
		//cout<<endl<<chainF[0];

		for(i = 1; i < numTop; ++i)
		{
			if(tree[chainF[i-1]].prev == -1)
			{
				break;
			}
			chainF[i] = tree[chainF[i-1]].prev;
			timeToNull += tree[chainF[i-1]].timeToOwner;			
			//cout<<"  "<<chainF[i]<<"  "<<tree[chainF[i]].prev<<" "<<endl;
		}

		//cout<<endl<<timeToNull<<endl;

		chainT[0] = to;		
		//cout<<endl<<chainT[0];

		for(j = 1; j < numTop; ++j)
		{
			if(tree[chainT[j-1]].prev == -1)
			{
				break;
			}
			chainT[j] = tree[chainT[j-1]].prev;
			timeToNull += tree[chainT[j-1]].timeToOwner;
			//cout<<"  "<<chainT[j]<<"  "<<tree[chainT[j]].prev<<" "<<endl;
		}
		//cout<<endl<<timeToNull<<endl;

		i--;
		j--;

		//cout<<endl<<chainF[i]<<"  "<<chainT[j]<<endl<<"///////////////////////////"<<endl;		

		while((chainT[j] == chainF[i]) && (i>=0)&&(j>=0))
		{	
			timeToNull -= tree[chainF[i]].timeToOwner;
			timeToNull -= tree[chainT[j]].timeToOwner;		

			i--;
			j--;
		} 		

		delete chainF;
		delete chainT;		
		//cout << chainF[i] << "  " << chainT[j] << endl;
		cout<<timeToNull<< endl;
		return result;
	}

};

int main()
{
	TREE newTree;

	newTree.buildTree();
	newTree.readCmd();	
	
	//system("pause");
	return 0;
}