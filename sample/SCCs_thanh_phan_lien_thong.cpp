#include <bits/stdc++.h>
#define MAX 10005
using namespace std;

int n;
vector<int> a[MAX];  // Đồ thị G
vector<int> ra[MAX]; // Đồ thị đảo ngược G^T
bool visited[MAX];
stack<int> s;

void dfs1(int u)
{
    visited[u] = true;
    for (int v : a[u])
        if (!visited[v])
            dfs1(v);
    s.push(u);
}

void dfs2(int u, vector<int> &current_scc)
{
    visited[u] = true;
    current_scc.push_back(u);
    for (int v : ra[u])
        if (!visited[v])
            dfs2(v, current_scc);
}

vector<vector<int>> find_sccs_kosaraju()
{
    vector<vector<int>> sccs;

    for (int i = 1; i <= n; ++i)
        if (!visited[i])
            dfs1(i);

    fill(visited, visited + n + 1, false);

    while (!s.empty())
    {
        int u = s.top();
        s.pop();
        if (!visited[u])
        {
            vector<int> current_scc;
            dfs2(u, current_scc);
            sccs.push_back(current_scc);
        }
    }
    return sccs;
}

// Hàm gộp SCC thành đồ thị mới
vector<vector<int>> build_condensed_graph(
    const vector<vector<int>> &sccs,
    const vector<int> &node_to_scc)
{
    int scc_count = sccs.size();
    vector<set<int>> condensed_set(scc_count);
    vector<vector<int>> condensed_graph(scc_count);

    for (int u = 1; u <= n; ++u)
    {
        int su = node_to_scc[u];
        for (int v : a[u])
        {
            int sv = node_to_scc[v];
            if (su != sv)
                condensed_set[su].insert(sv);
        }
    }

    for (int i = 0; i < scc_count; ++i)
        condensed_graph[i].assign(condensed_set[i].begin(), condensed_set[i].end());

    return condensed_graph;
}

vector<int> topo;
vector<bool> visited_dfs;
void dfs_topo_condensed(int u, const vector<vector<int>> &g)
{
    visited_dfs[u] = true;

    for (int v : g[u])
        if (!visited_dfs[v])
            dfs_topo_condensed(v, g);

    topo.push_back(u); // đẩy vào khi kết thúc node
}

vector<int> topo_sort_condensed(const vector<vector<int>> &g)
{
    int m = g.size(); // số SCC
    visited_dfs.assign(m, false);
    topo.clear();

    for (int u = 0; u < m; ++u)
        if (!visited_dfs[u])
            dfs_topo_condensed(u, g);

    reverse(topo.begin(), topo.end());
    return topo;
}

int main()
{
    n = 8;
    vector<pair<int, int>> edges = {
        // SCC1
        {1, 2},
        {2, 3},
        {3, 1},

        // SCC2
        {4, 5},
        {5, 4},

        // SCC3
        {6, 7},
        {7, 6},

        // Liên kết giữa các SCC
        {3, 4}, // SCC1 → SCC2
        {5, 6}, // SCC2 → SCC3
        {7, 8}, // SCC3 → SCC4
        {2, 8}  // SCC1 → SCC4
    };

    for (const auto &edge : edges)
    {
        int u = edge.first, v = edge.second;
        a[u].push_back(v);
        ra[v].push_back(u);
    }

    vector<vector<int>> sccs = find_sccs_kosaraju();

    cout << "Cac thanh phan lien thong manh (SCCs):\n";
    for (int i = 0; i < (int)sccs.size(); ++i)
    {
        cout << "SCC " << i << ": { ";
        for (int node : sccs[i])
            cout << node << " ";
        cout << "}\n";
    }

    // Gán node -> scc_id
    vector<int> node_to_scc(n + 1);
    for (int i = 0; i < (int)sccs.size(); ++i)
        for (int node : sccs[i])
            node_to_scc[node] = i;

    // Xây đồ thị co
    vector<vector<int>> condensed = build_condensed_graph(sccs, node_to_scc);

    cout << "\nDo thi moi sau khi gop SCCs (condensed graph):\n";
    for (int i = 0; i < (int)condensed.size(); ++i)
    {
        cout << "SCC " << i << " -> ";
        for (int v : condensed[i])
            cout << "SCC" << v << " ";
        cout << "\n";
    }

    cout << "\nMoi nut thuoc condensed nao (node -> scc_id):\n";
    for (int u = 1; u <= n; ++u)
    {
        cout << "Node " << u << " thuoc SCC" << node_to_scc[u] << "\n";
    }

    vector<int> topo = topo_sort_condensed(condensed);

    cout << "\nThu tu topo cua do thi condensed:\n";
    for (int x : topo)
        cout << "SCC" << x << " ";
    cout << "\n";

    return 0;
}
