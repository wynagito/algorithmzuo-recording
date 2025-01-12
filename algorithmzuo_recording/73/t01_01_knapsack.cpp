// 01背包：每个物品 要和不要 两种可能性展开
// 有依赖的背包：多个物品变成一个复合物品（互斥），每件复合物品 不要和怎么要 多种可能性展开
// 时间复杂度O(物品个数 * 背包容量)，额外空间复杂度O(背包容量)
// 不能用01背包来解，但是非常重要的问题：非负数组前k个最小的子序列和问题

// 01背包(模版)
// 给定一个正数t，表示背包的容量
// 有m个货物，每个货物可以选择一次
// 每个货物有自己的体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1048

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXT = 1001, MAXM = 101;

int cost[MAXM], val[MAXM], dp[MAXT];

int t, n;

// 严格位置依赖的动态规划
// n个物品编号1~n，第i号物品的花费cost[i]、价值val[i]
// cost、val数组是全局变量，已经把数据读入了
int compute1()
{
    // dp[i][j]表示前i个物品恰好装入容量为j的背包可以获得的最大价值
    vector<vector<int>> dp(n + 1, vector<int>(t + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= t; j++)
        {
            // 不要i号物品
            dp[i][j] = dp[i - 1][j];
            if (j - cost[i] >= 0)
            {
                // 要i号物品
                dp[i][j] = max(dp[i][j], dp[i - 1][j - cost[i]] + val[i]);
            }
        }
    }
    return dp[n][t];
}

// 空间压缩
int compute2()
{
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++)
    {
        for (int j = t; j >= cost[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }
    return dp[t];
}

int main()
{
    cin >> t >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> cost[i] >> val[i];
    }
    cout << compute1() << endl;
    return 0;
}