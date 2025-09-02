#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class SparseTable {
private:
    vector<vector<long long>> st_min;
    vector<vector<long long>> st_max;
    vector<int> log2s;
    int n;

public:
    // Constructor
    SparseTable(const vector<long long>& a) {
        n = a.size();
        int max_log = log2(n) + 1;

        log2s.resize(n + 1);
        log2s[1] = 0;
        for (int i = 2; i <= n; ++i)
            log2s[i] = log2s[i / 2] + 1;

        st_min.assign(n, vector<long long>(max_log));
        st_max.assign(n, vector<long long>(max_log));

        // Base case: j = 0
        for (int i = 0; i < n; ++i) {
            st_min[i][0] = a[i];
            st_max[i][0] = a[i];
        }

        // DP fill
        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
                st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Truy vấn min từ l đến r (0-based)
    long long query_min(int l, int r) const {
        int k = log2s[r - l + 1];
        return min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
    }

    // Truy vấn max từ l đến r (0-based)
    long long query_max(int l, int r) const {
        int k = log2s[r - l + 1];
        return max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
    }
};


int main() {
    vector<long long> a = {3.2, 1.5, 4.8, 2.9, 0.7, 5.1};
    SparseTable st(a);

    cout << "Min [1..4]: " << st.query_min(1, 4) << "\n"; // 0.7
    cout << "Max [1..4]: " << st.query_max(1, 4) << "\n"; // 4.8

    return 0;
}