
#include <iostream>

//по поводу организации очереди:
//вообще правильно сделать класс для DQ, при таком подходе, но пока так протестирую, а дальше как успею.
int * dqueue;
int lengthDQ;

int pointerBegDQ;
int pointerEndDQ;

void initDQ(int n)
{
	dqueue = new int [n];
	lengthDQ = n;
}

void deleteDQ()
{
	delete [] dqueue;
}

int popDQ()
{
	int temp = dqueue [pointerBegDQ];
	if(pointerBegDQ == lengthDQ - 1)
	{
		pointerBegDQ = 0;
	}
	else
	{
		pointerBegDQ += 1;
	}
	return temp;
}

void pushFrontDQ(int arg)
{
	if(pointerBegDQ == 0)
	{
		pointerBegDQ = lengthDQ - 1;
	}
	else
	{
		pointerBegDQ -= 1;
	}
	dqueue [pointerBegDQ] = arg;
}

void pushBackDQ(int arg)
{
	dqueue [pointerEndDQ] = arg;
	if(pointerEndDQ == lengthDQ - 1)
	{
		pointerEndDQ = 0;
	}
	else
	{
		pointerEndDQ += 1;
	}
}

void clearDQ()
{
	pointerBegDQ = 0;
	pointerEndDQ = 0;
}

bool isEmptyDQ()
{
	return pointerEndDQ == pointerBegDQ;
}


using namespace std;

int main(int argc, char * argv[])
{
	int N, M;

	int ** graph;
	int ** rootsToFind;
	int * algoArray;
	int * prevArray;
	int i, j, k;

	//для IDArray
	//M0 - вершины, расстояние до которых уже вычислено (но, возможно, не окончательно);	== 2
	//M1 - вершины, расстояние до которых вычисляется;										== 1
	//M2 - вершины, расстояние до которых ещё не вычислено.									== 0
	int * IDArray;

	int tempA, tempB, tempWeight;

	//input
	//graph
	cin >> N;
	algoArray = new int [N];
	prevArray = new int [N];
	IDArray = new int [N];
	initDQ(N);

	graph = new int * [N];
	for (i = 0 ; i < N ; i++ )
	{
		graph [i] = new int [N];
		for (j = 0 ; j < N ; j++ )
		{
			graph [i][j] = 0;
		}
	}
	
	for (i = 0 ; i < N - 1 ; i++ )
	{
		cin >> tempA;
		cin >> tempB;
		cin >> tempWeight;
		graph [tempA - 1][tempB - 1] = tempWeight;
		graph [tempB - 1][tempA - 1] = tempWeight;
	}
	

	//wanted to count
	cin >> M;
	rootsToFind = new int * [M];
	for (i = 0 ; i < M ; i++ )
	{
		int temp;
		rootsToFind [i] = new int [2];
		
		cin >> temp;
		rootsToFind [i][0] = temp - 1;
		cin >> temp;
		rootsToFind [i][1] = temp - 1;
	}		

	//Levit's algorithm
	for (i = 0 ; i < M ; i++ )
	{
		//initialization
		for (k = 0 ; k < N ; k++ )
		{
			algoArray [k] = 1000000; //чтобы было больше 40000 пусть будет миллион
			IDArray [k] = 2;
		}

		//algorithm
		algoArray[rootsToFind [i][0]] = 0;
		IDArray[rootsToFind [i][0]] = 1;
		
		clearDQ();
		pushBackDQ( rootsToFind [i][0] );

		while (!isEmptyDQ())
		{
			int v;
			v = popDQ();
			IDArray[v] = 0;

			for (k = 0 ; k < N ; ++k)
			{
				if(graph [v][k] != 0)
				{
					int to = k, len = graph [v][k];
					if ( algoArray [to] > algoArray [v] + len)
					{
						algoArray [to] = algoArray [v] + len;
						if ( IDArray [to] == 2)
							pushBackDQ (to);
						else if (IDArray [to] == 1)
							pushFrontDQ (to);
						prevArray [to] = v;
						IDArray [to] = 1;
					}
				}
			}
		}		
		
		cout << algoArray [rootsToFind [i][1]] << endl;

	}



	//delete
	for (i = 0 ; i < M ; i++ )
	{
		delete[] rootsToFind [i];
	}
	delete [] rootsToFind;
	for (i = 0 ; i < N ; i++ )
	{
		delete[] graph [i];
	}
	delete [] graph;
	delete [] algoArray;
	delete [] prevArray;
	delete [] IDArray;
	deleteDQ();

	return 0;
}

