// segment tree max, min, sum
#include <bits/stdc++.h>
#define ll long long int
#define MOD 10000007
using namespace std;
#define INF 99999999999999ll
// lazy segment tree
// đếm từ 0
struct Node
{
    ll sum;
    ll minVal;
    ll maxVal;

    Node()
    {
        sum = 0;
        minVal = INF;
        maxVal = -INF;
    }

    Node(ll val) : sum(val), minVal(val), maxVal(val) {}

    void merge(const Node &left, const Node &right)
    {
        sum = left.sum + right.sum;
        minVal = min(left.minVal, right.minVal);
        maxVal = max(left.maxVal, right.maxVal);
    }
};

class SegmentTree
{
    int n;
    vector<Node> tree;
    vector<ll> lazy_add, lazy_set;
    vector<bool> to_set;

public:
    SegmentTree(const vector<ll> &data)
    {
        n = data.size();
        tree.resize(4 * n);
        lazy_add.assign(4 * n, 0);
        lazy_set.assign(4 * n, 0);
        to_set.assign(4 * n, false);
        build(1, 0, n - 1, data);
    }

    void set_range(int L, int R, ll val)
    {
        update_set(1, 0, n - 1, L, R, val);
    }

    void add_range(int L, int R, ll val)
    {
        update_add(1, 0, n - 1, L, R, val);
    }

    Node query_range(int L, int R)
    {
        return query(1, 0, n - 1, L, R);
    }

private:
    void build(int id, int l, int r, const vector<ll> &data)
    {
        if (l == r)
        {
            tree[id] = Node(data[l]);
        }
        else
        {
            int mid = (l + r) / 2;
            build(id * 2, l, mid, data);
            build(id * 2 + 1, mid + 1, r, data);
            tree[id].merge(tree[id * 2], tree[id * 2 + 1]);
        }
    }

    void push(int id, int l, int r)
    {
        if (to_set[id])
        {
            ll val = lazy_set[id];
            tree[id] = Node(val * (r - l + 1));
            tree[id].minVal = val;
            tree[id].maxVal = val;

            if (l != r)
            {
                to_set[id * 2] = to_set[id * 2 + 1] = true;
                lazy_set[id * 2] = lazy_set[id * 2 + 1] = val;
                lazy_add[id * 2] = lazy_add[id * 2 + 1] = 0;
            }

            to_set[id] = false;
        }

        if (lazy_add[id] != 0)
        {
            ll val = lazy_add[id];
            tree[id].sum += val * (r - l + 1);
            tree[id].minVal += val;
            tree[id].maxVal += val;

            if (l != r)
            {
                lazy_add[id * 2] += val;
                lazy_add[id * 2 + 1] += val;
            }

            lazy_add[id] = 0;
        }
    }

    void update_set(int id, int l, int r, int L, int R, ll val)
    {
        push(id, l, r);
        if (r < L || l > R)
            return;
        if (L <= l && r <= R)
        {
            to_set[id] = true;
            lazy_set[id] = val;
            lazy_add[id] = 0;
            push(id, l, r);
            return;
        }

        int mid = (l + r) / 2;
        update_set(id * 2, l, mid, L, R, val);
        update_set(id * 2 + 1, mid + 1, r, L, R, val);
        tree[id].merge(tree[id * 2], tree[id * 2 + 1]);
    }

    void update_add(int id, int l, int r, int L, int R, ll val)
    {
        push(id, l, r);
        if (r < L || l > R)
            return;
        if (L <= l && r <= R)
        {
            lazy_add[id] += val;
            push(id, l, r);
            return;
        }

        int mid = (l + r) / 2;
        update_add(id * 2, l, mid, L, R, val);
        update_add(id * 2 + 1, mid + 1, r, L, R, val);
        tree[id].merge(tree[id * 2], tree[id * 2 + 1]);
    }

    Node query(int id, int l, int r, int L, int R)
    {
        push(id, l, r);
        if (r < L || l > R)
            return Node();
        if (L <= l && r <= R)
            return tree[id];

        int mid = (l + r) / 2;
        Node left = query(id * 2, l, mid, L, R);
        Node right = query(id * 2 + 1, mid + 1, r, L, R);
        
        Node result;
        result.merge(left, right);
        return result;
    }
};

int main()
{
    vector<ll> a = {1, 2, 3, 4, 5, 6};
    SegmentTree tree(a);

    cout << tree.query_range(1, 5).minVal;

    return 0;
}