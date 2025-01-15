// 购买足量干草的最小花费
// 有n个提供干草的公司，每个公司都有两个信息
// cost[i]代表购买1次产品需要花的钱
// val[i]代表购买1次产品所获得的干草数量
// 每个公司的产品都可以购买任意次
// 你一定要至少购买h数量的干草，返回最少要花多少钱
// 测试链接 : https://www.luogu.com.cn/problem/P2918

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int MAXN = 101;
const int MAXM = 55001;

int val[MAXN];
int cost[MAXN];
int dp[MAXM];
int n, h, maxv, m;

// dp[i][j] : 1...i里挑公司，购买严格j磅干草，需要的最少花费
// 1) dp[i-1][j]
// 2) dp[i][j-val[i]] + cost[i]
// 两种可能性中选最小
// 但是关于j需要进行一定的扩充
// 保证一定有答案
// 一个公司 3 磅干草 1 元 我们至少要7磅
// 则dp[1][3] = 1 , dp[1][6] = 2 , dp[1][9] = 3
// 最优解是dp[1][9] = 3
int compute1()
{
    vector<vector<int>> dp(MAXN, vector<int>(MAXM, numeric_limits<int>::max()));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j - val[i] >= 0 && dp[i][j - val[i]] != numeric_limits<int>::max())
            {
                dp[i][j] = min(dp[i][j], dp[i][j - val[i]] + cost[i]);
            }
        }
    }
    // >= h
    // h h+1 h+2 ... m
    int ans = numeric_limits<int>::max();
    for (int j = h; j <= m; j++)
    {
        ans = min(ans, dp[n][j]);
    }
    return ans;
}

// 空间压缩
int compute2()
{
    fill(dp + 1, dp + m + 1, numeric_limits<int>::max());

    for (int i = 1; i <= n; i++)
    {
        for (int j = val[i]; j <= m; j++)
        {
            if (dp[j - val[i]] != numeric_limits<int>::max())
            {
                dp[j] = min(dp[j], dp[j - val[i]] + cost[i]);
            }
        }
    }

    int ans = numeric_limits<int>::max();
    for (int j = h; j <= m; j++)
    {
        ans = min(ans, dp[j]);
    }
    return ans;
}

int main()
{
    while (cin >> n >> h)
    {
        maxv = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> val[i] >> cost[i];
            maxv = max(maxv, val[i]);
        }
        // 最核心的一句
        // 包含重要分析
        m = h + maxv;
        cout << compute2() << "\n"; // 返回最少花费
    }

    return 0;
}