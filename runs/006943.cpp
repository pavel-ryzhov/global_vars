#include <stdlib.h>
#include <stdio.h>


#define MAX_VALUE 40001


typedef struct
{
	int from, to;
} Edge;


typedef struct
{
	int   verticesCount;
	int   desiredLengthsCount;
	int  *graph;
	Edge *desiredLengths;
} State;


State *loadData(void)
{
	int verticesCount, vertex0, vertex1, length, i;
	if (scanf("%i", &verticesCount) != 1)
		return NULL;

	int const size = verticesCount * verticesCount;
	int *graph = (int *)malloc(sizeof(int) * size);
	for (i = 0; i < size; ++i)
		graph[i] = MAX_VALUE;

	for (i = 1; i < verticesCount; ++i)
	{
		if (scanf("%i%i%i", &vertex0, &vertex1, &length) != 3 || vertex0 > verticesCount || vertex1 > verticesCount)
		{
			free(graph);
			return NULL;
		}
		--vertex0;
		--vertex1;
		graph[vertex0 * verticesCount + vertex1] = length;
		graph[vertex1 * verticesCount + vertex0] = length;
	}

	int desiredLengthsCount;
	if (scanf("%i", &desiredLengthsCount) != 1)
	{
		free(graph);
		return NULL;
	}

	Edge *desiredLengths = (Edge *)malloc(sizeof(Edge) * desiredLengthsCount);
	for (i = 0; i < desiredLengthsCount; ++i)
	{
		if (scanf("%i%i", &vertex0, &vertex1) != 2 || vertex0 > verticesCount || vertex1 > verticesCount)
		{
			free(graph);
			free(desiredLengths);
			return NULL;
		}
		desiredLengths[i].from = vertex0 - 1;
		desiredLengths[i].to   = vertex1 - 1;
	}

	State *state = (State *)malloc(sizeof(State));
	state->verticesCount       = verticesCount;
	state->desiredLengthsCount = desiredLengthsCount;
	state->graph               = graph;
	state->desiredLengths      = desiredLengths;
	return state;
}


int computePathsLengths(State *state)
{
	if (state == NULL)
		return -1;
	if (state->verticesCount <= 0 || state->graph == NULL)
		return -2;

	int const verticesCount = state->verticesCount;
	int *graph = state->graph;
	int i, j, k;
	for (k = 0; k < verticesCount; ++k)
	{
		int const k1 = k * verticesCount;
		for (i = 0; i < verticesCount; ++i)
		{
			int const i1 = i * verticesCount;
			for (j = 0; j < verticesCount; ++j)
			{
				int const newLength = graph[i1 + k] + graph[k1 + j];
				if (graph[i1 + j] > newLength)
					graph[i1 + j] = newLength;
			}
		}
	}

	return 0;
}


int printPathsLengths(State *state)
{
	if (state == NULL)
		return -1;
	if (state->desiredLengthsCount < 0 || state->verticesCount < 0 || state->desiredLengths == NULL || state->graph == NULL)
		return -2;

	int from, to;
	int i;
	int const verticesCount = state->verticesCount;
	int const desiredLengthsCount = state->desiredLengthsCount;
	int *graph = state->graph;
	Edge *desiredLengths = state->desiredLengths;
	for (i = 0; i < desiredLengthsCount; ++i)
	{
		Edge *current = desiredLengths + i;
		printf("%i\n", state->graph[current->from * verticesCount + current->to]);
	}

	return 0;
}


void freeData(State *state)
{
	if (state->graph)
		free(state->graph);
	if (state->desiredLengths)
		free(state->desiredLengths);
	free(state);
}


int main(void)
{
	int result = 0;
	State *state = loadData();
	if (state == NULL)
		return -1;
	if ((result = computePathsLengths(state)) < 0)
	{
		freeData(state);
		return result;
	}
	if ((result = printPathsLengths(state)) < 0)
	{
		freeData(state);
		return result;
	}
	return 0;
}
