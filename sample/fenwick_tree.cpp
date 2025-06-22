#include <bits/stdc++.h>
using namespace std;

// Fenwick Tree
// đếm từ 1
class FenwickTree
{
private:
    vector<int> tree;
    int n;

public:
    FenwickTree(int size)
    {
        n = size;
        tree.resize(n + 1, 0);
    }

    void update(int i, int delta)
    {
        while (i <= n)
        {
            tree[i] += delta;
            i += (i & -i);
        }
    }

    int query(int i)
    {
        int sum = 0;
        while (i > 0)
        {
            sum += tree[i];
            i -= (i & -i);
        }
        return sum;
    }

    int range_query(int i, int j)
    {
        return query(j) - query(i - 1);
    }
};

int main()
{
    vector<int> a = {1, 2, 3, 4, 5, 6};
    FenwickTree tree(6); // đếm từ 1
    for (int i = 0; i < a.size(); i++)
    {
        tree.update(i + 1, a[i]);
    }
    cout << "a";
    cout << tree.range_query(2, 6);

    return 0;
}