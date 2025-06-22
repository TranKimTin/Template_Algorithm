#include <bits/stdc++.h>
#define ull long long
#define mod 1000000007
#define minn LONG_MIN
#define maxx LONG_MAX
using namespace std;
 
ull v1, v2, c1, c2, n, x, res;
vector<ull> A;
vector<bool> visited;
// unordered_map<ull,vector<tuple<ull,ull>>> allmask;
vector<vector<tuple<ull,ull>>> allmask;
vector<vector<ull>> dp;
void init_allmask(){
    allmask = vector<vector<tuple<ull,ull>>>(101);
    for (auto it:A){
        if (!allmask[it].empty()) continue;
        ull b = 0;
        while (b*v2 <= it){
            if ((it-b*v2)%v1==0) allmask[it].push_back({(it-b*v2)/v1,b});
            b++;
        }
    }
    // for (auto it:allmask){
    //     cout << it.first << " -> ";
    //     for (auto [it0,it1]:it.second) cout << it0 << "_" << it1 << " ";
    //     cout << "\n";
    // }
}
 
bool dofor(ull here, ull soc1, ull soc2){
    if (soc1 > c1 || soc2 > c2){return false;}
    if (here == n){
        if (soc1 == c1 && soc2 == c2) return true;
        return false;
    }
    if (dp[here][soc2] != -1) return dp[here][soc2];
    dp[here][soc2] = 0;
    for (auto [v00,v11]:allmask[A[here]]){
        if (soc1+v00 > c1 || soc2+v11 > c2) continue;
        if (dofor(here+1,soc1+v00,soc2+v11)){
            dp[here][soc2] = 1;
            if (soc2+v11 > x && soc2 <= x) {
                visited[here] = true;
                break;
            }
        }
    }
    return dp[here][soc2];
}
 
void solve(){
    cin >> v1 >> c1 >> v2 >> c2 >> n >> x; 
    x--;
    res = 0;
    A = vector<ull>(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    visited = vector<bool>(n);
    init_allmask();
    dp = vector<vector<ull>>(n, vector<ull>(c2+1,-1));
    ull soc1 = 0, soc2 = 0, here = 0;
    for (auto [v00,v11]:allmask[A[0]]){
        if (soc1+v00 > c1 || soc2+v11 > c2) continue;
        if (dofor(here+1,soc1+v00,soc2+v11)){
            if (soc2+v11>x) visited[0] = true;
        }
    }
    for (auto it:visited) if (it) res++;
    if (res == 0) cout << "-1\n";
    else cout << res << "\n";
}
 
int main()
{
    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int tc; cin >> tc;
    while(tc--) solve();
    return 0;
}