// 表格填数
// 给定一个长度为n的数组arr，arr[i]表示i位置上方的正方形格子数量
// 那么从1位置到n位置，每个位置就是一个直方图，所有的直方图紧靠在一起
// 在这片区域中，你要放入k个相同数字，不能有任意两个数字在同一行或者同一列
// 注意在这片区域中，如果某一行中间断开了，使得两个数字无法在这一行连通，则不算违规
// 返回填入数字的方法数，答案对 1000000007 取模
// 1 <= n、k <= 500    0 <= arr[i] <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P6453

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 501;
const int MAXH = 1000000;

int arr[MAXN];
int fac[MAXH + 1], inv[MAXH + 1];
int leftChild[MAXN], rightChild[MAXN];
int stack[MAXN], size[MAXN];
int dp[MAXN][MAXN], tmp[MAXN];

int n, k;

int power(long long x, long long p)
{
    long long ans = 1;
    while (p > 0)
    {
        if (p & 1)
        {
            ans = ans * x % MOD;
        }
        x = x * x % MOD;
        p >>= 1;
    }
    return ans;
}

int c(int n, int k)
{
    return n < k ? 0 : (long long)fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}

void build()
{
    fac[0] = fac[1] = inv[0] = 1;
    for (int i = 2; i <= MAXH; i++)
    {
        fac[i] = (long long)fac[i - 1] * i % MOD;
    }
    inv[MAXH] = power(fac[MAXH], MOD - 2);
    for (int i = MAXH - 1; i >= 1; i--)
    {
        inv[i] = (long long)inv[i + 1] * (i + 1) % MOD;
    }

    for (int i = 1, top = 0, pos; i <= n; i++)
    {
        pos = top;
        while (pos > 0 && arr[stack[pos]] > arr[i])
        {
            pos--;
        }
        if (pos > 0)
        {
            rightChild[stack[pos]] = i;
        }
        if (pos < top)
        {
            leftChild[i] = stack[pos + 1];
        }
        stack[++pos] = i;
        top = pos;
    }
}

void dfs(int u, int fa)
{
    if (u == 0)
    {
        return;
    }
    dfs(leftChild[u], u);
    dfs(rightChild[u], u);
    size[u] = size[leftChild[u]] + size[rightChild[u]] + 1;
    fill(tmp, tmp + k + 1, 0);

    for (int l = 0; l <= min(size[leftChild[u]], k); l++)
    {
        for (int r = 0; r <= min(size[rightChild[u]], k - l); r++)
        {
            tmp[l + r] = (tmp[l + r] + (long long)dp[leftChild[u]][l] * dp[rightChild[u]][r] % MOD) % MOD;
        }
    }

    for (int i = 0; i <= min(size[u], k); i++)
    {
        for (int p = 0; p <= i; p++)
        {
            dp[u][i] = (dp[u][i] + (long long)c(size[u] - p, i - p) * c(arr[u] - arr[fa], i - p) % MOD * fac[i - p] % MOD * tmp[p] % MOD) % MOD;
        }
    }
}

int compute()
{
    build();
    dp[0][0] = 1;
    dfs(stack[1], 0);
    return dp[stack[1]][k];
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    cout << compute() << endl;
    return 0;
}
