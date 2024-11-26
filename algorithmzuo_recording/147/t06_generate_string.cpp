// 生成字符串
// 有n个1和m个0，要组成n+m长度的数列，保证任意前缀上，1的数量 >= 0的数量
// 返回有多少种排列方法，答案对 20100403 取模
// 1 <= m <= n <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P1641

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 20100403;
const int MAXN = 2000001;

vector<long long> fac(MAXN);
vector<long long> inv(MAXN);

long long power(long long x, long long p);
void build(int n);
long long c(int n, int k);

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

long long compute(int n, int m)
{
    build(n + m);
    return (c(n + m, m) - c(n + m, m - 1) + MOD) % MOD;
}

int main()
{
    int n, m;
    cin >> n >> m;
    cout << compute(n, m) << endl;
    return 0;
}