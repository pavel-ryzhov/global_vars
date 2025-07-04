#include "iostream"
int tree[40000][3]; //0 - parent, 1 - deep, 2 - distance

int res(int u, int v) {
	int h1,h2,r = 0;

	h1 = tree[u][1];		//deep u
	h2 = tree[v][1];		//deep v

	while (h1!=h2) {
		if (h1>h2) {
			r = r + tree[u][2];
			u = tree[u][0];
			h1 = h1 - 1;
		} else {
			r =r + tree[v][2];
			v = tree[v][0];
			h2 = h2 - 1;
		}
	}

	while (u!=v) {
		r = r + tree[u][2];
		u = tree[u][0];
		r = r + tree[v][2];
		v = tree[v][0];
	}
	return r;
}

int main()
{
	int n,m,t;
	long r;
	int k,i,j,dis,u,v;
	tree[1][1] = 0;
	std::cin >> n;
	for (k=1; k < n; k++) {
		std::cin >> i;
		std::cin >> j;
		std::cin >> dis;
		if (tree[j][0] != 0) {
			t = j;
			j = i;
			i = t;
		}
		tree[j][0] = i;						//parent
		tree[j][1] = tree[i][1]+1;			//deep
		tree[j][2] = dis;					//distance
	}
	std::cin >> m;
	for (k=0; k<m; k++) {
		std::cin >> u;
		std::cin >> v;
		r = res(u,v);						//result distance
		std::cout << r;
		std::cout << "\n";
	}
	return 0;
}

