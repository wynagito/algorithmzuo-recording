// 最小移动总距离
// 所有工厂和机器人都分布在x轴上
// 给定长度为n的二维数组factory，factory[i][0]为i号工厂的位置，factory[i][1]为容量
// 给定长度为m的一维数组robot，robot[j]为第j个机器人的位置
// 每个工厂所在的位置都不同，每个机器人所在的位置都不同，机器人到工厂的距离为位置差的绝对值
// 所有机器人都是坏的，但是机器人可以去往任何工厂进行修理，但是不能超过某个工厂的容量
// 测试数据保证所有机器人都可以被维修，返回所有机器人移动的最小总距离
// 1 <= n、m <= 100
// -10^9 <= factory[i][0]、robot[j] <= +10^9
// 0 <= factory[i][1] <= m
// 测试链接 : https://leetcode.cn/problems/minimum-total-distance-traveled/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

class Solution
{
public:
    static const long long NA = LONG_MAX;
    static const int MAXN = 101;
    static const int MAXM = 101;

    int n, m;
    // 工厂下标从1开始，fac[i][0]表示位置，fac[i][1]表示容量
    int fac[MAXN][2];
    // 机器人下标从1开始，rob[i]表示位置
    int rob[MAXM];
    // dp[i][j]: 1...i工厂去修理1...j号机器人，最短总距离是多少
    long long dp[MAXN][MAXM];
    // 前缀和数组
    long long sum[MAXM];
    // 单调队列
    int queue[MAXM];
    int l, r;

    void build(const vector<vector<int>> &factory, const vector<int> &robot)
    {
        // 工厂和机器人都根据所在位置排序
        vector<vector<int>> sortedFactory = factory;
        sort(sortedFactory.begin(), sortedFactory.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[0] < b[0]; });

        vector<int> sortedRobot = robot;
        sort(sortedRobot.begin(), sortedRobot.end());

        n = sortedFactory.size();
        m = sortedRobot.size();

        // 让工厂和机器人的下标都从1开始
        for (int i = 1; i <= n; i++)
        {
            fac[i][0] = sortedFactory[i - 1][0];
            fac[i][1] = sortedFactory[i - 1][1];
        }
        for (int i = 1; i <= m; i++)
        {
            rob[i] = sortedRobot[i - 1];
        }

        // dp初始化
        for (int j = 1; j <= m; j++)
        {
            dp[0][j] = NA;
        }
    }

    // 最优解O(n * m)
    long long minimumTotalDistance(const vector<int> &robot, const vector<vector<int>> &factory)
    {
        build(factory, robot);

        for (int i = 1, cap; i <= n; i++)
        {
            // i号工厂的容量
            cap = fac[i][1];

            // sum[j]表示前j号机器人去往i号工厂的距离总和
            for (int j = 1; j <= m; j++)
            {
                sum[j] = sum[j - 1] + dist(i, j);
            }

            l = r = 0;
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (value(i, j) != NA)
                {
                    while (l < r && value(i, queue[r - 1]) >= value(i, j))
                    {
                        r--;
                    }
                    queue[r++] = j;
                }
                if (l < r && queue[l] == j - cap)
                {
                    l++;
                }
                if (l < r)
                {
                    dp[i][j] = min(dp[i][j], value(i, queue[l]) + sum[j]);
                }
            }
        }

        return dp[n][m];
    }

    // i号工厂和j号机器人的距离
    long long dist(int i, int j)
    {
        return abs(static_cast<long long>(fac[i][0]) - rob[j]);
    }

    // i号工厂从j号机器人开始负责的指标
    // 真的可行，返回指标的值
    // 如果不可行，返回NA
    long long value(int i, int j)
    {
        if (dp[i - 1][j - 1] == NA)
        {
            return NA;
        }
        return dp[i - 1][j - 1] - sum[j - 1];
    }
};
