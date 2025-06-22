#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

// Template Radix Sort cho các kiểu unsigned
template <typename T>
void radixSortUnsigned(vector<T> &arr)
{
    static_assert(is_unsigned<T>::value, "radixSortUnsigned chỉ dùng cho kiểu unsigned");

    constexpr int BITS = 16;        // only change this line
    constexpr int BASE = 1 << BITS; // 256
    constexpr int MASK = BASE - 1;  // 0xFF
    constexpr int MAX_SHIFT = sizeof(T) * 8;

    int n = arr.size();
    vector<T> output(n);
    vector<int> count(BASE);

    // LSD Radix Sort
    for (int shift = 0; shift < MAX_SHIFT; shift += BITS)
    {
        fill(count.begin(), count.end(), 0);

        for (int i = 0; i < n; ++i)
            count[(arr[i] >> shift) & MASK]++;

        for (int i = 1; i < BASE; ++i)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; --i)
        {
            int byteVal = (arr[i] >> shift) & MASK;
            output[--count[byteVal]] = arr[i];
        }

        arr = output;
    }
}

int main()
{
    vector<unsigned int> v1 = {42, 0, 123456, 999, 1};
    vector<unsigned long long> v2 = {123456789ULL, 0ULL, 9999999999ULL};

    for (int i = 0; i < 10000000; i++)
    {
        v1.push_back(rand());
        v2.push_back((unsigned long long)rand() * (unsigned long long)rand());
    }

    auto t1 = clock();
    radixSortUnsigned(v1);
    auto t2 = clock();
    radixSortUnsigned(v2);
    auto t3 = clock();

    cout << t2 - t1 << " " << t3 - t2 << endl;

    // cout << "v1 da sort: ";
    // for (auto x : v1)
    //     cout << x << " ";
    // cout << endl;

    // cout << "v2 da sort: ";
    // for (auto x : v2)
    //     cout << x << " ";
    // cout << endl;

    return 0;
}
