#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 12;
const int MAXM = 12;
const int MOD = 100000000;

int grid[MAXN][MAXM];
int dp[MAXN][1 << MAXM];
int n, m, maxs;

int compute();
int f(int i, int s);
int dfs(int i, int j, int s, int ss);
int get(int s, int j);
int set(int s, int j, int v);

int main()
{
    cin >> n >> m;
    maxs = 1 << m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }
    cout << compute() << endl;
    return 0;
}

int compute()
{
    memset(dp, -1, sizeof(dp));
    return f(0, 0);
}

int f(int i, int s)
{
    if (i == n)
    {
        return 1;
    }
    if (dp[i][s] != -1)
    {
        return dp[i][s];
    }
    int ans = dfs(i, 0, s, 0);
    dp[i][s] = ans;
    return ans;
}

int dfs(int i, int j, int s, int ss)
{
    if (j == m)
    {
        return f(i + 1, ss);
    }
    int ans = dfs(i, j + 1, s, ss);
    if (grid[i][j] == 1 && (j == 0 || get(ss, j - 1) == 0) && get(s, j) == 0)
    {
        ans = (ans + dfs(i, j + 1, s, set(ss, j, 1))) % MOD;
    }
    return ans;
}

// 得到s的第j位的值
int get(int s, int j)
{
    return (s >> j) & 1;
}

// 设置s的第j位的值为v, 然后返回新的s
int set(int s, int j, int v)
{
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}
