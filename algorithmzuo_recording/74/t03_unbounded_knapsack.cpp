// 完全背包：与01背包的区别仅在于 每种商品可以选取无限次。时间复杂度O(物品数量 * 背包容量)

// 完全背包(模版)
// 给定一个正数t，表示背包的容量
// 有m种货物，每种货物可以选择任意个
// 每种货物都有体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1616

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXM = 10001;
const int MAXT = 10000001;

int cost[MAXM];
int val[MAXM];
long dp[MAXT];

int t, m;

// 严格位置依赖的动态规划
// 会空间不够，导致无法通过全部测试用例
long compute1()
{
    // dp[0][.....] = 0
    // dp[i][j] = max(dp[i-1][j], dp[i-1][j-cost[i]] + val[i] , ... , dp[i-1][j-cost[i]*k] + val[i] * k)
    // dp[i][j - cost[i]] = max(dp[i-1][j-cost[i]], dp[i-1][j-cost[i]*2] + val[i] , ... , dp[i-1][j-cost[i]*k] + val[i] * (k-1))
    vector<vector<long>> dp(m + 1, vector<long>(t + 1, 0));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j <= t; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j - cost[i] >= 0)
            {
                dp[i][j] = max(dp[i][j], dp[i][j - cost[i]] + val[i]);
            }
        }
    }
    return dp[m][t];
}

long compute2()
{
    fill(dp, dp + t + 1, 0); // 初始化 dp 数组为 0
    for (int i = 1; i <= m; i++)
    {
        // 反向遍历 dp 数组，防止覆盖问题
        for (int j = cost[i]; j <= t; j++)
        {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }
    return dp[t];
}

int main()
{
    while (cin >> t >> m)
    {
        // 读取每个物品的 cost 和 val
        for (int i = 1; i <= m; i++)
        {
            cin >> cost[i] >> val[i];
        }

        cout << compute2() << '\n'; // 输出结果
    }
    return 0;
}
