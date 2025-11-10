#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define MAX 100005
#define ll long long
#define MOD ((ll)(1e9 + 7))
#define INF ((ll)1e9)
// #define int long long

// tính giai thừa, số mũ, tổ hợp: http://collab.lge.com/main/pages/viewpage.action?pageId=1950193217

ll fact[MAX], inv[MAX];
// giai thua, 1 chia giai thua

ll pw(ll x, ll e) //(x^e) % MOD
{
    if (e == 0)
        return 1;
    if (e == 1)
        return x;
    ll y = pw(x, e / 2);
    y = (y * y) % MOD;
    if (e % 2 == 0)
        return y;
    return (y * x) % MOD;
}

void init()
{
    fact[0] = 1;
    for (int i = 1; i < MAX; i++)
    {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    // 1/k!
    inv[0] = 1;
    for (int i = 1; i < MAX; i++)
    {
        ll unit = pw(i, MOD - 2);
        inv[i] = inv[i - 1] * unit;
        inv[i] %= MOD;
    }
}

ll C(ll k, ll n) // to hop k cua n
{
    if (k > n)
        return 0;

    ll v1 = fact[n];
    ll v2 = inv[k];
    ll v3 = inv[n - k];
    return (((v1 * v2) % MOD) * v3) % MOD;
}

// (1/b)%MOD
ll get_inv(ll b)
{
    return pw(b, MOD - 2);
}

// to hop khi n lon, k nho
// ll C(ll k, ll n) // to hop k cua n
// {
//     if (k > n)
//         return 0;

//     // ll v1 = fact[n];
//     ll v2 = inv[k];
//     // ll v3 = inv[n - k];
//     ll v13 = 1;
//     for (int i = n - k + 1; i <= n; i++)
//     {
//         v13 *= i;
//         v13 %= MOD;
//     }

//     // return (((v1 * v2) % MOD) * v3) % MOD;
//     return (v13 * v2) % MOD;
// }

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    init();
    for (int i = 1; i <= 10; i++)
    {
        cout << i << "!= " << fact[i] << endl;
    }
    cout << endl;
    for (int i = 1; i < 10; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << i << "C" << j << "= " << C(j, i) << endl;
        }
        cout << endl;
    }
    return 0;
}
