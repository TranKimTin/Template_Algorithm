#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#define pii pair<int, int>
#define MAX_TC 10
#define MAX_N 100
#define MAX_M 300
using namespace std;
int main()
{
    // freopen("output.txt", "w", stdout);
    srand(time(0));

    for (int tc = 0; tc < 10; tc++)
    {

        string problemName = "topo sort";
        string filename = "./input/";
        filename += problemName + "_" + to_string(tc) + ".in";
        freopen(filename.c_str(), "w", stdout);

        // write code here
        int t = 1;
        // t = rand() % MAX_TC + 1;
        // cout << t << endl;
        while (t--)
        {
            set<pii> edges;
            int n = rand() % MAX_N + 1;
            int m = n == 1 ? 0 : rand() % (min(MAX_M, (n * (n - 1) / 2)));
            if (m < n / 2)
                m += n / 2;
            cout << n << " " << m << endl;

            // vector<int> v;
            // for (int i = 0; i < n; i++)
            //     v.push_back(i);

            // random_device rd; // Khởi tạo một thiết bị ngẫu nhiên
            // mt19937 g(rd());  // Sử dụng thuật toán Mersenne Twister
            // shuffle(v.begin(), v.end(), g);

            for (int i = 0; i < m; i++)
            {
                int u = rand() % n + 1;
                int v = rand() % n + 1;
                if (u == v || edges.find({u, v}) != edges.end())
                {
                    i--;
                }
                else
                {
                    cout << u << " " << v << endl;
                    edges.insert({u, v});
                    edges.insert({v, u});
                }
            }
        }
    }

    return 0;
}