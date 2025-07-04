#include <iostream>
#include <vector>
#include <utility>
#include <ctime>
using namespace std;

typedef pair<int, int> ip;
typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<ip> vip;

int tree(vi &v, vi &t, vi &h, int L = 0, int R = -1, int i = 0) {
    if(R == -1) R = v.size() - 1;
    if(L == R) return t[i] = v[L];
    int M = (L + R) / 2, i1 = 2 * i + 1, i2 = 2 * i + 2;
    int t1 = tree(v, t, h, L, M, i1), t2 = tree(v, t, h, M + 1, R, i2);
    return t[i] = (h[t1] < h[t2] ? t1 : t2);
}

// v[L...R], min from v[l...r]
int min(int l, int r, vi &v, vi &t, vi &h, int L = 0, int R = -1, int i = 0) {
    if(R == -1) R = v.size() - 1;
    if(l == L && r == R) return t[i];
    int M = (L + R) / 2, i1 = 2 * i + 1, i2 = 2 * i + 2;
    if(r <= M) return min(l, r, v, t, h, L, M, i1);
    if(l > M) return min(l, r, v, t, h, M + 1, R, i2);
    int t1 = min(l, M, v, t, h, L, M, i1), t2 = min(M + 1, r, v, t, h, M + 1, R, i2);
    return h[t1] < h[t2] ? t1 : t2;
}

void dfs(vector<vip> &g, vip &p, vi &h, vi &f, vi &o, vc &c, int u = 0) {
    c[u] = true;
    o.push_back(u);
    f[u] = o.size() - 1;
    vip::iterator t;
    int v, w;
    for(t = g[u].begin(); t != g[u].end(); t++) {
        v = (*t).first;
        w = (*t).second;
        if(!c[v]) {
            p[v].first = u;
            p[v].second = w;
            h[v] = h[u] + 1;
            dfs(g, p, h, f, o, c, v);
            o.push_back(u);
        }
    }
}

int lca(int u, int v, vi &f, vi &o, vi &t, vi &h) {
    return min(min(f[u], f[v]), max(f[u], f[v]), o, t, h);
}

// weight of u~>v
int weight(int u, int v, vip &p) {
    int w = 0;
    for( ; u != v; u = p[u].first)
        w += p[u].second;   
    return w;
}

int main() {
    int N, M, u, v, w, i;
    cin >> N;
    vector<vip> g(N);
    vip p(N); //parent
    vi h(N, 0); //height
    vi f(N); //first
    vi o; //order
    vc c(N, false); //color(=opened)
    for(i = 0; i < N - 1; i++) {
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back(ip(v, w));
        g[v].push_back(ip(u, w));
    }
    dfs(g, p, h, f, o, c);
    vi t(4 * o.size());
    tree(o, t, h);
    cin >> M;
    int l, w1, w2;
    for(i = 0; i < M; i++) {
        cin >> u >> v;
        u--, v--;
        l = lca(u, v, f, o, t, h);
        w1 = (l == u) ? 0 : weight(u, l, p);
        w2 = (l == v) ? 0 : weight(v, l, p);
        cout << w1 + w2 << "\n";
    }
    return 0;
}
