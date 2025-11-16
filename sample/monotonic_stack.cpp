#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

#define MAX 1000

// Biến toàn cục – Trả về giá trị
int next_greater_right[MAX];
int next_smaller_right[MAX];
int next_greater_equal_right[MAX];
int next_smaller_equal_right[MAX];

int next_greater_left[MAX];
int next_smaller_left[MAX];
int next_greater_equal_left[MAX];
int next_smaller_equal_left[MAX];

void monotonic(int a[MAX], int n)
{
    fill(next_greater_right, next_greater_right + n, -1);
    fill(next_smaller_right, next_smaller_right + n, -1);
    fill(next_greater_equal_right, next_greater_equal_right + n, -1);
    fill(next_smaller_equal_right, next_smaller_equal_right + n, -1);

    fill(next_greater_left, next_greater_left + n, -1);
    fill(next_smaller_left, next_smaller_left + n, -1);
    fill(next_greater_equal_left, next_greater_equal_left + n, -1);
    fill(next_smaller_equal_left, next_smaller_equal_left + n, -1);

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
int n = 6;
int a[MAX] = {3, 7, 1, 7, 8, 4};
int main()
{
    monotonic(a, n);

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    auto print = [](const string &label, int v[MAX])
    {
        cout << label << ": ";
        for (int i = 0; i < n; i++)
            cout << v[i] << " ";
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
