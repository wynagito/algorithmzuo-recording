// 混合背包 + 多重背包普通窗口优化
// 能成功找零的钱数种类
// 每一种货币都给定面值val[i]，和拥有的数量cnt[i]
// 想知道目前拥有的货币，在钱数为1、2、3...m时
// 能找零成功的钱数有多少
// 也就是说当钱数的范围是1~m
// 返回这个范围上有多少可以找零成功的钱数
// 比如只有3元的货币，数量是5张
// m = 10
// 那么在1~10范围上，只有钱数是3、6、9时，可以成功找零
// 所以返回3表示有3种钱数可以找零成功
// 测试链接 : http://poj.org/problem?id=1742

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 101;
const int MAXM = 100001;

int val[MAXN];
int cnt[MAXN];
bool dp[MAXM];
int n, m;

// 直接提供空间压缩版
int compute()
{
    fill(dp + 1, dp + m + 1, false);
    dp[0] = true;
    for (int i = 1; i <= n; i++)
    {
        if (cnt[i] == 1)
        {
            // 01背包的空间压缩实现是从右往左更新的
            for (int j = m; j >= val[i]; j--)
            {
                if (dp[j - val[i]])
                {
                    dp[j] = true;
                }
            }
        }
        else if (val[i] * cnt[i] > m)
        {
            // 完全背包的空间压缩实现是从左往右更新的
            for (int j = val[i]; j <= m; j++)
            {
                if (dp[j - val[i]])
                {
                    dp[j] = true;
                }
            }
        }
        else
        {
            // 多重背包的空间压缩实现
            // 每一组都是从右往左更新的
            // 同余分组
            for (int mod = 0; mod < val[i]; mod++)
            {
                int trueCnt = 0;
                for (int j = m - mod, size = 0; j >= 0 && size <= cnt[i]; j -= val[i], size++)
                {
                    trueCnt += dp[j] ? 1 : 0;
                }
                for (int j = m - mod, l = j - val[i] * (cnt[i] + 1); j >= 1; j -= val[i], l -= val[i])
                {
                    if (dp[j])
                    {
                        trueCnt--;
                    }
                    else
                    {
                        if (trueCnt != 0)
                        {
                            dp[j] = true;
                        }
                    }
                    if (l >= 0)
                    {
                        trueCnt += dp[l] ? 1 : 0;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        if (dp[i])
        {
            ans++;
        }
    }
    return ans;
}

int main()
{
    while (cin >> n >> m, n != 0 || m != 0)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> val[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> cnt[i];
        }
        cout << compute() << endl;
    }
    return 0;
}