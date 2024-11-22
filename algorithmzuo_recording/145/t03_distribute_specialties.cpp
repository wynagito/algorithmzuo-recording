// 分特产
// 一共有m种特产，arr[i]表示i种特产有几个
// 一共有n个同学，每个同学至少要得到一个特产
// 返回分配特产的方法数，答案对 1000000007 取模
// 0 <= n、m <= 1000
// 0 <= arr[i] <= 1000
// 测试链接 : https://www.luogu.com.cn/problem/P5505

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1001;
const int MAXK = MAXN * 2;
const int MOD = 1000000007;

int arr[MAXN];
long long c[MAXK][MAXK];
long long g[MAXN];
int n, k, m;

long long compute()
{
    for (int i = 0; i <= k; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }

    for (int i = 0; i < n; i++)
    {
        g[i] = c[n][i];
        for (int j = 1; j <= m; j++)
        {
            g[i] = (g[i] * c[arr[j] + n - i - 1][n - i - 1]) % MOD;
        }
    }
    g[n] = 0;

    long long ans = 0;
    for (int i = 0; i <= n; i++)
    {
        if ((i & 1) == 0)
        {
            ans = (ans + g[i]) % MOD;
        }
        else
        {
            // -1 和 (MOD-1) 同余
            ans = (ans + g[i] * (MOD - 1) % MOD) % MOD;
        }
    }
    return ans;
}

int main()
{

    cin >> n >> m;
    k = n * 2;
    for (int i = 1; i <= m; i++)
    {
        cin >> arr[i];
    }

    cout << compute() << endl;
    return 0;
}