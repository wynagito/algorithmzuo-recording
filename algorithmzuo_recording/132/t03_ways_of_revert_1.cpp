// 还原数组的方法数
// 原本有一个长度为n的数组arr，下标从1开始，数组中都是<=200的正数
// 并且任意i位置的数字都满足 : arr[i] <= max(arr[i-1], arr[i+1])
// 特别的，arr[1] <= arr[2]，arr[n] <= arr[n-1]
// 但是输入的arr中有些数字丢失了，丢失的数字用0表示
// 返回还原成不违规的arr有多少种方法，答案很大需要对998244353取余
// 3 <= n <= 10^4
// 测试链接 : https://www.nowcoder.com/practice/49c5284278974cbda474ec13d8bd86a9

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 998244353;
const int MAXN = 10001;
int arr[MAXN];
int n;
int m = 200;
// 1...i范围上去决定数字，i+1位置的数字已经变成了v
// 如果s == 0, 表示i+1位置变成的数字v > i+2位置变成的数字
// 如果s == 1, 表示i+1位置变成的数字v <= i+2位置变成的数字
// 返回还原的方法数
int f1(int i, int v, int s, vector<vector<vector<int>>> &dp)
{
    if (i == 0)
    {
        return s;
    }
    if (dp[i][v][s] != -1)
    {
        return dp[i][v][s];
    }
    int ans = 0;
    if (arr[i] != 0)
    {
        if (arr[i] >= v || s == 1)
        {
            ans = f1(i - 1, arr[i], arr[i] > v ? 0 : 1, dp);
        }
    }
    else
    {
        for (int cur = v + 1; cur <= m; cur++)
        {
            ans = (ans + f1(i - 1, cur, 0, dp)) % MOD;
        }
        if (v != 0)
        {
            ans = (ans + f1(i - 1, v, 1, dp)) % MOD;
        }
        if (s == 1)
        {
            for (int cur = 1; cur < v; cur++)
            {
                ans = (ans + f1(i - 1, cur, 1, dp)) % MOD;
            }
        }
    }
    dp[i][v][s] = ans;
    return ans;
}
// 递归 + 记忆化搜索，不优化枚举
// 时间复杂度O(n * m平方)
int compute1()
{
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(2, -1)));
    return f1(n, 0, 1, dp);
}
// 严格位置依赖的动态规划，不优化枚举
// 时间复杂度O(n * m平方)
int compute2()
{
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(2, 0)));
    for (int v = 0; v <= m; v++)
    {
        dp[0][v][1] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int v = 0; v <= m; v++)
        {
            for (int s = 0; s <= 1; s++)
            {
                int ans = 0;
                if (arr[i] != 0)
                {
                    if (arr[i] >= v || s == 1)
                    {
                        ans = dp[i - 1][arr[i]][arr[i] > v ? 0 : 1];
                    }
                }
                else
                {
                    for (int cur = v + 1; cur <= m; cur++)
                    {
                        ans = (ans + dp[i - 1][cur][0]) % MOD;
                    }
                    if (v != 0)
                    {
                        ans = (ans + dp[i - 1][v][1]) % MOD;
                    }
                    if (s == 1)
                    {
                        for (int cur = 1; cur < v; cur++)
                        {
                            ans = (ans + dp[i - 1][cur][1]) % MOD;
                        }
                    }
                }
                dp[i][v][s] = ans;
            }
        }
    }
    return dp[n][0][1];
}
// 空间压缩版本，不优化枚举
// 时间复杂度O(n * m平方)
int compute3()
{
    vector<vector<int>> dp(m + 1, vector<int>(2, 0));
    vector<vector<int>> memo(m + 1, vector<int>(2, 0));
    for (int v = 0; v <= m; v++)
    {
        memo[v][1] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int v = 0; v <= m; v++)
        {
            for (int s = 0; s <= 1; s++)
            {
                int ans = 0;
                if (arr[i] != 0)
                {
                    if (arr[i] >= v || s == 1)
                    {
                        ans = memo[arr[i]][arr[i] > v ? 0 : 1];
                    }
                }
                else
                {
                    for (int cur = v + 1; cur <= m; cur++)
                    {
                        ans = (ans + memo[cur][0]) % MOD;
                    }
                    if (v != 0)
                    {
                        ans = (ans + memo[v][1]) % MOD;
                    }
                    if (s == 1)
                    {
                        for (int cur = 1; cur < v; cur++)
                        {
                            ans = (ans + memo[cur][1]) % MOD;
                        }
                    }
                }
                dp[v][s] = ans;
            }
        }
        for (int v = 0; v <= m; v++)
        {
            memo[v][0] = dp[v][0];
            memo[v][1] = dp[v][1];
        }
    }
    return memo[0][1];
}

vector<vector<int>> memo(m + 1, vector<int>(2));
vector<vector<int>> dp(m + 1, vector<int>(2));
vector<int> suf0(m + 1);
vector<int> pre1(m + 1);

// 预处理结构优化枚举
void prepare()
{
    suf0[m] = memo[m][0];
    for (int v = m - 1; v >= 0; v--)
    {
        suf0[v] = (suf0[v + 1] + memo[v][0]) % MOD;
    }
    pre1[1] = memo[1][1];
    for (int v = 2; v <= m; v++)
    {
        pre1[v] = (pre1[v - 1] + memo[v][1]) % MOD;
    }
}

// 正式方法
// 优化枚举 + 空间压缩
// 时间复杂度O(n * m)，可以通过所有测试用例
int compute4()
{
    for (int v = 0; v <= m; v++)
    {
        memo[v][0] = 0;
        memo[v][1] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        prepare();
        for (int v = 0; v <= m; v++)
        {
            for (int s = 0; s <= 1; s++)
            {
                int ans = 0;
                if (arr[i] != 0)
                {
                    if (arr[i] >= v || s == 1)
                    {
                        ans = memo[arr[i]][arr[i] > v ? 0 : 1];
                    }
                }
                else
                {
                    if (v + 1 <= m)
                    {
                        ans = (ans + suf0[v + 1]) % MOD;
                    }
                    if (v != 0)
                    {
                        ans = (ans + memo[v][1]) % MOD;
                    }
                    if (s == 1)
                    {
                        if (v - 1 >= 0)
                        {
                            ans = (ans + pre1[v - 1]) % MOD;
                        }
                    }
                }
                dp[v][s] = ans;
            }
        }
        swap(memo, dp);
    }
    return memo[0][1];
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    cout << compute4() << "\n"; // 或者调用 compute1() / compute2() / compute3() 根据需要
    return 0;
}
