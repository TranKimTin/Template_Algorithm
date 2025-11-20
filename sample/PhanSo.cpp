#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define MAX 1005
#define ll long long
#define MOD ((ll)(1e9 + 7))
#define INF ((ll)1e18)
#define int long long

// https://www.acmicpc.net/problem/30855
struct PhanSo
{
    ll tu;
    ll mau;

    void normalize()
    {
        if (mau < 0)
        {
            tu = -tu;
            mau = -mau;
        }
        ll g = std::gcd(tu, mau);
        if (g != 0)
        {
            tu /= g;
            mau /= g;
        }
    }

    void add(PhanSo &a)
    {
        tu = tu * a.mau + a.tu * mau;
        mau = mau * a.mau;
        normalize();
    }

    void sub(PhanSo &a)
    {
        tu = tu * a.mau - a.tu * mau;
        mau = mau * a.mau;
        normalize();
    }

    void mul(PhanSo &a)
    {
        tu = tu * a.tu;
        mau = mau * a.mau;
        normalize();
    }

    void div(PhanSo a)
    {
        swap(a.tu, a.mau);
        mul(a);
    }
};

int n;
vector<PhanSo> a;

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if (c == '(')
        {
            a.push_back({0, 0});
        }
        else if (c == ')')
        {
            int size = a.size();

            if (size < 4 || a[size - 1].tu == 0 || a[size - 2].tu == 0 || a[size - 3].tu == 0 || a[size - 4].tu != 0)
            {
                cout << -1 << "\n";
                return 0;
            }

            PhanSo C = a.back();
            a.pop_back();
            PhanSo B = a.back();
            a.pop_back();
            PhanSo A = a.back();
            a.pop_back();
            a.pop_back();

            B.div(C);
            A.add(B);

            a.push_back(A);
        }
        else
        {
            PhanSo x = {c - '0', 1};
            a.push_back(x);
        }
    }

    if (a.size() != 1 || a[0].tu == 0)
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << a[0].tu << " " << a[0].mau << "\n";
    }

    return 0;
}
