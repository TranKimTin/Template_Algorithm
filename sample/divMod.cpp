#include <iostream>
using namespace std;

using ll = long long;

// Tính a^b % mod
ll powmod(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// Tính nghịch đảo modular của b mod mod
ll mod_inverse(ll b, ll mod) {
    return powmod(b, mod - 2, mod); // Chỉ dùng được khi mod là số nguyên tố
}

int main() {
    // (a * b) % MOD = c
    // a = c/b % MOD = c* inv(b) % MOD
    // a % MOD = ?
    ll b = 2;
    ll MOD = 1e9 + 7;
    ll c = 14;

    ll inv_b = mod_inverse(b, MOD);
    ll a = (c * inv_b) % MOD;

    cout << "a % mod = " << a << endl;
    return 0;
}
