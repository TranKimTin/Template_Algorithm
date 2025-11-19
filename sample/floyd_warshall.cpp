#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Giá trị đại diện cho vô cực
const int MAXN = 5;  // Số đỉnh

int main()
{
    int n = MAXN;

    // Ma trận khoảng cách ban đầu
    int dist[MAXN][MAXN] = {
        {0, 3, INF, 7, INF},
        {8, 0, 2, INF, INF},
        {5, INF, 0, 1, INF},
        {2, INF, INF, 0, 1},
        {INF, INF, INF, INF, 0}};

    // Thuật toán Floyd-Warshall
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // In ma trận khoảng cách
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
