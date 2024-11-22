// 集合计数
// 一共有n个不同的数，能构成2^n个不同集合
// 在2^n个集合中挑出若干个集合，至少挑一个
// 希望这若干个集合的交集，正好有k个数
// 返回挑选集合的方案数，答案对 1000000007 取模
// 1 <= n <= 10^6
// 0 <= k <= n
// 测试链接 : https://www.luogu.com.cn/problem/P10596

#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1000001;
const int MOD = 1000000007;

long long fac[MAXN];
long long inv[MAXN];
long long g[MAXN];
int n, k;

void build();
long long power(long long x, long long p);
long long c(int n, int k);
long long compute();

void build()
{
    fac[0] = inv[0] = 1;
    fac[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        fac[i] = (static_cast<long long>(i) * fac[i - 1]) % MOD;
    }
    inv[n] = power(fac[n], MOD - 2);
    for (int i = n - 1; i >= 1; i--)
    {
        inv[i] = (static_cast<long long>(i + 1) * inv[i + 1]) % MOD;
    }
}

long long power(long long x, long long p)
{
    long long ans = 1;
    while (p > 0)
    {
        if (p & 1)
        {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ans;
}

long long c(int n, int k)
{
    return (((fac[n] * inv[k]) % MOD) * inv[n - k]) % MOD;
}

long long compute()
{
    build();
    long long tmp = 2;
    for (int i = n; i >= 0; i--)
    {
        g[i] = tmp;
        tmp = tmp * tmp % MOD;
    }
    for (int i = 0; i <= n; i++)
    {
        // -1 和 (MOD-1) 同余
        g[i] = (g[i] + MOD - 1) * c(n, i) % MOD;
    }
    long long ans = 0;
    for (int i = k; i <= n; i++)
    {
        if (((i - k) & 1) == 0)
        {
            ans = (ans + c(i, k) * g[i] % MOD) % MOD;
        }
        else
        {
            // -1 和 (MOD-1) 同余
            ans = (ans + c(i, k) * g[i] % MOD * (MOD - 1) % MOD) % MOD;
        }
    }
    return ans;
}

int main()
{
    cin >> n >> k;
    cout << compute() << endl;
    return 0;
}