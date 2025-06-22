#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

// Biến toàn cục – Trả về giá trị
vector<int> next_greater_right, next_smaller_right;
vector<int> next_greater_equal_right, next_smaller_equal_right;

vector<int> next_greater_left, next_smaller_left;
vector<int> next_greater_equal_left, next_smaller_equal_left;

void monotonic(const vector<int> &a)
{
    int n = a.size();

    // Khởi tạo
    next_greater_right.assign(n, -1);
    next_smaller_right.assign(n, -1);
    next_greater_equal_right.assign(n, -1);
    next_smaller_equal_right.assign(n, -1);

    next_greater_left.assign(n, -1);
    next_smaller_left.assign(n, -1);
    next_greater_equal_left.assign(n, -1);
    next_smaller_equal_left.assign(n, -1);

    stack<int> st;

    // > bên phải
    while (!st.empty())
        st.pop();
    for (int i = n - 1; i >= 0; --i)
    {
        while (!st.empty() && a[st.top()] <= a[i])
            st.pop();
        if (!st.empty())
            next_greater_right[i] = st.top();
        st.push(i);
    }

    // >= bên phải
    while (!st.empty())
        st.pop();
    for (int i = n - 1; i >= 0; --i)
    {
        while (!st.empty() && a[st.top()] < a[i])
            st.pop();
        if (!st.empty())
            next_greater_equal_right[i] = st.top();
        st.push(i);
    }

    // < bên phải
    while (!st.empty())
        st.pop();
    for (int i = n - 1; i >= 0; --i)
    {
        while (!st.empty() && a[st.top()] >= a[i])
            st.pop();
        if (!st.empty())
            next_smaller_right[i] = st.top();
        st.push(i);
    }

    // <= bên phải
    while (!st.empty())
        st.pop();
    for (int i = n - 1; i >= 0; --i)
    {
        while (!st.empty() && a[st.top()] > a[i])
            st.pop();
        if (!st.empty())
            next_smaller_equal_right[i] = st.top();
        st.push(i);
    }

    // > bên trái
    while (!st.empty())
        st.pop();
    for (int i = 0; i < n; ++i)
    {
        while (!st.empty() && a[st.top()] <= a[i])
            st.pop();
        if (!st.empty())
            next_greater_left[i] = st.top();
        st.push(i);
    }

    // >= bên trái
    while (!st.empty())
        st.pop();
    for (int i = 0; i < n; ++i)
    {
        while (!st.empty() && a[st.top()] < a[i])
            st.pop();
        if (!st.empty())
            next_greater_equal_left[i] = st.top();
        st.push(i);
    }

    // < bên trái
    while (!st.empty())
        st.pop();
    for (int i = 0; i < n; ++i)
    {
        while (!st.empty() && a[st.top()] >= a[i])
            st.pop();
        if (!st.empty())
            next_smaller_left[i] = st.top();
        st.push(i);
    }

    // <= bên trái
    while (!st.empty())
        st.pop();
    for (int i = 0; i < n; ++i)
    {
        while (!st.empty() && a[st.top()] > a[i])
            st.pop();
        if (!st.empty())
            next_smaller_equal_left[i] = st.top();
        st.push(i);
    }
}

int main()
{
    vector<int> a = {3, 7, 1, 7, 8, 4};
    monotonic(a);

    auto print = [](const string &label, const vector<int> &v)
    {
        cout << label << ": ";
        for (int x : v)
            cout << x << " ";
        cout << "\n";
    };

    print("Next Greater Right (>)", next_greater_right);
    print("Next Smaller Right (<)", next_smaller_right);
    print("Next Greater Left (>)", next_greater_left);
    print("Next Smaller Left (<)", next_smaller_left);

    print("Next Greater= Right (>=)", next_greater_equal_right);
    print("Next Smaller= Right (<=)", next_smaller_equal_right);
    print("Next Greater= Left (>=)", next_greater_equal_left);
    print("Next Smaller= Left (<=)", next_smaller_equal_left);
}
