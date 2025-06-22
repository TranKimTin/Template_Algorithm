#include <bits/stdc++.h>
#define ll long long int
using namespace std;

#define INF 9999999
// segment tree max, min, sum
// đếm từ 0
struct Node
{
    int maxVal, minVal;
    ll sum;
};

class SegmentTree
{
private:
    vector<Node> tree;
    int n;

    void build(int id, int start, int end, const vector<ll> &arr)
    {
        if (start == end)
        {
            tree[id].maxVal = arr[start];
            tree[id].minVal = arr[start];
            tree[id].sum = arr[start];
        }
        else
        {
            int mid = (start + end) / 2;
            build(2 * id + 1, start, mid, arr);
            build(2 * id + 2, mid + 1, end, arr);
            tree[id].maxVal = max(tree[2 * id + 1].maxVal, tree[2 * id + 2].maxVal);
            tree[id].minVal = min(tree[2 * id + 1].minVal, tree[2 * id + 2].minVal);
            tree[id].sum = tree[2 * id + 1].sum + tree[2 * id + 2].sum;
        }
    }

    Node query(int id, int start, int end, int L, int R)
    {
        if (R < start || end < L)
        {
            return {-INF, INF, 0};
        }
        if (L <= start && end <= R)
        {
            return tree[id];
        }
        int mid = (start + end) / 2;
        Node leftChild = query(2 * id + 1, start, mid, L, R);
        Node rightChild = query(2 * id + 2, mid + 1, end, L, R);

        Node res;
        res.maxVal = max(leftChild.maxVal, rightChild.maxVal);
        res.minVal = min(leftChild.minVal, rightChild.minVal);
        res.sum = leftChild.sum + rightChild.sum;
        return res;
    }

    void update(int id, int start, int end, int idx, int value)
    {
        if (start == end)
        {
            tree[id].maxVal = value;
            tree[id].minVal = value;
            tree[id].sum = value;
        }
        else
        {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid)
            {
                update(2 * id + 1, start, mid, idx, value);
            }
            else
            {
                update(2 * id + 2, mid + 1, end, idx, value);
            }
            tree[id].maxVal = max(tree[2 * id + 1].maxVal, tree[2 * id + 2].maxVal);
            tree[id].minVal = min(tree[2 * id + 1].minVal, tree[2 * id + 2].minVal);
            tree[id].sum = tree[2 * id + 1].sum + tree[2 * id + 2].sum;
        }
    }

public:
    SegmentTree(const vector<ll> &data)
    {
        n = data.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, data);
    }

    Node query(int L, int R)
    {
        return query(0, 0, n - 1, L, R);
    }

    void update(int idx, int value)
    {
        update(0, 0, n - 1, idx, value);
    }
};

int main()
{
    vector<ll> a = {1, 2, 3, 4, 5, 6};
    SegmentTree tree(a);

    cout << tree.query(1, 5).sum;

    return 0;
}