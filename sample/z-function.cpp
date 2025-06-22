#include <iostream>
#include <vector>
using namespace std;

// Hàm tính Z-function cho mảng số nguyên
vector<int> z_function(const vector<int> &a)
{
    int n = a.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;

    for (int i = 1; i < n; i++)
    {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);

        // Mở rộng đoạn trùng
        while (i + z[i] < n && a[z[i]] == a[i + z[i]])
            z[i]++;

        // Cập nhật [l, r] nếu mở rộng được xa hơn
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

int main()
{
    vector<int> a = {1, 2, 3, 1, 2, 3, 1};
    vector<int> z = z_function(a);

    cout << "Z-function: ";
    for (int i = 0; i < z.size(); i++)
    {
        cout << z[i] << " ";
    }
    cout << endl;

    return 0;
}
