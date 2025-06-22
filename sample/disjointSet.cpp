#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
private:
    vector<int> parent;
    vector<int> size;

public:
    DisjointSet(int n)
    {
        // ban đầu rỗng, không có tập nào
        parent.resize(n, -1);
        size.resize(n, 0);
    }

    // Khởi tạo tập riêng biệt chứa phần tử u
    void make_set(int u)
    {
        parent[u] = u;
        size[u] = 1;
    }

    // Tìm gốc của tập chứa u (với path compression)
    int find(int u)
    {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Hợp nhất 2 tập chứa u và v (theo size)
    void union_sets(int u, int v)
    {
        int pu = find(u);
        int pv = find(v);
        if (pu != pv)
        {
            // Gộp cây nhỏ vào cây lớn
            if (size[pu] < size[pv])
                swap(pu, pv);
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }

    // Trả về số phần tử trong tập chứa u
    int get_size(int u)
    {
        return size[find(u)];
    }

    // Kiểm tra u và v có cùng tập không
    bool same_set(int u, int v)
    {
        return find(u) == find(v);
    }
};

int main()
{
    int n = 10;
    DisjointSet dsu(n);
    for (int i = 0; i < n; ++i)
        dsu.make_set(i);

    dsu.union_sets(1, 2);
    dsu.union_sets(2, 3);
    dsu.union_sets(4, 5);

    cout << dsu.same_set(1, 3) << "\n"; // 1
    cout << dsu.same_set(1, 4) << "\n"; // 0
    cout << dsu.get_size(2) << "\n";    // 3
}
