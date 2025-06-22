//copy right @ https://www.facebook.com/photo?fbid=483145713912279&set=pcb.483147020578815
//problem: https://oj.tlualgosec.com/problem/sumprime
// Số nguyên tố là lớp số tự nhiên đặc biệt đã được con người nghiên cứu từ hơn 2500 năm qua. 
// Đây là tập hợp vô tận các số tự nhiên mà không có ước số nào khác ngoài 1 và chính nó.

// Tập số nguyên tố thường được ký hiệu là P = 2,3,5,7,9,11,...

// Nhiệm vụ của bạn là tính tổng các số nguyên tố không vượt quá N

// Input:
// Số nguyên dương N, giá trị không quá 1 tỉ.
// Output:
// Tổng các số nguyên tố không vượt quá  N

//sample test:
// 100 -> 1060
// 1000 -> 76127

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#define ll long long int
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

ll hash_f(ll x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}

struct chash {
	ll operator()(ll x) const { return hash_f(x); }
};

gp_hash_table<ll, ll, chash> s;

int main() {
	int n;
	scanf("%d", &n);
	int r = sqrt(n);

	vector<ll>v;
	int nv = r + n / r - 1;
	for (register int i = 1; i <= r; i++) v.push_back(n / i);
	for (register int i = r; i < nv; i++) v.push_back(v.back() - 1);

	for (auto i : v) s[i] = i * (i + 1) / 2 - 1;

	for (register int i = 2; i <= r; i++) {
		if (s[i] > s[i - 1]) {
		    int ii = i * i;
			for (auto j : v) {
				if (j < ii) break;
				s[j] -= (s[j / i] - s[i - 1]) * i;
			}
		}
	}
	printf("%lld", s[n]);
	return 0;
}
