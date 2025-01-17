// 多重背包单调队列优化
// 宝物筛选
// 一共有n种货物, 背包容量为t
// 每种货物的价值(v[i])、重量(w[i])、数量(c[i])都给出
// 请返回选择货物不超过背包容量的情况下，能得到的最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1776

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

const int MAXN = 101;
const int MAXW = 40001;

int v[MAXN];
int w[MAXN];
int c[MAXN];
int dp[MAXW];
int queue[MAXW];
int l, r;
int n, t;

// 当前来到i号货物，需要j位置的指标，返回指标值
int value1(const std::vector<std::vector<int>> &dp, int i, int j)
{
    return dp[i - 1][j] - j / w[i] * v[i];
}

// 当前来到i号货物，需要j位置的指标，返回指标值
int value2(int i, int j)
{
    return dp[j] - j / w[i] * v[i];
}

// 严格位置依赖的动态规划 + 单调队列优化枚举
// dp[i][j] =  dp[i-1][j - k*w[i]] + k*v[i] = dp[i-1][j - k*w[i]] + (j - j + k*w[i]) / w[i] * v[i]
// dp[i][j] = max{dp[i-1][j - k*w[i]] - (j - k*w[i]) / w[i] * v[i]} + j / w[i] * v[i]
int compute1()
{
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(t + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        // 同余分组
        for (int mod = 0; mod <= std::min(t, w[i] - 1); mod++)
        {
            l = r = 0;
            for (int j = mod; j <= t; j += w[i])
            {
                while (l < r && value1(dp, i, queue[r - 1]) <= value1(dp, i, j))
                {
                    r--;
                }
                queue[r++] = j;
                if (queue[l] == j - w[i] * (c[i] + 1))
                {
                    l++;
                }
                dp[i][j] = value1(dp, i, queue[l]) + j / w[i] * v[i];
            }
        }
    }
    return dp[n][t];
}

// 空间压缩的动态规划 + 单调队列优化枚举
// 因为求dp[i][j]时需要上一行左侧的若干格子
// 所以做空间压缩时，每一行需要从右往左求
// 以此来保证左侧的格子还没有更新，还是"上一行"的状况
int compute2()
{
    std::fill(dp, dp + MAXW, 0);
    for (int i = 1; i <= n; i++)
    {
        for (int mod = 0; mod <= std::min(t, w[i] - 1); mod++)
        {
            l = r = 0;
            // 先把c[i]个的指标进入单调队列
            for (int j = t - mod, cnt = 1; j >= 0 && cnt <= c[i]; j -= w[i], cnt++)
            {
                while (l < r && value2(i, queue[r - 1]) <= value2(i, j))
                {
                    r--;
                }
                queue[r++] = j;
            }
            for (int j = t - mod, enter = j - w[i] * c[i]; j >= 0; j -= w[i], enter -= w[i])
            {
                // 窗口进入enter位置的指标
                if (enter >= 0)
                {
                    while (l < r && value2(i, queue[r - 1]) <= value2(i, enter))
                    {
                        r--;
                    }
                    queue[r++] = enter;
                }
                // 计算dp[i][j]
                dp[j] = value2(i, queue[l]) + j / w[i] * v[i];
                // 窗口弹出j位置的指标
                if (queue[l] == j)
                {
                    l++;
                }
            }
        }
    }
    return dp[t];
}

int main()
{
    while (std::scanf("%d%d", &n, &t) != EOF)
    {
        for (int i = 1; i <= n; i++)
        {
            std::scanf("%d%d%d", &v[i], &w[i], &c[i]);
        }
        std::printf("%d\n", compute2());
    }
    return 0;
}
