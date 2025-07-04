#include <iostream>
#include <cstdlib>
#include <vector>

using std::vector;
using std::endl;
using std::cerr;
using std::cout;
using std::cin;

struct two {
	int knot, index;
};

struct edge {
	int knot, ro;
};

const int MAXSZ = 40000;

vector<int> tree[MAXSZ];
vector<two> query[MAXSZ];
vector<edge> nolink[MAXSZ];
two stack[MAXSZ];
int answer_ro[MAXSZ], *bound_ro(answer_ro), parent[MAXSZ],
	ancestor[MAXSZ], finded_ro[MAXSZ], ro[MAXSZ];
int root;

#define is_rounded(v)	(ro[v] == -1)

int get_parent(const int v)
{
	int &p(parent[v]);
	if(v == p) return v;
	else p = get_parent(p);
}

void unite(int u, int v)
{
	const int anc = u;
	u = get_parent(u);
	v = get_parent(v);

	parent[u] = v;
	ancestor[v] = anc;
}

void round_tree()
{
	register int i, j(1);
	int v, u, r;

	stack[0].knot = root;

	do {
		int &index  = stack[j - 1].index;
		v = stack[j - 1].knot;

		const vector<int> &subtree = tree[v];

		if(index < (int) subtree.size()) {
			u = subtree[index];
			finded_ro[u] = finded_ro[v] + ro[u];
			ro[u] = -1;
			stack[j].knot = u;
			index++; j++;
		} else {
			const vector<two> &qv = query[v];

			for(i = 0; i < (int) qv.size(); i++)
				if(is_rounded(u = qv[i].knot)) {
					r = ancestor[get_parent(u)];
					answer_ro[qv[i].index] = 
						finded_ro[u] + finded_ro[v] - (finded_ro[r] << 1);
				}
			stack[--j].index = 0;
			unite(stack[j - 1].knot, v);
		}
	} while(j);

	for(register int *p(answer_ro); p < bound_ro; p++)
		cout << *p << endl;
}

int read_tree()
{	
	int n;

	cin >> n;

	if(n > 0) {
		register int i(1);
		int u, v, r, temp;

		cin >> root >> v >> r;

		tree[root].push_back(v);
		ro[v] = r;
		parent[root] = root;
		parent[v] = v;
		if(root) parent[0] = 1;

		n--;

		for(; i < n; i++) {
			cin >> u >> v >> r;
			if(parent[v] == v) { temp = v; v = u; u = temp; }
			else if(parent[u] != u) {
				edge e;
				e.knot = v; e.ro = r;
				nolink[u].push_back(e);
				e.knot = u;
				nolink[v].push_back(e);
				continue;
			}
			tree[u].push_back(v);
			ancestor[v] = parent[v] = v;
			ro[v] = r;

			if(nolink[v].size()) {
				register int j(1);

				stack[0].knot = v;

				do {
					int &index = stack[j - 1].index;
					v = stack[j - 1].knot;

					const vector<edge> &fromv = nolink[v];

					if(index < (int) fromv.size())
					{
						u = fromv[index].knot;
						if(parent[u] != u) {
							stack[j].knot = u;
							tree[v].push_back(u);
							ro[u] = fromv[index].ro;
							ancestor[u] = parent[u] = u;
							j++;
						}
						index++;
					} else stack[--j].index = 0;
				} while(j);
			}
		}
	}
	return n > 0;
}

int read_queries()
{
	register int i(0);
	int u, v, m;
	two t;

	cin >> m;

	bound_ro += m;

	for(; i < m; i++) {
		cin >> u >> v;
		t.knot = v; t.index = i;
		query[u].push_back(t);
		t.knot = u;
		query[v].push_back(t);
	}

	return m > 0;
}

int main(int argc, char **argv)
{
	int retv;

	try {
		if(read_tree() && read_queries())
			round_tree();
		retv = EXIT_SUCCESS;
	} catch(...) {
		cerr << "Unknown error." << endl;
		retv = EXIT_FAILURE;
	}
	return retv;
}