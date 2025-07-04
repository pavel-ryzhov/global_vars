#include "iostream"
int tree[40000][3]; //0 - parent, 1 - deep, 2 - distance
int a[40000][3];

void qs(int l, int r) {
	int i = l;
	int j = r;
	int x = a[(l+(r-l)/2)][0];
	do {
		while (a[i][0] < x)
			i++;
		while (a[j][0] > x)
			j--;
		if (i <= j) {
			int t = a[i][0];
			a[i][0] = a[j][0];
			a[j][0] = t;

			t = a[i][1];
			a[i][1] = a[j][1];
			a[j][1] = t;
			
			t = a[i][2];
			a[i][2] = a[j][2];
			a[j][2] = t;

			++i;
			--j;
		}
	} while (i <= j);
		if (l < j)
			qs(l,j);
		if (i > r)
			qs(i,r);
}

long res(int u, int v) {
	int h1,h2;
	long r = 0;

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
	for (k = 1; k < n; k++) {
		std::cin >> a[k][0];
		std::cin >> a[k][1];
		std::cin >> a[k][2];
		if (a[k][0] > a[k][1]) {
			t = a[k][0];
			a[k][0] = a[k][1];
			a[k][1] = t;
		}
	}
	if (n > 2) qs(1,n-1);
	for (k=1; k < n; k++) {
		if (tree[(a[k][1])][0] != 0) {
			t = a[k][1];
			a[k][1] = a[k][0];
			a[k][0] = t;
		}
		tree[(a[k][1])][0] = a[k][0];						//parent
		tree[(a[k][1])][1] = tree[(a[k][0])][1]+1;			//deep
		tree[(a[k][1])][2] = a[k][2];					//distance
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

