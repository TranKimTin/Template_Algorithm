#include <bits/stdc++.h>
using namespace std;

class WeightedTree
{
private:
    int n, logN;
    vector<vector<pair<int, int>>> a;
    vector<vector<int>> up;
    vector<int> depth;
    vector<long long> d;

    void dfs(int u, int parent)
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
                dfs(v, u);
            }
        }
    }

public:
    WeightedTree(int maxNode)
    {
        n = maxNode + 1;
        logN = 0;
        while ((1 << logN) <= n)
            ++logN;

        a.resize(n);
        up.assign(n, vector<int>(logN, -1));
        depth.assign(n, 0);
        d.assign(n, 0);
    }

    void add_edge(int u, int v, int w)
    {
        a[u].emplace_back(v, w);
        a[v].emplace_back(u, w);
    }

    void build(int root = 1)
    {
        dfs(root, -1);
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

    long long distance(int u, int v)
    {
        int ancestor = lca(u, v);
        return d[u] + d[v] - 2 * d[ancestor];
    }
};

int main()
{
    int n;
    cin >> n;
    WeightedTree tree(n);

    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        tree.add_edge(u, v, w);
    }

    tree.build(0); // gốc là node 0

    int u, v, k;
    cin >> u >> v >> k;
    cout << "LCA(" << u << ", " << v << ") = " << tree.lca(u, v) << '\n';
    cout << "Ancestor(" << u << ", " << k << ") = " << tree.kth_ancestor(u, k) << '\n';
    cout << "Distance(" << u << ", " << v << ") = " << tree.distance(u, v) << '\n';

    return 0;
}
