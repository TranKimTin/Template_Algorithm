#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int n, q;
int a[MAXN];
int block_size;

struct Query
{
    int l, r, id;
    bool operator<(const Query &other) const
    {
        int block_l = l / block_size;
        int block_r = other.l / block_size;
        if (block_l != block_r)
            return block_l < block_r;
        return (block_l & 1) ? (r > other.r) : (r < other.r); // tối ưu việc di chuyển con trỏ
    }
};

vector<Query> queries;
int answer[MAXN];       // lưu đáp án cho mỗi query
int freq[MAXN];         // tần suất của mỗi giá trị a[i]
int current_answer = 0; // số lượng phần tử khác nhau (ví dụ)

void add(int x)
{
    freq[x]++;
    if (freq[x] == 1)
        current_answer++;
}

void remove(int x)
{
    freq[x]--;
    if (freq[x] == 0)
        current_answer--;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    block_size = sqrt(n);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        queries.push_back({l, r, i});
    }

    sort(queries.begin(), queries.end());

    int l = 1, r = 0;
    //  int l = 0, r = -1; nếu đếm từ 0
    for (auto query : queries)
    {
        while (r < query.r)
            add(a[++r]);
        while (r > query.r)
            remove(a[r--]);
        while (l < query.l)
            remove(a[l++]);
        while (l > query.l)
            add(a[--l]);

        answer[query.id] = current_answer;
    }

    for (int i = 0; i < q; i++)
    {
        cout << answer[i] << '\n';
    }

    return 0;
}
