// 核心在于：
// 可能有一些张数情况有重复计算，但是不会漏掉任何一种张数情况，也不会多算任何一种张数情况
// 因为是二进制分组，让原本0~cnt规模的枚举，变成了0~log(cnt)规模的枚举

// 二进制优化
// for (int k = 1; k <= cnt; k <<= 1)
// {
//     v[++m] = k * value;
//     w[m] = k * weight;
//     cnt -= k;
// }
// if (cnt > 0)
// {
//     v[++m] = cnt * value;
//     w[m] = cnt * weight;
// }

// 多重背包通过二进制分组转化成01背包(模版)
// 宝物筛选
// 一共有n种货物, 背包容量为t
// 每种货物的价值(v[i])、重量(w[i])、数量(c[i])都给出
// 请返回选择货物不超过背包容量的情况下，能得到的最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1776

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1001;
const int MAXW = 40001;

// 把每一种货物根据个数做二进制分组，去生成衍生商品
// 衍生出来的每一种商品，价值放入v、重量放入w
int v[MAXN];
int w[MAXN];
int dp[MAXW];

int n, t, m;

// 01背包的空间压缩代码(模版)
int compute()
{
    fill(dp, dp + t + 1, 0); // 初始化dp数组
    for (int i = 1; i <= m; i++)
    {
        for (int j = t; j >= w[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[t];
}

// 时间复杂度O(t * (log(第1种商品的个数) + log(第2种商品的个数) + ... + log(第n种商品的个数)))
// 对每一种商品的个数取log，所以时间复杂度虽然大于O(n * t)，但也不会大多少
// 多重背包最常用的方式
int main()
{
    while (cin >> n >> t)
    {
        m = 0;
        for (int i = 1, value, weight, cnt; i <= n; i++)
        {
            cin >> value >> weight >> cnt;
            // 整个文件最重要的逻辑 : 二进制分组
            // 一般都使用这种技巧，这段代码非常重要
            // 虽然时间复杂度不如单调队列优化的版本
            // 但是好写，而且即便是比赛，时间复杂度也达标
            // 二进制分组的时间复杂度为O(log cnt)
            for (int k = 1; k <= cnt; k <<= 1)
            {
                v[++m] = k * value;
                w[m] = k * weight;
                cnt -= k;
            }
            if (cnt > 0)
            {
                v[++m] = cnt * value;
                w[m] = cnt * weight;
            }
        }
        cout << compute() << endl;
    }
    return 0;
}