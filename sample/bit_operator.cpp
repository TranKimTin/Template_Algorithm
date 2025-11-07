#include <bits/stdc++.h>
#define ll long long
using namespace std;

// 1. Kiểm tra bit thứ i có bật không
bool isBitSet(int n, int i)
{
    return (n >> i) & 1;
}

// bool isBitSet(ll n, int i) {
//     return (n >> i) & 1LL;
// }

// 2. Bật bit thứ i
int setBit(int n, int i)
{
    return n | (1 << i);
}

// ll setBit(ll n, int i) {
//     return n | (1LL << i);
// }

// 3. Tắt bit thứ i
int clearBit(int n, int i)
{
    return n & ~(1 << i);
}

// ll clearBit(ll n, int i) {
//     return n & ~(1LL << i);
// }

// 4. Đảo bit thứ i
int toggleBit(int n, int i)
{
    return n ^ (1 << i);
}

// ll toggleBit(ll n, int i) {
//     return n ^ (1LL << i);
// }

// 5. Đếm số bit 1
int countBits(int n)
{
    return __builtin_popcount(n);
}

// int countBits(ll n) {
//     return __builtin_popcountll(n);
// }

// 6. Lấy bit 1 thấp nhất
int lowestBit(int n)
{
    return n & -n;
}

// ll lowestBit(ll n) {
//     return n & -n;
// }

// 7. Kiểm tra là lũy thừa của 2
bool isPowerOfTwo(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

// bool isPowerOfTwo(ll n) {
//     return n > 0 && (n & (n - 1LL)) == 0;
// }

// 8. Đếm số bit 0 ở cuối
int countTrailingZeros(int n)
{
    return __builtin_ctz(n);
}

// int countTrailingZeros(ll n) {
//     return __builtin_ctzll(n);
// }

// 9. Tìm vị trí bit 1 cao nhất
int highestBitPosition(int n)
{
    return n == 0 ? -1 : 31 - __builtin_clz(n);
}

// ll highestBitPosition(ll n) {
//     return n == 0 ? -1 : 63 - __builtin_clzll(n);
// }

// 10. Duyệt tất cả subset của 1 bitmask
void iterateSubsets(int mask) {
    cout << "Các subset của bitmask " << bitset<4>(mask) << ":\n";
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        cout << bitset<4>(sub) << '\n';
    }
    cout << bitset<4>(0) << '\n'; // subset rỗng
}

// void iterateSubsets(ll mask)
// {
//     cout << "Các subset của bitmask " << bitset<4>(mask) << ":\n";
//     for (ll sub = mask; sub; sub = (sub - 1) & mask)
//     {
//         cout << bitset<4>(sub) << '\n';
//     }
//     cout << bitset<4>(0) << '\n'; // subset rỗng
// }

int main()
{
    system("chcp 65001");
    int n = 42; // 101010
    int i = 1;

    cout << "n = " << n << " (" << bitset<8>(n) << ")\n";
    cout << "Bit " << i << " is " << isBitSet(n, i) << '\n';

    cout << "Set bit " << i << ": " << bitset<8>(setBit(n, i)) << '\n';
    cout << "Clear bit " << i << ": " << bitset<8>(clearBit(n, i)) << '\n';
    cout << "Toggle bit " << i << ": " << bitset<8>(toggleBit(n, i)) << '\n';

    cout << "Số bit 1 trong n: " << countBits(n) << '\n';
    cout << "Bit 1 thấp nhất: " << bitset<8>(lowestBit(n)) << '\n';
    cout << "n có là lũy thừa của 2 không? " << (isPowerOfTwo(n) ? "Có" : "Không") << '\n';
    cout << "Số bit 0 ở cuối: " << countTrailingZeros(n) << '\n';
    cout << "Bit 1 cao nhất ở vị trí: " << highestBitPosition(n) << '\n';

    iterateSubsets(0b1011); // Ví dụ duyệt subset của bitmask 1011

    return 0;
}
