#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Số test kiểm tra
const int NTEST = 100;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

// Viết lại hàm random để sử dụng cho thuận tiện.
// Hàm random này sinh ngẫu nhiên số trong phạm vi long long
// Số sinh ra nằm trong [L;R].
ll Rand(ll L, ll R)
{
    assert(L <= R);
    return L + rd() % (R - L + 1);
}

// random mảng từ 1 đến n
vector<int> generateUniqueArray(int n)
{
    vector<int> a(n);
    iota(a.begin(), a.end(), 1); // a = [1, 2, ..., n]

    for (int i = n - 1; i > 0; --i)
    {
        int j = Rand(0, i); // chọn vị trí ngẫu nhiên trong [0, i]
        swap(a[i], a[j]);
    }

    return a;
}

// Sinh mảng n phần tử không trùng, mỗi phần tử ∈ [1, Max]
vector<ll> generateUniqueArray(int n, ll Max)
{
    assert(n <= Max);
    unordered_set<ll> s;
    while (s.size() < n)
    {
        ll val = Rand(1, Max);
        s.insert(val); // bỏ qua nếu đã tồn tại
    }
    return vector<ll>(s.begin(), s.end());
}

// Sinh n bộ (u, v, w) với u ≠ v, w ∈ [1, MaxW], và (u, v) không trùng nhau
vector<tuple<int, int, int>> generateUniqueTriples(int n, int MaxW)
{
    set<pair<int, int>> seen;
    vector<tuple<int, int, int>> res;

    while ((int)res.size() < n)
    {
        int u = Rand(1, n);
        int v = Rand(1, n);
        if (u == v)
            continue;
        if (seen.count({u, v}))
            continue;

        int w = Rand(1, MaxW);
        res.emplace_back(u, v, w);
        seen.insert({u, v});
    }

    return res;
}

// Sinh cây ngẫu nhiên với n đỉnh
vector<pair<int, int>> generateRandomTree(int n)
{
    vector<pair<int, int>> edges;

    // Với mỗi đỉnh từ 2 đến n, nối với 1 đỉnh trước đó bất kỳ
    for (int i = 2; i <= n; ++i)
    {
        int parent = Rand(1, i - 1);
        edges.emplace_back(parent, i);
    }

    // Xáo trộn các cạnh để không theo thứ tự
    shuffle(edges.begin(), edges.end(), rd);

    return edges;
}

// Sinh đồ thị vô hướng ngẫu nhiên với n đỉnh, m cạnh, trọng số ∈ [1, MaxW]
vector<tuple<int, int, int>> generateRandomGraph(int n, int m, int MaxW)
{
    assert(m <= 1LL * n * (n - 1) / 2); // giới hạn đồ thị vô hướng đơn

    set<pair<int, int>> edges;
    vector<tuple<int, int, int>> res;

    while ((int)res.size() < m)
    {
        int u = Rand(1, n);
        int v = Rand(1, n);
        if (u == v)
            continue;
        if (u > v)
            swap(u, v); // đảm bảo (u, v) và (v, u) là 1

        if (edges.count({u, v}))
            continue;

        int w = Rand(1, MaxW);
        res.emplace_back(u, v, w);
        edges.insert({u, v});
    }

    return res;
}

void generateTestCase()
{
    ofstream Cout("input.txt");

    int k = Rand(1, 100);
    int l = Rand(1, 1000);
    int r = Rand(l, l + 1000);

    Cout << k << " " << l << " " << r << "\n";

    Cout.close();
}

int main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        generateTestCase();

        system("test.exe > output.txt 2>&1");
        system("test_trau.exe > output_trau.txt 2>&1");
        
        if (system(("fc output.txt output_trau.txt")) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}