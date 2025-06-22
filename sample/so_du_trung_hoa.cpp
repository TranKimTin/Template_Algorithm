#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

// Hàm tính nghịch đảo modulo bằng Extended Euclidean Algorithm
long long modInverse(long long a, long long m) {
    long long m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    return (x < 0) ? x + m0 : x;
}

// Hàm giải hệ phương trình đồng dư bằng CRT
long long chineseRemainder(vector<long long> a, vector<long long> m) {
    long long M = 1, result = 0;
    int n = a.size();
    
    // Tính tích tất cả các modulo
    for (int i = 0; i < n; i++) M *= m[i];

    for (int i = 0; i < n; i++) {
        long long Mi = M / m[i];                // Mi = M / m_i
        long long Mi_inv = modInverse(Mi, m[i]); // Tìm Mi^(-1) mod m_i
        result += a[i] * Mi * Mi_inv;
    }

    return result % M; // Nghiệm nhỏ nhất
}

int main() {
    //giải hệ phương trình
    // (x % mi) = ai
    vector<long long> a = {3, 4, 2}; // Các giá trị đồng dư
    vector<long long> m = {5, 7, 3}; // Các modulo

    long long x = chineseRemainder(a, m);
    cout << "Nghiệm dương nhỏ nhất x = " << x << endl;
    //các nghiệm tiếp theo: x + k*M (k có thể âm)
    return 0;
}
