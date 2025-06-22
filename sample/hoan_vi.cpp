#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 3};

    // Sắp xếp ban đầu để đảm bảo bắt đầu từ hoán vị nhỏ nhất
    sort(a.begin(), a.end());

    do {
        for (int x : a)
            cout << x << " ";
        cout << "\n";
    } while (next_permutation(a.begin(), a.end()));

    return 0;
}
