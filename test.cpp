#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define MAX 200005

int n;
pii a[MAX];
int32_t main()
{
    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first >> a[i].second;
        if (a[i].first < a[i].second)
            swap(a[i].first, a[i].second);
    }
    sort(a, a + n, greater<pii>());
    vector<pii> ans;
    ans.push_back(a[0]);
    for (int i = 1; i < n; i++)
    {
        auto x = lower_bound(ans.begin(), ans.end(), a[i]);
        if (x == ans.end())
        {
            ans.push_back(a[i]);
        }
        else
            *x = a[i];
    }
    cout << ans.size() << "\n";
    return 0;
}