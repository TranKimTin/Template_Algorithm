

// dijkstra
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

struct Edge
{
    int to;
    int weight;
};

struct Node
{
    int vertex;
    int distance;

    bool operator<(const Node &a) const
    {
        return distance > a.distance;
    }
};

void printPath(vector<int> &parent, int vertex)
{
    stack<int> path;
    int crawl = vertex;
    path.push(crawl);
    while (parent[crawl] != -1)
    {
        path.push(parent[crawl]);
        crawl = parent[crawl];
    }
    while (!path.empty())
    {
        cout << path.top() << " ";
        path.pop();
    }
    cout << endl;
}

void dijkstra(const vector<vector<Edge>> &graph, int src)
{
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    priority_queue<Node> pq;
    pq.push({src, 0});
    dist[src] = 0;

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;

        if (visited[u])
            continue;
        visited[u] = true;

        for (auto &edge : graph[u])
        {
            int v = edge.to;
            int weight = edge.weight;
            if (!visited[v] && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        cout << "Khoang cach tu dinh " << src << " den dinh " << i << " la: " << dist[i];
        cout << " va duong di la: ";
        printPath(parent, i);
    }
}

int main()
{
    int V = 5;

    // Danh sách kề
    vector<vector<Edge>> graph(V);

    // Thêm cạnh vào đồ thị
    graph[0].push_back({1, 10});
    graph[0].push_back({3, 5});
    graph[1].push_back({2, 1});
    graph[1].push_back({3, 2});
    graph[2].push_back({4, 4});
    graph[3].push_back({2, 9});
    graph[3].push_back({4, 2});
    graph[4].push_back({0, 7});
    graph[4].push_back({2, 6});

    dijkstra(graph, 0);

    return 0;
}