// Từ L đến R có bao nhiêu số có tích các chữ số chia hết cho k
// L,R <= 1e20

#include <bits/stdc++.h>
#define ll long long
#define MAX 405
#define INF ((long long)(1e8))
#define MOD ((ll)1e9 + 7)
using namespace std;
#define int long long

int k;
string l, r;

vector<int> stringToVectorDigits(string s)
{
    vector<int> v;
    for (char c : s)
    {
        v.push_back(c - '0');
    }
    return v;
}

vector<int> minusOne(std::vector<int> digits)
{
    int i = digits.size() - 1;
    while (i >= 0)
    {
        if (digits[i] > 0)
        {
            digits[i] -= 1;
            break;
        }
        else
        {
            digits[i] = 9;
            --i;
        }
    }

    int firstNonZero = 0;
    while (firstNonZero < digits.size() && digits[firstNonZero] == 0)
    {
        firstNonZero++;
    }
    if (firstNonZero > 0)
    {
        digits.erase(digits.begin(), digits.begin() + firstNonZero);
    }

    return digits;
}

unordered_map<ll, ll> dp[21][2][2];
ll f(vector<int> &v, int pos, int tight, int zero, int x)
{
    if (pos == v.size())
    {
        return x == 0 || zero == 1;
    }
    if (dp[pos][tight][zero].count(x) == 0)
    {
        ll result = 0;
        int maxI = tight ? v[pos] : 9;
        for (int i = 0; i <= maxI; i++)
        {
            int newTight = tight && (i == maxI);
            int newZero = (zero == 0) ? 0 : (i == 0);
            int newX = newZero ? 1 : (x * i) % k;
            result += f(v, pos + 1, newTight, newZero, newX);
            result %= MOD;
        }
        return dp[pos][tight][zero][x] = result;
    }
    return dp[pos][tight][zero][x];
}

void init()
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                dp[i][j][k].clear();
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

    cin >> k >> l >> r;

    vector<int> L = stringToVectorDigits(l);
    vector<int> R = stringToVectorDigits(r);
    L = minusOne(L);

    init();
    ll fr = f(R, 0, 1, 1, 1);

    init();
    ll fl = f(L, 0, 1, 1, 1);

    cout << (fr - fl + MOD) % MOD << "\n";

    return 0;
}