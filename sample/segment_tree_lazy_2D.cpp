#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

struct Node
{
    long long sum = 0;
    long long mn = LLONG_MAX;
    long long mx = LLONG_MIN;
    long long add = 0;
    long long set = LLONG_MAX;
};

int n, m;
vector<vector<Node>> tree;

void apply(int x, int y, int h, int w, long long set_val, long long add_val)
{
    Node &node = tree[x][y];
    if (set_val != LLONG_MAX)
    {
        node.set = set_val;
        node.add = 0;
        node.sum = set_val * h * w;
        node.mn = node.mx = set_val;
    }
    if (add_val != 0)
    {
        if (node.set != LLONG_MAX)
            node.set += add_val;
        else
            node.add += add_val;
        node.sum += add_val * h * w;
        node.mn += add_val;
        node.mx += add_val;
    }
}

void push(int x, int y, int h, int w)
{
    if (h == 1 && w == 1)
        return;
    int hx = h / 2, wx = w / 2;
    for (int dx = 0; dx <= 1; ++dx)
        for (int dy = 0; dy <= 1; ++dy)
            apply(2 * x + dx, 2 * y + dy, (dx == 0 ? hx : h - hx), (dy == 0 ? wx : w - wx), tree[x][y].set, tree[x][y].add);
    tree[x][y].set = LLONG_MAX;
    tree[x][y].add = 0;
}

void merge(int x, int y)
{
    Node &node = tree[x][y];
    node.sum = 0;
    node.mn = LLONG_MAX;
    node.mx = LLONG_MIN;
    for (int dx = 0; dx <= 1; ++dx)
        for (int dy = 0; dy <= 1; ++dy)
        {
            Node &child = tree[2 * x + dx][2 * y + dy];
            node.sum += child.sum;
            node.mn = min(node.mn, child.mn);
            node.mx = max(node.mx, child.mx);
        }
}

void build(int x = 1, int y = 1, int h = n, int w = m)
{
    if (h == 1 && w == 1)
        return;
    int hx = h / 2, wx = w / 2;
    for (int dx = 0; dx <= 1; ++dx)
        for (int dy = 0; dy <= 1; ++dy)
            build(2 * x + dx, 2 * y + dy, (dx == 0 ? hx : h - hx), (dy == 0 ? wx : w - wx));
    merge(x, y);
}

void update(int x1, int y1, int x2, int y2, long long set_val, long long add_val,
            int x = 1, int y = 1, int r1 = 0, int c1 = 0, int r2 = n - 1, int c2 = m - 1)
{
    if (x2 < r1 || x1 > r2 || y2 < c1 || y1 > c2)
        return;
    if (x1 <= r1 && r2 <= x2 && y1 <= c1 && c2 <= y2)
    {
        apply(x, y, r2 - r1 + 1, c2 - c1 + 1, set_val, add_val);
        return;
    }
    push(x, y, r2 - r1 + 1, c2 - c1 + 1);
    int rm = (r1 + r2) / 2, cm = (c1 + c2) / 2;
    update(x1, y1, x2, y2, set_val, add_val, 2 * x, 2 * y, r1, c1, rm, cm);
    update(x1, y1, x2, y2, set_val, add_val, 2 * x, 2 * y + 1, r1, cm + 1, rm, c2);
    update(x1, y1, x2, y2, set_val, add_val, 2 * x + 1, 2 * y, rm + 1, c1, r2, cm);
    update(x1, y1, x2, y2, set_val, add_val, 2 * x + 1, 2 * y + 1, rm + 1, cm + 1, r2, c2);
    merge(x, y);
}

Node query(int x1, int y1, int x2, int y2,
           int x = 1, int y = 1, int r1 = 0, int c1 = 0, int r2 = n - 1, int c2 = m - 1)
{
    if (x2 < r1 || x1 > r2 || y2 < c1 || y1 > c2)
        return {0, LLONG_MAX, LLONG_MIN, 0, LLONG_MAX};
    if (x1 <= r1 && r2 <= x2 && y1 <= c1 && c2 <= y2)
        return tree[x][y];
    push(x, y, r2 - r1 + 1, c2 - c1 + 1);
    int rm = (r1 + r2) / 2, cm = (c1 + c2) / 2;
    vector<Node> res = {
        query(x1, y1, x2, y2, 2 * x, 2 * y, r1, c1, rm, cm),
        query(x1, y1, x2, y2, 2 * x, 2 * y + 1, r1, cm + 1, rm, c2),
        query(x1, y1, x2, y2, 2 * x + 1, 2 * y, rm + 1, c1, r2, cm),
        query(x1, y1, x2, y2, 2 * x + 1, 2 * y + 1, rm + 1, cm + 1, r2, c2)};
    Node ans;
    ans.sum = res[0].sum + res[1].sum + res[2].sum + res[3].sum;
    ans.mn = min({res[0].mn, res[1].mn, res[2].mn, res[3].mn});
    ans.mx = max({res[0].mx, res[1].mx, res[2].mx, res[3].mx});
    return ans;
}

int main()
{
    n = 4;
    m = 4;
    tree.assign(4 * MAXN, vector<Node>(4 * MAXN));
    build();

    // set tất cả = 2
    update(0, 0, 3, 3, 2, 0);

    // cộng thêm 3 vào góc trên trái 2x2
    update(0, 0, 1, 1, LLONG_MAX, 3);

    // truy vấn tổng/min/max trên toàn bảng
    Node result = query(0, 0, 3, 3);
    cout << "Sum: " << result.sum << "\n";
    cout << "Min: " << result.mn << "\n";
    cout << "Max: " << result.mx << "\n";
}
