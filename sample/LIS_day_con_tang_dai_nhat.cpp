#include <bits/stdc++.h>
#define MAX 1000
using namespace std;

int n = 6;
int a[MAX] = {6, 7, 7, 10, 8, 20};

int pos[MAX];          // pos[i] = độ dài LIS khi thêm a[i]
int trace[MAX];        // trace[i] = chỉ số phần tử trước đó trong LIS
vector<int> lis;       // chứa các giá trị nhỏ nhất kết thúc LIS độ dài k
vector<int> lastIndex; // lastIndex[k] = chỉ số phần tử cuối của LIS dài k+1

// độ dài dãy con tăng dài nhất = lis.size()
// pos, trace, lastIndex để truy ngược dãy

// https://www.acmicpc.net/problem/23248
// định lý Dilworth cho poset 2D: số chuỗi tăng tối thiểu bằng độ dài dãy giảm dài nhất sau khi sắp xếp 1 chiều
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fill(trace, trace + n, -1);

    for (int i = 0; i < n; i++)
    {
        int x = a[i]; // dãy tăng
        // int x = -a[i]; // dãy giảm

        auto it = upper_bound(lis.begin(), lis.end(), x); // dãy không giảm
        // auto it = lower_bound(lis.begin(), lis.end(), x); // dãy tăng
        int k = it - lis.begin();

        // cập nhật lis và vị trí cuối
        if (it == lis.end())
        {
            lis.push_back(x);
            lastIndex.push_back(i);
        }
        else
        {
            *it = x;
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