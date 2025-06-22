#include <iostream>
#include <vector>
#include <numeric> // for std::gcd in C++17 and later
using namespace std;

// Hàm tính ƯCLN của hai số
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Hàm tính ƯCLN của một mảng
int gcdArray(const vector<int> &arr)
{
    int result = arr[0];
    for (size_t i = 1; i < arr.size(); ++i)
    {
        result = gcd(result, arr[i]);
        if (result == 1)
        {
            break; // Nếu ƯCLN là 1, dừng sớm
        }
    }
    return result;
}

// Hàm tính BCNN của hai số
int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

// Hàm tính BCNN của một mảng
int lcmArray(const vector<int> &arr)
{
    int result = arr[0];
    for (size_t i = 1; i < arr.size(); ++i)
    {
        result = lcm(result, arr[i]);
        if (result == 0)
        {
            break; // Nếu BCNN là 0, dừng sớm (trường hợp không hợp lệ)
        }
    }
    return result;
}

int main()
{
    // Ví dụ sử dụng
    vector<int> arr = {12, 18, 24};

    cout << "Ước chung lớn nhất của mảng: " << gcdArray(arr) << endl;
    cout << "Bội chung nhỏ nhất của mảng: " << lcmArray(arr) << endl;

    return 0;
}
