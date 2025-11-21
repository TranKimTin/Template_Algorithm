// https://codeforces.com/contest/2132/problem/D
// cho dãy 12345678910111213.... tính tổng các chữ số của n số đầu tiên

#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t;

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
ll cnt[20][2], sum[20][2];

ll f(vector<int> &v, int pos, int tight)
{
    if (pos == v.size())
        return 0;
    ll &res = sum[pos][tight];
    if (res != -1)
        return res;

    res = 0;
    ll &c = cnt[pos][tight];
    c = 0;

    int maxD = tight ? v[pos] : 9;
    for (int d = 0; d <= maxD; d++)
    {
        int nt = tight && (d == maxD);
        ll subSum = f(v, pos + 1, nt);
        ll subCnt = cnt[pos + 1][nt];

        if (pos == v.size() - 1)
        {
            subCnt = 1;
            subSum = 0;
        }

        res += d * subCnt + subSum;
        c += subCnt;
    }
    return res;
}

void init()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cnt[i][j] = sum[i][j] = -1;
        }
    }
}

ll sumLR(ll l, ll r)
{
    auto R = toVectorDigits(r);
    auto L = toVectorDigits(l - 1);

    init();
    ll fr = f(R, 0, 1);

    init();
    ll fl = f(L, 0, 1);

    return fr - fl;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    cin >> t;

    while (t--)
    {
        ll n;
        cin >> n;

        ll x = 9;
        ll num = 0;
        int length = 1;

        while (n > 0)
        {
            if (x * length <= n)
            {
                n -= x * length;
                x *= 10;
                num = num * 10 + 9;
                length++;
            }
            else
            {
                num += n / length;
                n %= length;
                break;
            }
        }

        ll ans = sumLR(1, num);
        while (n > 0)
        {
            // cout << n << endl;
            num++;
            auto L = toVectorDigits(num);
            for (int i = 0; i < L.size(); i++)
            {
                ans += L[i];
                n--;
                if (n == 0)
                    break;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
