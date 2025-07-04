#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_NODES 40000


struct node
{
	int *edge;
	int *len;
	int en;
};

struct node *tree;

int *stack1, *stack2, *stack3;
int ix = 0;

void push (int a, int b, int c)
{
	stack1[ix] = a;
	stack2[ix] = b;
	stack3[ix] = c;
	ix++;
	assert (ix <= MAX_NODES);
}
void pop (int *a, int *b, int *c)
{
	ix--;
	assert (ix >= 0);
	*a = stack1[ix];
	*b = stack2[ix];
	*c = stack3[ix];
}

int find_way (int from, int to)
{
	int cur = from;
	if (from == to) return 0;
	int sum = 0;
	int ed = 0;
	ix = 0;
	push (-1, -1, -1);

	while (1)
	{
		if (cur == to) return sum;
		if (ed >= tree[cur].en)
		{
			if (cur == from) return -1;
			else
			{
				pop (&cur, &ed, &sum);
				ed++;
			}
		}
		else
		{
			if (tree[cur].edge[ed] == stack1[ix-1]) ed++;
			else
			{
				push (cur, ed, sum);
				sum += tree[cur].len[ed];
				cur = tree[cur].edge[ed];
				ed = 0;
			}

		}

	}
}

int main ()
{
	stack1 = (int*) malloc (sizeof(int) * MAX_NODES);
	if (stack1 == NULL) exit(1);
	stack2 = (int*)malloc (sizeof(int) * MAX_NODES);
	if (stack2 == NULL) exit(1);
	stack3 = (int*)malloc (sizeof(int) * MAX_NODES);
	if (stack3 == NULL) exit(1);
	int num_edges;
	scanf ("%i", &num_edges);

	tree = (struct node*)malloc (sizeof(struct node) * MAX_NODES);
	memset (tree, 0, sizeof(struct node) * MAX_NODES);
	int i;
	for (i = 1; i < num_edges; i++)
	{
		int a, b, c;
		scanf ("%u %u %u", &a, &b, &c);
		if (tree[a].en == 0)
		{
			if ((tree[a].edge = (int*)malloc (sizeof(int) * 16)) == NULL)
				exit (1);
			if ((tree[a].len = (int*)malloc (sizeof(int) * 16)) == NULL)
				exit (1);
		}
		else if (tree[a].en == 16 || tree[a].en == 64 || tree[a].en == 256
				|| tree[a].en == 1024 
				|| tree[a].en == 4096
				|| tree[a].en == 16384)
		{
			tree[a].edge = (int*)realloc (tree[a].edge, sizeof(int)*tree[a].en*4);
			tree[a].len = (int*)realloc (tree[a].len, sizeof(int)*tree[a].en*4);
		}
		tree[a].edge[tree[a].en] = b;
		tree[a].len[tree[a].en] = c;
		tree[a].en++;

		if (tree[b].en == 0)
		{
			tree[b].edge = (int*)malloc (sizeof(int) * 16);
			tree[b].len = (int*)malloc (sizeof(int) * 16);
		}
		else if (tree[b].en == 16 || tree[b].en == 64 || tree[b].en == 256
				|| tree[b].en == 1024 
				|| tree[b].en == 4096
				|| tree[b].en == 16384)
		{
			tree[b].edge = (int*)realloc (tree[b].edge, sizeof(int)*tree[b].en*4);
			tree[b].len = (int*)realloc (tree[b].len, sizeof(int)*tree[b].en*4);
		}
		tree[b].edge[tree[b].en] = a;
		tree[b].len[tree[b].en] = c;
		tree[b].en++;
	}

	int num_ways;
	scanf ("%i", &num_ways);

	for (i = 0; i < num_ways; i++)
	{
		int from, to;
		scanf ("%i %i", &from, &to);
		int way = find_way (from, to);
		printf ("%i\n", way);
	}


	for (i = 0; i < MAX_NODES; i++)
		if (tree[i].en != 0)
		{
			free (tree[i].edge);
			free (tree[i].len);
		}

	free (tree);
	free (stack1);
	free (stack2);
	free (stack3);
}
