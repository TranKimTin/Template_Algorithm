#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Tiền xử lý: chèn -1 giữa các số và đầu/cuối
vector<int> preprocess(const vector<int>& nums)
{
    vector<int> t;
    t.push_back(INT_MIN); // giống như '^'
    for (int x : nums)
    {
        t.push_back(-1);   // giống như '#'
        t.push_back(x);
    }
    t.push_back(-1);       // giống như '#' cuối
    t.push_back(INT_MAX);  // giống như '$'
    return t;
}

// Trả về vector<int> con đối xứng dài nhất
vector<int> longestPalindrome(const vector<int>& nums)
{
    vector<int> t = preprocess(nums);
    int n = t.size();
    vector<int> p(n, 0); // p[i]: bán kính palindrome tại i
    int center = 0, right = 0;

    for (int i = 1; i < n - 1; ++i)
    {
        int mirror = 2 * center - i;

        if (i < right)
            p[i] = min(right - i, p[mirror]);

        while (t[i + 1 + p[i]] == t[i - 1 - p[i]])
            ++p[i];

        if (i + p[i] > right)
        {
            center = i;
            right = i + p[i];
        }
    }

    // Tìm chỉ số có palindrome dài nhất
    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; ++i)
    {
        if (p[i] > maxLen)
        {
            maxLen = p[i];
            centerIndex = i;
        }
    }

    // Tính vị trí bắt đầu trong mảng gốc
    int start = (centerIndex - maxLen) / 2;

    return vector<int>(nums.begin() + start, nums.begin() + start + maxLen);
}

// Demo
int main()
{
    vector<int> nums = {1, 2, 3, 2, 1, 4, 5};

    vector<int> res = longestPalindrome(nums);

    cout << "Mang con doi xung dai nhat: ";
    for (int x : res)
        cout << x << ' ';
    cout << '\n';

    return 0;
}
