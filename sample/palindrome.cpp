#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Hàm tiền xử lý: chèn ký tự '#' giữa các ký tự và ở đầu/cuối
string preprocess(const string &s)
{
    string t = "^";
    for (char c : s)
    {
        t.push_back('#');
        t.push_back(c);
    }
    t.push_back('#');
    t.push_back('$');
    return t;
}

// Thuật toán Manacher
string longestPalindrome(const string &s)
{
    string t = preprocess(s);
    int n = t.size();
    vector<int> p(n, 0); // p[i]: bán kính palindrome tại vị trí i
    int center = 0, right = 0;

    for (int i = 1; i < n - 1; ++i)
    {
        int mirror = 2 * center - i;

        if (i < right)
            p[i] = min(right - i, p[mirror]);

        // Mở rộng palindrome xung quanh i
        while (t[i + (1 + p[i])] == t[i - (1 + p[i])])
            ++p[i];

        // Cập nhật center và right nếu cần
        if (i + p[i] > right)
        {
            center = i;
            right = i + p[i];
        }
    }

    // Tìm vị trí có độ dài lớn nhất
    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 1; i < n - 1; ++i)
    {
        if (p[i] > maxLen)
        {
            maxLen = p[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLen) / 2; // chuyển lại vị trí trong chuỗi gốc
    return s.substr(start, maxLen);
}

// Ví dụ sử dụng
int main()
{
    string s = "cbb`";

    string res = longestPalindrome(s);
    cout << "Chuoi con doi xung dai nhat: " << res << '\n';

    return 0;
}