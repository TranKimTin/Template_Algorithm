#include <bits/stdc++.h>
using namespace std;

struct SegTree
{
    int n;
    int BITS;                // số bit tối đa (vd: 20 nếu a[i] <= 1e6, 60 nếu dùng long long)
    vector<vector<int>> cnt; // cnt[id][b] = số phần tử có bit b = 1 trong node id
    vector<long long> lazy;  // lazy[id] = xor pending

    SegTree(vector<int> &a, int maxBit = 20)
    {
        n = a.size();
        BITS = maxBit;
        cnt.assign(4 * n, vector<int>(BITS, 0));
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, a);
    }

    void build(int id, int l, int r, vector<int> &a)
    {
        if (l == r)
        {
            for (int b = 0; b < BITS; b++)
            {
                if (a[l] >> b & 1)
                    cnt[id][b] = 1;
            }
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid, a);
        build(id * 2 + 1, mid + 1, r, a);
        for (int b = 0; b < BITS; b++)
            cnt[id][b] = cnt[id * 2][b] + cnt[id * 2 + 1][b];
    }

    void applyXor(int id, int l, int r, long long x)
    {
        int len = r - l + 1;
        for (int b = 0; b < BITS; b++)
        {
            if (x >> b & 1)
            {
                cnt[id][b] = len - cnt[id][b]; // flip bit
            }
        }
        lazy[id] ^= x;
    }

    void pushDown(int id, int l, int r)
    {
        if (!lazy[id])
            return;
        int mid = (l + r) / 2;
        applyXor(id * 2, l, mid, lazy[id]);
        applyXor(id * 2 + 1, mid + 1, r, lazy[id]);
        lazy[id] = 0;
    }

    void update(int id, int l, int r, int ql, int qr, long long x)
    {
        if (qr < l || r < ql)
            return;
        if (ql <= l && r <= qr)
        {
            applyXor(id, l, r, x);
            return;
        }
        pushDown(id, l, r);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, ql, qr, x);
        update(id * 2 + 1, mid + 1, r, ql, qr, x);
        for (int b = 0; b < BITS; b++)
            cnt[id][b] = cnt[id * 2][b] + cnt[id * 2 + 1][b];
    }

    long long query(int id, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
        {
            long long res = 0;
            for (int b = 0; b < BITS; b++)
            {
                res += 1LL * cnt[id][b] * (1LL << b);
            }
            return res;
        }
        pushDown(id, l, r);
        int mid = (l + r) / 2;
        return query(id * 2, l, mid, ql, qr) +
               query(id * 2 + 1, mid + 1, r, ql, qr);
    }

    // wrapper
    void update(int l, int r, long long x)
    {
        update(1, 0, n - 1, l, r, x);
    }

    long long query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> a = {1, 2, 3, 4, 5};
    SegTree st(a, 4); // vì 5 < 2^4

    cout << "Initial sum [0,4]: " << st.query(0, 4) << "\n"; // 1+2+3+4+5 = 15

    st.update(1, 3, 2); // XOR [1..3] với 2
    cout << "After XOR [1,3] with 2, sum [0,4]: " << st.query(0, 4) << "\n";

    cout << "Sum [1,3]: " << st.query(1, 3) << "\n";

    st.update(0, 4, 1); // XOR toàn bộ [0..4] với 1
    cout << "After XOR [0,4] with 1, sum [0,4]: " << st.query(0, 4) << "\n";

    cout << "Sum [2,4]: " << st.query(2, 4) << "\n";

    return 0;
}
