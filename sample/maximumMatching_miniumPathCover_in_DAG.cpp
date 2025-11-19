#include <bits/stdc++.h>
using namespace std;

const int MAX = 1005;
int n = 5;          // số đỉnh ban đầu
vector<int> a[MAX]; // DAG
vector<int> L[MAX]; // đồ thị bipartite
int match[MAX * 2];
int used[MAX * 2];
int USED;

// DFS tìm augmenting path
bool bpm(int u)
{
    for (int v : L[u])
    {
        if (used[v] != USED)
        {
            used[v] = USED;
            if (match[v] == -1 || bpm(match[v]))
            {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

// tìm maximum matching
int maxMatching(int nLeft)
{
    // nLeft = số đỉnh bên trái
    fill(match, match + n * 2, -1);
    int res = 0;
    for (int u = 0; u < nLeft; u++)
    {
        USED++;
        if (bpm(u))
            res++;
    }
    return res;
}

int main()
{
    // DAG mẫu
    a[0] = {1, 2};
    a[1] = {3, 4};
    a[2] = {3};
    a[3] = {4};
    a[4] = {};

    // Tạo bipartite graph
    // Left = u_out = 0..n-1, Right = v_in = n..2n-1
    for (int u = 0; u < n; u++)
    {
        for (int v : a[u])
        {
            L[u].push_back(v + n);
        }
    }

    int res = maxMatching(n);
    cout << "Maximum matching trong DAG tong quat la: " << res << "\n";

    cout << "Cac cung trong matching:\n";
    for (int v = n; v < n * 2; v++)
    {
        if (match[v] != -1)
        {
            cout << match[v] << " -> " << (v - n) << "\n";
        }
    }

    cout << "Minimum path cover: " << n - res << endl;

    return 0;
}
