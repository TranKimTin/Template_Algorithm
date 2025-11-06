#include <bits/stdc++.h>
using namespace std;

static uint64_t splitmix64(uint64_t x)
{
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}
static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();

struct pair_hash
{
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const
    {
        uint64_t h1 = splitmix64(hash<T1>()(p.first) + FIXED_RANDOM);
        uint64_t h2 = splitmix64(hash<T2>()(p.second) + FIXED_RANDOM);
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

struct tuple_hash
{
    template <typename... T>
    size_t operator()(const tuple<T...> &t) const
    {
        uint64_t h = 0;
        apply([&](auto const &...args)
              { ((h ^= splitmix64(hash<decay_t<decltype(args)>>()(args) + FIXED_RANDOM) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2)), ...); }, t);
        return h;
    }
};

int main()
{
    {
        unordered_map<pair<int, int>, int, pair_hash> mp;
        mp[{1, 2}] = 5;
        cout << mp[{1, 2}] << "\n";
    }
    {
        unordered_map<tuple<int, int, int>, string, tuple_hash> mp;
        mp[{1, 2, 3}] = "abc";
        cout << mp[{1, 2, 3}] << "\n";
    }
}
