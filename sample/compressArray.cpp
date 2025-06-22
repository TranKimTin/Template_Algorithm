#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = 1e6; // bạn chỉnh lại tùy kích thước mảng
int n;
int a[MAXN];

map<int, int> compressedMap;   // từ số ban đầu -> số nén
map<int, int> decompressedMap; // từ số nén -> số ban đầu

void compress()
{
    vector<int> b(a, a + n);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    compressedMap.clear();
    decompressedMap.clear();

    for (int i = 0; i < (int)b.size(); i++)
    {
        compressedMap[b[i]] = i + 1;   // nén từ 1
        decompressedMap[i + 1] = b[i]; // ngược lại
    }

    for (int i = 0; i < n; i++)
    {
        a[i] = compressedMap[a[i]];
    }
}

int main()
{
    // ví dụ:
    n = 5;
    a[0] = 100;
    a[1] = 200;
    a[2] = 100;
    a[3] = 300;
    a[4] = 200;

    compress();

    // In mảng đã nén
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << ' ';
    }
    cout << "\n";

    // In map từ số ban đầu -> số nén
    cout << "Map compressed:\n";
    for (auto &p : compressedMap)
    {
        cout << p.first << " -> " << p.second << '\n';
    }

    // In map ngược lại
    cout << "Map decompressed:\n";
    for (auto &p : decompressedMap)
    {
        cout << p.first << " -> " << p.second << '\n';
    }

    return 0;
}
