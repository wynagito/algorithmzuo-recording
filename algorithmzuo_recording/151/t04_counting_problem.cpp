// 序列计数
// 有一个概念叫，最左端最大值位置，表示一段范围上
// 如果最大值有一个，那么最大值所在的位置，就是最左端最大值位置
// 如果最大值有多个，最左的那个所在的位置，就是最左端最大值位置
// 给定一个长度为n的数组A，那么必然存在等长的数组B，当选择同样的子范围时
// 两者在这段范围上，最左端最大值位置是相同的，不仅存在这样的数组B，而且数量无限多
// 现在要求，数组B中的每个值都在[1,m]范围，返回有多少个这样的数组，答案对 1000000007 取模
// 2 <= n、m <= 2 * 10^5    1 <= A[i] <= m    n * m <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/CF1748E
// 测试链接 : https://codeforces.com/problemset/problem/1748/E

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 1000001;

// 所有数字
int arr[MAXN];

// 笛卡尔树需要
int left[MAXN];
int right[MAXN];
int stack[MAXN];

// tmp是动态规划的临时结果
long tmp[MAXN];

int n, m;

void build()
{
    for (int i = 1, top = 0, pos; i <= n; i++)
    {
        pos = top;
        while (pos > 0 && arr[stack[pos]] < arr[i])
        {
            pos--;
        }
        if (pos > 0)
        {
            right[stack[pos]] = i;
        }
        if (pos < top)
        {
            left[i] = stack[pos + 1];
        }
        stack[++pos] = i;
        top = pos;
    }
}

void dfs(int u, vector<vector<int>> &dp)
{
    if (u == 0)
    {
        return;
    }
    dfs(left[u], dp);
    dfs(right[u], dp);
    for (int j = 1; j <= m; j++)
    {
        tmp[j] = (static_cast<long>(dp[left[u]][j - 1]) * dp[right[u]][j]) % MOD;
    }
    for (int j = 1; j <= m; j++)
    {
        dp[u][j] = (dp[u][j - 1] + tmp[j]) % MOD;
    }
}

void clear()
{
    memset(left + 1, 0, n * sizeof(int));
    memset(right + 1, 0, n * sizeof(int));
}

long compute()
{
    build();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = 1; // 没有节点时，只要有一种形态
    }
    dfs(stack[1], dp);
    clear();
    return dp[stack[1]][m];
}

int main()
{

    int cases;
    cin >> cases;
    for (int t = 1; t <= cases; t++)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i];
        }
        cout << compute() << endl;
    }

    return 0;
}