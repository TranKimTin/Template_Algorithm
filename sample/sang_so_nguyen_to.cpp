#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

const int MAX = 1e7 + 1; // Giới hạn tối đa cho n (10^7)
bitset<MAX> isPrime;

void sangNguyenTo(int n)
{
    isPrime.set(); // Khởi tạo tất cả bit = true
    isPrime[0] = isPrime[1] = false;

    int sqrtN = sqrt(n);
    for (int i = 2; i <= sqrtN; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    cout << "Cac so nguyen to tu 1 den " << n << " la:\n";
    for (int i = 2; i <= n; ++i)
    {
        if (isPrime[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Nhap n (toi da " << MAX - 1 << "): ";
    cin >> n;

    if (n >= MAX)
    {
        cout << "Vuot qua gioi han, giam n xuong < " << MAX << endl;
        return 1;
    }

    sangNguyenTo(n);
    return 0;
}
