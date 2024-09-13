// 摆盘子的方法
// 一共有n个盘子k种菜，所有盘子排成一排，每个盘子只能放一种菜
// 要求最多连续两个盘子菜品一样，更长的重复出现是不允许的
// 返回摆盘的方法数，答案可能很大，对1000000007取余
// 1 <= n <= 1000
// 1 <= k <= 1000
// 来自真实大厂笔试，对数器验证

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

const int MOD = 1000000007;

int f1(int i, int k)
{
    if (i == 0)
    {
        return 1;
    }
    if (i == 1)
    {
        return k - 1;
    }
    long long p1 = f1(i - 1, k);
    long long p2 = f1(i - 2, k);
    return (int)(((p1 + p2) * (k - 1)) % MOD);
}

// 正式方法的尝试思路
int dp1(int n, int k)
{
    if (n == 1)
    {
        return k;
    }
    return (int)((((long long)f1(n - 1, k) + f1(n - 2, k)) * k) % MOD);
}

// 正式方法的普通动态规划版本
// 时间复杂度O(n)
int dp2(int n, int k)
{
    if (n == 1)
    {
        return k;
    }
    vector<int> dp(n);
    dp[0] = 1;
    dp[1] = k - 1;
    for (int i = 2; i < n; i++)
    {
        long long p1 = dp[i - 1];
        long long p2 = dp[i - 2];
        dp[i] = (int)(((p1 + p2) * (k - 1)) % MOD);
    }
    return (int)((((long long)dp[n - 1] + dp[n - 2]) * k) % MOD);
}

// 最优解的版本，动态规划 + 矩阵快速幂优化
// 时间复杂度O(log n)
vector<vector<int>> multiply(const vector<vector<int>> &a, const vector<vector<int>> &b)
{
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int c = 0; c < k; c++)
            {
                ans[i][j] = (int)(((long long)ans[i][j] + (long long)a[i][c] * b[c][j]) % MOD);
            }
        }
    }
    return ans;
}

vector<vector<int>> power(const vector<vector<int>> &m, int p)
{
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        ans[i][i] = 1;
    }
    vector<vector<int>> base = m;
    for (; p != 0; p >>= 1)
    {
        if ((p & 1) != 0)
        {
            ans = multiply(ans, base);
        }
        base = multiply(base, base);
    }
    return ans;
}

int dp3(int n, int k)
{
    if (n == 1)
    {
        return k;
    }
    int s = k - 1;
    vector<vector<int>> start = {{1, s}};
    vector<vector<int>> base = {{0, s}, {1, s}};
    vector<vector<int>> ans = multiply(start, power(base, n - 2));
    return (int)((((long long)ans[0][0] + ans[0][1]) * k) % MOD);
}

// 暴力方法
// 为了验证
int dfs(vector<int> &path, int i, int k)
{
    if (i == path.size())
    {
        int len = 1;
        for (int j = 1; j < path.size(); j++)
        {
            if (path[j - 1] == path[j])
            {
                len++;
            }
            else
            {
                len = 1;
            }
            if (len > 2)
            {
                return 0;
            }
        }
        return len > 2 ? 0 : 1;
    }
    else
    {
        int ans = 0;
        for (int j = 0; j < k; j++)
        {
            path[i] = j;
            ans += dfs(path, i + 1, k);
        }
        return ans;
    }
}

// 暴力方法
// 为了验证
int right(int n, int k)
{
    vector<int> path(n);
    return dfs(path, 0, k);
}

// 对数器
// 为了验证
int main()
{
    cout << "功能测试开始" << endl;
    for (int n = 1; n <= 8; n++)
    {
        for (int k = 1; k <= 8; k++)
        {
            int ans1 = dp1(n, k);
            int ans2 = dp2(n, k);
            int ans3 = dp3(n, k);
            int ans4 = right(n, k);
            if (ans1 != ans2 || ans1 != ans3 || ans1 != ans4)
            {
                cout << "出错了!" << endl;
            }
        }
    }
    cout << "功能测试结束" << endl;
    cout << endl;

    cout << "性能测试开始" << endl;
    int n = 505060123;
    int k = 303060123;
    cout << "数据量 : n = " << n << ", k = " << k << endl;

    long start, end;
    start = clock();
    cout << "dp2方法结果(已经取余) : " << dp2(n, k) << endl;
    end = clock();
    cout << "dp2方法用时(毫秒) : " << (end - start) << endl;

    start = clock();
    cout << "dp3方法结果(已经取余) : " << dp3(n, k) << endl;
    end = clock();
    cout << "dp3方法用时(毫秒) : " << (end - start) << endl;
    cout << "性能测试结束" << endl;

    return 0;
}
