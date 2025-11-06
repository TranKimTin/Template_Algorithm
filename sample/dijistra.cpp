

// dijkstra
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#define pii pair<int, int>
#define MAX 999
#define INF ((int)1e9)

using namespace std;
struct Node
{
    int u;
    int d;

    bool operator<(const Node &a) const
    {
        return d > a.d;
    }
};

void printPath(int parent[MAX], int u)
{
    stack<int> path;
    path.push(u);
    while (parent[u] != -1)
    {
        path.push(parent[u]);
        u = parent[u];
    }
    while (!path.empty())
    {
        cout << path.top() << " ";
        path.pop();
    }
    cout << endl;
}

int n;
vector<pii> a[MAX];
int d[MAX];
bool visited[MAX];
int parent[MAX];

void dijkstra(int src)
{
    fill(d, d + n, INF);
    fill(visited, visited + n, false);
    fill(parent, parent + n, -1);

    priority_queue<Node> pq;
    pq.push({src, 0});
    d[src] = 0;

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();
        int u = current.u;

        if (visited[u])
            continue;
        visited[u] = true;

        for (auto [v, w] : a[u])
        {
            if (!visited[v] && d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                parent[v] = u;
                pq.push({v, d[v]});
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        cout << "Khoang cach tu dinh " << src << " den dinh " << i << " la: " << d[i];
        cout << " va duong di la: ";
        printPath(parent, i);
    }
}

int main()
{

    n = 5;

    // Thêm cạnh vào đồ thị
    a[0].push_back({1, 10});
    a[0].push_back({3, 5});
    a[1].push_back({2, 1});
    a[1].push_back({3, 2});
    a[2].push_back({4, 4});
    a[3].push_back({2, 9});
    a[3].push_back({4, 2});
    a[4].push_back({0, 7});
    a[4].push_back({2, 6});

    dijkstra(0);

    return 0;
}