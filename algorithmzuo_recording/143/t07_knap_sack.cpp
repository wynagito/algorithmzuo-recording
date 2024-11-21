// 背包(两次转圈法)
// 一共有n种物品，第i种物品的体积为v[i]，价值为c[i]，每种物品可以选择任意个，个数不能是负数
// 一共有m条查询，每次查询都会给定jobv，代表体积的要求
// 要求挑选物品的体积和一定要严格是jobv，返回能得到的最大价值和
// 如果没有方案能正好凑满jobv，返回-1
// 1 <= n <= 50
// 1 <= m <= 10^5
// 1 <= v[i] <= 10^5
// 1 <= c[i] <= 10^6
// 10^11 <= jobv <= 10^12
// 测试链接 : https://www.luogu.com.cn/problem/P9140

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int MAXN = 100001;
const long long inf = numeric_limits<long long>::min();
int v[MAXN];
int c[MAXN];
long long dp[MAXN];
int n, m, x, y;

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

void compute()
{
    fill(dp, dp + x, inf);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (v[i] != x)
        {
            for (int j = 0, d = gcd(v[i], x); j < d; j++)
            {
                for (int cur = j, circle = 0; circle < 2; circle += (cur == j ? 1 : 0))
                {
                    int next = (cur + v[i]) % x;
                    if (dp[cur] != inf)
                    {
                        dp[next] = max(dp[next], dp[cur] - (long long)((cur + v[i]) / x) * y + c[i]);
                    }
                    cur = next;
                }
            }
        }
    }
}

int main()
{

    cin >> n >> m;
    double best = 0, ratio;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i] >> c[i];
        ratio = static_cast<double>(c[i]) / v[i];
        if (ratio > best)
        {
            best = ratio;
            x = v[i];
            y = c[i];
        }
    }

    compute();

    for (int i = 1; i <= m; i++)
    {
        long long jobv;
        cin >> jobv;
        int v = static_cast<int>(jobv % x);
        if (dp[v] == inf)
        {
            cout << "-1\n";
        }
        else
        {
            cout << jobv / x * y + dp[v] << '\n';
        }
    }

    return 0;
}