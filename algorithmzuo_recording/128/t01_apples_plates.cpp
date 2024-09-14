// 苹果和盘子
// 有m个苹果，认为苹果之间无差别，有n个盘子，认为盘子之间无差别
// 比如5个苹果如果放进3个盘子，那么(1, 3, 1) (1, 1, 3) (3, 1, 1)认为是同一种方法
// 允许有些盘子是空的，返回有多少种放置方法
// 测试链接 : https://www.nowcoder.com/practice/bfd8234bb5e84be0b493656e390bdebf

#include <iostream>
#include <vector>

using namespace std;

const int MAXM = 11, MAXN = 11;

vector<vector<int>> dp(MAXM, vector<int>(MAXN, -1));

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
    cout << f(m, n) << endl;
    return 0;
}
