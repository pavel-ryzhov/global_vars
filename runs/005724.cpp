#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_NODES 40001


struct node
{
	int *edge;
	int *len;
	int en;
};

struct node *tree;

unsigned *stack1;
int ix = 0;

void push (int a, int b)
{
	stack1[ix] = a | (b << 16);
	ix++;
}
void pop (int *a, int *b)
{
	ix--;
	int x = stack1[ix];
	*a = x & 0xFFFF;
	*b = x >> 16;
}

int find_way (int from, int to)
{
	struct node *cnode;
	int cur = from;
	if (from == to) return 0;
	int sum = 0;
	int ed = 0;
	int ced;
	int cen;
	ix = 0;
	push (cur, 0);
	cur = tree[cur].edge[0];

	while (1)
	{
		cnode = &tree[cur];
		ced = cnode -> edge[ed];
		cen = cnode -> en;

		if (cur == to) break;

		if (ed >= cen)
		{
			pop (&cur, &ed);
//			printf ("Восстанавливаем из стека: ix = %i, cur = %i, ed = %i\n", ix, cur, ed);
			ed++;
			continue;
		}
		else if (ced == (stack1[ix-1] & (unsigned)0xFFFF)) 
			ed++;
		else
		{
			push (cur, ed);
//			printf ("Записываем в стек: ix = %i, cur = %i, ed = %i\n", ix, cur, ed);
			cur = ced;
			ed = 0;
		}


	}
	int i;
	for (i = 0; i < ix; i++)
	{
		unsigned x = stack1[i];
//		printf ("i = %d node = %d len = %i sum = %i\n", i, x&0xFFFF, tree[x & 0xFFFF].len [x >> 16], sum);
		sum += tree[x & 0xFFFF].len [x >> 16];
	}
	return sum;
}

int main ()
{
	stack1 = (unsigned*) malloc (sizeof(int) * MAX_NODES);
	int num_edges;
	scanf ("%i", &num_edges);

	tree = (struct node*) malloc (sizeof(struct node) * MAX_NODES);
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
		else if (tree[a].en == 16 || tree[a].en == 128
				|| tree[a].en == 1024 
				|| tree[a].en == 8192)
		{
			tree[a].edge = (int*)realloc (tree[a].edge, sizeof(int)*tree[a].en*8);
			tree[a].len = (int*)realloc (tree[a].len, sizeof(int)*tree[a].en*8);
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
}
