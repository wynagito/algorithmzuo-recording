// 多重背包：每一种物品给定数量的限制，进行可能性展开
//         多重背包的枚举优化：二进制分组优化（最常用）、单调队列优化（复杂度最好，理解稍难）

// 混合背包：多种背包模型的组合与转化

// 多重背包不进行枚举优化
// 宝物筛选
// 一共有n种货物, 背包容量为t
// 每种货物的价值(v[i])、重量(w[i])、数量(c[i])都给出
// 请返回选择货物不超过背包容量的情况下，能得到的最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1776

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 101;
const int MAXW = 40001;

int v[MAXN];
int w[MAXN];
int c[MAXN];
int dp[MAXW];

int n, t;

// 严格位置依赖的动态规划
// 时间复杂度O(n * t * 每种商品的平均个数)
int compute1()
{
    // dp[0][....] = 0，表示没有货物的情况下，背包容量不管是多少，最大价值都是0
    vector<vector<int>> dp(n + 1, vector<int>(t + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= t; j++)
        {
            dp[i][j] = dp[i - 1][j];
            for (int k = 1; k <= c[i] && w[i] * k <= j; k++)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - k * w[i]] + k * v[i]);
            }
        }
    }
    return dp[n][t];
}

// 空间压缩
// 部分测试用例超时
// 因为没有优化枚举
// 时间复杂度O(n * t * 每种商品的平均个数)
int compute2()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = t; j >= 0; j--)
        {
            for (int k = 1; k <= c[i] && w[i] * k <= j; k++)
            {
                dp[j] = max(dp[j], dp[j - k * w[i]] + k * v[i]);
            }
        }
    }
    return dp[t];
}

int main()
{
    while (cin >> n >> t)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> v[i] >> w[i] >> c[i];
        }
        cout << compute2() << endl;
    }
    return 0;
}
