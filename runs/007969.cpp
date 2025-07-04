#include <cstring>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;
#define PII pair<int, int>

vector<PII > ways[40005];
vector<PII> q[40005];
vector<PII> _q;
int res[40005];
int snm[40005];
int predst[40005];
int dist[40005];

int sn(int i)
{
    return snm[i] == i ? i : snm[i] = sn(snm[i]);
}

void join(int a, int b, int p)
{
    a = sn(a);
    b = sn(b);
    if(rand() & 1)swap(a,b);
    snm[b] = a;
    predst[a] = p;
}

void dfs(int i, int h)
{
    if(!dist[i])
    {
        dist[i] = h;
        snm[i] = i;
        predst[i] = i;
        for(size_t j = 0; j < ways[i].size(); j++)
        {
            if(!dist[ways[i][j].first])
            {
                dfs(ways[i][j].first, h + ways[i][j].second);
                join(i, ways[i][j].first, i);
            }
        }
        for(size_t j = 0; j < q[i].size(); j++)
            if(dist[q[i][j].first])
            {
                res[q[i][j].second] = predst[sn(q[i][j].first)];
            }
    }
}

int main()
{
        int n, m;
        scanf("%d", &n);

        for(int i = 0; i < n-1; i++)
        {
                int from, to, len;
                scanf("%d %d %d", &from, &to, &len);
                from--, to--;
                ways[from].push_back( make_pair(to, len) );
                ways[to].push_back( make_pair(from, len) );
        }

		scanf("%d", &m);

        for(int i = 0; i < m; i++)
        {
                int l, r;
                scanf("%d %d", &l, &r);
                l--, r--;
                q[l].push_back(PII(r, i));
                q[r].push_back(PII(l, i));
                _q.push_back( make_pair(l, r) );
        }

        dfs(0, 1);

        for(int i = 0; i < m; i++)
        {
            int l1 = dist[_q[i].first];
            int l2 = dist[_q[i].second];
            int l_mid = dist[res[i]];
            printf("%d\n", (l1 - l_mid) + (l2 - l_mid) );
        }

        return 0;
}
