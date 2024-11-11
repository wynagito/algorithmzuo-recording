// 牛群的才艺展示
// 一共有n只牛，每只牛有重量和才艺两个属性值
// 要求一定要选若干只牛，使得总重量不少于w，并且选出的牛，希望让
// 才艺的和 / 重量的和，这个比值尽量大
// 返回该比值 * 1000的整数结果，小数部分舍弃
// 1 <= n <= 250
// 1 <= w <= 1000
// 1 <= 牛的重量 <= 10^6
// 1 <= 牛的才艺 <= 10^3
// 测试链接 : https://www.luogu.com.cn/problem/P4377

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 251;
const int MAXW = 1001;

// 足够小代表无效解
const double NA = -1e9;

// 最小精度
const double sml = 1e-6;

// 重量
int weight[MAXN];

// 才艺
int talent[MAXN];

// (才艺 - x * 重量)的结余
double value[MAXN];

// dp[i][j] : 1...i号牛自由选择，重量必须是j的情况下，最大的结余和
// 特别的，dp[i][w]表示1...i号牛自由选择，重量必须是w、w+1...的所有情况中，最大的结余和
// 为了节省时间和空间选择这么定义，同时做空间压缩
double dp[MAXW];

int n, w;

bool check(double x)
{
    for (int i = 1; i <= n; i++)
    {
        value[i] = (double)talent[i] - x * weight[i];
    }
    dp[0] = 0;
    fill(dp + 1, dp + w + 1, NA);

    for (int i = 1; i <= n; i++)
    {
        for (int p = w; p >= 0; p--)
        {
            int j = p + weight[i];
            if (j >= w)
            {
                dp[w] = max(dp[w], dp[p] + value[i]);
            }
            else
            {
                dp[j] = max(dp[j], dp[p] + value[i]);
            }
        }
    }
    return dp[w] >= 0;
}

int main()
{
    cin >> n >> w;
    for (int i = 1; i <= n; i++)
    {
        cin >> weight[i] >> talent[i];
    }

    double l = 0, r = 0, x;
    for (int i = 1; i <= n; i++)
    {
        r += talent[i];
    }

    double ans = 0;

    while (l < r && r - l >= sml)
    {
        x = (l + r) / 2;
        if (check(x))
        {
            ans = x;
            l = x + sml;
        }
        else
        {
            r = x - sml;
        }
    }

    cout << static_cast<int>(ans * 1000) << endl;
    return 0;
}
