// 炮兵阵地
// 给定一个n * m的二维数组grid，其中的1代表可以摆放炮兵，0代表不可以摆放
// 任何炮兵攻击范围是一个"十字型"的区域，具体是上下左右两个格子的区域
// 你的目的是在gird里摆尽量多的炮兵，但要保证任何两个炮兵之间无法互相攻击
// 返回最多能摆几个炮兵
// 1 <= n <= 100
// 1 <= m <= 10
// 0 <= grid[i][j] <= 1
// 测试链接 : https://www.luogu.com.cn/problem/P2704

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100;
const int MAXM = 10;
const int MAXS = 60; // M = 10, 最大状态数为 60

// grid[i][j] : 第i行第j列是否可以放炮兵 0-不可以 1-可以
int grid[MAXN][MAXM];

// dp[i][a][b] : 在第i行的状态a号，第i-1行的状态b号的情况下 1-i行的最多炮兵数
int dp[MAXN][MAXS][MAXS];

// 当前行的所有有效状态
// 状态s的第j位为1代表第j列可以放炮兵，0代表不可以放炮兵
// sta[i] : 第i个状态
int sta[MAXS];
int n, m, k;

// 状态压缩
// 上一层的状态
int memo[MAXS][MAXS];
int tmp[MAXS][MAXS];
// 当前层的状态
int fp[MAXS][MAXS];

void prepare(int j, int s)
{
    if (j >= m)
    {
        sta[k++] = s;
    }
    else
    {
        prepare(j + 1, s);            // 第j列不放炮兵
        prepare(j + 3, s | (1 << j)); // 第j列放炮兵
    }
}

// 第i行士兵状态为s，结合grid第i号的状况
// 返回摆放士兵的数量
int cnt(int i, int s)
{
    int ans = 0;
    for (int j = 0; j < m; j++)
    {
        if (((s >> j) & 1) == 1 && grid[i][j] == 1)
        {
            ans++;
        }
    }
    return ans;
}

// 解法一
int compute1()
{
    for (int a = 0, cntVal; a < k; a++)
    {
        cntVal = cnt(0, sta[a]);
        dp[0][a][0] = cntVal;
    }
    for (int i = 1; i < n; i++)
    {
        for (int a = 0, cntVal; a < k; a++)
        {
            cntVal = cnt(i, sta[a]);
            for (int b = 0; b < k; b++)
            {
                // 第i行和第i-1行的同列不冲突
                if ((sta[a] & sta[b]) == 0)
                {
                    for (int c = 0; c < k; c++)
                    {
                        // 第i行, 第i-1行, 第i-2行的同列不冲突
                        if ((sta[b] & sta[c]) == 0 && (sta[a] & sta[c]) == 0)
                        {
                            dp[i][a][b] = max(dp[i][a][b], dp[i - 1][b][c] + cntVal);
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int a = 0; a < k; a++)
    {
        for (int b = 0; b < k; b++)
        {
            ans = max(ans, dp[n - 1][a][b]);
        }
    }
    return ans;
}

// 解法二：空间压缩
int compute2()
{
    for (int a = 0, cntval; a < k; a++)
    {
        cntval = cnt(0, sta[a]);
        memo[a][0] = cntval;
    }
    for (int i = 1; i < n; i++)
    {
        for (int a = 0, cntval; a < k; a++)
        {
            cntval = cnt(i, sta[a]);
            for (int b = 0; b < k; b++)
            {
                fp[a][b] = 0;
                if ((sta[a] & sta[b]) == 0)
                {
                    for (int c = 0; c < k; c++)
                    {
                        if ((sta[b] & sta[c]) == 0 && (sta[a] & sta[c]) == 0)
                        {
                            fp[a][b] = max(fp[a][b], memo[b][c] + cntval);
                        }
                    }
                }
            }
        }
        
        // 交换 memo 和 fp
        memcpy(tmp, memo, sizeof(memo));
        memcpy(memo, fp, sizeof(fp));
        memcpy(fp, tmp, sizeof(tmp));
    }
    int ans = 0;
    for (int a = 0; a < k; a++)
    {
        for (int b = 0; b < k; b++)
        {
            ans = max(ans, memo[a][b]);
        }
    }
    return ans;
}

int main()
{
    cin >> n >> m;
    char c;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> c;
            // 注意：这里的输入是'P'代表可以放炮兵，'H'代表不可以放炮兵
            grid[i][j] = (c == 'P');
        }
    }
    k = 0;
    prepare(0, 0);
    int ans = compute2();
    cout << ans << endl;
    return 0;
}
