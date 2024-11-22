// 计算系数
// 多项式为，(ax + by)的k次方，其中a、b、k为常数
// 计算这个多项式展开后，x的n次方 * y的m次方，这一项的系数
// 0 <= k <= 1000
// 0 <= a、b <= 10^6
// n + m == k
// 测试链接 : https://www.luogu.com.cn/problem/P1313

#include <iostream>
#include <vector>

using namespace std;

const int MAXK = 1001;
const int MOD = 10007;

// fac[i]代表 i! 在 %MOD 意义下的余数
long long fac[MAXK + 1];

// inv[i]代表 i! 在 %MOD 意义下的逆元
long long inv[MAXK + 1];

int a, b, k, n, m;

// 乘法快速幂，x的p次方 % MOD
long long power(long long x, int p)
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

// 生成阶乘表和逆元表
void build()
{
    // 阶乘表线性递推
    fac[0] = 1; // 0! = 1
    fac[1] = 1;
    for (int i = 2; i <= MAXK; i++)
    {
        fac[i] = ((long long)i * fac[i - 1]) % MOD;
    }
    // 逆元表线性递推
    inv[MAXK] = power(fac[MAXK], MOD - 2);
    for (int i = MAXK - 1; i >= 0; i--)
    {
        inv[i] = ((long long)(i + 1) * inv[i + 1]) % MOD;
    }
}

// 组合公式
long long c(int n, int k)
{
    return (((fac[n] * inv[k]) % MOD) * inv[n - k]) % MOD;
}

long long compute()
{
    build();
    return (((power(a, n) * power(b, m)) % MOD) * c(k, k - n)) % MOD;
}

int main()
{
    cin >> a >> b >> k >> n >> m;
    cout << compute() << endl;
    return 0;
}
