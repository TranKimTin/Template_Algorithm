// problem: https://oj.tlualgosec.com/problem/tamgiac
// Cho số nguyên dương N
// Hãy đếm xem có bao nhiêu tam giác vuông có độ dài các cạnh nguyên và chu vi không vượt quá N

// Chú ý: Những tam giác mà thứ tự các cạnh chỉ là hoán vị của nhau thì được tính là một.
// Chẳng hạn như tam giác (3,4,5), tam giác (5,4,3), tam giác (4,5,3) đều tính là một tam giác.

// sample test:
// 12 -> 1
// 30 -> 3

// lý thuyết: https://cses.fi/book/book.pdf trang 216. Pythagorean triples

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long k;
    cin >> k;
    long long sum = 0;
    for (long long m = 2; m * m < k; m++)
    {
        for (long long n = 1 + m % 2; n < m; n += 2)
        {
            if (gcd(m, n) == 1)
            {
                long long a = m * m - n * n;
                long long b = 2 * m * n;
                long long c = m * m + n * n;
                sum += k / (a + b + c);
            }
        }
    }
    cout << sum;
}
