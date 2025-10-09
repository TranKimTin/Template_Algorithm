#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#define MAX 10005

using namespace std;

// node đếm từ 1->n
int n;
vector<int> a[MAX];  // Đồ thị G
vector<int> ra[MAX]; // Đồ thị đảo ngược G^T
bool visited[MAX];
stack<int> s;

// Hàm DFS Lần 1: Duyệt trên G và lưu thứ tự finish time
void dfs1(int u)
{
    visited[u] = true;
    for (int v : a[u])
    {
        if (!visited[v])
        {
            dfs1(v);
        }
    }
    // Sau khi thăm hết các nút kề (và các nút con), đẩy u vào stack
    s.push(u);
}

// Hàm DFS Lần 2: Duyệt trên G^T và tìm SCCs
void dfs2(int u, vector<int> &current_scc)
{
    visited[u] = true;
    current_scc.push_back(u);
    for (int v : ra[u])
    {
        if (!visited[v])
        {
            dfs2(v, current_scc);
        }
    }
}

// Hàm chính thực hiện thuật toán Kosaraju
vector<vector<int>> find_sccs_kosaraju()
{
    vector<vector<int>> sccs;

    // DFS Lần 1: Duyệt trên G để lấy thứ tự finish time
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            dfs1(i);
        }
    }

    // Chuẩn bị cho DFS Lần 2
    fill(visited, visited + n + 1, false);

    // DFS Lần 2: Duyệt trên G^T theo thứ tự finish time giảm dần
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

int main()
{
    // 5 đỉnh (1-based index)
    n = 5;
    // Các cạnh: 1->2, 2->3, 3->1, 3->4, 4->5
    vector<pair<int, int>> edges = {
        {1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}};

    for (const auto &edge : edges)
    {
        int u = edge.first;
        int v = edge.second;
        a[u].push_back(v);  // Cạnh u -> v trong G
        ra[v].push_back(u); // Cạnh v -> u trong G^T
    }

    vector<vector<int>> result_sccs = find_sccs_kosaraju();

    cout << "Cac thanh phan lien thong manh (SCCs) la:" << endl;
    for (const auto &scc : result_sccs)
    {
        cout << "{ ";
        for (int node : scc)
        {
            cout << node << " ";
        }
        cout << "}" << endl;
    }
    // Kết quả mong đợi: { 5 }, { 4 }, { 1 3 2 } (thứ tự có thể khác)
    // (Lưu ý: SCCs có thể được trả về theo thứ tự topo đảo ngược)

    return 0;
}
