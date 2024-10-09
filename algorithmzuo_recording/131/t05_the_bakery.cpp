// 划分k段的最大得分
// 给定一个长度为n的数组，最多可以分成k段不重合的子数组
// 每个子数组获得的分值为内部不同数字的个数
// 返回能获得的最大分值
// 1 <= n <= 35000
// 1 <= k <= 50
// k <= n
// 1 <= arr[i] <= n
// 测试链接 : https://www.luogu.com.cn/problem/CF833B
// 测试链接 : https://codeforces.com/problemset/problem/833/B

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 35001;

int n, k;
int arr[MAXN];
int dp[MAXN];
int pre[MAXN];
int maxn[MAXN << 2];
int add[MAXN << 2];

void up(int i)
{
    maxn[i] = max(maxn[i << 1], maxn[i << 1 | 1]);
}

void down(int i)
{
    if (add[i] != 0)
    {
        // 懒惰标记
        maxn[i << 1] += add[i];
        maxn[i << 1 | 1] += add[i];
        add[i << 1] += add[i];
        add[i << 1 | 1] += add[i];
        add[i] = 0;
    }
}

void lazy(int i, int v)
{
    maxn[i] += v;
    add[i] += v;
}

void build(int l, int r, int i)
{
    if (l == r)
    {
        maxn[i] = dp[l];
    }
    else
    {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i] = 0;
}

void addfunc(int jobl, int jobr, int jobv, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        lazy(i, jobv);
    }
    else
    {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid)
        {
            addfunc(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid)
        {
            addfunc(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        return maxn[i];
    }
    down(i);
    int mid = (l + r) >> 1;
    int ans = INT_MIN;
    if (jobl <= mid)
    {
        ans = max(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid)
    {
        ans = max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

// 注意本题的线段树范围不是1~n，而是0~n
// 因为线段树需要维护0号~n号指标
int compute()
{
    fill(dp + 1, dp + n + 1, 0);
    for (int t = 1; t <= k; t++)
    {
        build(0, n, 1);
        fill(pre + 1, pre + n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            addfunc(pre[arr[i]], i - 1, 1, 0, n, 1);
            if (i >= t)
            {
                dp[i] = query(0, i - 1, 0, n, 1);
            }
            pre[arr[i]] = i;
        }
    }
    return dp[n];
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    cout << compute() << endl;
    return 0;
}
