#include <bits/stdc++.h>
#define MAX 1000
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a = {6, 7, 7, 10, 8, 20};
    int n = a.size();

    vector<int> lis;          // chứa các giá trị nhỏ nhất kết thúc LIS độ dài k
    vector<int> pos(n);       // pos[i] = độ dài LIS khi thêm a[i]
    vector<int> trace(n, -1); // trace[i] = chỉ số phần tử trước đó trong LIS
    vector<int> lastIndex;    // lastIndex[k] = chỉ số phần tử cuối của LIS dài k+1

    for (int i = 0; i < n; i++)
    {
        auto it = upper_bound(lis.begin(), lis.end(), a[i]); // dãy không giảm
        // auto it = lower_bound(lis.begin(), lis.end(), a[i]); // dãy tăng
        int k = it - lis.begin();

        // cập nhật lis và vị trí cuối
        if (it == lis.end())
        {
            lis.push_back(a[i]);
            lastIndex.push_back(i);
        }
        else
        {
            *it = a[i];
            lastIndex[k] = i;
        }

        pos[i] = k;
        if (k > 0)
        {
            trace[i] = lastIndex[k - 1];
        }
    }

    // truy vết dãy LIS
    vector<int> seq;
    int idx = lastIndex.back();
    while (idx != -1)
    {
        seq.push_back(a[idx]);
        idx = trace[idx];
    }
    reverse(seq.begin(), seq.end());

    cout << seq.size() << "\n";
    for (int x : seq)
        cout << x << " ";

    return 0;
}