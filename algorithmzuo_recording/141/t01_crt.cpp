// 中国剩余定理
// 给出n个同余方程，m1、m2、..一定两两互质，求满足同余方程的最小正数解x
// x ≡ r1 (% m1)  x ≡ r2 (% m2)   x ≡ r3 (% m3) ..  x ≡ rn (% mn)

// 求解的原理：x = c1 + c2 + c3 + .. + cn，如果i!=j，ci % mi = ri，ci % mj = 0，则x达标
// 当m1、m2、..一定两两互质，必存在这样的x，根据如下过程就可以求出这样的x，并且是最小正数解

// 求解过程
// 1，计算m1 * m2 .. * mn的结果，因为m1、m2、.. mn一定两两互质，所以结果为最小公倍数lcm
// 2，对每一个同余方程计算：
//    ai = lcm / mi    ai逆元 = ai在%mi意义下的逆元    ci = (ri * ai * ai逆元) % lcm
// 3，最小正数解x = 每一项ci的累加和 % lcm，因为，通解x = ? * lcm + 最小正数解x

// 中国剩余定理模版
// 给出n个同余方程，求满足同余方程的最小正数解x
// 一共n个同余方程，x ≡ ri(% mi)
// 1 <= n <= 10
// 0 <= ri、mi <= 10^5
// 所有mi一定互质
// 所有mi整体乘积 <= 10^18
// 测试链接 : https://www.luogu.com.cn/problem/P1495

#include <iostream>
#include <vector>
#include <numeric> // For std::gcd
using namespace std;

const int MAXN = 11;
long long m[MAXN], r[MAXN], d, x, y, px, py;

// 扩展欧几里得算法
void exgcd(long long a, long long b)
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// 位运算实现乘法，防止溢出
long long multiply(long long a, long long b, long long mod)
{
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;
    long long ans = 0;
    while (b != 0)
    {
        if (b & 1)
        {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

// 中国剩余定理模版
long long crt(int n)
{
    long long lcm = 1;
    for (int i = 1; i <= n; i++)
    {
        lcm = lcm * m[i];
    }
    long long ai, ci, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        // ai = lcm / m[i]
        ai = lcm / m[i];
        // ai逆元，在%m[i]意义下的逆元
        exgcd(ai, m[i]);
        // ci = (ri * ai * ai逆元) % lcm
        ci = multiply(r[i], multiply(ai, x, lcm), lcm);
        ans = (ans + ci) % lcm;
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> m[i] >> r[i];
    }
    cout << crt(n) << endl;
    return 0;
}