//https://oj.vnoi.info/problem/segtree_itladder
// Cho một dãy số có N số, ban đầu tất cả bằng 0. Bạn cần xử lí 2 loại truy vấn:
// • Truy vấn loại 1 có dạng 1 L R A B, ta cộng thêm vào phần tử thứ i thêm (i − L)A + B đơn vị với
// mọi L ≤ i ≤ R
// • Truy vấn loại 2 có dạng 2 L R, ta cần in ra tổng của các phần tử trong khoảng [L..R], lấy dư cho
// 109 + 7

#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MOD = 1e9 + 7;
const ll INF = 1e18;

struct Node
{
    ll sum, minVal, maxVal;
    ll lazy_a = 0, lazy_b = 0;
};

class SegmentTree
{
private:
    vector<Node> tree;
    int size;

    void push(int node, int l, int r)
    {
        ll a = tree[node].lazy_a;
        ll b = tree[node].lazy_b;
        if (a == 0 && b == 0)
            return;

        int len = r - l + 1;
        ll first = (1LL * a * l + b) % MOD;
        ll last = (1LL * a * r + b) % MOD;
        ll total = ((first + last) % MOD * len % MOD * 500000004LL % MOD) % MOD; // /2 mod

        tree[node].sum = (tree[node].sum + total) % MOD;
        tree[node].minVal = (tree[node].minVal + min(first, last)) % MOD;
        tree[node].maxVal = (tree[node].maxVal + max(first, last)) % MOD;

        if (l != r)
        {
            tree[2 * node].lazy_a = (tree[2 * node].lazy_a + a) % MOD;
            tree[2 * node].lazy_b = (tree[2 * node].lazy_b + b) % MOD;
            tree[2 * node + 1].lazy_a = (tree[2 * node + 1].lazy_a + a) % MOD;
            tree[2 * node + 1].lazy_b = (tree[2 * node + 1].lazy_b + b) % MOD;
        }

        tree[node].lazy_a = 0;
        tree[node].lazy_b = 0;
    }

    void build(int node, int l, int r, const vector<ll> &a)
    {
        if (l == r)
        {
            tree[node].sum = a[l];
            tree[node].minVal = a[l];
            tree[node].maxVal = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, a);
        build(2 * node + 1, mid + 1, r, a);
        merge(node);
    }

    void merge(int node)
    {
        tree[node].sum = (tree[2 * node].sum + tree[2 * node + 1].sum) % MOD;
        tree[node].minVal = min(tree[2 * node].minVal, tree[2 * node + 1].minVal);
        tree[node].maxVal = max(tree[2 * node].maxVal, tree[2 * node + 1].maxVal);
    }

    void update(int node, int l, int r, int u, int v, ll A, ll B)
    {
        push(node, l, r);
        if (r < u || v < l)
            return;

        if (u <= l && r <= v)
        {
            ll adj_b = (B - 1LL * A * u % MOD + MOD) % MOD;
            tree[node].lazy_a = (tree[node].lazy_a + A) % MOD;
            tree[node].lazy_b = (tree[node].lazy_b + adj_b) % MOD;
            push(node, l, r);
            return;
        }

        int mid = (l + r) / 2;
        update(2 * node, l, mid, u, v, A, B);
        update(2 * node + 1, mid + 1, r, u, v, A, B);
        merge(node);
    }

    Node query(int node, int l, int r, int u, int v)
    {
        push(node, l, r);
        if (r < u || v < l)
            return {0, INF, -INF};
        if (u <= l && r <= v)
            return tree[node];

        int mid = (l + r) / 2;
        Node left = query(2 * node, l, mid, u, v);
        Node right = query(2 * node + 1, mid + 1, r, u, v);
        return {
            (left.sum + right.sum) % MOD,
            min(left.minVal, right.minVal),
            max(left.maxVal, right.maxVal)};
    }

public:
    SegmentTree(const vector<ll> &a)
    {
        int n = a.size();
        size = n;
        tree.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    void update(int l, int r, ll A, ll B)
    {
        update(1, 0, size - 1, l, r, A, B);
    }

    Node query(int l, int r)
    {
        return query(1, 0, size - 1, l, r);
    }
};

int n, q;
vector<ll> a;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("input.txt", "r", stdin);

    cin >> n >> q;
    a.resize(n + 1, 0);
    // for (int i = 1; i <= n; i++)
    //     cin >> a[i];

    SegmentTree tree(a);

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r, a, b;
            cin >> l >> r >> a >> b;
            tree.update(l, r, a, b);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << tree.query(l, r).sum << "\n";
        }
    }

    return 0;
}
