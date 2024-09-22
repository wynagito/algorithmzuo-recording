// 向下收集获得最大能量
// 有一个n * m的区域，行和列的编号从1开始
// 每个能量点用(i, j, v)表示，i行j列上有价值为v的能量点
// 一共有k个能量点，并且所有能量点一定在不同的位置
// 一开始可以在第1行的任意位置，然后每一步必须向下移动
// 向下去往哪个格子是一个范围，如果当前在(i, j)位置
// 那么往下可以选择(i+1, j-t)...(i+1, j+t)其中的一个格子
// 到达最后一行时，收集过程停止，返回能收集到的最大能量价值
// 1 <= n、m、k、t <= 4000
// 1 <= v <= 100
// 测试链接 : https://www.luogu.com.cn/problem/P3800

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

const int MAXN = 4001;
const int MAXM = 4001;

int dp[MAXN][MAXM];
int qu[MAXM];
int l, r;
int n, m, k, t;

void add(int i, int j)
{
    if (j <= m)
    {
        while (l < r && dp[i][qu[r - 1]] <= dp[i][j])
        {
            r--;
        }
        qu[r++] = j;
    }
}

void overdue(int t)
{
    if (l < r && qu[l] == t)
    {
        l++;
    }
}

int compute()
{
    for (int i = 2; i <= n; i++)
    {
        l = r = 0;
        for (int j = 1; j <= t; j++)
        {
            add(i - 1, j);
        }
        for (int j = 1; j <= m; j++)
        {
            add(i - 1, j + t);
            overdue(j - t - 1);
            dp[i][j] += dp[i - 1][qu[l]];
        }
    }
    int ans = INT_MIN;
    for (int j = 1; j <= m; j++)
    {
        ans = max(ans, dp[n][j]);
    }
    return ans;
}

int main()
{
    cin >> n >> m >> k >> t;
    for (int i = 1, r, c, v; i <= k; i++)
    {
        cin >> r >> c >> v;
        dp[r][c] = v;
    }
    cout << compute() << endl;
    return 0;
}