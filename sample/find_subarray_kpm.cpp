#include <iostream>
#include <vector>
using namespace std;

// Tính mảng LPS (Longest Prefix Suffix) cho pattern
// pi[i] định nghĩa: độ dài tiền tố dài nhất = hậu tố của s[0..i].
// tính cả overlap
// pi[i] = độ dài đoạn prefix dài nhất = suffix kết thúc tại i.
vector<int> computeLPS(const vector<int> &pattern)
{
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1]; // quay lại prefix trước đó
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

// KMP để tìm tất cả vị trí xuất hiện của pattern trong arr
vector<int> kmpSearch(const vector<int> &arr, const vector<int> &pattern)
{
    int n = arr.size();
    int m = pattern.size();
    vector<int> lps = computeLPS(pattern);
    vector<int> result;

    int i = 0; // chỉ số arr
    int j = 0; // chỉ số pattern

    while (i < n)
    {
        if (arr[i] == pattern[j])
        {
            i++;
            j++;
            if (j == m)
            {
                result.push_back(i - j); // tìm thấy pattern tại i - j
                j = lps[j - 1];          // tiếp tục tìm pattern tiếp theo
            }
        }
        else
        {
            if (j != 0)
            {
                j = lps[j - 1]; // quay lại vị trí lặp hợp lý
            }
            else
            {
                i++;
            }
        }
    }

    return result;
}

int main()
{
    vector<int> arr = {1, 2, 3, 44, 2, 3, 44, 5};
    vector<int> pattern = {2, 3, 44};

    vector<int> positions = kmpSearch(arr, pattern);

    for (int pos : positions)
    {
        cout << "Pattern found at index: " << pos << endl;
    }

    return 0;
}
