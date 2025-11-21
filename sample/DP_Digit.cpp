// Có bao nhiêu số từ L đến R có <= 3 chữ số khác 0
// https://codeforces.com/problemset/problem/1036/C

#include <bits/stdc++.h>
#define ll long long
#define MAX 405
#define INF ((long long)(1e8))
using namespace std;
// #define int long long

vector<int> toVectorDigits(long long n)
{
    if (n == 0)
        return {0};

    vector<int> res;
    while (n > 0)
    {
        res.push_back(n % 10);
        n /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

ll dp[19][2][4];
ll f(vector<int> &v, int pos, int tight, int cnt)
{
    if (cnt > 3)
        return 0;
    if (pos == v.size())
    {
        return 1;
    }
    ll &result = dp[pos][tight][cnt];
    if (result == -1)
    {
        result = 0;
        int maxI = tight ? v[pos] : 9;
        for (int i = 0; i <= maxI; i++)
        {
            int newTight = tight && (i == maxI);
            int newCnt = (i == 0) ? cnt : cnt + 1;
            result += f(v, pos + 1, newTight, newCnt);
        }
    }
    return result;
}

void init()
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                dp[i][j][k] = -1;
            }
        }
    }
}

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        ll l, r;
        cin >> l >> r;
        auto R = toVectorDigits(r);
        auto L = toVectorDigits(l - 1);

        init();
        ll fr = f(R, 0, 1, 0);

        init();
        ll fl = f(L, 0, 1, 0);

        cout << fr - fl << "\n";
    }
    return 0;
}