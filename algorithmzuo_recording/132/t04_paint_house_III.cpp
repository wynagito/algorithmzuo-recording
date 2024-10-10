// 粉刷房子III
// 房子有n个，从左到右排列，编号1..n，颜色有c种，编号1..c
// 给定数组house，house[i]表示房子的颜色，如果house[i]为0说明房子没有涂色
// 你必须给每个没有涂色的房子涂上颜色，如果有颜色的房子不能改变颜色
// 给定二维数组cost，cost[i][v]表示如果i号房涂成v号颜色，需要花费多少钱
// 相邻的、拥有同一种颜色的房子为1个街区
// 比如如果所有房子的颜色为: {1, 1, 2, 3, 2, 2}，那么一共4个街区
// 最终所有的房子涂完颜色，一定要形成t个街区，返回最少的花费
// 1 <= t <= n <= 100
// 1 <= c <= 20
// 0 <= house[i] <= c
// 1 <= cost[i][v] <= 10^4
// 测试链接 : https://leetcode.cn/problems/paint-house-iii/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    static const int NA = INT_MAX;
    static const int MAXN = 101;
    static const int MAXT = 101;
    static const int MAXC = 21;

    vector<int> house = vector<int>(MAXN);
    vector<vector<int>> cost = vector<vector<int>>(MAXN, vector<int>(MAXC));

    int n, t, c;
    // 原始测试页面的数据描述非常绕，一律转化成课上描述的形式
    // 房子编号从1开始，颜色编号从1开始，颜色0代表没有涂色
    // build方法就是转化逻辑
    void build(vector<int> &houses, vector<vector<int>> &costs, int hsize, int csize, int tsize)
    {
        n = hsize;
        t = tsize;
        c = csize;
        for (int i = 1; i <= n; i++)
        {
            house[i] = houses[i - 1];
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                cost[i][j] = costs[i - 1][j - 1];
            }
        }
    }
    // 1...i范围的房子去确定颜色，i+1号房子的颜色已经涂成了v
    // 1...i+1范围的房子必须凑齐j个街区，返回最少的花费
    // 如果做不到返回NA
    int f1(int i, int j, int v, vector<vector<vector<int>>> &dp)
    {
        if (j == 0)
            return NA;
        if (i == 0)
            return j == 1 ? 0 : NA;
        if (dp[i][j][v] != -1)
            return dp[i][j][v];

        int ans = NA;
        if (house[i] != 0)
        {
            if (house[i] == v)
            {
                ans = f1(i - 1, j, house[i], dp);
            }
            else
            {
                ans = f1(i - 1, j - 1, house[i], dp);
            }
        }
        else
        {
            for (int color = 1; color <= c; color++)
            {
                int next;
                if (color == v)
                {
                    next = f1(i - 1, j, color, dp);
                }
                else
                {
                    next = f1(i - 1, j - 1, color, dp);
                }
                if (next != NA)
                {
                    ans = min(ans, next + cost[i][color]);
                }
            }
        }
        dp[i][j][v] = ans;
        return ans;
    }

    // 递归 + 记忆化搜索
    int minCost1(vector<int> &houses, vector<vector<int>> &costs, int hsize, int csize, int tsize)
    {
        build(houses, costs, hsize, csize, tsize);
        t++;
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(t + 1, vector<int>(c + 1, -1)));
        int ans = f1(n, t, 0, dp);
        return ans == NA ? -1 : ans;
    }

    // 严格位置依赖的动态规划，不优化枚举
    // 时间复杂度O(n * t * c平方)
    int minCost2(vector<int> &houses, vector<vector<int>> &costs, int hsize, int csize, int tsize)
    {
        build(houses, costs, hsize, csize, tsize);
        t++;
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(t + 1, vector<int>(c + 1, NA)));
        for (int j = 1; j <= t; j++)
        {
            for (int v = 0; v <= c; v++)
            {
                dp[0][j][v] = (j == 1) ? 0 : NA;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= t; j++)
            {
                for (int v = 0; v <= c; v++)
                {
                    int ans = NA;
                    if (house[i] != 0)
                    {
                        if (house[i] == v)
                        {
                            ans = dp[i - 1][j][house[i]];
                        }
                        else
                        {
                            ans = dp[i - 1][j - 1][house[i]];
                        }
                    }
                    else
                    {
                        for (int color = 1; color <= c; color++)
                        {
                            int next;
                            if (color == v)
                            {
                                next = dp[i - 1][j][color];
                            }
                            else
                            {
                                next = dp[i - 1][j - 1][color];
                            }
                            if (next != NA)
                            {
                                ans = min(ans, next + cost[i][color]);
                            }
                        }
                    }
                    dp[i][j][v] = ans;
                }
            }
        }
        int ans = dp[n][t][0];
        return ans == NA ? -1 : ans;
    }

    // 空间压缩版本，不优化枚举
    // 时间复杂度O(n * t * c平方)
    int minCost3(vector<int> &houses, vector<vector<int>> &costs, int hsize, int csize, int tsize)
    {
        build(houses, costs, hsize, csize, tsize);
        t++;
        vector<vector<int>> memo(t + 1, vector<int>(c + 1, NA));
        vector<vector<int>> dp(t + 1, vector<int>(c + 1, NA));
        // 因为此时只有memo、dp两份空间
        // 所以让memo[0][v] = dp[0][v] = NA
        // 这样一来，在滚动更新时，不管i是多少，只要j==0，那么结果都是NA
        // i == 0时，结果填入memo表
        for (int j = 1; j <= t; j++)
        {
            for (int v = 0; v <= c; v++)
            {
                memo[j][v] = (j == 1) ? 0 : NA;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= t; j++)
            {
                for (int v = 0; v <= c; v++)
                {
                    int ans = NA;
                    if (house[i] != 0)
                    {
                        if (house[i] == v)
                        {
                            ans = memo[j][house[i]];
                        }
                        else
                        {
                            ans = memo[j - 1][house[i]];
                        }
                    }
                    else
                    {
                        for (int color = 1; color <= c; color++)
                        {
                            int next = (color == v) ? memo[j][color] : memo[j - 1][color];
                            if (next != NA)
                            {
                                ans = min(ans, next + cost[i][color]);
                            }
                        }
                    }
                    dp[j][v] = ans;
                }
            }
            swap(memo, dp);
        }
        int ans = memo[t][0];
        return ans == NA ? -1 : ans;
    }

    // 最优解
    // 优化枚举 + 空间压缩
    // 时间复杂度O(n * t * c)
    int minCost4(vector<int> &houses, vector<vector<int>> &costs, int hsize, int csize, int tsize)
    {
        build(houses, costs, hsize, csize, tsize);
        t++;
        vector<vector<int>> memo(t + 1, vector<int>(c + 1, NA));
        vector<vector<int>> dp(t + 1, vector<int>(c + 1, NA));
        // pre[s] : dp[i-1][j][1...s] + cost[i][1...s]中的最小值
        // suf[s] : dp[i-1][j][s...c] + cost[i][s...c]中的最小值
        for (int j = 1; j <= t; j++)
        {
            for (int v = 0; v <= c; v++)
            {
                memo[j][v] = j == 1 ? 0 : NA;
            }
        }
        vector<int> pre(c + 2), suf(c + 2);
        pre[0] = suf[c + 1] = NA;

        for (int j = 1; j <= t; j++)
        {
            memo[j][0] = (j == 1) ? 0 : NA;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= t; j++)
            {
                // 预处理结构优化前缀枚举
                for (int v = 1; v <= c; v++)
                {
                    pre[v] = pre[v - 1];
                    if (memo[j - 1][v] != NA)
                    {
                        pre[v] = min(pre[v], memo[j - 1][v] + cost[i][v]);
                    }
                }
                // 预处理结构优化后缀枚举
                for (int v = c; v >= 1; v--)
                {
                    suf[v] = suf[v + 1];
                    if (memo[j - 1][v] != NA)
                    {
                        suf[v] = min(suf[v], memo[j - 1][v] + cost[i][v]);
                    }
                }
                for (int v = 0; v <= c; v++)
                {
                    int ans = NA;
                    if (house[i] != 0)
                    {
                        ans = (house[i] == v) ? memo[j][house[i]] : memo[j - 1][house[i]];
                    }
                    else
                    {
                        if (v == 0)
                        {
                            ans = suf[1];
                        }
                        else
                        {
                            ans = min(pre[v - 1], suf[v + 1]);
                            if (memo[j][v] != NA)
                            {
                                ans = min(ans, memo[j][v] + cost[i][v]);
                            }
                        }
                    }
                    dp[j][v] = ans;
                }
            }
            swap(memo, dp);
        }
        int ans = memo[t][0];
        return ans == NA ? -1 : ans;
    }
};