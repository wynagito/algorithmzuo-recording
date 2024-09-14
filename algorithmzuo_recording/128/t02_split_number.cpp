// 数的划分方法
// 将整数m分成n份，且每份不能为空，任意两个方案不相同(不考虑顺序)
// 比如，m=7、n=3，那么(1, 1, 5) (1, 5, 1) (5, 1, 1)认为是同一种方法
// 返回有多少种不同的划分方法
// 测试链接 : https://www.luogu.com.cn/problem/P1025

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 201, MAXK = 7;

vector<vector<int>> dp(MAXN, vector<int>(MAXK, -1));

int f(int m, int n);

int compute(int m, int n)
{
    if (m < n)
    {
        return 0;
    }
    if (m == n)
    {
        return 1;
    }
    m -= n;
    return f(m, n);
}

int f(int m, int n)
{
    if (m == 0)
    {
        return 1;
    }
    if (n == 0)
    {
        return 0;
    }
    if (dp[m][n] != -1)
    {
        return dp[m][n];
    }
    int ans;
    if (n > m)
    {
        ans = f(m, m);
    }
    else
    {
        ans = f(m, n - 1) + f(m - n, n);
    }
    dp[m][n] = ans;
    return ans;
}

int main()
{
    int m, n;
    cin >> m >> n;
    cout << compute(m, n) << endl;
    return 0;
}
