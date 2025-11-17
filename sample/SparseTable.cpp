#include <bits/stdc++.h>
#define ll long long
#define MAX 10000

using namespace std;

class SparseTable
{
private:
    vector<vector<ll>> st_min;
    vector<vector<ll>> st_max;
    vector<int> log2s;
    int n;

public:
    // Constructor
    SparseTable(ll a[MAX], int N)
    {
        n = N;
        int max_log = log2(n) + 1;

        log2s.resize(n + 1);
        log2s[1] = 0;
        for (int i = 2; i <= n; ++i)
            log2s[i] = log2s[i / 2] + 1;

        st_min.assign(n, vector<ll>(max_log));
        st_max.assign(n, vector<ll>(max_log));

        // Base case: j = 0
        for (int i = 0; i < n; ++i)
        {
            st_min[i][0] = a[i];
            st_max[i][0] = a[i];
        }

        // DP fill
        for (int j = 1; (1 << j) <= n; ++j)
        {
            for (int i = 0; i + (1 << j) <= n; ++i)
            {
                st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
                st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Truy vấn min từ l đến r (0-based)
    ll query_min(int l, int r) const
    {
        int k = log2s[r - l + 1];
        return min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
    }

    // Truy vấn max từ l đến r (0-based)
    ll query_max(int l, int r) const
    {
        int k = log2s[r - l + 1];
        return max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
    }
};

int main()
{
    const int n = 6;
    ll a[n] = {3, 1, 4, 2, 1, 5};
    SparseTable st(a, n);

    cout << "Min [1..4]: " << st.query_min(1, 4) << "\n"; // 0.7
    cout << "Max [1..4]: " << st.query_max(1, 4) << "\n"; // 4.8

    return 0;
}