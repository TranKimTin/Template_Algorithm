#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 10005
vector<int> a[MAX];
int visited[MAX];
bool round;
vector<int> ans;
void dfs(int x)
{
    if (visited[x] == 1)
    {
        round = true;
        return;
    }
    if (visited[x])
        return;
    visited[x] = 1;

    for (int i = 0; i < a[x].size(); i++)
    {
        dfs(a[x][i]);
    }
    ans.push_back(x);
    visited[x] = 2;
}
int main()
{
    for (int tc = 0; tc < 10; tc++)
    {
        string problemName = "topo sort";

        string fileIn = "./input/";
        fileIn += problemName + "_" + to_string(tc) + ".in";
        string fileOut = "./input/";
        fileOut += problemName + "_" + to_string(tc) + ".out";

        freopen(fileIn.c_str(), "r", stdin);
        freopen(fileOut.c_str(), "w", stdout);

        // write code here

        int n, m;
        cin >> n >> m;
        for (int i = 0; i < MAX; i++)
        {
            a[i].clear();
            visited[i] = 0;
        }
        round = false;
        ans.clear();
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
        }
        for (int i = 1; i <= n; i++)
        {
            sort(a[i].begin(), a[i].end(), [](int a, int b)
                 { return a > b; });
        }
        for (int i = n; i >= 1; i--)
        {
            if (!visited[i])
            {
                dfs(i);
            }
        }
        if (round)
            cout << "-1";
        else
        {
            for (int i = 0; i < n; i++)
            {
                cout << ans[n - i - 1] << " ";
            }
        }
    }

    return 0;
}