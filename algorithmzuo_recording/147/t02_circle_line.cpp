// 圆上连线
// 圆上有2n个点，这些点成对连接起来，形成n条线段，任意两条线段不能相交，返回连接的方法数
// 注意！答案不对 10^9 + 7 取模！而是对 10^8 + 7 取模！
// 1 <= n <= 2999
// 测试链接 : https://www.luogu.com.cn/problem/P1976

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 100000007;
const int MAXN = 1000001;

vector<long long> fac(MAXN);
vector<long long> inv(MAXN);

long long power(long long x, long long p);

void build(int n)
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

long long compute(int n)
{
    build(2 * n);
    return (c(2 * n, n) - c(2 * n, n - 1) + MOD) % MOD;
}

int main()
{
    int n;
    cin >> n;
    cout << compute(n) << endl;
    return 0;
}