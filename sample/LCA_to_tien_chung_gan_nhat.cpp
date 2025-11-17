#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define ll long long
#define MAX 1000
#define MAX_LOG_N 20

int n;
vector<pii> a[MAX];
int up[MAX][MAX_LOG_N];
int depth[MAX];
ll d[MAX];
int logN;

void init()
{
    logN = 0;
    while ((1 << logN) <= n + 1)
        ++logN;

    for (int i = 0; i <= n; i++)
    {
        fill(up[i], up[i] + logN, -1);
    }
    fill(depth, depth + n + 1, 0);
    fill(d, d + n + 1, 0);
}


void f(int u, int parent)
{
    up[u][0] = parent;
    for (int i = 1; i < logN; ++i)
    {
        if (up[u][i - 1] != -1)
            up[u][i] = up[up[u][i - 1]][i - 1];
        else
            up[u][i] = -1;
    }

    for (auto [v, w] : a[u])
    {
        if (v != parent)
        {
            depth[v] = depth[u] + 1;
            d[v] = d[u] + w;
            f(v, u);
        }
    }
}

int kth_ancestor(int u, int k)
{
    for (int i = 0; i < logN; ++i)
    {
        if (k & (1 << i))
        {
            u = up[u][i];
            if (u == -1)
                break;
        }
    }
    return u;
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    u = kth_ancestor(u, depth[u] - depth[v]);

    if (u == v)
        return u;

    for (int i = logN - 1; i >= 0; --i)
    {
        if (up[u][i] != -1 && up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

ll distance(int u, int v)
{
    int ancestor = lca(u, v);
    return d[u] + d[v] - 2 * d[ancestor];
}

int main()
{
    n = 5;


    tuple<int, int, int> edges[n - 1] = {{2, 3, 100}, {4, 3, 200}, {1, 5, 150}, {1, 3, 50}};
    for (int i = 0; i < n - 1; i++)
    {
        auto [u, v, w] = edges[i];
        a[u].push_back({v, w});
        a[v].push_back({u, w});
    }
    
    init();
    f(1, -1); // gốc là node 1

    for (int u = 1; u <= n; u++)
    {
        for (int k = 0; k < 3; k++)
        {
            cout << "Ancestor(" << u << ", " << k << ") = " << kth_ancestor(u, k) << '\n';
        }

        for (int v = u + 1; v <= n; v++)
        {
            cout << "LCA(" << u << ", " << v << ") = " << lca(u, v) << '\n';
            cout << "Distance(" << u << ", " << v << ") = " << distance(u, v) << '\n';
        }
        cout << endl;
    }

    return 0;
}
